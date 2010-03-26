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

#define _WIN32_WINNT  0x0403 // required for InitializeCriticalSectionAndSpinCount

#include <windows.h>
#include "BaseTypes.h"
#include "Synchronization.h"


SpinWait::SpinWait(
    void
    )
{
    // IMPLEMENTATION NOTE
    // In cases when there is no oversubscription the reasonable value of the spin 
    // count would be 50000 - 100000 (25 - 50 microseconds on modern CPUs).
    // Unfortunately the spinning in Windows critical section is power inefficient
    // so the value is a traditional 1000 (approx. the cost of kernel mode transition)
    //
    // To achieve maximal locking efficiency use TBB spin_mutex (which employs 
    // exponential backoff technique, and supports cooperative behavior in case 
    // of oversubscription)
    Bool Result = ::InitializeCriticalSectionAndSpinCount( reinterpret_cast<LPCRITICAL_SECTION>(m_Lock), 1000 );
    
    ASSERT( Result );
    UNREFERENCED_PARAM( Result ); // For Release build (prevent warning)
}


SpinWait::~SpinWait(
    void
    )
{
    ::DeleteCriticalSection( reinterpret_cast<LPCRITICAL_SECTION>(m_Lock) );
}


SpinWait::Lock::Lock(
    SpinWait& sw,
    Bool bReadOnly
    )
    : m_SpinWait( sw )
{
    DBG_UNREFERENCED_PARAM( bReadOnly );

    ::EnterCriticalSection( reinterpret_cast<LPCRITICAL_SECTION>(m_SpinWait.m_Lock) );
}


SpinWait::Lock::~Lock(
    void
    )
{
    ::LeaveCriticalSection( reinterpret_cast<LPCRITICAL_SECTION>(m_SpinWait.m_Lock) );
}
