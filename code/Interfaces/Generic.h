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
///   <c>IGenericScene</c> is an interface for providing generic scene related functionality.  Any
///    objects that modify scene information are required to implement this class.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IGenericScene
{
public:

    struct CreateObjectData
    {
        pcstr                       pszName;    // The name of the object to create.
        System::Types::BitMask      Types;      // The types to extend this object with.
    };
    typedef std::vector<CreateObjectData> CreateObjectDataArray;
    typedef CreateObjectDataArray::iterator CreateObjectDataArrayIt;
    typedef CreateObjectDataArray::const_iterator CreateObjectDataArrayConstIt;

    typedef std::vector<pcstr> DestroyObjectDataArray;
    typedef DestroyObjectDataArray::iterator DestroyObjectDataArrayIt;
    typedef DestroyObjectDataArray::const_iterator DestroyObjectDataArrayConstIt;

    struct ExtendObjectData
    {
        pcstr                       pszName;    // The name of the object to extend.
        void*                       pUserData;  // User data.
    };
    typedef std::vector<ExtendObjectData> ExtendObjectDataArray;
    typedef ExtendObjectDataArray::iterator ExtendObjectDataArrayIt;
    typedef ExtendObjectDataArray::const_iterator ExtendObjectDataArrayConstIt;

    typedef std::vector<pcstr> UnextendObjectDataArray;
    typedef UnextendObjectDataArray::iterator UnextendObjectDataArrayIt;
    typedef UnextendObjectDataArray::const_iterator UnextendObjectDataArrayConstIt;

    /// <summary>
    ///   Returns the creation data of all the universal objects to create.
    /// </summary>
    /// <param name="apszNames">A reference to an array to fill in with the creation data.</param>
    virtual void GetCreateObjects( CreateObjectDataArray& apszNames ) = 0;

    /// <summary>
    ///   Returns the names of all the universal objects to destroy.
    /// </summary>
    /// <param name="apszNames">A reference to an array to fill in with the names.</param>
    virtual void GetDestroyObjects( DestroyObjectDataArray& apszNames ) = 0;

    /// <summary>
    ///   Returns the names of all the universal objects to extend.
    /// </summary>
    /// <param name="apszNames">A reference to an array to fill in with the names.</param>
    virtual void GetExtendObjects( ExtendObjectDataArray& apszNames ) = 0;

    /// <summary>
    ///   Returns the names of all the universal objects to unextend.
    /// </summary>
    /// <param name="apszNames">A reference to an array to fill in with the names.</param>
    virtual void GetUnextendObjects( UnextendObjectDataArray& apszNames ) = 0;

    /// <summary>
    ///   Returns the universal object extension.
    /// </summary>
    /// <param name="pszName">The name of the universal object to extend.</param>
	/// <param name="pUserData">Pointer to user data for this call.</param>
    /// <returns>A pointer to the new system object extension.</returns>
    virtual ISystemObject* ExtendObject( pcstr pszName, void* pUserData ) = 0;

    /// <summary>
    ///   Informs the ISystemScene of the object extension being removed.
    /// </summary>
    /// <param name="pszName">The name of the universal object to unextend.</param>
    /// <returns>A pointer to the system object extension to remove.</returns>
    virtual ISystemObject* UnextendObject( pcstr pszName ) = 0;
};
