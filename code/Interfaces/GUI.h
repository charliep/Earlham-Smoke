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
// Any object that wants to provide gui data must implement this interface.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// These are flags for which data is being modified
//
#define WINDOW_SHOW    0x0001  // Show or hide window
#define WINDOW_DATA    0x0002  // New data point
#define WINDOW_NAME    0x0004  // Name of window to modify
#define WINDOW_CAPTION 0x0008  // New caption text
#define WINDOW_BODY    0x0010  // New body text
#define WINDOW_ALL     0xFFFF  // Everything changed
#define WINDOW_NONE    0x0000  // No Changes

/// <summary>
/// Structure containing all data that might update an Ogre GUI window.
/// Flags dictate which fields are used; not all are used at once.
/// </summary>
typedef struct {
	std::string sName;       // name of the window we are modifying
	u32         nFlags;      // which data is being modified
	bool        bShow;       // show or hide the window
	f32         nDataPoint;  // add a new data point to a chart window 
	std::string sCaption;    // text of caption
	std::string sBody;       // text of body
} WindowData;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   Any object that wants to provide gui data must implement this interface.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IGUIObject
{
public:

	/// <summary>
    /// Gets the data for the window.
	/// </summary>
	/// <returns>A constant pointer to the window data.</returns>
	virtual const WindowData* GetWindowData(void) = 0;
};