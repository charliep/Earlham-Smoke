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

class ISubject;
class IObserver;
class IChangeManager;

#include "Interface.h"


// THREAD SAFETY NOTE
//
// Affects CSubject class implementation
//
// Currently there are no concurrent initial attach or detach operations on subject 
// objects. Thus corresponding locking operations (protecting the integrity of 
// the observers list) are disabled.
//
// It is not recommended to introduce concurrency of this sort, because it not only
// would result in additional performance impact to _all_ operations with subject
// (including frequent PostChanges), but also would introduce the risk of deadlocks
// (implementation of the Change Control Manager will have to be carefully revised).
// Most probably eliminating the deadlocks threat will further increase the overhead.
// One of the ways to avoid deadlock is posting change notifications (ChangeOccured)
// after the lock is released, but this would require ref counting on the IObserver
// interface.
// 
// Yet concurrent _repeated_ attaches (updating interest bits for already registered 
// CCM observer) are possible, so the protection against race conditions introduced
// by them must always be in place. 
#define SUPPORT_CONCURRENT_ATTACH_DETACH_TO_SUBJECTS 0


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   The <c>IObserver</c> interface supplies loosely coupling systems with dependency.  It
///    facilitates a lazy behaviour where by systems only need to react to a change and facilitates
///    dependent callback threading.
/// <para>
///   This interface follows the pattern commonly know as the Observer pattern,
///    the Publish/Subscribe pattern, or the Dependents pattern.
/// </para>
/// <seealso cref="ISubject"/>
/// <seealso cref="IChangeManager"/>
/// </summary>
/// <remarks>
///   The Observer pattern is documented in "Design Patterns," written by Erich Gamma et. al.,
///    published by Addison-Wesley in 1995.
/// </remarks>
/////////////////////////////////////////////////////////////////////////////////////////////////

class IObserver
{
public:
    // All interfaces must have virtual destructors
    virtual ~IObserver () {}

    /// <summary>
    ///   Lets the ISubject notify the IObserver in changes in registered aspects of interest.
    /// </summary>
    /// <remarks> This method is typically called from 	IChangeManager::DistributeQueuedChanges() or 
    ///		ISubject::PostChanges() depending on whether the observer registered with an IChangeManager 
    ///		or an ISubject respectively.	
    ///  </remarks>
    /// <param name="pSubject">  A pointer to the ISubject interface of the component that 
    ///  changed.</param>
    /// <param name="ChangeType"> The aspects of interest that changed as defined by the supplied 
    ///        ISubject's published interest bits.  
    ///        if uInChangeBits are 0, then the subject is shutting down, and should be released. 
    ///	</param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInSubject was NULL.
    ///     Error::OutOfMemory                                   
    ///			Not enough memory is available to resolve the change.
    ///</returns>
    virtual Error ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   The <c>ISubject</c> interface supplies loosely coupling systems with dependency
///       It facilitates a lazy behaviour where by systems only need to react to a change
///		  and facilitates dependent callback threading.      
/// </summary>
/// <remarks>
///    Related interfaces: \n IObserver\n IChangeManager       
/// </remarks>
/// <remarks>
///    This interface follows the pattern commonly know as the Observer
///	   pattern, the Publish/Subscribe pattern, or the Dependents pattern. 
/// </remarks>
/// <remarks>
///    The Observer pattern is documented in "Design Patterns," written by
///	   Erich Gamma et. al., published by Addison-Wesley in 1995.          
/// </remarks>
/////////////////////////////////////////////////////////////////////////////////////////////////

class ISubject
{
public:
    // All interfaces must have virtual destructors
    virtual ~ISubject () {}

    /// <summary>
    ///  Associates the provided IObserver with the given ISubject aspects of interest.
    /// </summary>
    /// <remarks>
    ///  This method is typically called from @e ChangeManager::Register()
    ///  or the IObserver, if used without a ChangeManager.             
    ///  </remarks>
    /// <param name="pInObserver"> A pointer to the IObserver.</param>
    /// <param name="uInIntrestBits"> The aspects of interest that changed as defined by the supplied
    ///				ISubject's published interest bits.</param>
    /// <param name="uID"> ID assigned by pInObserver to this subject.</param>
    /// <param name="shiftBits">Used for components supporting multiply inherited interfaces each
    ///				with subject interfaces.</param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///     Error::OutOfMemory                                   
    ///			Not enough memory is available to resolve the change.
    ///</returns>
    virtual Error Attach( IObserver* pInObserver, u32 uInIntrestBits, u32 uID, u32 shiftBits=0 ) = 0;

    /// <summary>
    ///  Disassociates the provided Observer with the Subject
    /// </summary>
    /// <remarks>
    ///  This method is typically called from @e ChangeManager::Register()
    ///  or the IObserver, if used without a ChangeManager.             
    ///  </remarks>
    /// <param name="pInObserver"> A pointer to the IObserver that should be disassociated.</param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///</returns>
    virtual Error Detach( IObserver* pInObserver ) = 0;

    virtual Error UpdateInterestBits( IObserver* pInObserver, u32 uInIntrestBits ) = 0;

    /// <summary>
    ///  Returns the ID assigned by pObserver to this subject
    /// </summary>
    virtual u32 GetID ( IObserver* pObserver ) const = 0;

    /// <summary>
    ///  Publishes to attached Observers and ChanageManager that changes have occurred.
    /// </summary>
    /// <remarks>
    ///  This method is typically called from @e ChangeManager::Register()
    ///  or the IObserver, if used without a ChangeManager.             
    ///  </remarks>
    /// <param name="uInChangedBits"> TThe u32 bit field that describes the conceptual change with 
    ///				 respect to the published interests.
    /// </param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///</returns>
	virtual void PostChanges( System::Changes::BitMask uInChangedBits ) = 0;

