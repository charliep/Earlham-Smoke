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

// Behavior enumerators are used to index arrays in other parts of the program.
// So keep their values zero-based and incremental.
enum Behavior
{
    e_Behavior_Idle,
    e_Behavior_Walking,
    e_Behavior_Running,
    e_Behavior_Flying,
    e_Behavior_Panicked,
    e_Behavior_None,

    e_Max_Behavior
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>IBehaviorObject</c> is an interface for providing contact related functionality.  Any
///    objects that modify contact data are required to implement this class.  FTW!
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IBehaviorObject
{
public:

	/// <summary>
    /// Gets the current behavior of this object.
	/// </summary>
	/// <returns>Behavior of this object.</returns>
	virtual const Behavior GetBehavior( void ) = 0;
};
