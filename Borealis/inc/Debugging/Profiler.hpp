/******************************************************************************/
/*!
\file		Profiler.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 10, 2024
\brief		Declares the classes for profiling tools

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#define ENGINE_PROFILE 1

#ifndef PROFILER_HPP
#define PROFILER_HPP

#define CONCATENATE_IMPL(a, b) a##b
#define CONCATENATE(a, b) CONCATENATE_IMPL(a, b)

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
#include <glm/glm.hpp>
namespace Borealis
{

	struct mySourceLocationData
	{
		const char* name;
		const char* function;
		const char* file;
		uint32_t line;
		uint32_t color;
	};

	class TracyProfiler {
	public:
		// Default constructor
		TracyProfiler() = delete;

		// Method to record a custom plot value
		static void recordPlot(const char* plotName, float value);

		// Method to log a message in the profiler
		static void logMessage(const char* message);

		// Method to log a colored message in the profiler
		static void logMessageColored(const char* message, const glm::vec4& color);

		// Methods for memory allocation tracking
		static void trackAllocation(void* ptr, size_t size);
		static void trackFree(void* ptr);
		static void trackSecureAllocation(void* ptr, size_t size);
		static void trackSecureFree(void* ptr);

		// Mark the frame boundary
		static void markFrame(const char* frameName = nullptr);
		static void markFrameStart(const char* frameName = nullptr);
		static void markFrameEnd(const char* frameName = nullptr);

		//Application information
		static void sendAppInfo(const char* message);

		// Method to start a custom profiling zone
		static void startZone(const mySourceLocationData* srcLoc);

		// Destructor that ends the profiling zone
		~TracyProfiler();

		static uint32_t vec4ToColor(const glm::vec4& color);

	private:
		// Disable copying
		TracyProfiler(const TracyProfiler&) = delete;
		TracyProfiler& operator=(const TracyProfiler&) = delete;
	};


}

// Macros for profiling
#if ENGINE_PROFILE
#define PROFILE_START(name) ::Borealis::TracyProfiler::markFrameStart(name)
#define PROFILE_END() ::Borealis::TracyProfiler::markFrameEnd()
#define PROFILE_SCOPE(name) static mySourceLocationData CONCATENATE(__source_location,__LINE__){ name, __FUNCTION__, __FILE__ , (uint32_t)__LINE__, 0 }; \
::Borealis::TracyProfiler::startZone(&CONCATENATE(__source_location,__LINE__));
#define PROFILE_FUNCTION() static mySourceLocationData CONCATENATE(__source_location,__LINE__){ nullptr, __FUNCTION__, __FILE__ , (uint32_t)__LINE__, 0 }; \
::Borealis::TracyProfiler::startZone(&CONCATENATE(__source_location,__LINE__));
#else
#define PROFILE_START(name, filepath) 
#define PROFILE_END() 
#define PROFILE_FUNCTION()
#define PROFILE_SCOPE(name)
#endif

#endif