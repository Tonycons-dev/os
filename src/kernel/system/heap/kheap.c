#include "kpool.h"
#include "libc/include/string.h"
#include "kernel/tty.h"

KMemPool sMainPool;
KMemPool* KGetMainPool()
{
    return &sMainPool;
}

char sMainPoolBuffer[0xFFFF];


void KInitMainPool()
{
    if ((sizeof(sMainPoolBuffer) == 0) || (sMainPoolBuffer == NULL) 
    || (sizeof(sMainPoolBuffer) <= sizeof(KMemNode))) 
        return;

    sMainPool = (KMemPool){ 0 };
    memset(sMainPoolBuffer, 0x00, sizeof(sMainPoolBuffer));

    sMainPool.arena.size = sizeof(sMainPoolBuffer);
    sMainPool.arena.mem = ( uintptr_t )sMainPoolBuffer;
    sMainPool.arena.offs = sMainPool.arena.mem + sMainPool.arena.size;

    KTerminalWrite("Main Heap: %u bytes available.", sMainPool.arena.size);
    KTerminalNewLine();
}

void KResetMainPool()
{
    if ((sizeof(sMainPoolBuffer) == 0) || (sMainPoolBuffer == NULL) 
    || (sizeof(sMainPoolBuffer) <= sizeof(KMemNode))) 
        return;

    KTerminalPutString("Resetting main memory pool...\n");
    memset(sMainPoolBuffer, 0x00, sizeof(sMainPoolBuffer));

    sMainPool.large.head = sMainPool.large.tail = NULL;
    sMainPool.large.len = 0;

    for (size_t i = 0; i < MEMPOOL_BUCKET_SIZE; i++)
    {
        sMainPool.buckets[i].head = sMainPool.buckets[i].tail = NULL;
        sMainPool.buckets[i].len = 0;
    }

    sMainPool.arena.offs = sMainPool.arena.mem + sMainPool.arena.size;   
    KTerminalPutString("Main memory pool reset.\n"); 
}

uintptr KMainPoolFreeMem()
{
    size_t total_remaining = sMainPool.arena.offs - sMainPool.arena.mem;

    for (KMemNode *node = sMainPool.large.head; node != NULL; node = node->next) 
        total_remaining += node->size;

    for (size_t i = 0UL; i < MEMPOOL_BUCKET_SIZE; i++) 
        for (KMemNode *node = sMainPool.buckets[i].head; node != NULL; node = node->next) 
            total_remaining += node->size;

    return total_remaining;
}

void* KMainPoolAlloc(uintptr size)
{
    return KMemPoolAlloc(&sMainPool, size);
}

void KMainPoolFree(void* ptr)
{

}

uintptr KMainPoolAvailable()
{

}