//E_Smoke.cpp
//Created by Gilbert Bailey on 2/26/10.
 
// Copyright � 2008-2009 Intel Corporation
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


#include <tchar.h>

#include "../BaseTypes/BaseTypes.h"
#include "../Interfaces/Interface.h"
#include "../Framework/FrameworkAPI.h"
#include "../Framework/EnvironmentManager.cpp"

#include <atlbase.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char **argv )
{
	int          c;
	bool         bLogging = FALSE;
	char         *logfile = "logdefault.txt";
	std::string  sGdfPath = "Smoke.gdf"
	
	
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
	
	return 0;
}