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

//
// forward declarations
//
class ISystemObject;

//
// service api
//
#include "Services/CollisionAPI.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   Interface class for providing services to the systems.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IService
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Interface class for providing access to other systems' ISystem, ISystemScene, and
    ///    ISystemObject.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class ISystemAccess
    {
    public:

        /// <summary>
        ///   Gets a system by its name.
        /// </summary>
        /// <param name="pszSystemName">The name of the system to get.</param>
        /// <returns>A handle to the system or null if the system doesn't exist.</returns>
        virtual Handle GetSystem( pcstr pszSystemName ) = 0;

        /// <summary>
        ///   Gets a system by its type.
        /// </summary>
        /// <param name="Type">The type of the system to get.</param>
        /// <returns>A handle to the system or null if the system doesn't exist.</returns>
        virtual Handle GetSystem( System::Type Type ) = 0;

        /// <summary>
        ///   Gets a system scene by its system name.
        /// </summary>
        /// <param name="pszSystemName">The name of the system scene to get.</param>
        /// <returns>A handle to the system scene or null if it doesn't exist.</returns>
        virtual Handle GetScene( pcstr pszSystemName ) = 0;

        /// <summary>
        ///   Gets a system scene by its system type.
        /// </summary>
        /// <param name="Type">The type of the system scene to get.</param>
        /// <returns>A handle to the system scene or null if it doesn't exist.</returns>
        virtual Handle GetScene( System::Type Type ) = 0;

        /// <summary>
        ///   Gets a system object by its system name.
        /// </summary>
        /// <param name="pszSystemName">The name of the system object to get.</param>
        /// <param name="pszName">The name of the object.</param>
        /// <returns>A handle to the system object or null if it doesn't exist.</returns>
        virtual Handle GetSystemObject( pcstr pszSystemName, pcstr pszName ) = 0;

        /// <summary>
        ///   Gets a system object by its system type and name.
        /// </summary>
        /// <param name="Type">The type of the system object to get.</param>
		/// <param name="pszName">Name of the object.</param>
        /// <returns>A handle to the system object or null if it doesn't exist.</returns>
        virtual Handle GetSystemObject( System::Type Type, pcstr pszName ) = 0;

        /// <summary>
        ///   Gets a single system property.
        /// </summary>
        /// <param name="hSystem">The handle of the system.</param>
        /// <param name="Property">The property to store the data in.  The name of the property
        ///  must be set prior to entering this function.</param>
        virtual void GetSystemProperty( Handle hSystem, InOut Properties::Property& Property ) = 0;

        /// <summary>
        ///   Sets a single system property.
        /// </summary>
        /// <param name="hSystem">The handle of the system.</param>
        /// <param name="Property">The property to containing the property data.  This must be
        ///  properly filled in prior to calling this function.</param>
        virtual void SetSystemProperty( Handle hSystem, In Properties::Property& Property ) = 0;

        /// <summary>
        ///   Gets a single system scene property.
        /// </summary>
        /// <param name="hScene">The handle of the system scene.</param>
        /// <param name="Property">The property to store the data in.  The name of the property
        ///  must be set prior to entering this function.</param>
        virtual void GetSceneProperty( Handle hScene, InOut Properties::Property& Property ) = 0;

        /// <summary>
        ///   Sets a single system scene property.
        /// </summary>
        /// <param name="hScene">The handle of the system scene.</param>
        /// <param name="Property">The property to containing the property data.  This must be
        ///  properly filled in prior to calling this function.</param>
        virtual void SetSceneProperty( Handle hScene, In Properties::Property& Property ) = 0;

        /// <summary>
        ///   Gets a single object property.
        /// </summary>
        /// <param name="hObject">The handle of the system object.</param>
        /// <param name="Property">The property to store the data in.  The name of the property
        ///  must be set prior to entering this function.</param>
        virtual void GetObjectProperty( Handle hObject, InOut Properties::Property& Property ) = 0;

        /// <summary>
        ///   Sets a single object property.
        /// </summary>
        /// <param name="hObject">The handle of the system object.</param>
        /// <param name="Property">The property to containing the property data.  This must be
        ///  properly filled in prior to calling this function.</param>
        virtual void SetObjectProperty( Handle hObject, In Properties::Property& Property ) = 0;
    };

    /// <summary>
    ///   Gets a reference to the ISystemAccess class.
    /// </summary>
    /// <returns>A reference to the ICollision class.</returns>
    virtual ISystemAccess& SystemAccess( void ) = 0;

    /// <summary>
    ///   Used by a system/framework to register itself as a provider for ISystemAccess.
    /// </summary>
    /// <param name="pSystemAccess">A pointer to the provider to register.</param>
    virtual void RegisterSystemAccessProvider( ISystemAccess* pSystemAccess ) = 0;

    /// <summary>
    ///   Used by a system/framework to de-register itself as a provider for ISystemAccess.
    /// </summary>
    /// <param name="pSystemAccess">A pointer to the provider to de-register.</param>
    virtual void UnregisterSystemAccessProvider( ISystemAccess* pSystemAccess ) = 0;



    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    ///   Interface class for providing collision tests to the systems.
    /// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class ICollision
    {
    public:
		/// <summary>
        ///   Requests a collision test.
        /// </summary>
        /// <param name="Request">Collision request.</param>
        /// <returns>A handle used to get the results.</returns>
		virtual Coll::Handle Test( const Coll::Request& Request ) = 0;

		/// <summary>
        ///   Requests a collision line test.
        /// </summary>
		/// <param name="Position0">Vector position to start test.</param>
		/// <param name="Position1">Vector position to end test.</param>
        /// <param name="Request">Collision request.</param>
        /// <returns>A handle used to get the results.</returns>
		virtual Coll::Handle LineTest( const Math::Vector3& Position0, const Math::Vector3& Position1, Coll::Request& Request ) = 0;

		/// <summary>
        ///   Gets results for the given handle.
        /// </summary>
        /// <param name="Handle">Collision test handle.</param>
		/// <param name="Result">Pointer to structure to be filled with results.</param>
        /// <returns>Returns True if test has finished.</returns>
		virtual Bool Finalize( Coll::Handle Handle, Coll::Result* Result ) = 0;
    };

    /// <summary>
    ///   Gets a reference to the ICollision class.
    /// </summary>
    /// <returns>A reference to the ICollision class.</returns>
    virtual ICollision& Collision( void ) = 0;

    /// <summary>
    ///   Used by a system/framework to register itself as a provider for ICollision.
    /// </summary>
    /// <param name="pCollision">A pointer to the provider to register.</param>
    virtual void RegisterCollisionProvider( ICollision* pCollision ) = 0;

    /// <summary>
    ///   Used by a system/framework to de-register itself as a provider for ICollision.
    /// </summary>
    /// <param name="pCollision">A pointer to the provider to de-register.</param>
    virtual void UnregisterCollisionProvider( ICollision* pCollision ) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///   Instrumentation interface, to let various pieces of code touch the instrumentation.
	/// </summary>
    ////////////////////////////////////////////////////////////////////////////////////////////////

	class IInstrumentation
	{
	public:
		/// <summary cref="IInstrumentation::UpdatePeriodicData">
		///		This function drives the instrumentation; it's called regularly from
		///		the scheduler in the framework, to let the instrumentation know that another
		///		frame has elapsed.  Whenever it is called, this function will make sure that
		///		the cached stats used by the instrumentation are up to date; if they've gotten
		///		too old, it will refresh those stats.
		/// </summary>
		/// <param name="deltaTime">f32 - Elapsed wall-clock time since the last call to this function.</param>
		virtual void UpdatePeriodicData( f32 deltaTime ) = 0;
		
		/// <summary cref=IInstrumentation::getCPUCount>
		///		Get the number of available CPUs in the system, including physical and logical CPUs.
		/// </summary>
		/// <returns>i32 - Number of available CPUs in the system.</returns>
		virtual i32 getCPUCount( ) = 0;

		/// <summary cref=IInstrumentation::getNumCounters>
		///		Get the number of CPU performance counters that we're using.  There will be one for
		///		each available CPU, and one more for the total.
		/// </summary>
		/// <returns>i32 - Number of CPU performance counters, which will be returned by the getCPUCounters call.</returns>
		virtual i32 getNumCounters( ) = 0;

		/// <summary cref=IInstrumentation::getCPUCounters>
		///		Get the most recently measured CPU counters.  This value is automatically refreshed.
		/// </summary>
		/// <param name="CPUCounters">
		///		f64* - Array, filled by this call, of CPU counters showing percent CPU load.
		///		Must be big enough to hold all counters, see Instrumentation::getNumCounters().
		/// </param>
		virtual void getCPUCounters( f64* CPUCounters ) = 0;

		/// <summary cref=IInstrumentation::getCurrentFPS>
		///		Get the most recently-measured frame rate (in Frames Per Second).  This value is
		///		automatically refreshed.  It is averaged over the last few frames (defined by the
		///		update interval in this class).
		/// </summary>
		/// <returns>f32 - Frame rate, in frames per second.</returns>
		virtual f32	 getCurrentFPS( ) = 0;

		/// <summary cref=IInstrumentation::setActiveThreadCount>
		///		Set the number of threads the application will now run.
		/// </summary>
		/// <param name="activeThreadCount">i32 - Number of active threads the app should use now.</param>
		virtual void setActiveThreadCount( i32 activeThreadCount ) = 0;

		/// <summary cref=IInstrumentation::getActiveThreadCount>
		///		Get the number of threads that we're currently using in this application.
		/// </summary>
		/// <returns>i32 - Current active thread count.</returns>
		virtual i32 getActiveThreadCount( ) = 0;

		/// <summary cref=IInstrumentation::CaptureJobCounterTicks>
		///		Called when some job has finished.  Keep track of how much time this job has spent in this frame.
		///		There may be many jobs of one type passed in during a single frame; their results will be appended.
		/// </summary>
		/// <param name="jobType">u32 - The type of the job that has just completed; a member of System::Types.</param>
		/// <param name="jobCounterTicks">i64 - The number of clock ticks, from _RDTSC, that this job used during this frame.</param>
		virtual void CaptureJobCounterTicks( u32 jobType, i64 jobCounterTicks ) = 0;

		/// <summary cref=IInstrumentation::getJobCount>
		///		Get the max number of job types possible in the system, so the caller can allocate the right sized array.
		/// </summary>
		/// <returns>i32 - Max number of job types.</returns>
		virtual i32 getJobCount() = 0;

		/// <summary cref=IInstrumentation::getJobRatios>
		///		Get the ratios of job work done in this most recent frame.
		/// </summary>
		/// <param name="jobRatios">
		///		f32* - Array that this function should fill with the ratios of time spent in each workload on this frame.
		///		Must be the right length; call getJobCount.
		/// </param>
		virtual void getJobRatios( f32* jobRatios ) = 0;

	};

	/// <summary>
	///   Get the instrumentation interface.
	/// </summary>
	virtual IInstrumentation& Instrumentation( void ) = 0;

	/// <summary>
	///   Register the given instrumentation object as the global provider.
	///   Call this once during startup.
	/// </summary>
	/// <param name="pInstrumentation">IInstrumentation* - Instrumentation object to register.</param>
	virtual void RegisterInstrumentationProvider( IInstrumentation* pInstrumentation ) = 0;
	
	/// <summary>
	///   Unregister the given instrumentation object as the global provider.
	///   Call this once during shutdown.
	/// </summary>
	/// <param name="pInstrumentation">IInstrumentation* - Instrumentation object to unregister.</param>
	virtual void UnregisterInstrumentationProvider( IInstrumentation* pInstrumentation ) = 0;
};
