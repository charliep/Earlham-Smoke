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

#include <xmmintrin.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// <summary>
//   Miscellaneous SSE functionality.
// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
///   Convenience function for adding 3 __m128 types.
/// </summary>
/// <param name="a">The first variable to add.</param>
/// <param name="b">The second variable to add.</param>
/// <param name="c">The third variable to add.</param>
/// <returns>The three way add result.</returns>

__m128 __inline__ _mm_add3_ps_composite( const __m128& a, const __m128& b, const __m128& c )
{
    return _mm_add_ps( _mm_add_ps( a, b ), c );
}


/// <summary>
///   Convenience function for adding 4 __m128 types.
/// </summary>
/// <param name="a">The first variable to add.</param>
/// <param name="b">The second variable to add.</param>
/// <param name="c">The third variable to add.</param>
/// <param name="d">The fourth variable to add.</param>
/// <returns>The four way add result.</returns>
__m128 __inline__ _mm_add4_ps_composite( const __m128& a, const __m128& b,
                                            const __m128& c, const __m128& d )
{
    return _mm_add_ps( _mm_add_ps( a, b ), _mm_add_ps( c, d ) );
}


/// <summary>
///   Divides 2 __m128 types and zeroes out indeterminate values caused by divide-by-zero.
/// </summary>
/// <remarks>This function is used when masking divide-by-zero.</remarks>
/// <param name="a">The dividend.</param>
/// <param name="b">The divisor.</param>
/// <returns>The quotient.</returns>
__m128 __inline__ _mm_div_ps_composite( const __m128& a, const __m128& b )
{
    __m128 xMask = _mm_cmpneq_ps( b, _mm_setzero_ps() );
    __m128 t = _mm_div_ps( a, b );
    t = _mm_and_ps( t, xMask );
    return t;
}


namespace Math
{
    class XVector3;
    class XVector4;
    class XQuaternion;
    class XMatrix4x4;


    class XVector
    {
        friend class XMatrix4x4;


    public:

        XVector( void ) {}

        /// <summary>
        ///   Operator new override for allocation of SSE aligned memory.
        /// </summary>
        /// <param name="Size">The size to allocate.</param>
        /// <returns>A pointer to the allocated memory.</returns>
        void* operator new( size_t Size )
        {
		void** ptr;	
            posix_memalign( ptr, sizeof (__m128), Size);
		return ptr;
        }

        /// <summary>
        ///   Operator delete override for deallocation of SSE aligned memory.
        /// </summary>
        /// <param name="p">The pointer to deallocate.</param>
        void operator delete( void* p )
        {
            free( p );
        }

        /// <summary>
        ///   Provides a const cast to a __m128.
        /// </summary>
        /// <returns>This vector as a __m128.</returns>
        operator const __m128( void ) const
        {
            return m_Vector;
        }

        /// <summary>
        ///   Returns the x value of the vector.
        /// </summary>
        /// <returns>The x value of the vector.</returns>
        f32 GetX( void )
        {
            f32 x;
            _mm_store_ss( &x, m_Vector );
            return x;
        }

        /// <summary>
        ///   Returns the y value of the vector.
        /// </summary>
        /// <returns>The y value of the vector.</returns>
        f32 GetY( void )
        {
            f32 y;
            _mm_store_ss( &y, _mm_shuffle_ps( m_Vector, m_Vector, 1 ) );
            return y;
        }

        /// <summary>
        ///   Returns the z value of the vector.
        /// </summary>
        /// <returns>The z value of the vector.</returns>
        f32 GetZ( void )
        {
            f32 z;
            _mm_store_ss( &z, _mm_movehl_ps( m_Vector, m_Vector ) );
            return z;
        }

        /// <summary>
        ///   Returns the y value of the vector.
        /// </summary>
        /// <returns>The w value of the vector.</returns>
        f32 GetW( void )
        {
            f32 w;
            _mm_store_ss( &w, _mm_shuffle_ps( m_Vector, m_Vector, 3 ) );
            return w;
        }


    protected:

        static const __m128 sm_kxUnitX;
        static const __m128 sm_kxUnitY;
        static const __m128 sm_kxUnitZ;
        static const __m128 sm_kxUnitW;
        static const __m128 sm_kxNegateX;
        static const __m128 sm_kxNegateY;
        static const __m128 sm_kxNegateZ;
        static const __m128 sm_kxNegateW;
        static const __m128 sm_kxNegateXYZ;
        static const __m128 sm_kxNegateXYZW;
        static const __m128 sm_kxOne;
        static const __m128 sm_kxTwo;
        static const __m128 sm_kxTranslationMask;

