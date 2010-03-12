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

#include "BaseTypes.h"
using namespace Math;

_MM_ALIGN16 static const u32 kaTranslationMask[ 4 ] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 };
_MM_ALIGN16 static const f32 kaIdentityMatrix[ 16 ] =
{
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

const __m128 XVector::sm_kxUnitX = { 1.0f, 0.0f, 0.0f, 0.0f };
const __m128 XVector::sm_kxUnitY = { 0.0f, 1.0f, 0.0f, 0.0f };
const __m128 XVector::sm_kxUnitZ = { 0.0f, 0.0f, 1.0f, 0.0f };
const __m128 XVector::sm_kxUnitW = { 0.0f, 0.0f, 0.0f, 1.0f };
const __m128 XVector::sm_kxNegateX = { -0.0f, 0.0f, 0.0f, 0.0f };
const __m128 XVector::sm_kxNegateY = { 0.0f, -0.0f, 0.0f, 0.0f };
const __m128 XVector::sm_kxNegateZ = { 0.0f, 0.0f, -0.0f, 0.0f };
const __m128 XVector::sm_kxNegateW = { 0.0f, 0.0f, 0.0f, -0.0f };
const __m128 XVector::sm_kxNegateXYZ = { -0.0f, -0.0f, -0.0f, 0.0f };
const __m128 XVector::sm_kxNegateXYZW = { -0.0f, -0.0f, -0.0f, -0.0f };
const __m128 XVector::sm_kxOne = { 1.0f, 1.0f, 1.0f, 1.0f };
const __m128 XVector::sm_kxTwo = { 2.0f, 2.0f, 2.0f, 2.0f };
const __m128 XVector::sm_kxTranslationMask = *((const __m128*)kaTranslationMask);

const XVector3 XVector3::Zero( 0.0f );
const XVector3 XVector3::One( 1.0f );
const XVector3 XVector3::UnitX( sm_kxUnitX );
const XVector3 XVector3::UnitY( sm_kxUnitY );
const XVector3 XVector3::UnitZ( sm_kxUnitZ );

const XVector4 XVector4::Zero( 0.0f, 0.0f, 0.0f, 1.0f );
const XVector4 XVector4::One( 1.0f );

const XQuaternion XQuaternion::Zero( 0.0f, 0.0f, 0.0f, 1.0f );

const XMatrix4x4 XMatrix4x4::Identity( kaIdentityMatrix );

const __m128 XMatrix4x4::sm_kxHighOne = { 0.0f, 0.0f, 0.0f, 1.0f };


XVector3::XVector3(
    f32 x,
    f32 y,
    f32 z
    )
{
    __m128 xx = _mm_load_ss( &x );
    __m128 xy = _mm_load_ss( &y );
    __m128 xz = _mm_load_ss( &z );

    m_Vector = _mm_movelh_ps( _mm_unpacklo_ps( xx, xy ), xz );
}


XVector4::XVector4(
    f32 x,
    f32 y,
    f32 z,
    f32 w
    )
{
    __m128 xx = _mm_load_ss( &x );
    __m128 xy = _mm_load_ss( &y );
    __m128 xz = _mm_load_ss( &z );
    __m128 xw = _mm_load_ss( &w );

    m_Vector = _mm_movelh_ps( _mm_unpacklo_ps( xx, xy ), _mm_unpacklo_ps( xz, xw ) );
}


XQuaternion::XQuaternion(
    f32 x,
    f32 y,
    f32 z,
    f32 w
    )
{
    __m128 xx = _mm_load_ss( &x );
    __m128 xy = _mm_load_ss( &y );
    __m128 xz = _mm_load_ss( &z );
    __m128 xw = _mm_load_ss( &w );

    m_Vector = _mm_movelh_ps( _mm_unpacklo_ps( xx, xy ), _mm_unpacklo_ps( xz, xw ) );
}


XQuaternion::XQuaternion(
    const XVector3& Axis,
    f32 Angle
    )
{
    ASSERTMSG( Axis.Magnitude() == 1.0f,
               "This function requires the vector to be normalized upon entry." );
    ASSERT( ((const __m128)Axis).m128_f32[ 3 ] == 0.0f );

    const __m128 xSin = Axis * Angle::Sin( Angle );
    const __m128 xCos = _mm_set_ss( Angle::Cos( Angle ) );
    m_Vector = _mm_or_ps( xSin, xCos );
}


XQuaternion::XQuaternion(
    const Vector3& Angles
    )
{
    //
    // This function is by no means optimal since it is known that several of the coordinates
    //  are zero and so can be ignored in the quaternion multiply.
    //
    XQuaternion qx( XVector3::UnitX, Angles.x );
    XQuaternion qy( XVector3::UnitY, Angles.y );
    XQuaternion qz( XVector3::UnitZ, Angles.z );

    *this = qx * qy;
    *this *= qz;
}


XMatrix4x4::XMatrix4x4(
    const XVector3& Translation,
    const XQuaternion& Orientation
    )
{
    SetTranslation( Translation );
    SetOrientation( Orientation );
}


XQuaternion
XQuaternion::operator*(
    XQuaternion& a
    ) const
{
    __m128 t0 = _mm_mul_ps( _mm_shuffle_ps(   m_Vector,   m_Vector, _MM_SHUFFLE( 3, 3, 3, 3 ) ),
                            a.m_Vector );
    __m128 t1 = _mm_mul_ps( m_Vector,
                            _mm_shuffle_ps( a.m_Vector, a.m_Vector, _MM_SHUFFLE( 0, 3, 3, 3 ) ) );
    __m128 t2 = _mm_mul_ps( _mm_shuffle_ps(   m_Vector,   m_Vector, _MM_SHUFFLE( 1, 0, 2, 1 ) ),
                            _mm_shuffle_ps( a.m_Vector, a.m_Vector, _MM_SHUFFLE( 1, 1, 0, 2 ) ) );
    __m128 t3 = _mm_mul_ps( _mm_shuffle_ps(   m_Vector,   m_Vector, _MM_SHUFFLE( 2, 1, 0, 2 ) ),
                            _mm_shuffle_ps( a.m_Vector, a.m_Vector, _MM_SHUFFLE( 2, 0, 2, 1 ) ) );

    t1 = _mm_xor_ps( t1, sm_kxNegateW );
    t2 = _mm_xor_ps( t2, sm_kxNegateW );

    return XQuaternion( _mm_add_ps( _mm_add_ps( t0, t1 ), _mm_sub_ps( t2, t3 ) ) );
}


XVector3
XMatrix4x4::operator*(
    const XVector3& a
    ) const
{
    const __m128 xVec = a;
    __m128 xVecRes;

    xVecRes =
        _mm_add4_ps_composite(
            _mm_mul_ps( m_Matrix[ 0 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 0, 0, 0, 0 ) ) ),
            _mm_mul_ps( m_Matrix[ 1 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 1, 1, 1, 1 ) ) ),
            _mm_mul_ps( m_Matrix[ 2 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 2, 2, 2, 2 ) ) ),
                        m_Matrix[ 3 ]
            );

    return XVector3( _mm_and_ps( xVecRes, XVector::sm_kxTranslationMask ) );
}


