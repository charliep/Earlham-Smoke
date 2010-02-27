<<<<<<< HEAD:code/Smoke.cpp
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

//#include "../BaseTypes/BaseTypes.h"
//#include "../Interfaces/Interface.h"
//#include "../Framework/FrameworkAPI.h"
//#include "../Framework/EnvironmentManager.cpp"
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;


//extern "C" int APIENTRY
int main(int argc, const char** argv)
{
//	USES_CONVERSION;
	
	//int					argc, iArg;

	while ( ( c = getopt( argc, argv, "l::" ) ) != -1 )
	{
		switch(c)
		{
			case 'l':
				bLogging = TRUE;
				if( optarg != NULL )
					logfile = optarg;
				break;
			case '?':
				if( isprint( optopt ) )
					fprintf( stderr, "unknown option '-%c'. \n", optopt );
				else
					fprintf (stderr,
							 "Unknown option character `\\x%x'.\n",
							 optopt);
				return 1;
			default:
				sGdfPath = argv[optind];
		}
	}	
	string	sGdfPath = "Smoke.gdf";
	//bool				bLogging;
	//
    // Start up debug functionality.
    //
	// NOTE: checking the environment will never work, because the Environment hasn't been read yet
    //Bool bLogging = Singletons::EnvironmentManager.Variables().GetAsBool( "Debug::Logging", False );
//	Debug::Startup( bLogging );

    //
    // Call the engine to start execution.
    //
//	EngineExecuteGDF(sGdfPath.c_str());

	//
    // Shutdown debug functionality.
    //
//	Debug::Shutdown();
	cout << "Smoke!!!" << endl;
    return 0;
}
