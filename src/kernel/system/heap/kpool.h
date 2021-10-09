#ifndef _OS_SYSTEM_MEMORY_POOL_
#define _OS_SYSTEM_MEMORY_POOL_

#include "kernel/constants/types.h"

enum 
{
    MEMPOOL_BUCKET_SIZE = 8,
    MEMPOOL_BUCKET_BITS = (sizeof(uintptr_t) >> 1) + 1,
    MEM_SPLIT_THRESHOLD = sizeof(uintptr_t) * 4
};

typedef struct MemNode_s
{
    uintptr_t size;
    KMemNode *next, *prev;
} KMemNode;

typedef struct AllocList_s 
{
    KMemNode *head, *tail;
    uintptr_t len;
} KAllocList;

typedef struct Arena_s
{
    uintptr_t mem, offs;
    uintptr_t size;
} KArena;

typedef struct MemPool_s
{
    KAllocList large, buckets[MEMPOOL_BUCKET_SIZE];
    KArena arena;
} KMemPool;

typedef struct
{
    const char* name;
    uintptr sizeBytes;
} KMemPoolCreateInfo;

void KInitMainPool();
void KResetMainPool();
uintptr KMainPoolFreeMem();
KMemPool* KGetMainPool();
void* KMainPoolAlloc(uintptr sizeb);
void KMainPoolFree(void* ptr);
uintptr KMainPoolAvailable();

KMemPool* KCreateMemPool(KMemPoolCreateInfo createInfo);
void KDestroyMemPool(KMemPool* mempool);
void* KMemPoolAlloc(KMemPool* mempool, uintptr sizeb);
void *KMemPoolRealloc(KMemPool *const restrict mempool, void *const ptr, const size_t size);
void KMemPoolFree(KMemPool* mempool, void* ptr);
size_t KMemPoolFreeSpace(KMemPool* mempool);

#endif