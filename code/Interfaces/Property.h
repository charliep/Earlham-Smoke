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

/*******************************************************************************
* STRUCT: Property
*
* DESCRIPTION:
* Defines a structure used to get and set properties for a system and object.
*******************************************************************************/

namespace Properties
{
    namespace Values
    {
        #define VALUE1( v1 )                         ((v1) << 0)
        #define VALUE2( v1, v2 )                     (VALUE1(v1) | ((v2) << 8))
        #define VALUE3( v1, v2, v3 )                 (VALUE2(v1, v2) | ((v3) << 16))
        #define VALUE4( v1, v2, v3, v4 )             (VALUE3(v1, v2, v3) | ((v4) << 24))

        #define VALUE1x2( v1 )                       VALUE2( v1, v1 )
        #define VALUE1x3( v1 )                       VALUE3( v1, v1, v1 )
        #define VALUE1x4( v1 )                       VALUE4( v1, v1, v1, v1 )

        static const u32 Count                      = 4;
        static const u32 Mask                       = 0x000000FF;

        static const u32 None                       = 0x00000000;
        static const u32 Boolean                    = 0x00000001;
        static const u32 Enum                       = 0x00000002;
        static const u32 Int32                      = 0x00000003;
        static const u32 Float32                    = 0x00000004;
        static const u32 String                     = 0x00000005;
        static const u32 Path                       = 0x00000006;
        static const u32 Angle                      = 0x00000007;

        static const u32 Vector3                    = 0x00101010;
        static const u32 Vector4                    = 0x11111111;

        static const u32 Quaternion                 = 0x12121212;

        static const u32 Color3                     = 0x00131313;
        static const u32 Color4                     = 0x14141414;
    }

    namespace Flags
    {
        static const u32 Valid                      = 0x00000001;
        static const u32 InitOnly                   = 0x00000002;
        static const u32 Multiple                   = 0x00000004; // this is write only by default
        static const u32 WriteOnly                  = 0x00000008;
    }

    /// <summary>
    ///   Class for providing a method to transfer paramters between a system and the framework.
    /// </summary>
    class Property
    {
    public:

        /// <summary>
        ///   Empty constructor.
        /// </summary>
        Property( void ) {}

        /// <summary>
        ///   Constructor for creating a well formed property.  Useful for creating an array of
        ///    statically defined properties.
        /// </summary>
        /// <param name="pszPropertyName">The name of this property.</param>
        /// <param name="PropertyType">The type of property from Proerties::Values.</param>
        /// <param name="PropertyFlags">Flags for qualifying the use of the property.</param>
        //Property( pcstr pszPropertyName, u32 PropertyType, u32 PropertyFlags, ... );

        /// <summary>
        ///   Constructor for creating a well formed property.  Useful for creating an array of
        ///    statically defined properties.  Gives the extra added bonus of naming the values
        ///    within an xDF instead of just Value1, Value2, etc.
        /// </summary>
        /// <param name="pszPropertyName">The name of this property.</param>
        /// <param name="PropertyType">The type of property from Proerties::Values.</param>
        /// <param name="PropertyFlags">Flags for qualifying the use of the property.</param>
		/// <param name="pszValue1Name">Name of value 1.</param>
		/// <param name="pszValue2Name">Name of value 2.</param>
		/// <param name="pszValue3Name">Name of value 3.</param>
		/// <param name="pszValue4Name">Name of value 4.</param>
        Property( pcstr pszPropertyName, u32 PropertyType, u32 PropertyFlags,
                  pcstr pszValue1Name, pcstr pszValue2Name, pcstr pszValue3Name, pcstr pszValue4Name,
                  ... );

        /// <summary>
        ///   Returns the property name.
        /// </summary>
        /// <returns>The property's name.</returns>
        pcstr GetName( void ) const
        {
            return m_pszName;
        }

        u32 GetValueType( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return (m_Type >> (Index * 8)) & Values::Mask;
        }

        u32 GetFlags( void ) const
        {
            return m_Flags;
        }

        void SetFlag( u32 Flag )
        {
            m_Flags |= Flag;
        }

        void ClearFlag( u32 Flag )
        {
            m_Flags &= ~Flag;
        }

        Bool GetBool( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_aValues[ Index ].Boolean;
        }

        i32 GetInt32( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_aValues[ Index ].Int32;
        }

        f32 GetFloat32( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_aValues[ Index ].Float32;
        }

        const std::string GetString( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_asValues[ Index ];
        }

