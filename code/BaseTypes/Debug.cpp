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

#include "BaseTypes.h"
#include "Debug.h"

#ifdef DEBUG_BUILD

#include <direct.h>
#include <stdio.h>
#include <time.h>

#if defined ( WIN32 ) || defined ( WIN64 )
#define _WIN32_WINNT 0x0400 
#include <windows.h>  // For LPCRITICAL_SECTION
#endif

#define MAX_STRING_LENGTH 2048

// Local data
LogFile s_LogFiles[ LogType::e_LogTypeCount ] = 
{
	{ NULL, "Debug.log",           ""          },
	{ NULL, "Debug_AI.log",        "AI"        },
	{ NULL, "Debug_Animation.log", "Animation" },
	{ NULL, "Debug_Audio.log",     "Audio"     },
	{ NULL, "Debug_Fire.log",      "Fire"      },
	{ NULL, "Debug_Geometry.log",  "Geometry"  },
	{ NULL, "Debug_Graphics.log",  "Graphics"  },
	{ NULL, "Debug_Input.log",     "Input"     },
	{ NULL, "Debug_Physics.log",   "Physics"   },
	{ NULL, "Debug_Smoke.log",     "Smoke"     },
	{ NULL, "Debug_Trees.log",     "Trees"     },
};

COMPILE_ASSERT( sizeof( s_LogFiles ) / sizeof( s_LogFiles[ 0 ] ) == LogType::e_LogTypeCount );

static Debug::Debugger* s_Debugger = NULL;

///////////////////////////////////////////////////////////////////////////////
// Init - Initialize Debug functionality (call once for each dll)
void Debug::Init( Debug::Debugger* p_Debugger )
{
	// Store the pointed to the debugging interface
	s_Debugger = p_Debugger;
}


///////////////////////////////////////////////////////////////////////////////
// Startup - Startup Debug functionality (called once by the application)
void Debug::Startup( Bool bLogging )
{
	// Create instance of debugger interface
	s_Debugger = new Debugger(bLogging);
}


///////////////////////////////////////////////////////////////////////////////
// Shutdown - Shutdown Debug functionality (called once by the appilcation)
void Debug::Shutdown( void )
{
	// Release s_Debugger resources
	if( s_Debugger )
	{
		delete s_Debugger;
		s_Debugger = NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////
// GetDebugger - Return a pointer to the global instance for the Debugger
Debug::Debugger* Debug::GetDebugger( void )
{
	return s_Debugger;
}


///////////////////////////////////////////////////////////////////////////////
// Print - Print a debug string to the output window
void Debug::Print( const char* Format, ... )
{
	va_list ArgList;
	va_start( ArgList, Format );

	s_Debugger->Print( Format, ArgList );

	va_end( ArgList );
}


///////////////////////////////////////////////////////////////////////////////
// Debugger - Constructor for debugger class
Debug::Debugger::Debugger(Bool bLogging)
{
    m_bLogging = bLogging;

#if defined ( WIN32 ) || defined ( WIN64 )
    // Create critical section
    m_CsFileWrite = new CRITICAL_SECTION;
    InitializeCriticalSection( m_CsFileWrite );
#else
    ASSERT( False );  // Only Windows critical sections are supported
#endif

    if(m_bLogging)
    {
	    // Copy the s_LogFiles into the instance
	    memcpy( m_LogFiles, s_LogFiles, sizeof( s_LogFiles ) );

	    // Create a directory with the current timestamp
        // ( Format: Month_Day_HourMinute )
	    time_t Time;
	    time( &Time );

	    tm Date;
	    localtime_s( &Date, &Time );

	    char FolderName[ MAX_STRING_LENGTH ];
	    sprintf_s( FolderName, MAX_STRING_LENGTH, "..\\Logs\\%.2d%.2d%.2d%.2d\\", (Date.tm_mon + 1), Date.tm_mday, Date.tm_hour, Date.tm_min );

	    int Result = _mkdir( FolderName );
        
        ASSERT( Result == 0 );
        if( Result == 0 )
        {
	        // Open all the log files
	        for( u8 Index = 0; Index < LogType::e_LogTypeCount; Index++ )
	        {
		        char FileName[ MAX_STRING_LENGTH ];
		        strncpy_s( FileName, MAX_STRING_LENGTH, FolderName, MAX_STRING_LENGTH - strlen( m_LogFiles[ Index ].FileName ) );
		        strcat_s( FileName, MAX_STRING_LENGTH, m_LogFiles[ Index ].FileName );

		        fopen_s( &m_LogFiles[ Index ].FileHandle, FileName, "w" );
	        }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// Debugger - Destructor for debugger class
Debug::Debugger::~Debugger()
{
#if defined ( WIN32 ) || defined ( WIN64 )
    // Release critical sections
    DeleteCriticalSection( m_CsFileWrite );
    delete m_CsFileWrite;
#endif

    if(m_bLogging)
    {
	    // Close all the log files
	    for( u8 Index = 0; Index < LogType::e_LogTypeCount; Index++ )
	    {
		    fclose( m_LogFiles[ Index ].FileHandle );
	    }
    }
}


///////////////////////////////////////////////////////////////////////////////
// Print - Print a debug string to the output window (actually does output)
void Debug::Debugger::Print( const char* Format, va_list ArgList )
{
#if defined ( WIN32 ) || defined ( WIN64 )
	// Format the string
	char Buffer[ MAX_STRING_LENGTH ];
	vsprintf_s( Buffer, MAX_STRING_LENGTH, Format, ArgList );

	EnterCriticalSection( m_CsFileWrite );

	// Print the string
	OutputDebugStringA( Buffer );

	// Leave the critical section
	LeaveCriticalSection( m_CsFileWrite );
#else
	vsprintf( _Format, Args );
#endif
}


///////////////////////////////////////////////////////////////////////////////
// Log - Logs the given string to the file associated with Type
void Debug::Debugger::Log( LogType::LogType Type, const char* Format, va_list ArgList )
{
    if(!m_bLogging)
        return;

	ASSERT( m_LogFiles[ Type ].FileHandle );

	// Write to the appropriate log file
	vfprintf( m_LogFiles[ Type ].FileHandle, Format, ArgList );
	fflush( m_LogFiles[ Type ].FileHandle );

	// Format the string
	char Buffer[ MAX_STRING_LENGTH ];
	vsprintf_s( Buffer, MAX_STRING_LENGTH, Format, ArgList );
	OutputDebugStringA( Buffer );

	// If this is a system specific log file, also log it to the general log
	if( Type != LogType::e_Debug )
	{
		ASSERT( m_LogFiles[ LogType::e_Debug ].FileHandle );
		
#if defined ( WIN32 ) || defined ( WIN64 )
		// Try to enter the critical section
		u32 Index;
		for( Index = 0; Index < 1000; Index++ )
		{
			if( TryEnterCriticalSection( m_CsFileWrite ) )
			{
				break;
			}
			Sleep(1);
		}

		// If we failed to enter, call the full EnterCriticalSection and wait
		if( Index == 1000 )
		{
			EnterCriticalSection( m_CsFileWrite );
		}
		
		// Print the string
		fprintf_s( m_LogFiles[ LogType::e_Debug ].FileHandle, "[%s] %s", m_LogFiles[ Type ].SystemName, Buffer );
		fflush( m_LogFiles[ LogType::e_Debug ].FileHandle );

		// Leave the critical section
		LeaveCriticalSection( m_CsFileWrite );
#endif
	}
}

#endif
