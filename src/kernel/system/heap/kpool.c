#include "kpool.h"


static inline size_t __AlignSize(const size_t size, const size_t align)
{
    return (size + (align - 1)) & -align;
}

static KMemNode *__SplitMemNode(KMemNode *const node, const size_t bytes)
{
    uintptr_t n = ( uintptr_t )node;
    KMemNode *const r = ( KMemNode* )(n + (node->size - bytes));
    node->size -= bytes;
    r->size = bytes;
    return r;
}

static void __InsertMemNodeBefore(
    KAllocList *const list, KMemNode *const insert, KMemNode *const curr)
{
    insert->next = curr;

    if (curr->prev==NULL) 
        list->head = insert;
    else
    {
        insert->prev = curr->prev;
        curr->prev->next = insert;
    }

    curr->prev = insert;
}

static void __ReplaceMemNode(KMemNode *const old, KMemNode *const replace)
{
    replace->prev = old->prev;
    replace->next = old->next;

    if( old->prev != NULL )
        old->prev->next = replace;

    if( old->next != NULL )
        old->next->prev = replace;
}

static KMemNode *__RemoveMemNode(KAllocList *const list, KMemNode *const node)
{
    if (node->prev != NULL) node->prev->next = node->next;
    else
    {
        list->head = node->next;
        if (list->head != NULL) list->head->prev = NULL;
        else list->tail = NULL;
    }

    if (node->next != NULL) node->next->prev = node->prev;
    else
    {
        list->tail = node->prev;
        if (list->tail != NULL) list->tail->next = NULL;
        else list->head = NULL;
    }
    list->len--;
    return node;
}

static KMemNode *__FindMemNode(KAllocList *const list, const size_t bytes)
{
    for (KMemNode *node = list->head; node != NULL; node = node->next)
    {
        if (node->size < bytes) 
            continue;

        else if (node->size <= bytes + MEM_SPLIT_THRESHOLD) 
            return __RemoveMemNode(list, node);

        else return __SplitMemNode(node, bytes);
    }
    return NULL;
}

static void __InsertMemNode(KMemPool *const mempool, 
    KAllocList *const list, KMemNode *const node, const uint8 is_bucket)
{
    if (list->head == NULL)
    {
        list->head = node;
        list->len++;
        return;
    }

    for (KMemNode *iter = list->head; iter != NULL; iter = iter->next) 
    {
    if ((uintptr)iter == mempool->arena.offs)
    {
        mempool->arena.offs += iter->size;
        __RemoveMemNode(list, iter);

        iter = list->head;
        if (iter == NULL) 
        {
            list->head = node;    
            return;
        }
    }

    const uintptr inode = (uintptr)node, iiter = (uintptr)iter;
    const uintptr iter_end = iiter + iter->size, node_end = inode + node->size;

    if (iter == node) 
        return;

    if (iter < node)
    {
        // node was coalesced prior.
        if (iter_end > inode) 
            return;
            
        else if (iter_end==inode && !is_bucket)
        {
            // if we can coalesce, do so.
            iter->size += node->size;
            return;
        }
        else if (iter->next == NULL)
        {
            // we reached the end of the free list -> append the node
            iter->next = node;
            node->prev = iter;
            list->len++;
            return;    
        }
    }
    else if (iter > node)
    {
        // Address sort, lowest to highest aka ascending order.
        if (iiter < node_end) 
            return;

        else if (iter==list->head && !is_bucket)
        {
            if (iter_end==inode) 
                iter->size += node->size;

            else if (node_end==iiter)
            {
                node->size += list->head->size;
                node->next = list->head->next;
                node->prev = NULL;
                list->head = node;
            }
            else
            {
                node->next = iter;
                node->prev = NULL;
                iter->prev = node;
                list->head = node;
                list->len++;
            }
            return;
        }
        else if (iter_end==inode && !is_bucket)
        {
            // if we can coalesce, do so.
            iter->size += node->size;
            return;
        }
        else
        {
            __InsertMemNodeBefore(list, node, iter);
            list->len++;
            return;
        }
    }
    }
}