        pcstr GetStringPtr( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_asValues[ Index ].c_str();
        }

        const Math::Vector3 GetVector3( void ) const
        {
            return Math::Vector3( m_aValues[ 0 ].Float32,
                                  m_aValues[ 1 ].Float32,
                                  m_aValues[ 2 ].Float32);
        }

        const Math::Vector4 GetVector4( void ) const
        {
            Math::Vector4 v = { m_aValues[ 0 ].Float32, m_aValues[ 1 ].Float32,
                                m_aValues[ 2 ].Float32, m_aValues[ 3 ].Float32 };
            return v;
        }

        const Math::Quaternion GetQuaternion( void ) const
        {
            Math::Quaternion q ={ m_aValues[ 0 ].Float32, m_aValues[ 1 ].Float32,
                                  m_aValues[ 2 ].Float32, m_aValues[ 3 ].Float32 };
            return q;
        }

        const Math::Color3 GetColor3( void ) const
        {
            Math::Color3 c = { m_aValues[ 0 ].Float32, m_aValues[ 1 ].Float32,
                               m_aValues[ 2 ].Float32 };
            return c;
        }

        const Math::Color4 GetColor4( void ) const
        {
            Math::Color4 c = { m_aValues[ 0 ].Float32, m_aValues[ 1 ].Float32,
                               m_aValues[ 2 ].Float32, m_aValues[ 3 ].Float32 };
            return c;
        }

        void SetValue( i32 Index, const Bool& Value )
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            m_aValues[ Index ].Boolean = Value;
        }

        void SetValue( i32 Index, const i32& Value )
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            m_aValues[ Index ].Int32 = Value;
        }

        void SetValue( i32 Index, const f32& Value )
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            m_aValues[ Index ].Float32 = Value;
        }

        void SetValue( i32 Index, const std::string& Value )
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            m_asValues[ Index ] = Value;
        }

        void SetValue( const Math::Vector3& Value )
        {
            m_aValues[ 0 ].Float32 = Value.x;
            m_aValues[ 1 ].Float32 = Value.y;
            m_aValues[ 2 ].Float32 = Value.z;
        }

        void SetValue( const Math::Vector4& Value )
        {
            m_aValues[ 0 ].Float32 = Value.x;
            m_aValues[ 1 ].Float32 = Value.y;
            m_aValues[ 2 ].Float32 = Value.z;
            m_aValues[ 3 ].Float32 = Value.w;
        }

        void SetValue( const Math::Quaternion& Value )
        {
            m_aValues[ 0 ].Float32 = Value.x;
            m_aValues[ 1 ].Float32 = Value.y;
            m_aValues[ 2 ].Float32 = Value.z;
            m_aValues[ 3 ].Float32 = Value.w;
        }

        void SetValue( const Math::Color3& Value )
        {
            m_aValues[ 0 ].Float32 = Value.b;
            m_aValues[ 1 ].Float32 = Value.g;
            m_aValues[ 2 ].Float32 = Value.r;
        }

        void SetValue( const Math::Color4& Value )
        {
            m_aValues[ 0 ].Float32 = Value.b;
            m_aValues[ 1 ].Float32 = Value.g;
            m_aValues[ 2 ].Float32 = Value.r;
            m_aValues[ 3 ].Float32 = Value.a;
        }

        pcstr GetEnumOption( i32 Index ) const
        {
            return m_apszEnumOptions[ Index ];
        }

        void SetEnumOptions( const pcstr* apszEnumOptions )
        {
            m_apszEnumOptions = apszEnumOptions;
        }

        pcstr GetValueName( i32 Index ) const
        {
            ASSERT( Index >= 0 && Index < Values::Count );
            return m_apszValueNames[ Index ];
        }


    protected:

        static pcstr            sm_kpszValue1Name;
        static pcstr            sm_kpszValue2Name;
        static pcstr            sm_kpszValue3Name;
        static pcstr            sm_kpszValue4Name;

        pcstr                   m_pszName;

        u32                     m_Type;
        u32                     m_Flags;

        union Value
        {
            u32                 Boolean;
            i32                 Int32;
            f32                 Float32;
        };
        Value                   m_aValues[ Values::Count ];
        std::string             m_asValues[ Values::Count ];

        const pcstr*            m_apszEnumOptions;

        pcstr                   m_apszValueNames[ Values::Count ];
    };

    typedef std::vector<Properties::Property>       Array;
    typedef Array::iterator                         Iterator;
    typedef Array::const_iterator                   ConstIterator;
}

