// Copyright © 2008-2009 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.

#include "UnitAllocator.h"
#include "Defines.h"
// Constructor for UnitAllocator
UnitAllocator::UnitAllocator()
{
	m_NumGrownSegments  = 0;
	m_FirstSegmentSize  = 0;
    m_GrowSegmentSize   = 0;
	m_AllocListSize     = 0;
	m_FreeListSize      = 0;
 	m_NumGrowUnits      = 0;
	m_UnitSize          = 0;
	m_NumUnits          = 0;
 
    m_pHeap = NULL;
    m_pFree = NULL;
    m_pEnd  = NULL;
}


UnitAllocator::~UnitAllocator()
{
    Destroy();
}


Error UnitAllocator::Initialize(u32 unitSize, u32 numUnits, u32 numGrowUnits)
{
//	ASSERT((unitSize & 0x00000003) == 0x00000000);	// Warn about alignment issues

	m_UnitSize     = unitSize;
	m_NumUnits     = numUnits;
	m_FreeListSize = m_NumUnits;
	m_NumGrowUnits = numGrowUnits;

	if( m_NumGrowUnits == 0 ) m_NumGrowUnits = numUnits;

    // Compute segment sizes:
	m_FirstSegmentSize = m_UnitSize * m_NumUnits;
    m_GrowSegmentSize = m_NumGrowUnits * m_UnitSize;
	m_pHeap = new u8[m_FirstSegmentSize + sizeof(u8*)];
    if( !m_pHeap )
		return Errors::Memory::OutOfMemory;

	m_pFree = m_pHeap;
	m_pEnd  = m_pHeap + m_FirstSegmentSize;

    // Set next segment pointer to Null for now:
    u8 **ppNextSegmentPtr = (u8 **) m_pEnd;
    *ppNextSegmentPtr = NULL;

	ThreadMemory(m_pHeap);

	return Errors::Success;
}


Error UnitAllocator::Destroy()
{
	// Delete allocated memory - 2 Steps
	//    Step 1: Delete each "grown" memory chunk
	//    Step 2: Delete initially allocated chunk
	
    if (!m_pHeap)
		return Errors::Undefined;

    // Delete first segment:
    u8  *pNextSegment = * (u8 **)(m_pHeap + m_FirstSegmentSize);
    if (m_pHeap) SAFE_DELETE_ARRAY(m_pHeap);
    m_pHeap = NULL;

	u32 i;

    // Now delete grown segments if they exist:
    for (i = 0; i < m_NumGrownSegments; i++)
    {
        if (pNextSegment)
        {
            u8 *pCurrentSegment = pNextSegment;
            pNextSegment = * (u8 **)(pCurrentSegment + m_GrowSegmentSize);

            SAFE_DELETE_ARRAY(pCurrentSegment);
        }
    }

    m_NumGrownSegments = 0;
    m_pFree = NULL;;
    m_pEnd  = NULL;

	return Errors::Success;
}


Error UnitAllocator::ThreadMemory(u8 *pPtr)
{
	Error result = Errors::Success;

	if( pPtr )
	{
		u8 *tmpPtr;

		for(; pPtr < m_pEnd; )
		{
			// Get Next Block Offset
			tmpPtr = pPtr + m_UnitSize;

			// Put NextBlock address into first 4 bytes of pPtr
		   *((u8 **) pPtr) = (u8 *)tmpPtr;
			pPtr = tmpPtr;
		}
	}
	else result = Errors::Memory::InvalidAddress;
	return result;
}


u8* UnitAllocator::Grow()
{
	// Allocate new memory
    u8  *pNewSegment = (u8 *)(new u8[m_GrowSegmentSize + sizeof(u8*)]);
    if (!pNewSegment) return NULL;

    // Increment grown segment count and free list unit count:
    m_NumGrownSegments++;
    m_FreeListSize += m_NumGrowUnits;

    *((u8 **)m_pEnd) = pNewSegment;
        
    m_pFree = pNewSegment;
    m_pEnd  = pNewSegment + m_GrowSegmentSize;

    // Set last segment pointer to Null:
    u8 **ppNextSegmentPtr = (u8 **) m_pEnd;
    *ppNextSegmentPtr = NULL;

	// Thread the new segment in:
	ThreadMemory(m_pFree);

	return m_pFree;
}


