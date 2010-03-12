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
///   An interface for getting and setting information about the environment.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IEnvironment
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   An interface for environment variable functionality.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class IVariables
    {
    public:

        /// <summary>
        ///   Returns the environment variable value as a string.
        /// </summary>
        /// <param name="pszName">The name of the variable.</param>
        /// <param name="pszDefaultValue">The value returned if the variable doesn't exist.</param>
        /// <returns>The value of the variable.</returns>
        virtual pcstr GetAsString( In pcstr pszName, In pcstr pszDefaultValue="" ) = 0;

        /// <summary>
        ///   Compares the environment variable against a string, returning True if equal.
        /// </summary>
        /// <param name="pszName">The name of the variable.</param>
        /// <param name="pszCompareValue">The value to compare against.</param>
        /// <returns>True if the variable exists and is equal to pszCompareValue, False otherwise.</returns>
        virtual Bool IsString( In pcstr pszName, In pcstr pszCompareValue ) = 0;

        /// <summary>
        ///   Returns the environment variable value as a bool.
        /// </summary>
        /// <param name="pszName">The name of the variable.</param>
        /// <param name="bDefaultValue">The value returned if the variable doesn't exist.</param>
        /// <returns>The value of the variable.</returns>
        virtual Bool GetAsBool( In pcstr pszName, In Bool bDefaultValue=False ) = 0;

        /// <summary>
        ///   Returns the environment variable value as an int.
        /// </summary>
        /// <param name="pszName">The name of the variable.</param>
        /// <param name="DefaultValue">The value returned if the variable doesn't exist.</param>
        /// <returns>The value of the variable.</returns>
        virtual i32 GetAsInt( In pcstr pszName, In i32 DefaultValue=0 ) = 0;

        /// <summary>
        ///   Returns the environment variable value as a float.
        /// </summary>
        /// <param name="pszName">The name of the variable.</param>
        /// <param name="DefaultValue">The value returned if the variable doesn't exist.</param>
        /// <returns>The value of the variable.</returns>
        virtual f32 GetAsFloat( In pcstr pszName, In f32 DefaultValue=0.0f ) = 0;

        /// <summary>
        ///   Sets new value for environment variable.
        /// </summary>
        /// <param name="pszName">The name of the variable</param>
        /// <param name="pszValue">The new value for the variable</param>
        virtual void SetValue( In pcstr pszName, In pcstr pszValue ) = 0;

    };

    /// <summary>
    ///   Returns a reference to the variables class for access to its functionality.
    /// </summary>
    /// <returns>A reference to the variables class.</returns>
    virtual IVariables& Variables( void ) = 0;


    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   An interface for environment runtime functionality.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class IRuntime
    {
    public:

        enum Status
        {
            Unknown, Running, Paused, NextScene, Quit
        };

        /// <summary>
        ///   Returns the status of execution.
        /// </summary>
        /// <returns>The execution status.</returns>
        virtual Status GetStatus( void ) = 0;

        /// <summary>
        ///   Sets the status of execution.
        /// </summary>
        /// <param name="Status">The execution status.</param>
        virtual void SetStatus( Status Status ) = 0;
    };

    /// <summary>
    ///   Returns a reference to the runtime class for access to its functionality.
    /// </summary>
    /// <returns>A reference to the runtime class.</returns>
    virtual IRuntime& Runtime( void ) = 0;
};
