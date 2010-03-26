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
///   An interface for accessing platform specific functionality for things like the OS and
///    processor.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IPlatform
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   An interface for accessing processor information.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class IProcessor
    {
    public:
        /// <summary>
        ///   Returns the number of processors available for this process.
        /// </summary>
        /// <returns>The processor count.</returns>
        virtual u32 GetNumProcessors( void ) = 0;

        /// <summary>
        ///   Sets the calling threads affinity to the specified processor.
        /// </summary>
        /// <param name="ProcessorNumber">The processor number to set the affinity to.</param>
        virtual void AffinitizeThreadToProcessor( u32 ProcessorNumber ) = 0;
    };

    /// <summary>
    ///   Gets a reference to the IProcessor class.
    /// </summary>
    /// <returns>A reference to the IProcessor class.</returns>
    virtual IProcessor& Processor( void ) = 0;
};
