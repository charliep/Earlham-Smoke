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

#include <StdArg.h>

#include "../BaseTypes/BaseTypes.h"
#include "Interface.h"


namespace Interface
{
namespace Properties
{
    pcstr Property::sm_kpszValue1Name = "Value1";
    pcstr Property::sm_kpszValue2Name = "Value2";
    pcstr Property::sm_kpszValue3Name = "Value3";
    pcstr Property::sm_kpszValue4Name = "Value4";

    Property::Property(
        pcstr pszName,
        u32 Type,
        u32 Flags,
        pcstr pszValue1Name,
        pcstr pszValue2Name,
        pcstr pszValue3Name,
        pcstr pszValue4Name,
        ...
        )
        : m_pszName( pszName )
        , m_Type( Type )
        , m_Flags( Flags )
        , m_apszEnumOptions( NULL )
    {
        //
        // Set to default if nothing is passed in.
        //
        m_apszValueNames[ 0 ] = (pszValue1Name != NULL) ? pszValue1Name : sm_kpszValue1Name;
        m_apszValueNames[ 1 ] = (pszValue2Name != NULL) ? pszValue2Name : sm_kpszValue2Name;
        m_apszValueNames[ 2 ] = (pszValue3Name != NULL) ? pszValue3Name : sm_kpszValue3Name;
        m_apszValueNames[ 3 ] = (pszValue4Name != NULL) ? pszValue4Name : sm_kpszValue4Name;
/*
        //
        // Do some extra processing for the known types.
        //
        if ( Type == Values::Vector3 )
        {
            if ( pszValue1Name == NULL && pszValue2Name == NULL && pszValue3Name == NULL )
            {
                m_apszValueNames[ 0 ] = "X";
                m_apszValueNames[ 1 ] = "Y";
                m_apszValueNames[ 2 ] = "Z";
            }
        }
        else if ( Type == Values::Vector4 || Type == Values::Quaternion )
        {
            if ( pszValue1Name == NULL && pszValue2Name == NULL &&
                 pszValue3Name == NULL && pszValue4Name == NULL )
            {
                m_apszValueNames[ 0 ] = "X";
                m_apszValueNames[ 1 ] = "Y";
                m_apszValueNames[ 2 ] = "Z";
                m_apszValueNames[ 3 ] = "W";
            }
        }
        else if ( Type == Values::Color3 )
        {
            if ( pszValue1Name == NULL && pszValue2Name == NULL && pszValue3Name == NULL )
            {
                m_apszValueNames[ 0 ] = "B";
                m_apszValueNames[ 1 ] = "G";
                m_apszValueNames[ 2 ] = "R";
            }
        }
        else if ( Type == Values::Color4 )
        {
            if ( pszValue1Name == NULL && pszValue2Name == NULL &&
                 pszValue3Name == NULL && pszValue4Name == NULL )
            {
                m_apszValueNames[ 0 ] = "B";
                m_apszValueNames[ 1 ] = "G";
                m_apszValueNames[ 2 ] = "R";
                m_apszValueNames[ 3 ] = "A";
            }
        }
*/
        //
        // Read in the ... passed in values.
        //
        va_list pArg;
        va_start( pArg, pszValue4Name );

        for ( i32 i=0; i < Values::Count; i++ )
        {
            switch ( Type & Values::Mask )
            {
            case Values::None:
                i = Values::Count;
                break;

            case Values::Boolean:
                m_aValues[ i ].Boolean = va_arg( pArg, u32 );
                break;

            case Values::Enum:
            case Values::Int32:
                m_aValues[ i ].Int32 = va_arg( pArg, i32 );
                break;

            case Values::Float32:
            case Values::Angle:
                m_aValues[ i ].Float32 = va_arg( pArg, f32 );
                break;

            case Values::Vector3 & Values::Mask:
            case Values::Color3 & Values::Mask:
            {
                ASSERTMSG( i == 0, "Vector3 or Color3 can be the only value on a property." );
                m_aValues[ 0 ].Float32 = va_arg( pArg, f32 );
                m_aValues[ 1 ].Float32 = va_arg( pArg, f32 );
                m_aValues[ 2 ].Float32 = va_arg( pArg, f32 );
                i = Values::Count;
                break;
            }

            case Values::Vector4 & Values::Mask:
            case Values::Quaternion & Values::Mask:
            case Values::Color4 & Values::Mask:
            {
                ASSERTMSG( i == 0, "Vector4, Quaternion, or Color4 can be the only value on a property." );
                m_aValues[ 0 ].Float32 = va_arg( pArg, f32 );
                m_aValues[ 1 ].Float32 = va_arg( pArg, f32 );
                m_aValues[ 2 ].Float32 = va_arg( pArg, f32 );
                m_aValues[ 3 ].Float32 = va_arg( pArg, f32 );
                i = Values::Count;
                break;
            }

            case Values::String:
            case Values::Path:
                m_asValues[ i ] = va_arg( pArg, pcstr );
                break;

            default:
                ASSERTMSG( False, "Unhandled property type." );
                break;
            }

            Type >>= 8;
        }

        va_end( pArg );
    }
}
}
