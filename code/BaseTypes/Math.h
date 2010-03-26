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

#include <math.h>

#define MIN(x,y) ( ( (x) < (y) ) ? (x) : (y) )
#define MAX(x,y) ( ( (x) > (y) ) ? (x) : (y) )

namespace Math
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides some functionality for dealing with angles.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class Angle
    {
    public:

        static float Deg2Rad( f32 Degrees )
        {
            return Degrees * (Pi / 180.0f);
        }

        static f32 Sin( f32 Rad )
        {
            return sin( Rad );
        }

        static f32 Cos( f32 Rad )
        {
            return cos( Rad );
        }

        static f32 Tan( f32 Rad )
        {
            return tan( Rad );
        }

        static f32 ASin( f32 Rad )
        {
            return asin( Rad );
        }

        static f32 ACos( f32 Rad )
        {
            return acos( Rad );
        }

        static f32 ATan( f32 Rad )
        {
            return atan( Rad );
        }


    public:

        static const f32 Pi;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality of a 2D vector.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Vector2
    {
        static const Vector2 Zero;
        static const Vector2 One;

        f32             x;
        f32             y;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality of a 3D vector.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Vector3
    {
        //
        // Common constants.
        //
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;

        /// <summary>
        ///   Provides a cast to a f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the matrix array.</returns>
        operator f32*( void )
        {
            return &x;
        }

        /// <summary>
        ///   Provides a cast to a constant f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the constant matrix array.</returns>
        operator const f32*( void ) const
        {
            return &x;
        }

        /// <summary>
        ///   Functionality for adding two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to add to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector3& operator+=( const Vector3& Vector )
        {
            x += Vector.x;
            y += Vector.y;
            z += Vector.z;
            return *this;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to subtract from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector3& operator-=( const Vector3& Vector )
        {
            x -= Vector.x;
            y -= Vector.y;
            z -= Vector.z;
            return *this;
        }

        /// <summary>
        ///   Functionality for doing a straight multipy between two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector3& operator*=( Vector3 Vector )
        {
            x *= Vector.x;
            y *= Vector.y;
            z *= Vector.z;
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector3& operator*=( f32 Scalar )
        {
            x *= Scalar;
            y *= Scalar;
            z *= Scalar;
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector3& operator/=( f32 Scalar )
        {
            if ( Scalar != 0.0f )
            {
                f32 Inv = 1.0f / Scalar;
                x *= Inv;
                y *= Inv;
                z *= Inv;
            }
            else
            {
                x = y = z = 0.0f;
            }
            return *this;
        }

        /// <summary>
        ///   Functionality for adding two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to add to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector3 operator+( const Vector3& Vector ) const
        {
            Vector3 v(x + Vector.x, y + Vector.y, z + Vector.z);
            return v;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to subtract from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector3 operator-( const Vector3& Vector ) const
        {
            Vector3 v(x - Vector.x, y - Vector.y, z - Vector.z);
            return v;
        }


        //Vector3 operator/(const f32 &v)const
        //{
        //    return Vector3(*this) /= v;
        //}

        //Vector3 operator*(const f32 &v)const
        //{
        //    return Vector3(*this) *= v;
        //}

        /// <summary>
        ///   unary minus.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>The new negative vector created by this operation.</returns>
        Vector3 operator-( ) const
        {
            return Vector3(-x, -y,-z);
        }

        /// <summary>
        ///   Functionality for doing a straight multipy between two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector3 operator*( Vector3 Vector ) const
        {
            Vector3 v(x * Vector.x, y * Vector.y, z * Vector.z);
            return v;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector3 operator*( f32 Scalar ) const
        {
            Vector3 v(x * Scalar, y * Scalar, z * Scalar);
            return v;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector3 operator/( f32 Scalar ) const
        {
            Vector3 v = Zero;

            if ( Scalar != 0.0f )
            {
                f32 Inv = 1.0f / Scalar;
                v.x = x * Inv;
                v.y = y * Inv;
                v.z = z * Inv;
            }

            return v;
        }

        /// <summary>
        ///   Functionality for equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator==( const Math::Vector3& a ) const
        {
            return (x == a.x) && (y == a.y) && (z == a.z);
        }

        /// <summary>
        ///   Functionality for not equals.
        /// </summary>
        /// <param name="a">The vector to compare to this vector.</param>
        /// <returns>The result of the comparison.</returns>
        bool operator!=( const Math::Vector3& a ) const
        {
			return (x != a.x) || (y != a.y) || (z != a.z);
        }

        /// <summary>
        ///   Returns the magnitude of the vector.
        /// </summary>
        /// <returns>The magnitude of the vector.</returns>
        f32 Magnitude( void ) const
        {
            return sqrtf( x*x + y*y + z*z );
        }

        /// <summary>
        ///   Normalizes this vector.
        /// </summary>
        /// <returns>A refrence to this vector.</returns>
        const Vector3& Normalize( void )
        {
            f32 Mag = Magnitude();

            if ( Mag != 0.0f )
            {
                f32 Inv = 1.0f / Mag;
                x *= Inv;
                y *= Inv;
                z *= Inv;
            }

            return *this;
        }

        /// <summary>
        ///   Returns the dot product of 2 vectors.
        /// </summary>
        /// <param name="a">The other vector.</param>
        /// <returns>The dot product.</returns>
        f32 Dot( const Vector3& a ) const
        {
            return x * a.x + y * a.y + z*a.z;
        }

        /// <summary>
        ///   Returns the cross product of 2 vectors.
        /// </summary>
        /// <param name="a">The other vector.</param>
        /// <returns>The cross product.</returns>
        Vector3 Cross( const Vector3& a ) const
        {
            Vector3 r( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
            return r;
        }


        /// <summary>
        ///   Construct a vector from 3 floats
        /// </summary>
        /// <param name="_x">the x value.</param>
        /// <param name="_y">the y value.</param>
        /// <param name="_z">the z value.</param>
        /// <returns>The constructed vector3.</returns>
        Vector3(f32 _x, f32 _y, f32 _z )
        {
            x = _x;
            y = _y;
            z = _z;
        }

        /// <summary>
        ///   Construct a vector from one float
        /// </summary>
        /// <param name="_v">the value to use for x, y and z.</param>
        /// <returns>The constructed Vector3.</returns>
        Vector3(f32 _v)
        {
            x = y = z = _v;
        }


        /// <summary>
        ///   Construct an uninitialized vector
        /// </summary>
        /// <returns>The constructed Vector3.</returns>
        Vector3()
        {
        }

        f32             x;
        f32             y;
        f32             z;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality of a 3D vector with a modifier.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Vector4
    {
        //
        // Common constants.
        //
        static const Vector4 Zero;
        static const Vector4 One;

        /// <summary>
        ///   Provides a cast to a f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the matrix array.</returns>
        operator f32*( void )
        {
            return &x;
        }

        /// <summary>
        ///   Provides a cast to a constant f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the constant matrix array.</returns>
        operator const f32*( void ) const
        {
            return &x;
        }

        /// <summary>
        ///   Functionality for adding two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to add to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector4& operator+=( const Vector4& Vector )
        {
            x += Vector.x;
            y += Vector.y;
            z += Vector.z;
            w += Vector.w;
            return *this;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to subtract from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector4& operator-=( const Vector4& Vector )
        {
            x -= Vector.x;
            y -= Vector.y;
            z -= Vector.z;
            w -= Vector.w;
            return *this;
        }

        /// <summary>
        ///   Functionality for a straight multiply between two vectors with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector4& operator*=( Vector4 Vector )
        {
            x *= Vector.x;
            y *= Vector.y;
            z *= Vector.z;
            w *= Vector.w;
            return *this;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to multiply to this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector4& operator*=( f32 Scalar )
        {
            x *= Scalar;
            y *= Scalar;
            z *= Scalar;
            w *= Scalar;
            return *this;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to divide from this vector.</param>
        /// <returns>A reference to this vector.</returns>
        Vector4& operator/=( f32 Scalar )
        {
            if ( Scalar != 0.0f )
            {
                f32 Inv = 1.0f / Scalar;
                x *= Inv;
                y *= Inv;
                z *= Inv;
                w *= Inv;
            }
            else
            {
                x = y = z = w = 0.0f;
            }
            return *this;
        }

        /// <summary>
        ///   Functionality for adding two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to add to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector4 operator+( const Vector4& Vector ) const
        {
            Vector4 v = { x + Vector.x, y + Vector.y, z + Vector.z, w + Vector.w };
            return v;
        }

        /// <summary>
        ///   Functionality for subtracting two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to subtract from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector4 operator-( const Vector4& Vector ) const
        {
            Vector4 v = { x - Vector.x, y - Vector.y, z - Vector.z, w - Vector.w };
            return v;
       }

        /// <summary>
        ///   Functionality for a straight multiply between two vectors.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Vector">The vector to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector4 operator*( Vector4 Vector ) const
        {
            Vector4 v = { x * Vector.x, y * Vector.y, z * Vector.z, w * Vector.w };
            return v;
        }

        /// <summary>
        ///   Functionality for multiplying a vector with a scalar.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to multiply to this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector4 operator*( f32 Scalar ) const
        {
            Vector4 v = { x * Scalar, y * Scalar, z * Scalar, w * Scalar };
            return v;
        }

        /// <summary>
        ///   Functionality for dividing a vector with a scalar.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Scalar">The scalar to divide from this vector.</param>
        /// <returns>The new vector created by this operation.</returns>
        Vector4 operator/( f32 Scalar ) const
        {
            Vector4 r = Zero;
            
            if ( Scalar != 0.0f )
            {
                f32 Inv = 1.0f / Scalar;
                r.x = x * Inv;
                r.y = y * Inv;
                r.z = z * Inv;
                r.w = w * Inv;
            }

            return r;
        }

        f32             x;
        f32             y;
        f32             z;
        f32             w;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality for a quanternion.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Quaternion
    {
        //
        // Common constants.
        //
        static const Quaternion Zero;

		/// <summary>
        ///   Functionality for adding two quaternions.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="a">The quaternion to add to this quaternion.</param>
        /// <returns>The new quaternion created by this operation.</returns>
        Quaternion operator+( const Quaternion& a ) const
        {
            Quaternion r = { x + a.x, y + a.y, z + a.z, w + a.w };
            return r;
        }

		/// <summary>
        ///   Functionality for subtracting two quaternions.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="a">The quaternion to subtract from this quaternion.</param>
        /// <returns>The new quaternion created by this operation.</returns>
        Quaternion operator-( const Quaternion& a ) const
        {
            Quaternion r = { x - a.x, y - a.y, z - a.z, w - a.w };
            return r;
        }

        /// <summary>
        ///   Functionality for multiplying two quaternions.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="a">The quaternion to multiply to this quaterion.</param>
        /// <returns>The new quaternion.</returns>
        Quaternion operator*( Quaternion& a ) const
        {
            Quaternion r;
            r.x = w * a.x + x * a.w + y * a.z - z * a.y;
            r.y = w * a.y + y * a.w + z * a.x - x * a.z;
            r.z = w * a.z + z * a.w + x * a.y - y * a.x;
            r.w = w * a.w - x * a.x - y * a.y - z * a.z;
            return r;
        }

        /// <summary>
        ///   Functionality for multiplying two quaternions with assignment.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="a">The quaternion to multiply to this quaterion.</param>
        /// <returns>A reference to this quaternion.</returns>
        Quaternion& operator*=( Quaternion& a )
        {
            Quaternion r;
            r.x = w * a.x + x * a.w + y * a.z - z * a.y;
            r.y = w * a.y + y * a.w + z * a.x - x * a.z;
            r.z = w * a.z + z * a.w + x * a.y - y * a.x;
            r.w = w * a.w - x * a.x - y * a.y - z * a.z;
            *this = r;
            return *this;
        }

        /// <summary>
        ///   Sets a quaternion using rotation axis and angle.
        /// </summary>
        /// <param name="Axis">The normalized vector axis."</param>
        /// <param name="Angle">The angle of the vector axis."</param>
        /// <returns>A reference to this quaternion.</returns>
        const Quaternion& Set( In Math::Vector3& Axis, In f32 Angle );

        /// <summary>
        ///   Sets a quaternion using Euler angles.
        /// </summary>
        /// <param name="Angles">The Euler angles for the quaternion."</param>
        /// <returns>A reference to this quaternion.</returns>
        const Quaternion& Set( In Math::Vector3& Angles );

		/// <summary>
        ///   Sets a quaternion using Euler angles.
        /// </summary>
        /// <param name="RotationX">The rotation around X in radians."</param>
		/// <param name="RotationY">The rotation around Y in radians."</param>
		/// <param name="RotationZ">The rotation around Z in radians."</param>
        /// <returns>A reference to this quaternion.</returns>
        const Quaternion& Set( In f32 RotationX, In f32 RotationY, In f32 RotationZ )
		{
			Vector3 Angles(RotationX, RotationY, RotationZ );
			return Set( Angles );
		}

        /// <summary>
        ///   Calculates the magnitude of this quaternion.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>The magnitude.</returns>
        f32 Magnitude( void )
        {
            return sqrtf( x*x + y*y + z*z + w*w );
        }

        /// <summary>
        ///   Calculates the conjugate or inverse of a quaternion.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        void Conjugate( void )
        {
            x = -x;
            y = -y;
            z = -z;
        }

        /// <summary>
        ///   Calculates the conjugate or inverse of a quaternion.
        /// </summary>
        /// <param name="r">The quaternion to set as the inverse of this quaternion.</param>
        /// <remarks>Inlined for performance.</remarks>
        void Conjugate( Quaternion& r )
        {
            r.x = -x;
            r.y = -y;
            r.z = -z;
            r.w = w;
        }

		/// <summary>
        ///   Rotates the given vector by this quaternion.
        /// </summary>
        /// <param name="a ">The vector to be rotated by this this quaternion.</param>
        /// <remarks>Inlined for performance.</remarks>
        void Rotate( Vector3& a );

        f32             x;
        f32             y;
        f32             z;
        f32             w;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Row major implementation of a 4x4 matrix.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Matrix4x4
    {
        //
        // Common constants.
        //
        static const Matrix4x4 Identity;

        /// <summary>
        ///   Vector matrix multiplication.
        /// </summary>
        /// <param name="a">The vector to multiply to this matrix.</param>
        /// <returns>The new vector.</returns>
        Vector3 operator*( In Vector3& a ) const;

        /// <summary>
        ///   Vector matrix multiplication.
        /// </summary>
        /// <param name="a">The vector to multiply to this matrix.</param>
        /// <returns>The new vector.</returns>
        Vector4 operator*( In Vector4& a ) const;

        /// <summary>
        ///   Functionality for multiplying two matrices.
        /// </summary>
        /// <param name="a">The matrix to multiply to this matrix.</param>
        /// <returns>The new matrix.</returns>
        Matrix4x4 operator*( In Matrix4x4& a ) const;

        /// <summary>
        ///   Functionality for multiplying two matrices with assignment.
        /// </summary>
        /// <param name="a">The matrix to multiply to this matrix.</param>
        /// <returns>A reference to this matrix.</returns>
        const Matrix4x4& operator*=( In Matrix4x4& a );

        /// <summary>
        ///   Makes this matrix a transformation matrix based on the translation and orientation
        ///    passed in.
        /// </summary>
        /// <param name="Translation">The translation for the matrix.</param>
        /// <param name="Orientation">The orientation for the matrix.</param>
        /// <returns>A reference to this matrix.</returns>
        const Matrix4x4& Transformation( const Vector3& Translation,
                                         const Quaternion& Orientation );

        /// <summary>
        ///   Gets the translation of this matrix.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A reference to the translation.</returns>
        const Vector3& GetTranslation( void ) const
        {
            return *reinterpret_cast<const Vector3*>(m+12);
        };

        /// <summary>
        ///   Gets the orientation of this matrix.
        /// </summary>
        /// <param name="Orientation">A reference to the orientation variable to fill in.</param>
        void GetOrientation( Quaternion& Orientation ) const;

        /// <summary>
        ///   Sets the translation of this matrix.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <param name="Translation">A reference to the translation to set this matrix to.</param>
        /// <returns>A reference to this matrix.</returns>
        const Matrix4x4& SetTranslation( const Vector3& Translation )
        {
            *reinterpret_cast<Vector3*>(m+12) = Translation;
            return *this;
        }

        /// <summary>
        ///   Sets the Orientation of this matrix.
        /// </summary>
        /// <param name="Orientation">A reference to the orientation to set this matrix to.</param>
        /// <returns>A reference to this matrix.</returns>
        const Matrix4x4& SetOrientation( const Quaternion& Orientation );

        /// <summary>
        ///   Set the transpose of this matrix.
        /// </summary>
        /// <param name="Transpose">The matrix to set as the transpose.</param>
        /// <returns>A reference to the transpose matrix.</returns>
        const Matrix4x4& Transpose( Out Matrix4x4& Transpose);

        /// <summary>
        ///   Set the inverse of this matrix.
        /// </summary>
        /// <param name="Inverse">The matrix to set as the inverse.</param>
        /// <returns>A reference to the inverse matrix.</returns>
        const Matrix4x4& Inverse( Out Matrix4x4& Inverse );

        /// <summary>
        ///   calulates a cofactor for a 3x3 matrix.
        /// </summary>
        /// <param name="a">Input a.</param>
        /// <param name="b">Input b.</param>
        /// <param name="c">Input c.</param>
        /// <param name="d">Input d.</param>
		/// <returns>Calculates a Cofactor4</returns>
        f32 Cofactor4(f32 a, f32 b, f32 c, f32 d);

        /// <summary>
        ///   calulates a cofactor for a 4x4 matrix or determinent of a 3x3 matrix.
        /// </summary>
		/// <param name="a">Input a.</param>
		/// <param name="b">Input b.</param>
		/// <param name="c">Input c.</param>
		/// <param name="d">Input d.</param>
		/// <param name="e">Input e.</param>
		/// <param name="f">Input f.</param>
		/// <param name="g">Input g.</param>
		/// <param name="h">Input h.</param>
		/// <param name="i">Input i.</param>
        /// <returns>Calculates a Cofactor9</returns>
        f32 Cofactor9(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i);

        /// <summary>
        ///   Provides a cast to a f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the matrix array.</returns>
        operator f32*( void )
        {
            return m;
        }

        /// <summary>
        ///   Provides a cast to a f32 pointer.
        /// </summary>
        /// <remarks>Inlined for performance.</remarks>
        /// <returns>A pointer to the constant matrix array.</returns>
        operator const f32*( void ) const
        {
            return m;
        }

        f32 m[ 16 ];
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality for a BGR color vector.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Color3
    {
        static const Color3 Black;
        static const Color3 White;

        f32             r;
        f32             g;
        f32             b;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality for a BGRA color vector.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Color4
    {
        static const Color4 Black;
        static const Color4 White;

        f32             b;
        f32             g;
        f32             r;
        f32             a;
    };


	// Min/Max for f32
	inline f32 Min( f32 x, f32 y ) { return ( x < y ) ? x : y; }
	inline f32 Max( f32 x, f32 y ) { return ( x > y ) ? x : y; }
	
	inline f32 Floor( f32 x ) { return floor( x ); }

	// Min/Max for Vector3
	inline Vector3 Min( Math::Vector3& x, Math::Vector3& y ) { return ( x.Magnitude() < y.Magnitude() ) ? x : y; }
	inline Vector3 Max( Math::Vector3& x, Math::Vector3& y ) { return ( x.Magnitude() > y.Magnitude() ) ? x : y; }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Provides the functionality for generic methods.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    struct Random
    {
        static f32 GetRandomFloat(float a, float b);
    };
}
