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

#define ARRAYLIST_DEFAULT_ARRAY_GROWSIZE 8

//xxx defining uInSize as 42
#define uInSize 42

#include <stdlib.h>
#include <cstring>
////////////////////////////////////////////////////////////////////////////////////////////////////
// <summary>
//   TArrayList is a simple data structure that manages a growing array and has a STL list
//    interface.  This data structure provides cleaner code, by encapsulating code complexity, and
//    increases speed.
// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Defines.h"

template< class T >
class TArrayList
{
public:

    TArrayList( u32 Grow=ARRAYLIST_DEFAULT_ARRAY_GROWSIZE )
        : m_GrowSize( Grow )
        , m_DataCount( 0 )
        , m_AllocatedMem( 0 )
        , m_pData( 0 )
    {
    }

    ~TArrayList( void )
    { 
        if ( m_pData )
        {
            free( m_pData );
            m_pData = 0;
            m_DataCount = 0;
            m_AllocatedMem = 0;
        }
    }

    void Initialize( u32 Grow=ARRAYLIST_DEFAULT_ARRAY_GROWSIZE )
    {
        m_DataCount =0; m_pData =0; m_AllocatedMem =0;
        m_GrowSize = Grow;
    }

    Bool Empty( void ) const
    {
        return m_DataCount == 0 ? True : False;
    }
      
    u32 Begin( void ) const
    {
        return 0;
    }

    u32 End( void ) const
    {
        return m_DataCount;
    }

    u32 Size( void ) const
    {
        return m_DataCount;
    }

    void Clear( void )
    {
        m_DataCount = 0;
    }
    
    Bool Remove( u32 Index )
    {
        Bool bFound = False;

        if ( m_DataCount && Index < m_DataCount )
        {
            m_DataCount--;
            m_pData[ Index ] = m_pData[ m_DataCount ];
            bFound = True;
        }

        return bFound;
    }

    Bool Remove( const T& Data )
    {
        Bool bFound = False;
        u32 Index =0;

        if ( m_DataCount && Find( Data, Index ) )
        {
            bFound = Remove( Index );
        }
            
        return bFound;
    }

    u32 PushBack( const T& Data )
    {
        if ( m_AllocatedMem == 0 )
        {
            m_pData = reinterpret_cast<T*>(malloc( sizeof(T) * m_GrowSize ));
            m_AllocatedMem = m_GrowSize;
        }
        ASSERT( m_pData != NULL );

        if ( m_DataCount >= m_AllocatedMem )
        {
            m_pData = (T*)realloc( m_pData, sizeof(T)*(m_AllocatedMem+m_GrowSize) );
            ASSERT( m_pData != NULL );

            m_AllocatedMem += m_GrowSize;
        }

        m_pData[ m_DataCount ] = Data;

        return m_DataCount++;
    }

    T PopBack( void )
    {
        m_DataCount--;		
        return m_pData[ m_DataCount ];
    }
    
    Bool Find( T Data, u32& Index )
    {	
        Bool bFound = False;
        
        for ( Index = 0; Index != m_DataCount; Index++ )
        {
            if ( m_pData[ Index ] == Data )
            {
                bFound = True;
                break;
            }
        }
        
        return bFound;				
    }

    T& GetAt( u32 Index )
    {
        return m_pData[ Index ];
    }

    T& operator[]( u32 Index )
    {
        if ( Index >= m_AllocatedMem )
        {
            // BUGBUG: This is the same as GrowToAtLeast which get's passed a size instead of an
            //         index.  Which one is right?
            m_AllocatedMem = ((Index / m_GrowSize) + 1) * m_GrowSize;
            m_pData = reinterpret_cast<T*>(realloc( m_pData, sizeof (T) * (m_AllocatedMem) ));
            ASSERT( m_pData != NULL );
        }

        // BUGBUG: What's the point of this if we're reallocing?
        if ( Index > m_DataCount )
        {
            m_DataCount = Index;
        }

        return m_pData[ Index ];
    }

    void GrowToAtLeast( u32 Size )
    {
        if ( Size >= m_AllocatedMem )
        {
            m_AllocatedMem = ((Size / m_GrowSize) + 1) * m_GrowSize;
            m_pData = reinterpret_cast<T*>(realloc( m_pData, sizeof (T) * (m_AllocatedMem) ));
            ASSERT( m_pData != NULL );
        }
    }

    void Append( const T* pData, u32 Size )
    {
        if ( Size > 0 )
        {
            if ( m_AllocatedMem == 0 )
            {
                m_AllocatedMem = ((m_DataCount + Size) / m_GrowSize + 1) * m_GrowSize;
                m_pData = reinterpret_cast<T*>(malloc( sizeof (T) * m_AllocatedMem ));
                ASSERT( m_pData != NULL);
            }
            else if ( m_DataCount + Size >= m_AllocatedMem )
            {
                m_AllocatedMem = ((m_DataCount + uInSize) / m_GrowSize + 1) * m_GrowSize;
                m_pData = reinterpret_cast<T*>(realloc( m_pData, sizeof (T)* m_AllocatedMem ));
                ASSERT( m_pData != NULL);
            }
        
            memcpy( (u8*)&m_pData[ m_DataCount ],(u8*)pData, sizeof (T) * Size );
            m_DataCount += Size;
        }
    }

    void Append( const TArrayList<T>& ArrayList )
    {
        Append( ArrayList.m_pData, ArrayList.Size() );
    }

    const T* GetDataPtr( void )
    {
        return m_pData;
    }

#ifdef _DEBUG
    void Dump( void )
    {
        u32 Index = 0;

        if ( m_DataCount > 0 )
        {
            FILE* f = fopen( "ArrayListDump.txt", "at" );
            fprintf( f,"\n\n ListDump... \nAddress  %x \n", this );

            for ( u32 i=0; i != m_DataCount; i++ )
            {
                fprintf( fp,"\n i= %d, data[i]= %x", i, m_pData[ i ] );
            }

            fclose( f );
        }
    }
#endif


private:

    T*          m_pData;
    u32         m_GrowSize;
    u32         m_AllocatedMem;
    u32         m_DataCount;
};