XVector4
XMatrix4x4::operator*(
    const XVector4& a
    ) const
{
    const __m128 xVec = a;
    __m128 xVecRes;

    xVecRes =
        _mm_add4_ps_composite(
            _mm_mul_ps( m_Matrix[ 0 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 0, 0, 0, 0 ) ) ),
            _mm_mul_ps( m_Matrix[ 1 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 1, 1, 1, 1 ) ) ),
            _mm_mul_ps( m_Matrix[ 2 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 2, 2, 2, 2 ) ) ),
            _mm_mul_ps( m_Matrix[ 3 ], _mm_shuffle_ps( xVec, xVec, _MM_SHUFFLE( 3, 3, 3, 3 ) ) )
            );

    return XVector4( xVecRes );
}


XMatrix4x4
XMatrix4x4::operator*(
    const XMatrix4x4& a
    ) const
{
    XMatrix4x4 r;

    __m128 t0, t1, t2, t3;
    __m128 r0, r1, r2, r3;
                                                                // MSB               LSB
    t0 = _mm_unpacklo_ps( m_Matrix[ 0 ], m_Matrix[ 1 ] );       // [ 11 | 01 | 10 | 00 ]
    t1 = _mm_unpackhi_ps( m_Matrix[ 0 ], m_Matrix[ 1 ] );       // [ 13 | 03 | 12 | 02 ]
    t2 = _mm_unpacklo_ps( m_Matrix[ 2 ], m_Matrix[ 3 ] );       // [ 31 | 21 | 30 | 20 ]
    t3 = _mm_unpackhi_ps( m_Matrix[ 2 ], m_Matrix[ 3 ] );       // [ 33 | 23 | 32 | 22 ]

    r0 = _mm_movelh_ps( t0, t2 );                               // [ 30 | 20 | 10 | 00 ]
    r1 = _mm_movehl_ps( t0, t2 );                               // [ 31 | 21 | 11 | 01 ]
    r2 = _mm_movelh_ps( t1, t3 );                               // [ 32 | 22 | 12 | 02 ]
    r3 = _mm_movehl_ps( t1, t3 );                               // [ 33 | 23 | 13 | 03 ]

    r.m_Matrix[ 0 ] = _mm_add4_ps_composite( _mm_mul_ps( r0, a.m_Matrix[ 0 ] ),
                                             _mm_mul_ps( r1, a.m_Matrix[ 0 ] ),
                                             _mm_mul_ps( r2, a.m_Matrix[ 0 ] ),
                                             _mm_mul_ps( r3, a.m_Matrix[ 0 ] ) );

    r.m_Matrix[ 1 ] = _mm_add4_ps_composite( _mm_mul_ps( r0, a.m_Matrix[ 1 ] ),
                                             _mm_mul_ps( r1, a.m_Matrix[ 1 ] ),
                                             _mm_mul_ps( r2, a.m_Matrix[ 1 ] ),
                                             _mm_mul_ps( r3, a.m_Matrix[ 1 ] ) );

    r.m_Matrix[ 2 ] = _mm_add4_ps_composite( _mm_mul_ps( r0, a.m_Matrix[ 2 ] ),
                                             _mm_mul_ps( r1, a.m_Matrix[ 2 ] ),
                                             _mm_mul_ps( r2, a.m_Matrix[ 2 ] ),
                                             _mm_mul_ps( r3, a.m_Matrix[ 2 ] ) );

    r.m_Matrix[ 3 ] = _mm_add4_ps_composite( _mm_mul_ps( r0, a.m_Matrix[ 3 ] ),
                                             _mm_mul_ps( r1, a.m_Matrix[ 3 ] ),
                                             _mm_mul_ps( r2, a.m_Matrix[ 3 ] ),
                                             _mm_mul_ps( r3, a.m_Matrix[ 3 ] ) );

    return r;
}


