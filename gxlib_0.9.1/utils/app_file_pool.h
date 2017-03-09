#ifndef __APP_FILE_POOL_H__
#define  __APP_FILE_POOL_H__
/**
 *  \file app_file_pool.h
 *  \brief 파일매니저에서 사용할 memory pool 관리자
 */
////////////////////////////////////////////////////////////////////////////////
//
// Basic type define
typedef unsigned int uint; 
typedef unsigned char uchar; 
 
typedef struct 
{ 
 
 uint m_numOfBlocks; // Num of blocks 
 uint m_sizeOfEachBlock; // Size of each block 
 uint m_numFreeBlocks; // Num of remaining blocks 
 uint m_numInitialized; // Num of initialized blocks 
 uchar* m_memStart; // Beginning of memory pool 
 uchar* m_next; 
} POOL_C;

int CreatePool(POOL_C * meminfo, size_t sizeOfEachBlock, uint numOfBlocks, uchar * memStart);
void DestroyPool(POOL_C * meminfo);

uchar* AddrFromIndex(POOL_C * meminfo ,int i);
uint IndexFromAddr(POOL_C * meminfo ,const uchar* p);
void* FnodeAlloc();
void FNodeDeAlloc(void* p);

void* DnodeAlloc();
void DNodeDeAlloc(void* p);

void* listalloc();
void listfree(void* p);
#endif