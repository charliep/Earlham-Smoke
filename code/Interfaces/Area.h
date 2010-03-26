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
///   <c>IAreaObject</c> is an interface for providing Area related functionality.  Any
///    objects that modify or provide Area data are required to implement this class.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IAreaObject
{
public:
    enum AreaType
    {
        e_Fire,
        e_Zombie,
        
        e_None
    };

    /// <summary>
    ///   Returns the axis-aligned bounding box for the area.
    /// </summary>
    /// <param name="Min">The returned minimum AABB point.</param>
    /// <param name="Max">The returned maximum AABB point.</param>
	virtual void GetAreaBB( Out Math::Vector3& Min, Out Math::Vector3& Max ) = 0;

    /// <summary>
    ///   Returns the name to id this area.
    /// </summary>
	virtual pcstr GetAreaName( void ) = 0;

    /// <summary>
    ///   Returns the type of the area.
    /// </summary>
	virtual AreaType GetAreaType( void ) = 0;

    /// <summary>
    ///   Return True if this ares is active (i.e. the area has been triggered).
    /// </summary>
	virtual Bool IsAreaActive( void ) = 0;  
};
