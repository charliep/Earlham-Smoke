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

//////////////////////////////////////////////////////////////////////////
/// <summary>
///		The System namespace contains meta-data about the various sytems, 
///		and various enums, datatypes and helper functions for system types.
/// </summary>
//////////////////////////////////////////////////////////////////////////
namespace System
{
    enum Components
    {
        System, Scene, Object, Task
    };

	////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		An int enum, used to index the types of systems.
	///		Custom systems do not have predefined types.  Their types are made with
	///		System::Types::MakeCustom(), so they're not listed here.
	/// </summary>
	/// <seealso cref="System::Types::MakeCustom()"/>
	////////////////////////////////////////////////////////////////////////////////////////////////
	enum TypeIndices
	{
		// Standard types
		NotUsed = 0,
		Generic,
		Geometry,
		Graphics,
		PhysicsCollision,
		Audio,
		Input,
		AI,
		Animation,
		Scripting,
		Explosion,
		Water,

		// Custom indices are not fixed, so do not belong here.

		MaxIndex
	};

	//////////////////////////////////////////////////////////////////////////
	/// <summary>
    ///		The Types namespace contains specifics about the system types.
    /// </summary>
	//////////////////////////////////////////////////////////////////////////
    namespace Types
    {

		// A bit mask of the different systems available.  Not all need to be actual
		// systems.  Custom systems can identify themselves by setting their bit in
		// the upper 16-bits, and can use the MakeCustom() function to make a custom
		// type ID.
		static const u32 Null                   = 0;
		static const u32 Generic                = (1 << Generic);
		static const u32 Geometry               = (1 << Geometry);
		static const u32 Graphics               = (1 << Graphics);
		static const u32 PhysicsCollision       = (1 << PhysicsCollision);
		static const u32 Audio                  = (1 << Audio);
		static const u32 Input                  = (1 << Input);
		static const u32 AI                     = (1 << AI);
		static const u32 Animation              = (1 << Animation);
		static const u32 Scripting              = (1 << Scripting);
		static const u32 Explosion		= (1 << Explosion);
		static const u32 Water                  = (1 << System::Water);
		// If you extend this list to add a new system, also update the rest of the type-related
		// lists in this file as well as the PerformanceHints list in the TaskManager.

		// Custom types fit in here.  See MakeCustom().

        static const u32 All                    = static_cast<u32>(-1);
        static const u32 MAX                    = 32;

		//////////////////////////////////////////////////////////////////////////
		/// <summary>
		///		Make a special system type identifier, to be used for a custom type.
		///		The caller must guarantee that there are no collisions.
		/// </summary>
		/// <param name="Index">u32 - Index to use for the custom system ID.</param>
		/// <returns>u32 - Type ID for this custom system.</returns>
		//////////////////////////////////////////////////////////////////////////
        __inline__ u32 MakeCustom( u32 Index )
        {
            return 1 << (16 + Index);
        }

		//////////////////////////////////////////////////////////////////////////
		/// <summary>
		///		Get the index of the system with the given type ID.  Useful for 
		///		looking up indexed properties.
		/// </summary>
		/// <remarks>
		///		This function works on both predefined and custom system type IDs.
		/// </remarks>
		/// <param name="SystemType">u32 - The type ID of a system.</param>
		/// <returns>u32 - Index of this system.</returns>
		//////////////////////////////////////////////////////////////////////////
        __inline__ u32 GetIndex( u32 SystemType )
        {
//xxx First attempt at converting _BitScanForward to g++ compilable code
            u32 Index = All;
	    Index = __builtin_ctz(SystemType);
            //_BitScanForward( (unsigned long*)&Index, SystemType );
            return Index;
        }

        typedef u32 BitMask;
    }
    typedef u32 Type;

	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		Plaintext names for the predefined systems, useful while debugging.
	/// </summary>
	/// <seealso cref="System::Types::DisplayNames"/>
	//////////////////////////////////////////////////////////////////////////
    /*namespace Names
    {
        static pcstr Geometry                   = "Geometry";
        static pcstr Graphics                   = "Graphics";
        static pcstr PhysicsCollision           = "PhysicsCollision";
        static pcstr Audio                      = "Audio";
        static pcstr Input                      = "Input";
        static pcstr AI                         = "AI";
        static pcstr Animation                  = "Animation";
        static pcstr Scripting                  = "Scripting";
		static pcstr Explosion					= "Explosion";
        static pcstr Water                      = "Water";
    }*/

	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		Display names for each system, to be used when describing them in
	///		the UI.
	/// </summary>
	/// <seealso cref="System::Types::Names"/>
	//////////////////////////////////////////////////////////////////////////
/*	namespace DisplayNames
	{
		static pcstr Geometry                   = "Geometry";
		static pcstr Graphics                   = "Graphics";
		static pcstr PhysicsCollision           = "Physics collision";
		static pcstr Audio                      = "Audio";
		static pcstr Input                      = "Input";
		static pcstr AI                         = "AI";
		static pcstr Animation                  = "Animation";
		static pcstr Scripting                  = "Scripting";
		static pcstr Explosion					= "Meteor impact";
		static pcstr Water                      = "Water";
		static pcstr Tree						= "Procedural trees";
		static pcstr Fire						= "Procedural fire";
	}
*/
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///		Defines the different changes as a bit mask that the systems can request for other systems to
    ///		perform.
    ///		Custom changes are not allowed.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Changes
    {
        static const u32 None                   = 0;

        namespace Generic
        {
            static const u32 CreateObject       = (1 <<  0);
            static const u32 DeleteObject       = (1 <<  1);
            static const u32 ExtendObject       = (1 <<  2);
            static const u32 UnextendObject     = (1 <<  3);
            static const u32 All                = CreateObject | DeleteObject | ExtendObject | UnextendObject;
        }

        namespace Physics
        {
            static const u32 Velocity           = (1 << 26);  // Reusing this AI bit
        }

        namespace Geometry
        {
            static const u32 Position           = (1 <<  8);
            static const u32 Orientation        = (1 <<  9);
            static const u32 Scale              = (1 << 10);
            static const u32 All                = Position | Orientation | Scale;
        }

        namespace Graphics
        {
            static const u32 IndexDecl          = (1 << 12);
            static const u32 VertexDecl         = (1 << 13);
            static const u32 IndexBuffer        = (1 << 14);
            static const u32 VertexBuffer       = (1 << 15);
            static const u32 AABB               = (1 << 16);
            static const u32 AllMesh            = IndexDecl | VertexDecl | AABB | IndexBuffer | VertexBuffer;
            static const u32 ParticlesDecl      = (1 << 17);
            static const u32 Particles          = (1 << 18);
            static const u32 AllParticles       = ParticlesDecl | Particles;       
            static const u32 Animation          = (1 << 19);
            static const u32 GUI                = (1 << 20);
            static const u32 All                = AllMesh | AllParticles;
        }

        namespace POI
        {
            static const u32 Area               = (1 << 21);
            static const u32 Contact            = (1 << 22);
            static const u32 Target             = (1 << 23);
            static const u32 Intersection       = (1 << 24);
        }

        namespace AI
        {
            static const u32 Behavior           = (1 << 25);
            static const u32 Velocity           = (1 << 26);
        }

        namespace Input
        {
            static const u32 Firehose           = (1 << 27);
            static const u32 Position           = (1 << 28);
        }

        static const u32 Link                   = (1 << 29);
        static const u32 ParentLink             = (1 << 30);
        static const u32 Custom                 = (static_cast<u32>(1) << 31);

        static const u32 All                    = static_cast<u32>(-1);

        typedef u32 BitMask;
    }
    typedef u32 Change;
}