    /// <summary>
    ///   Identifies the system changes that this subject could possibly make.
    /// </summary>
    /// <returns>A bitmask of the possible system changes.</returns>
    virtual System::Changes::BitMask GetPotentialSystemChanges( void ) = 0;

    /// <summary>
    ///  Forces the Destruction 
    /// </summary>
    /// <remarks>
    ///	            
    ///  </remarks>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///</returns>
    virtual void PreDestruct( void ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   The <c>IObserver</c> interface supplies loosely coupling systems with dependency
///       It facilitates a lazy behaviour where by systems only need to react to a change
///		  and facilitates dependent callback threading.      
/// </summary>
/// <remarks>
///    Related interfaces: \n ISubject \n IObserver       
/// </remarks>
/// <remarks>
///    This interface follows the pattern commonly know as the Observer
///	   pattern, the Publish/Subscribe pattern, or the Dependents pattern. 
/// </remarks>
/// <remarks>
///    The Observer pattern is documented in "Design Patterns," written by
///	   Erich Gamma et. al., published by Addison-Wesley in 1995.          
/// </remarks>
/////////////////////////////////////////////////////////////////////////////////////////////////

class IChangeManager : public IObserver 
{
public:

    /// <summary>
    ///  Associates the provided IObserver with the given ISubject aspects of interest.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="pInSubject">A pointer to the ISubject.</param>
    /// <param name="uInIntrestBits">The aspects of interest that changed as defined by the supplied 
    ///				ISubject's published interest bits..</param>
    /// <param name="pInObserver">A pointer to the IObserver.</param>
	/// <param name="observerIdBits">Bitmask of the interest bits. (default = System::Types::All)</param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///     Error::OutOfMemory                                   
    ///			Not enough memory is available to resolve the change.
    ///</returns>
	virtual Error Register( ISubject* pInSubject, u32 uInIntrestBits, IObserver* pInObserver, System::Types::BitMask observerIdBits = System::Types::All ) = 0;
    
    /// <summary>
    ///   Disassociates the provided IObserver from the supplied ISubject.
    /// </summary>
    /// <remarks>
    /// </remarks>
    /// <param name="pInSubject">A pointer to the ISubject.</param>
    /// <param name="pInObserver">A pointer to the IObserver.</param>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///</returns>
    virtual Error Unregister( ISubject* pInSubject, IObserver* pInObserver ) = 0; 

    /// <summary>
    ///  Distributes the queued changes..
    /// </summary>
    /// <remarks>
    ///	 Intended to be called after all ISubject's have changed state to 
    ///	 deliver relevant queued change notifications to registered 
    ///	 IObservers via. IObserver::Update().
    /// </remarks>
    /// <returns>One of the following Error codes:
    ///     Error::Success
    ///			No error.
    ///     Error::InvalidAddress 
    ///			pInObserver and/or pInSubject was NULL.
    ///     Error::OutOfMemory
    ///			Not enough memory is available to resolve the change.
    ///</returns>
    virtual Error DistributeQueuedChanges( System::Types::BitMask systems2BeNotified = System::Types::All,
                                           System::Changes::BitMask ChangesToDist = System::Changes::All ) = 0;
    
};


class CSubject : public ISubject 
{
public :
    static const u32 InvalidID = u32(-1);

    CSubject( void );
    ~CSubject( void );

    // attaches an observer to this subject
    virtual Error Attach( IObserver* pObserver, u32 Interest, u32 nID, u32 Shift=0 );

    // removes an observer 
    virtual Error Detach( IObserver* pObserver );

    virtual Error UpdateInterestBits( IObserver* pInObserver, u32 uInIntrestBits );

    virtual u32 GetID ( IObserver* pObserver ) const;

    // the observers will get update calls when the 
    // subject state the observer is interested in changes
    virtual void PostChanges( System::Changes::BitMask changedBits );

    void PreDestruct( void );

protected:

    /// <summary>
    ///   Defines a structure used by the subject to store information about observers
    ///   for PostChanges notifications (CCMs).
    /// </summary>
    struct ObserverRequest
    {
        ObserverRequest(
            IObserver* pObserver = NULL,
            u32 Interests = 0,
            u32 myID = 0
            )
            : m_pObserver( pObserver )
            , m_interestBits( Interests )
            , m_myID( myID )
        {
        }

        IObserver*  m_pObserver;
        u32         m_interestBits;
        u32         m_myID;

        bool operator == ( IObserver* rhs ) const
        {
            return m_pObserver == rhs;
        }
    }; // struct CSubject::ObserverRequest


private:

    // IMPLEMENTATION NOTE
    // Since only Change Control Managers (CCM) are supposed to subscribe for 
    // notifications sent by PostChange, there are not many observers expected 
    // to be in the list. Another assumption is that repeated attaches are infrequent.
    // Thus the most frequent operation is the traversal and thus the usual std::list
    // will suit fine here.
    typedef std::list<ObserverRequest> ObserverList;

    // List of the observers (CCMs) that need notifications about changes in this subject 
    ObserverList    m_observerList;

#if SUPPORT_CONCURRENT_ATTACH_DETACH_TO_SUBJECTS
    // Synchronization object to protect m_observerList
    SpinWait        m_observerListMutex;
#endif /* SUPPORT_MULTIPLE_OBSERVERS_IN_POST_CHANGES */

    friend u32 GetBitsToPost( ObserverRequest&, System::Changes::BitMask );
};
