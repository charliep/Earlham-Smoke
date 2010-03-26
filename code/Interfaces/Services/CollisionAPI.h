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

//
// core includes
//
#include "../../BaseTypes/BaseTypes.h"
#include <string.h>

// Collision Data Types
namespace Coll
{
	// Collision Handle
	typedef u32 Handle;
	static const Handle InvalidHandle = u32(-1);

	// Collision Test Types
	enum Type
	{
		e_None,
		e_LineTest,

		e_Invalid
	};

	enum Flags
	{
		e_Defaults     = 0x00000000,  // No flags set (use defaults)
		e_Ground       = 0x00000001,  // Only test against the ground
		e_IgnoreGround = 0x00000002  // Exclude the ground from tests
	};

	// Collision Request
	struct Request
	{
		Math::Vector3 m_Position0;  // Start position of the test
		Math::Vector3 m_Position1;  // End position of the test
		Type          m_Type;       // Type of test
		Handle        m_Handle;     // Unique handle for this request
		pcstr         m_Ignore;     // Name of object to ignore in collision
		Flags         m_Flags;      // Flags (see Coll::Flags)

		Request() { memset( this, 0, sizeof( this ) ); }
		void SetIgnore( pcstr Ignore ) { m_Ignore = Ignore; }
		void SetFlags( Coll::Flags Flags ) { m_Flags = Flags; }
	};

	// Collision Result
	struct Result
	{
		Math::Vector3 m_Position;   // Contact position
		Math::Vector3 m_Normal;     // Normal vector (vector pernedicular to contact surface)
		pcstr         m_Hit;        // Name of object hit (null is no collision detected)
		f32           m_Depth;      // Penetration depth (along normal vector)
		u32           m_Finalized;  // Collision test has finished (0 = no, 1 = yes, >1 = delete)
		Bool          m_Valid;      // A valid collision was detected
	};
}
