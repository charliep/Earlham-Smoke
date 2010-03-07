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


#ifdef ASSERT
#undef ASSERT
#endif


#if defined( _DEBUG )
#define _ASSERTX( c )                       (void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, #c )) || \
                                                    (__debugbreak(), 0))
#define _ASSERTMSGX( c, m )                 (void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, m )) || \
                                                    (__debugbreak(), 0))
#define _ASSERTMSG1X( c, m, p1 )            (void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, m, p1 )) || \
                                                    (__debugbreak(), 0))
#define _ASSERTMSG2X( c, m, p1, p2 )        (void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, m, p1, p2 )) || \
                                                    (__debugbreak(), 0))
#define _ASSERTMSG3X( c, m, p1, p2, p3 )    (void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, m, p1, p2, p3 )) || \
                                                    (__debugbreak(), 0))
#define _ASSERTMSG4X( c, m, p1, p2, p3, p4 )(void) ((!!(c)) || \
                                                    (1 != _CrtDbgReport( _CRT_ASSERT, __FILE__, __LINE__, NULL, m, p1, p2, p3, p4 )) || \
                                                    (__debugbreak(), 0))

#define ASSERT( c )                         _ASSERTX( c )
#define ASSERTMSG( c, m )                   _ASSERTMSGX( c, m )
#define ASSERTMSG1( c, m, p1 )              _ASSERTMSG1X( c, m, p1 )
#define ASSERTMSG2( c, m, p1, p2 )          _ASSERTMSG2X( c, m, p1, p2 )
#define ASSERTMSG3( c, m, p1, p2, p3 )      _ASSERTMSG3X( c, m, p1, p2, p3 )
#define ASSERTMSG4( c, m, p1, p2, p3, p4 )  _ASSERTMSG4X( c, m, p1, p2, p3, p4 )
#else
#define ASSERT( c )
#define ASSERTMSG( c, m )
#define ASSERTMSG1( c, m, p1 )
#define ASSERTMSG2( c, m, p1, p2 )
#define ASSERTMSG3( c, m, p1, p2, p3 )
#define ASSERTMSG4( c, m, p1, p2, p3, p4 )
#endif
