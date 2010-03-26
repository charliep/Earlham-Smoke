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

#include "Synchronization.h"


#define USE_TBB_SPIN_MUTEX 1


#if USE_SPIN_MUTEX || USE_TBB_SPIN_MUTEX

    #if USE_TBB_SPIN_MUTEX

        #if !defined(__PLATFORM_MANAGER)
            #include <tbb/spin_mutex.h>
        #endif

        #define SmokeSpinMutex              tbb::spin_mutex
        #define SmokeSpinMutexScopedLock    tbb::spin_mutex::scoped_lock

    #else /* !USE_TBB_SPIN_MUTEX */

        #define SmokeSpinMutex              SpinWait
        #define SmokeSpinMutexScopedLock    SpinWait::Lock

    #endif /* !USE_TBB_SPIN_MUTEX */

    #define DEFINE_SPIN_MUTEX(mutex)             SmokeSpinMutex mutex
    #define DECLARE_STATIC_SPIN_MUTEX(mutex)     static SmokeSpinMutex mutex

    #define SCOPED_SPIN_LOCK(mutex)              SmokeSpinMutexScopedLock _lock(mutex)
    #define SCOPED_SPIN_LOCK_BEGIN(mutex)        { SmokeSpinMutexScopedLock _lock(mutex)
    #define SCOPED_SPIN_LOCK_END()               }

#else /* !USE_SPIN_MUTEX */

    #define DEFINE_SPIN_MUTEX(mutex)
    #define DECLARE_STATIC_SPIN_MUTEX(mutex)

    #define SCOPED_SPIN_LOCK(mutex)
    #define SCOPED_SPIN_LOCK_BEGIN(mutex)
    #define SCOPED_SPIN_LOCK_END()

#endif /* !USE_SPIN_MUTEX */