        __m128          m_Vector;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   A convenience class for doing scalar operations with the SSE vector classes.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class XScalar : public XVector
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        XScalar( void ) : XVector() {}

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="s">A scalar value.</param>
        XScalar( f32 s )
        {
            m_Vector = _mm_set1_ps( s );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">A broadcasted scalar value.</param>
        XScalar( __m128 x )
        {
            ASSERT( (x.m128_f32[ 0 ] == x.m128_f32[ 1 ]) &&
                    (x.m128_f32[ 0 ] == x.m128_f32[ 2 ]) &&
                    (x.m128_f32[ 0 ] == x.m128_f32[ 3 ]) );
            m_Vector = x;
        }

        /// <summary>
        ///   Provides a cast to an f32.
        /// </summary>
        /// <returns>Ths XScalar as an f32.</returns>
        operator f32( void ) const
        {
            f32 s;
            _mm_store_ss( &s, m_Vector );
            return s;
        }
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides SSE functionality for a 3D vector.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class XVector3 : public XVector
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        XVector3( void ) : XVector() {}

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="v">A vector in array form.</param>
        XVector3( f32* v )
        {
            m_Vector = _mm_loadl_pi( m_Vector, reinterpret_cast<__m64*>(v) );
            m_Vector = _mm_movelh_ps( _mm_load_ss( v+2 ), m_Vector );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">A vector in __m128 form.</param>
        XVector3( __m128 x )
        {
            m_Vector = x;
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="f">The value to broadcast.</param>
        XVector3( f32 f )
        {
            m_Vector = _mm_and_ps( _mm_set1_ps( f ), sm_kxTranslationMask );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">The x value.</param>
        /// <param name="y">The y value.</param>
        /// <param name="z">The z value.</param>
        XVector3( f32 x, f32 y, f32 z );

        /// <summary>
        ///   Functionality for adding two vectors with assignment.
        /// </summary>
        /// <param name="a">The vector to add to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator+=( const XVector3& a )
        {
            m_Vector = _mm_add_ps( m_Vector, a.m_Vector );
            return *this;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors with assignment.
        /// </summary>
        /// <param name="a">The vector to subtract from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator-=( const XVector3& a )
        {
            m_Vector = _mm_sub_ps( m_Vector, a.m_Vector );
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator*=( const XScalar& s )
        {
            m_Vector = _mm_mul_ps( m_Vector, s );
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator*=( f32 s )
        {
            m_Vector = _mm_mul_ps( m_Vector, _mm_set1_ps( s ) );
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator/=( const XScalar& s )
        {
            m_Vector = _mm_div_ps_composite( m_Vector, s );
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector3& operator/=( f32 s )
        {
            m_Vector = _mm_div_ps_composite( m_Vector, _mm_set1_ps( s ) );
            return *this;
        }

        /// <summary>
        ///   Functionality for adding two vectors.
        /// </summary>
        /// <param name="a">The vector to add to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator+( const XVector3& a ) const
        {
            return XVector3( _mm_add_ps( m_Vector, a.m_Vector ) );
        }

        /// <summary>
        ///   Functionality for subtracting two vectors.
        /// </summary>
        /// <param name="a">The vector to subtract from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator-( const XVector3& a ) const
        {
            return XVector3( _mm_sub_ps( m_Vector, a.m_Vector ) );
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator*( const XScalar& s ) const
        {
            return XVector3( _mm_mul_ps( m_Vector, s ) );
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator*( f32 s ) const
        {
            return XVector3( _mm_mul_ps( m_Vector, _mm_set1_ps( s ) ) );
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator/( const XScalar& s ) const
        {
            return XVector3( _mm_div_ps_composite( m_Vector, s ) );
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector3 operator/( f32 s ) const
        {
            return XVector3( _mm_div_ps_composite( m_Vector, _mm_set1_ps( s ) ) );
        }

        /// <summary>
        ///   Functionality for equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator==( const XVector3& a ) const
        {
            return _mm_movemask_ps( _mm_cmpeq_ps( m_Vector, a.m_Vector ) ) == 7;
        }

        /// <summary>
        ///   Functionality for not equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator!=( const XVector3& a ) const
        {
            return _mm_movemask_ps( _mm_cmpeq_ps( m_Vector, a.m_Vector ) ) != 7;
        }

        /// <summary>
        ///   Returns the dot product of 2 vectors.
        /// </summary>
        /// <param name="a">The other vector.</param>
        /// <returns>The dot product.</returns>
        XScalar Dot( const XVector3& a ) const
        {
            __m128 t;
            __m128 sq = _mm_mul_ps( m_Vector, a.m_Vector );
            t = _mm_add_ps( sq, _mm_shuffle_ps( sq, sq, _MM_SHUFFLE( 3, 1, 0, 2 ) ) );
            t = _mm_add_ps( t,  _mm_shuffle_ps( sq, sq, _MM_SHUFFLE( 3, 0, 2, 1 ) ) );
            return XScalar( t );
        }

        /// <summary>
        ///   Returns the cross product of 2 vectors.
        /// </summary>
        /// <param name="a">The other vector.</param>
        /// <returns>The cross product.</returns>
        XVector3 Cross( const XVector3& a ) const
        {
            __m128 x00 = _mm_shuffle_ps(   m_Vector,   m_Vector, _MM_SHUFFLE( 3, 0, 2, 1 ) );
            __m128 x10 = _mm_shuffle_ps( a.m_Vector, a.m_Vector, _MM_SHUFFLE( 3, 1, 0, 2 ) );
            __m128 x01 = _mm_shuffle_ps(   m_Vector,   m_Vector, _MM_SHUFFLE( 3, 1, 0, 2 ) );
            __m128 x11 = _mm_shuffle_ps( a.m_Vector, a.m_Vector, _MM_SHUFFLE( 3, 0, 2, 1 ) );

            return XVector3( _mm_add_ps( _mm_mul_ps( x00, x10 ), _mm_mul_ps( x01, x11 ) ) );
        }

        /// <summary>
        ///   Returns the magnitude of the vector.
        /// </summary>
        /// <returns>The magnitude of the vector.</returns>
        XScalar Magnitude( void ) const
        {
            XScalar s = Dot( *this );
            return XScalar( _mm_sqrt_ps( s ) );
        }

        /// <summary>
        ///   Normalizes this vector.
        /// </summary>
        /// <returns>A refrence to this vector.</returns>
        const XVector3& Normalize( void )
        {
            static const __m128 xPtFive = { 0.5f, 0.5f, 0.5f, 0.5f };
            static const __m128 xThree = { 3.0f, 3.0f, 3.0f, 3.0f };

            XScalar dot = Dot( *this );

            __m128 rsd = _mm_rsqrt_ps( dot );

		    rsd = _mm_mul_ps( _mm_mul_ps( xPtFive, rsd ),
                              _mm_sub_ps( xThree, _mm_mul_ps( _mm_mul_ps( dot, rsd ), rsd ) ) );

            m_Vector = _mm_mul_ps( m_Vector, rsd );
            return *this;
        }


    public:

        //
        // Common constants.
        //
        static const XVector3 Zero;
        static const XVector3 One;
        static const XVector3 UnitX;
        static const XVector3 UnitY;
        static const XVector3 UnitZ;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides SSE functionality of a 3D vector with a modifier.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class XVector4 : public XVector
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        XVector4( void ) {}

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="v">A vector in array form.</param>
        XVector4( f32* v )
        {
            m_Vector = _mm_loadu_ps( v );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">A vector in __m128 form.</param>
        XVector4( __m128 x )
        {
            m_Vector = x;
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="f">The value to broadcast.</param>
        XVector4( f32 f )
        {
            m_Vector = _mm_set1_ps( f );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">The x value.</param>
        /// <param name="y">The y value.</param>
        /// <param name="z">The z value.</param>
        /// <param name="w">The w value.</param>
        XVector4( f32 x, f32 y, f32 z, f32 w );

        /// <summary>
        ///   Functionality for adding two vectors with assignment.
        /// </summary>
        /// <param name="a">The vector to add to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator+=( const XVector4& a )
        {
            m_Vector = _mm_add_ps( m_Vector, a.m_Vector );
            return *this;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors with assignment.
        /// </summary>
        /// <param name="a">The vector to subtract from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator-=( const XVector4& a )
        {
            m_Vector = _mm_sub_ps( m_Vector, a.m_Vector );
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator*=( const XScalar& s )
        {
            m_Vector = _mm_mul_ps( m_Vector, s );
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator*=( f32 s )
        {
            m_Vector = _mm_mul_ps( m_Vector, _mm_set1_ps( s ) );
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator/=( const XScalar& s )
        {
            m_Vector = _mm_div_ps_composite( m_Vector, s );
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        XVector4& operator/=( f32 s )
        {
            m_Vector = _mm_div_ps_composite( m_Vector, _mm_set1_ps( s ) );
            return *this;
        }

        /// <summary>
        ///   Functionality for adding two vectors.
        /// </summary>
        /// <param name="a">The vector to add to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator+( const XVector4& a ) const
        {
            return XVector4( _mm_add_ps( m_Vector, a.m_Vector ) );
        }

        /// <summary>
        ///   Functionality for subtracting two vectors.
        /// </summary>
        /// <param name="a">The vector to subtract from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator-( const XVector4& a ) const
        {
            return XVector4( _mm_sub_ps( m_Vector, a.m_Vector ) );
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator*( const XScalar& s ) const
        {
            return XVector4( _mm_add_ps( m_Vector, s ) );
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <param name="s">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator*( f32 s ) const
        {
            return XVector4( _mm_add_ps( m_Vector, _mm_set1_ps( s ) ) );
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator/( const XScalar& s ) const
        {
            return XVector4( _mm_div_ps_composite( m_Vector, s ) );
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Divide by zero needs to be masked.</remarks>
        /// <param name="s">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        XVector4 operator/( f32 s ) const
        {
            return XVector4( _mm_div_ps_composite( m_Vector, _mm_set1_ps( s ) ) );
        }

        /// <summary>
        ///   Functionality for equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator==( const XVector4& a ) const
        {
            return _mm_movemask_ps( _mm_cmpeq_ps( m_Vector, a.m_Vector ) ) == 0x0F;
        }

        /// <summary>
        ///   Functionality for not equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator!=( const XVector4& a ) const
        {
            return _mm_movemask_ps( _mm_cmpeq_ps( m_Vector, a.m_Vector ) ) != 0x0F;
        }


    public:

        //
        // Common constants.
        //
        static const XVector4 Zero;
        static const XVector4 One;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides SSE functionality for a quanternion.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class XQuaternion : public XVector
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        XQuaternion( void ) {}

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="q">A quaternion in array form.</param>
        XQuaternion( f32* q )
        {
            m_Vector = _mm_loadu_ps( q );
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">A quaternion in __m128 form.</param>
        XQuaternion( __m128 x )
        {
            m_Vector = x;
        }

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="x">The x value.</param>
        /// <param name="y">The y value.</param>
        /// <param name="z">The z value.</param>
        /// <param name="w">The w value.</param>
        XQuaternion( f32 x, f32 y, f32 z, f32 w );

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="Axis">The normalized vector axis."</param>
        /// <param name="Angle">The angle of the vector axis."</param>
        /// <returns>A reference to this quaternion.</returns>
        XQuaternion( const XVector3& Axis, f32 Angle );

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="Angles">The Euler angles for the quaternion."</param>
        /// <returns>A reference to this quaternion.</returns>
        XQuaternion( const Vector3& Angles );

        /// <summary>
        ///   Functionality for multiplying two quaternions.
        /// </summary>
        /// <param name="a">The quaternion to multiply to this quaterion.</param>
        /// <returns>The new quaternion.</returns>
        XQuaternion operator*( XQuaternion& a ) const;

        /// <summary>
        ///   Functionality for multiplying two quaternions with assignment.
        /// </summary>
        /// <param name="a">The quaternion to multiply to this quaterion.</param>
        /// <returns>A reference to this quaternion.</returns>
        XQuaternion& operator*=( XQuaternion& a )
        {
            *this = *this * a;
            return *this;
        }

        /// <summary>
        ///   Calculates the magnitude of this quaternion.
        /// </summary>
        /// <returns>The magnitude.</returns>
        f32 Magnitude( void ) const
        {
            __m128 t;
            __m128 sq = _mm_mul_ps( m_Vector, m_Vector );
            t = _mm_add_ps( sq, _mm_shuffle_ps( sq, sq, _MM_SHUFFLE( 3, 1, 0, 2 ) ) );
            t = _mm_add_ps( t,  _mm_shuffle_ps( sq, sq, _MM_SHUFFLE( 3, 0, 2, 1 ) ) );
            return XScalar( _mm_sqrt_ps( t ) );
        }

        /// <summary>
        ///   Calculates the conjugate or inverse of a quaternion.
        /// </summary>
        XQuaternion& Conjugate( void )
        {
            m_Vector = _mm_xor_ps( m_Vector, sm_kxNegateXYZ );
            return *this;
        }

        /// <summary>
        ///   Calculates the conjugate or inverse of a quaternion.
        /// </summary>
        /// <param name="a">The quaternion to set as the inverse of this quaternion.</param>
        XQuaternion& Conjugate( Out XQuaternion& a )
        {
            a = _mm_xor_ps( m_Vector , sm_kxNegateXYZ );
            return a;
        }

        XVector3 Rotate( const XVector3& a )
        {
            ASSERTMSG( False, "This still needs to be implemented!!!" );
            return XVector3();
        }


    public:

        static const XQuaternion Zero;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Row major SSE implementation of a 4x4 matrix.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class XMatrix4x4
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        XMatrix4x4( void ) {}

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <param name="m">A matrix in array form.</param>
        XMatrix4x4( const f32* m )
        {
            m_Matrix[ 0 ] = _mm_loadu_ps( m );
            m_Matrix[ 1 ] = _mm_loadu_ps( m+4 );
            m_Matrix[ 2 ] = _mm_loadu_ps( m+8 );
            m_Matrix[ 3 ] = _mm_loadu_ps( m+12 );
        };

        /// <summary>
        ///   Constructor for a transformation matrix.
        /// </summary>
        /// <param name="Translation">The translation for the matrix.</param>
        /// <param name="Orientation">The orientation for the matrix.</param>
        XMatrix4x4( const XVector3& Translation, const XQuaternion& Orientation );

        /// <summary>
        ///   Vector matrix multiplication.
        /// </summary>
        /// <param name="a">The vector to multiply to this matrix.</param>
        /// <returns>The new vector.</returns>
        XVector3 operator*( const XVector3& a ) const;

        /// <summary>
        ///   Vector matrix multiplication.
        /// </summary>
        /// <param name="a">The vector to multiply to this matrix.</param>
        /// <returns>The new vector.</returns>
        XVector4 operator*( const XVector4& a ) const;

        /// <summary>
        ///   Functionality for multiplying two matrices.
        /// </summary>
        /// <param name="a">The matrix to multiply to this matrix.</param>
        /// <returns>The new matrix.</returns>
        XMatrix4x4 operator*( const XMatrix4x4& a ) const;

        /// <summary>
        ///   Functionality for multiplying two matrices with assignment.
        /// </summary>
        /// <param name="a">The matrix to multiply to this matrix.</param>
        /// <returns>A reference to this matrix.</returns>
        const XMatrix4x4& operator*=( const XMatrix4x4& a )
        {
            *this = *this * a;
        }

        /// <summary>
        ///   Gets the translation of this matrix.
        /// </summary>
        /// <param name="Translation">A reference to the translation variable to fill in.</param>
        /// <returns>The reference of the passed in translation.</returns>
        XVector3& GetTranslation( XVector3& Translation ) const
        {
            Translation = _mm_and_ps( m_Matrix[ 3 ], XVector::sm_kxTranslationMask );
            return Translation;
        }

        /// <summary>
        ///   Gets the orientation of this matrix.
        /// </summary>
        /// <param name="Orientation">A reference to the orientation variable to fill in.</param>
        /// <returns>The reference of the passed in orientation.</returns>
        XQuaternion& GetOrientation( XQuaternion& Orientation ) const;

        /// <summary>
        ///   Sets the translation of this matrix.
        /// </summary>
        /// <param name="Translation">A reference to the translation to set this matrix to.</param>
        /// <returns>A reference to this matrix.</returns>
        XMatrix4x4& SetTranslation( const XVector3& Translation )
        {
            ASSERT( ((const __m128)Translation).m128_f32[ 3 ] == 0.0f );
            m_Matrix[ 3 ] = _mm_or_ps( Translation, sm_kxHighOne );
            return *this;
        }

        /// <summary>
        ///   Sets the Orientation of this matrix.
        /// </summary>
        /// <param name="Orientation">A reference to the orientation to set this matrix to.</param>
        /// <returns>A reference to this matrix.</returns>
        XMatrix4x4& SetOrientation( const XQuaternion& Orientation );

        /// <summary>
        ///   Set the inverse of this matrix.
        /// </summary>
        /// <param name="Inverse">The matrix to set as the inverse.</param>
        /// <returns>A reference to the inverse matrix.</returns>
        XMatrix4x4& Inverse( Out XMatrix4x4& Inverse );


    public:

        static const XMatrix4x4 Identity;


    protected:

        static const __m128 sm_kxHighOne;

        __m128  m_Matrix[ 4 ];
    };
}
