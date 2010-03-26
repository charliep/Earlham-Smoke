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

#pragma once

#include "Defines.h"
#include "DataTypes.h"
#include "Errors.h"
#include "Assert.h"


//#define ANU_DIDNT_FINISH_IMPLEMENTING_THIS_CLASS


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   This module defines the CUnitAllocator class.  It provides a "fast" alternative to the
///    standard NEW and DELETE operators provided by C++.  The allocator doles out "unitSize" chunks
///    of memory, manages a freelist, and grows by "growSize" when the current memory has been
///    exhausted.
/// <para>
///   Since CUnitAllocator::Allocate() does not call new(), it does not call any constructors.  If
///    your pointers are to classes, you will presumably have to supply and call you own function to
///    initialize the class.
/// </para>
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class UnitAllocator
{
public:
	UnitAllocator();
	~UnitAllocator();
    Error Initialize( u32 UnitSize, u32 NumUnits, u32 NumGrowUnits );
    u8* Allocate( void )
    {
        u8* pPtr = m_pFree;

        if ( m_FreeListSize == 0 )
        {
            //
            // Memory exhausted, need to allocate more.
            //
            pPtr = Grow();
        }
        // Retrieve the next free block from first 4/8 bytes of pAlloc.
        m_pFree = (u8*)*((u8**)pPtr);
        m_FreeListSize--;
        m_AllocListSize++;

	    // BUGBUG: The pointer in the first 4/8 bytes is being returned.
        return pPtr;

    }

    void Deallocate( u8* pPtr )
    {
        if ( m_FreeListSize == 0 )
        {
            //
            // If the free list is empty simply point m_pFree to the newly freed node.
            //
            m_pFree = pPtr;
        }
        else
        {
            //
            // If the free list is not empty, point newly freed block to what m_pFree was pointing
            //  to and set m_pFree to the new node.
            // Put NextBlock address into first 4 bytes of pPtr
            //
            u8* pTmpPtr = m_pFree;

            *((u8**)pPtr) = (u8*)pTmpPtr;
            m_pFree = pPtr;
        }

        m_FreeListSize++;
        m_AllocListSize--;
    }

    u32 SizeList( void )
    {
        return m_AllocListSize + m_FreeListSize;
    }

    u32 NumAllocatedUnits( void )
    { 
        return m_AllocListSize;
    }

    u32 NumFreeUnits( void )
    { 
        return m_FreeListSize;
    }


private:

    u8*     m_pHeap;                // Pointer to allocated memory chunk
    u8*     m_pFree;                // Pointer to first element of free list
    u8*     m_pEnd;                 // Always points to the "next" pointer at end of LAST chuck

    u32     m_UnitSize;             // Size in bytes of each "Unit"
    u32     m_NumUnits;             // Number of units in initial allocation
    u32     m_NumGrowUnits;         // Grow by this many "Units" when memory is exhausted
    u32     m_FirstSegmentSize;     // Size in bytes of first segment
    u32     m_GrowSegmentSize;      // Size in bytes of grow segment
    u32     m_FreeListSize;         // Num objects on free list
    u32     m_AllocListSize;        // Num allocated objects
    u32     m_NumGrownSegments;     // Number of segments grown dynamically

	Error	ThreadMemory(u8 *pPtr);
	Error	Destroy();
	u8*		Grow();
};
