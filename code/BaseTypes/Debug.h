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

#include <stdarg.h>

//#ifdef _DEBUG
#define DEBUG_BUILD
//#endif

#define LOG_ACTUAL( x ) va_list ArgList;                                   \
	                    va_start( ArgList, Format );                       \
						Debug::GetDebugger()->Log( (x), Format, ArgList ); \
						va_end( ArgList );

// Forward declares
struct _RTL_CRITICAL_SECTION;
typedef _RTL_CRITICAL_SECTION* PRTL_CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

// Data structure for log files
struct LogFile
{
    FILE* FileHandle;
    char* FileName;
    char* SystemName;
};


// Types of log files
namespace LogType {
    enum LogType
    {
        e_Debug,

        e_AI,
        e_Animation,
        e_Audio,
        e_Fire,
        e_Geometry,
        e_Graphics,
        e_Input,
        e_Physics,
        e_Smoke,
        e_Trees,

        e_LogTypeCount,

        e_Invalid
    };
}

// Debugging Functionality
namespace Debug
{
	class Debugger
	{
	private:
        Bool m_bLogging;
        LogFile m_LogFiles[ LogType::e_LogTypeCount ];

		#if defined ( WIN32 ) || defined ( WIN64 )
		LPCRITICAL_SECTION m_CsFileWrite;  // Critical section for writing to logs
		#endif

	public:
		Debugger(Bool bLogging);
		~Debugger();
		void Print( const char* Format, va_list ArgList );
        void Log( LogType::LogType Type, const char* Format, va_list ArgList );
	};

#ifdef DEBUG_BUILD
	
	void Init( Debug::Debugger* p_Debugger );
	void Startup( Bool bLogging = False );
	void Shutdown( void );

	Debug::Debugger* GetDebugger( void );

	void Print( const char* Format, ... );

	inline void Log( const char* Format, ... )          { LOG_ACTUAL( LogType::e_Debug );     }
	inline void LogAI( const char* Format, ... )        { LOG_ACTUAL( LogType::e_AI );        }
	inline void LogAnimation( const char* Format, ... ) { LOG_ACTUAL( LogType::e_Animation ); }
	inline void LogAudio( const char* Format, ... )     { LOG_ACTUAL( LogType::e_Audio );     }
	inline void LogFire( const char* Format, ... )      { LOG_ACTUAL( LogType::e_Fire );      }
	inline void LogGeometry( const char* Format, ... )  { LOG_ACTUAL( LogType::e_Geometry );  }
	inline void LogGraphics( const char* Format, ... )  { LOG_ACTUAL( LogType::e_Graphics );  }
	inline void LogInput( const char* Format, ... )     { LOG_ACTUAL( LogType::e_Input );     }
	inline void LogPhysics( const char* Format, ... )   { LOG_ACTUAL( LogType::e_Physics );   }
	inline void LogSmoke( const char* Format, ... )     { LOG_ACTUAL( LogType::e_Smoke );     }
	inline void LogTrees( const char* Format, ... )     { LOG_ACTUAL( LogType::e_Trees );     } 

#else  // Debugging disable, all functions will in inline and empty (aka removed)
	
	inline void Init( Debug::Debugger* p_Debugger ){};
	inline void Startup( Bool bLogging = False ){};
	inline void Shutdown( void ){};

	inline Debug::Debugger* GetDebugger( void ){ return NULL; };

	inline void Print( const char* Format, ... ){};

	inline void Log( const char* Format, ... ){};
	inline void LogAI( const char* Format, ... ){};
	inline void LogAnimation( const char* Format, ... ){};
	inline void LogAudio( const char* Format, ... ){};
	inline void LogFire( const char* Format, ... ){};
	inline void LogGeometry( const char* Format, ... ){};
	inline void LogGraphics( const char* Format, ... ){};
	inline void LogInput( const char* Format, ... ){};
	inline void LogPhysics( const char* Format, ... ){};
	inline void LogSmoke( const char* Format, ... ){};
	inline void LogTrees( const char* Format, ... ){}; 

#endif
}
