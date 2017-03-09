/**
 *  \file app_file_pool.c
 *  \brief 파일매니저에서 사용할 memory pool 관리자
 */
//#include <unistd.h> //UNIX header file
#include <stddef.h> // NULL

#include <app_file_pool.h>

POOL_C FILEPOOL;
POOL_C DIRPOOL;
POOL_C LISTPOOL;

int CreatePool(POOL_C * meminfo, size_t sizeOfEachBlock, uint numOfBlocks, uchar * memStart) 
{

	POOL_C * lmeminfo = meminfo;

	 lmeminfo->m_numOfBlocks = numOfBlocks; 
	 lmeminfo->m_sizeOfEachBlock = sizeOfEachBlock; 
	 lmeminfo->m_memStart = memStart;
	 lmeminfo->m_numFreeBlocks = numOfBlocks; 
	 lmeminfo->m_next = lmeminfo->m_memStart; 
	 lmeminfo->m_numInitialized = 0;
 } 
 
  void DestroyPool(POOL_C * meminfo) 
 { 
	// todo
 }

/*
 * Name         : AddrFromIndex
 *
 * Synopsis     : uchar* AddrFromIndex(POOL_C * meminfo ,int i)
 *
 * Arguments    : int  i : 
 *
 * Description  : 
 * 
 * Returns      : uchar* 
 */
uchar* AddrFromIndex(POOL_C * meminfo ,int i) 
{
	return meminfo->m_memStart + ( i * meminfo->m_sizeOfEachBlock );
}
/**
 *  \brief Brief
 *  
 *  \param [in] meminfo Parameter_Description
 *  \param [in] p Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 */
uint IndexFromAddr(POOL_C * meminfo ,const uchar* p) 
{
	return (((uint)(p - meminfo->m_memStart)) / meminfo->m_sizeOfEachBlock);
}
/**
 *  \brief Brief
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void* FnodeAlloc()
{
	void* ret = NULL;
	
	if (FILEPOOL.m_numInitialized < FILEPOOL.m_numOfBlocks )
	{
		uint* p = (uint*)AddrFromIndex(&FILEPOOL, FILEPOOL.m_numInitialized );
		*p = FILEPOOL.m_numInitialized + 1;
		FILEPOOL.m_numInitialized++;
	}
	
	if ( FILEPOOL.m_numFreeBlocks > 0 )
	{
		ret = (void*)FILEPOOL.m_next;
		--FILEPOOL.m_numFreeBlocks;
		if (FILEPOOL.m_numFreeBlocks!=0)
		{
			FILEPOOL.m_next = AddrFromIndex(&FILEPOOL, *((uint*)FILEPOOL.m_next) );
		}
		else
		{
			FILEPOOL.m_next = NULL;
		}
	}
	return ret;
}/**
 *  \brief Brief
 *  
 *  \param [in] p Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 */
void FNodeDeAlloc(void* p)
{
	if (FILEPOOL.m_next != NULL)
	{
		(*(uint*)p) = IndexFromAddr( &FILEPOOL,FILEPOOL.m_next );
		FILEPOOL.m_next = (uchar*)p;
	}
	else
	{
		*((uint*)p) = FILEPOOL.m_numOfBlocks;
		FILEPOOL.m_next = (uchar*)p;
	}
	++FILEPOOL.m_numFreeBlocks;

}
/**
 *  \brief Brief
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void* DnodeAlloc()
{
	void* ret = NULL;
	
	if (DIRPOOL.m_numInitialized < DIRPOOL.m_numOfBlocks )
	{
		uint* p = (uint*)AddrFromIndex(&DIRPOOL, DIRPOOL.m_numInitialized );
		*p = DIRPOOL.m_numInitialized + 1;
		DIRPOOL.m_numInitialized++;
	}
	
	if ( DIRPOOL.m_numFreeBlocks > 0 )
	{
		ret = (void*)DIRPOOL.m_next;
		--DIRPOOL.m_numFreeBlocks;
		if (DIRPOOL.m_numFreeBlocks!=0)
		{
			DIRPOOL.m_next = AddrFromIndex(&DIRPOOL, *((uint*)DIRPOOL.m_next) );
		}
		else
		{
			DIRPOOL.m_next = NULL;
		}
	}
	return ret;
}
/**
 *  \brief Brief
 *  
 *  \param [in] p Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 */
void DNodeDeAlloc(void* p)
{
	if (DIRPOOL.m_next != NULL)
	{
		(*(uint*)p) = IndexFromAddr( &DIRPOOL,DIRPOOL.m_next );
		DIRPOOL.m_next = (uchar*)p;
	}
	else
	{
		*((uint*)p) = DIRPOOL.m_numOfBlocks;
		DIRPOOL.m_next = (uchar*)p;
	}
	++DIRPOOL.m_numFreeBlocks;

}
/**
 *  \brief Brief
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void* listalloc()
{
	void* ret = NULL;
	
	if (LISTPOOL.m_numInitialized < LISTPOOL.m_numOfBlocks )
	{
		uint* p = (uint*)AddrFromIndex(&LISTPOOL, LISTPOOL.m_numInitialized );
		*p = LISTPOOL.m_numInitialized + 1;
		LISTPOOL.m_numInitialized++;
	}
	
	if ( LISTPOOL.m_numFreeBlocks > 0 )
	{
		ret = (void*)LISTPOOL.m_next;
		--LISTPOOL.m_numFreeBlocks;
		if (LISTPOOL.m_numFreeBlocks!=0)
		{
			LISTPOOL.m_next = AddrFromIndex(&LISTPOOL, *((uint*)LISTPOOL.m_next) );
		}
		else
		{
			LISTPOOL.m_next = NULL;
		}
	}
	return ret;
}
/**
 *  \brief Brief
 *  
 *  \param [in] p Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 */
void listfree(void* p)
{
	if (LISTPOOL.m_next != NULL)
	{
		(*(uint*)p) = IndexFromAddr( &LISTPOOL,LISTPOOL.m_next );
		LISTPOOL.m_next = (uchar*)p;
	}
	else
	{
		*((uint*)p) = LISTPOOL.m_numOfBlocks;
		LISTPOOL.m_next = (uchar*)p;
	}
	++LISTPOOL.m_numFreeBlocks;

}