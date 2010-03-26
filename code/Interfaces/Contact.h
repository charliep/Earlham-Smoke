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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>IContactObject</c> is an interface for providing contact related functionality.
///    Any objects that modify contact data are required to implement this class.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IContactObject
{
public:

    /// <summary>
    ///   Structure for providing Contact information.
    /// </summary>
    struct Info
    {
		Math::Vector3 m_VelocityObjectA;
		Math::Vector3 m_VelocityObjectB;
		Math::Vector3 m_Normal;
        Math::Vector3 m_Position;
        f32           m_Impact;
        Bool          m_Static;
    };

    /// <summary>
    ///   Returns the Contact information.
    /// </summary>
    /// <returns>Data describing the last contact for this object.</returns>
    virtual const Info* GetContact( void ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>IIntersectionObject</c> is an interface for providing intersection related functionality.
///    Any objects that modify contact data are required to implement this class.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IIntersectionObject
{
public:

    /// <summary>
    ///   Structure for providing Intersection information.
    /// </summary>
    struct Info
    {
        pcstr               pszName;
        Math::Vector3       Position;
        Math::Quaternion    Orientation;
        Math::Vector3       LinearVelocity;
        Math::Vector3       AngularVelocity;
        Math::Vector3       AABBMin;
        Math::Vector3       AABBMax;
    };
    typedef std::vector<Info>           InfoArray;
    typedef InfoArray::const_iterator   InfoArrayIt;

    /// <summary>
    ///   Returns the Intersection information.
    /// </summary>
    /// <returns>An constant array of the Intersection information.</returns>
    virtual const InfoArray& GetIntersections( void ) = 0;
};