KMemPool* KCreateMemPool(KMemPoolCreateInfo createInfo)
{
    if (createInfo.sizeBytes >= KMainPoolAvailable())
        return NULL;
    
    KMemPool* mempool = (KMemPool*)KMainPoolAlloc(createInfo.sizeBytes);
    return mempool;
}

void KDestroyMemPool(KMemPool* mempool)
{
    if (mempool == NULL)
        return;

    KMainPoolFree(mempool);
}

void* KMemPoolAlloc(KMemPool* mempool, uintptr sizeb)
{
    if ((sizeb == 0) || (sizeb > mempool->arena.size))
        return NULL;        

    KMemNode *new_mem = NULL;
    uintptr allocSize = __AlignSize(sizeb + sizeof(KMemNode), sizeof(intptr_t));

    uintptr bucketSlot = (allocSize >> MEMPOOL_BUCKET_BITS);
    --bucketSlot;

    if (bucketSlot < MEMPOOL_BUCKET_SIZE)
        new_mem = __FindMemNode(&mempool->buckets[bucketSlot], allocSize);

    else if (mempool->large.head != NULL)
        new_mem = __FindMemNode(&mempool->large, allocSize);

    if (new_mem != NULL)
        return new_mem;

    if ((mempool->arena.offs - allocSize) < mempool->arena.mem) 
        return NULL;

    mempool->arena.offs -= allocSize;

    new_mem = (KMemNode*)mempool->arena.offs;

    new_mem->size = allocSize;
    new_mem->next = new_mem->prev = NULL;

    uint8_t *const restrict final_mem = (uint8_t*)new_mem + sizeof(KMemNode);
    return memset(final_mem, 0, new_mem->size - sizeof(KMemNode));
}

void *KMemPoolRealloc(KMemPool *const restrict mempool, void *const ptr, const size_t size)
{
    if (size > mempool->arena.size) 
        return NULL;

    if (ptr == NULL) 
        return MemPoolAlloc(mempool, size);

    if ((uintptr)ptr - sizeof(KMemNode) < mempool->arena.mem) 
        return NULL;

    const KMemNode* node = (KMemNode*)((uint8_t*)ptr - sizeof(KMemNode));
    const uint8_t* resized_block = MemPoolAlloc(mempool, size);

    if (resized_block == NULL) 
        return NULL;

    const KMemNode* resized = (KMemNode*)(resized_block - sizeof(KMemNode));

    memmove(resized_block, ptr, (node->size > resized->size) ? 
        (resized->size - sizeof(KMemNode)) : (node->size - sizeof(KMemNode)));

    MemPoolFree(mempool, ptr);
    return resized_block;
}

void KMemPoolFree(KMemPool* mempool, void* ptr)
{
    const uintptr addr = (uintptr)ptr;

    if ((ptr == NULL) || (addr - sizeof(KMemNode) < mempool->arena.mem)) 
        return;

    const uintptr block = addr - sizeof(KMemNode);
    KMemNode *const mem_node = ( KMemNode* )block;

    const size_t BUCKET_SLOT = (mem_node->size >> MEMPOOL_BUCKET_BITS) - 1;

    if ((block < mempool->arena.offs) ||
        ((block - mempool->arena.mem) > mempool->arena.size) ||
        (mem_node->size == 0) ||
        (mem_node->size > mempool->arena.size)) 
        return;

    if (block == mempool->arena.offs) {
        mempool->arena.offs += mem_node->size;
        return;     
    }

    struct AllocList *const l = (BUCKET_SLOT < MEMPOOL_BUCKET_SIZE) ? 
        &mempool->buckets[BUCKET_SLOT] : &mempool->large;

    __InsertMemNode(mempool, l, mem_node, (BUCKET_SLOT < MEMPOOL_BUCKET_SIZE));
}

size_t KMemPoolFreeSpace(KMemPool* mempool)
{
    if (mempool == NULL)
        return 0UL;

    size_t total_remaining = mempool->arena.offs - mempool->arena.mem;

    for (KMemNode *node = mempool->large.head; node != NULL; node = node->next) 
        total_remaining += node->size;

    for (size_t i = 0UL; i < MEMPOOL_BUCKET_SIZE; i++) 
        for (KMemNode *node = mempool->buckets[i].head; node != NULL; node = node->next) 
            total_remaining += node->size;

    return total_remaining;
}