XQuaternion&
XMatrix4x4::GetOrientation(
    XQuaternion& Orientation
    ) const
{
    _MM_ALIGN16 f32 m[ 16 ];
    _mm_store_ps( m, m_Matrix[ 0 ] );
    _mm_store_ps( m+4, m_Matrix[ 1 ] );
    _mm_store_ps( m+8, m_Matrix[ 2 ] );
    _mm_store_ps( m+12, m_Matrix[ 3 ] );

    const f32 T = 1.0f + m[ 0 ] + m[ 5 ] + m[ 10 ];

    if ( T > 0.00000001f )
    {
        const f32 S = sqrtf( T ) * 2.0f;
        const f32 invS = 1.0f / S;

        Orientation = XQuaternion( (m[ 6 ] - m[ 9 ]) * invS, 
                                   (m[ 8 ] - m[ 2 ]) * invS,
                                   (m[ 1 ] - m[ 4 ]) * invS,
                                   0.25f * S );
    }
    else if ( m[ 0 ] > m[ 5 ] && m[ 0 ] > m[ 10 ] )
    {
        const f32 S = sqrtf( 1.0f + m[ 0 ] - m[ 5 ] - m[ 10 ] ) * 2.0f;
        const f32 invS = 1.0f / S;

        Orientation = XQuaternion( 0.25f * S,
                                   (m[ 1 ] + m[ 4 ]) * invS,
                                   (m[ 8 ] + m[ 2 ]) * invS,
                                   (m[ 6 ] - m[ 9 ]) * invS );
    }
    else if ( m[ 5 ] > m[ 10 ] )
    {
        const f32 S  = sqrt( 1.0f + m[ 5 ] - m[ 0 ] - m[ 10 ] ) * 2.0f;
        const f32 invS = 1.0f / S;

        Orientation = XQuaternion( (m[ 1 ] + m[ 4 ]) * invS,
                                   0.25f * S,
                                   (m[ 6 ] + m[ 9 ]) * invS,
                                   (m[ 8 ] - m[ 2 ]) * invS );
    }
    else
    {
        const f32 S  = sqrt( 1.0f + m[ 10 ] - m[ 0 ] - m[ 5 ] ) * 2.0f;
        const f32 invS = 1.0f / S;

        Orientation = XQuaternion( (m[ 8 ] + m[ 2 ]) * invS,
                                   (m[ 6 ] + m[ 9 ]) * invS,
                                   0.25f * S,
                                   (m[ 1 ] - m[ 4 ]) * invS );
    }

    return Orientation;
}


