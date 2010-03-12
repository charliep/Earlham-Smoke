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

class ISystemTask;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>ITaskManager</c> is an interface class for linking ISystemTasks to a TaskManager
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class ITaskManager
{
public:

    /// <summary cref="ITaskManager::JobFunction">
	/// This type defines the callback used for generic jobs by the <c>ITaskManager</c>.
    /// </summary>
    typedef void ( *JobFunction )( void* );
	/// <summary cref="ITaskManager::JobCompletionFunction">
	/// This type defines the callback used for generic job completions by the <c>ITaskManager</c>.
    /// </summary>
	/// <returns>the number of jobs issued by this function</returns>
    typedef u32 ( *JobCompletionFunction )( void* );  // return number of jobs added

    typedef void ( *ParallelForFunction )( void* param, u32 begin, u32 end );

	/// <summary cref="ITaskManager::NonStandardPerThreadCallback">
    /// This method triggers a synchronized callback to be called once by each thread used by the <c>ITaskManager</c>.
    /// This method which should only be called during initialization and shutdown of 
	/// the <c>ITaskManager</c>.  This method waits until all callbacks have executed.
    /// </summary>
    /// <param name="pfnCallback">the function callback to execute</param>
    /// <param name="pData">a pointer to data that is passed to the callback</param>
    virtual void NonStandardPerThreadCallback( JobFunction pfnCallback, void* pData ) = 0;

    /// <summary cref="ITaskManager::JobCountInstructionHints">
	/// This type provides hints to the <c>GetRecommendedJobCount</c> method on the type of work
	/// about to be submitted to the <c>ITaskManager</c>.
    /// </summary>
	/// <seealso cref="ITaskManager::GetRecommendedJobCount"/>
    enum JobCountInstructionHints
    {
        None, Generic, FP, SIMD_FP, SIMD_INT
    };

    /// <summary cref="ITaskManager::GetRecommendedJobCount">
	/// Call this method to determine the ideal number of tasks to submit to the <c>ITaskManager</c>
	/// for maximum performance.
    /// </summary>
	/// <param name="Hints">guidance on the type of work done in the jobs about to be submitted</param>
	/// <returns>the number of jobs which is optimal for the type of work specified by <paramref name="Hints"/>
	/// </returns>
	virtual u32 GetRecommendedJobCount( JobCountInstructionHints Hints=None ) = 0;
	
	/// <summary cref="ITaskManager::SetNumberOfThreads">
	/// This method constrains the number of threads used by the <c>ITaskManager</c>.
    /// </summary>
	/// <param name="uNumberOfThreads">the limit of the number of threads to use</param>
	virtual void SetNumberOfThreads( u32 uNumberOfThreads )=0;

    virtual void ParallelFor( ISystemTask* pSystemTask,
                              ParallelForFunction pfnJobFunction, void* pParam, u32 begin, u32 end, u32 minGrain = 1 ) = 0;
};
