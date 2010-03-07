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

#define True						        1
#define False						        0


#define NULL						        0


#if defined( _MSC_VER )
#if defined( _WIN64 )
#define W64SAFE
#else
#define W64SAFE __w64
#endif
#endif


// TODO: make a better SAFE_DELETE for debug mode for interacting with the memory manager
#define SAFE_DELETE( p )			        if ((p)!=NULL){delete (p); (p)=NULL;}
#define SAFE_DELETE_ARRAY( p )		        if ((p)!=NULL){delete [] (p); (p)=NULL;}


#define UNREFERENCED_PARAM(P)               (P)
#define DBG_UNREFERENCED_PARAM(P)           (P)
#define DBG_UNREFERENCED_LOCAL_VAR(V)       (V)


#if defined( _MSC_VER )
#define In                                  __in const
#define Out                                 __out
#define InOut                               __inout
#else
#define In                                  const
#define Out
#define InOut
#endif


#define COMPILEMSGSTR2( s )                 #s
#define COMPILEMSGSTR( s )                  COMPILEMSGSTR2( s )
#define COMPILEMSGLOC                       __FILE__ "(" COMPILEMSGSTR( __LINE__ ) ") : message: "

#define COMPILE_ASSERT( e )                typedef char __FILE____LINE__[ (e) ? 1 : -1 ]
