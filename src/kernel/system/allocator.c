#include "allocator.h"
#include "heap/kpool.h"

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
        // close in size - reduce fragmentation by not splitting.
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
    }
    else for (KMemNode *iter = list->head; iter != NULL; iter = iter->next)
    {
        if (( uintptr_t )iter == mempool->arena.offs)
        {
            mempool->arena.offs += iter->size;
            __RemoveMemNode(list, iter);
            iter = list->head;
            if (iter == NULL) {
                list->head = node;    
                return;
            }
        }
        const uintptr_t inode = ( uintptr_t )node;
        const uintptr_t iiter = ( uintptr_t )iter;
        const uintptr_t iter_end = iiter + iter->size;
        const uintptr_t node_end = inode + node->size;
        if (iter==node) return;
        else if (iter < node)
        {
            // node was coalesced prior.
            if (iter_end > inode) return;
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
            if (iiter < node_end) return;
            else if (iter==list->head && !is_bucket)
            {
                if (iter_end==inode) iter->size += node->size;
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

KMemPool KCreateMemPool(void* buffer, uintptr sizeb)
{
    KMemPool mempool = { 0 };

    if ((sizeb == 0) || (sizeb == NULL) || (sizeb <= sizeof(KMemNode))) {
        return mempool;        
    }
    else
    {
        mempool.arena.size = sizeb;
        mempool.arena.mem = (uintptr_t)buffer;
        mempool.arena.offs = mempool.arena.mem + mempool.arena.size;
        return mempool;
    }
}

void KDestroyMemPool(KMemPool* mempool)
{
    if (mempool->arena.mem == 0) return;
    else
    {
        void *const restrict ptr = ( void* )mempool->arena.mem;

        for (uintptr i = 0; i < mempool->arena.size; i++)
            

        *mempool = (KMemPool){ 0 };
    }    
}

void* KMemPoolAlloc(KMemPool* mempool, uintptr sizeb)
{

}

void KMemPoolFree(KMemPool* mempool, void* ptr)
{

}