XMatrix4x4&
XMatrix4x4::SetOrientation(
    const XQuaternion& Orientation
    )
{
    __m128 t0, t1;

    //
    // m[  0 ] = 1.0f - ((yy + zz) * 2.0f);
    // m[  1 ] =        ((xy - zw) * 2.0f);
    // m[  2 ] =        ((xz + yw) * 2.0f);
    //
    t0 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 0, 0, 1 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 2, 1, 1 ) ) );
    t1 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 1, 2, 2 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 3, 3, 2 ) ) );
    t1 = _mm_xor_ps( t1, XVector::sm_kxNegateY );

    t0 = _mm_mul_ps( _mm_add_ps( t0, t1 ), XVector::sm_kxTwo );
    t0 = _mm_add_ps( _mm_xor_ps( t0, XVector::sm_kxNegateX ), XVector::sm_kxUnitX );

    m_Matrix[ 0 ] = _mm_and_ps( t0, XVector::sm_kxTranslationMask );

    //
    // m[  4 ] =        ((xy + zw) * 2.0f);
    // m[  5 ] = 1.0f - ((xx + zz) * 2.0f);
    // m[  6 ] =        ((yz - xw) * 2.0f);
    //
    t0 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 1, 0, 0 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 2, 0, 1 ) ) );
    t1 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 0, 2, 2 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 3, 2, 3 ) ) );
    t1 = _mm_xor_ps( t1, XVector::sm_kxNegateZ );

    t0 = _mm_mul_ps( _mm_add_ps( t0, t1 ), XVector::sm_kxTwo );
    t0 = _mm_add_ps( _mm_xor_ps( t0, XVector::sm_kxNegateY ), XVector::sm_kxUnitY );

    m_Matrix[ 1 ] = _mm_and_ps( t0, XVector::sm_kxTranslationMask );

    //
    // m[  8 ] =        ((xz - yw) * 2.0f);
    // m[  9 ] =        ((yz + xw) * 2.0f);
    // m[ 10 ] = 1.0f - ((xx + yy) * 2.0f);
    //
    t0 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 0, 1, 0 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 0, 2, 2 ) ) );
    t1 = _mm_mul_ps( _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 1, 0, 1 ) ),
                     _mm_shuffle_ps( Orientation, Orientation, _MM_SHUFFLE( 3, 1, 3, 3 ) ) );
    t1 = _mm_xor_ps( t1, XVector::sm_kxNegateX );

    t0 = _mm_mul_ps( _mm_add_ps( t0, t1 ), XVector::sm_kxTwo );
    t0 = _mm_add_ps( _mm_xor_ps( t0, XVector::sm_kxNegateZ ), XVector::sm_kxUnitZ );

    m_Matrix[ 2 ] = _mm_and_ps( t0, XVector::sm_kxTranslationMask );

    return *this;
}

#if 0

// This code is taken from 
// Intel AP-929 Streaming SIMD Extensions - Inverse of 6x6 Matrix
// 1999

XMatrix4x4& 
XMatrix4x4::Inverse( Out XMatrix4x4& src )
{
    __m128 minor0, minor1, minor2, minor3;
    __m128 row0, row1, row2, row3;
    __m128 det, tmp1;

    tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src.m_Matrix)), (__m64*)(src.m_Matrix+ 4));
    row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src.m_Matrix+8)), (__m64*)(src.m_Matrix+12));
    row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
    row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
    tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src.m_Matrix+ 2)), (__m64*)(src.m_Matrix+ 6));
    row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src.m_Matrix+10)), (__m64*)(src.m_Matrix+14));
    row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
    row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(row2, row3);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    minor0 = _mm_mul_ps(row1, tmp1);
    minor1 = _mm_mul_ps(row0, tmp1);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
    minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
    minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(row1, row2);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
    minor3 = _mm_mul_ps(row0, tmp1);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
    minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
    minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    row2 = _mm_shuffle_ps(row2, row2, 0x4E);
    minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
    minor2 = _mm_mul_ps(row0, tmp1);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
    minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
    minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(row0, row1);


    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
    minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
    minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(row0, row3);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
    minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
    minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
    // -----------------------------------------------
    tmp1 = _mm_mul_ps(row0, row2);
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
    minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
    minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
    tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
    minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
    minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
    // -----------------------------------------------
    det = _mm_mul_ps(row0, minor0);
    det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
    det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
    tmp1 = _mm_rcp_ss(det);
    det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
    det = _mm_shuffle_ps(det, det, 0x00);
    minor0 = _mm_mul_ps(det, minor0);
    _mm_storel_pi((__m64*)(src.m_Matrix), minor0);
    _mm_storeh_pi((__m64*)(src.m_Matrix+2), minor0);
    minor1 = _mm_mul_ps(det, minor1);
    _mm_storel_pi((__m64*)(src.m_Matrix+4), minor1);
    _mm_storeh_pi((__m64*)(src.m_Matrix+6), minor1);
    minor2 = _mm_mul_ps(det, minor2);
    _mm_storel_pi((__m64*)(src.m_Matrix+ 8), minor2);
    _mm_storeh_pi((__m64*)(src.m_Matrix+10), minor2);
    minor3 = _mm_mul_ps(det, minor3);
    _mm_storel_pi((__m64*)(src.m_Matrix+12), minor3);
    _mm_storeh_pi((__m64*)(src.m_Matrix+14), minor3);

    return src;
}

#endif
