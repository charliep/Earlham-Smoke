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
///   A spin wait object class similar to a critcal section.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SpinWait
{
    friend class Lock;

public:

    /// <summary>
    ///   Constructor.
    /// </summary>
    SpinWait( void );

    /// <summary>
    ///   Destructor.
    /// </summary>
    ~SpinWait( void );


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   A class for locking a spin wait object.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class Lock
    {
    public:

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <remarks>
        ///   Locks the spin wait object.
        /// </remarks>
        /// <param name="sw">The spin wait object to lock.</param>
        /// <param name="bReadOnly">Signifies if the lock is for reading,
        ///                         or for reading and writing.</param>
        Lock( SpinWait& sw, Bool bReadOnly=False );

        /// <summary>
        ///   Constructor.
        /// </summary>
        /// <remarks>
        ///   Unlocks the spin wait object.  So when the class goes out of scope the spin wait is
        //     released.
        /// </remarks>
        ~Lock( void );

        /// <summary>
        ///   This is a dummy assignment operator.  This class cannot be assigned.
        /// </summary>
        Lock& operator=( const Lock& l )
        {
            UNREFERENCED_PARAM( l );
            ASSERTMSG( False, "This class cannot be assigned." );
        }


    protected:

        SpinWait&       m_SpinWait;
    };


protected:

    u32  m_Lock[ 8 ];
};
