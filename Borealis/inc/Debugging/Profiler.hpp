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


#define ENGINE_PROFILE 0

#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
namespace Borealis
{
	struct ProfileResult
	{
		std::string mName; // Name of the profile
		long long mStart, mEnd; // Start and end time of the profile
		size_t mThreadID; // Thread ID of the profile
	};

	struct InstrumentationScope 
	{
		std::string mName; // Name of the scope
	};

	class Instrumentor
	{
	public:

		/*!***********************************************************************
			\brief
				Default constructor for the Instrumentor class
		*************************************************************************/
		Instrumentor() : mScope(nullptr), mProfileCount(0) {}

		/*!***********************************************************************
			\brief
				Starts the instrumentation process
			\param[in] name
				The name of the scope
			\param[in] filepath
				The filepath to write the results to
		*************************************************************************/
		void Start(const std::string& name, const std::string& filepath = "results.json")
		{
			mOutputStream.open(filepath);
			WriteHeader();
			mScope = new InstrumentationScope{ name };
		}

		/*!***********************************************************************
			\brief
				Ends the instrumentation process
		*************************************************************************/
		void End()
		{
			WriteFooter();
			mOutputStream.close();
			delete mScope;
			mScope = nullptr;
			mProfileCount = 0;
		}

		/*!***********************************************************************
			\brief
				Writes the profile results to the output stream
			\param[in] result
				The profile result to write
		*************************************************************************/
		void WriteProfile(const ProfileResult& result)
		{
			if (mProfileCount++ > 0)
				mOutputStream << ",";

			std::string name = result.mName;
			// Remove __cdecl
			if (name.find("__cdecl") != std::string::npos)
			{
				name.erase(name.find("__cdecl"), 7);
			}

			// remove void from void inputs
			if (name.find("(void)") != std::string::npos)
			{
				size_t pos = name.find("(void)");
				name.erase(pos+1, 4);
			}
			std::replace(name.begin(), name.end(), '"', '\'');

			mOutputStream << "{";
			mOutputStream << "\"cat\":\"function\",";
			mOutputStream << "\"dur\":" << (result.mEnd - result.mStart) << ',';
			mOutputStream << "\"name\":\"" << name << "\",";
			mOutputStream << "\"ph\":\"X\",";
			mOutputStream << "\"pid\":0,";
			mOutputStream << "\"tid\":" << result.mThreadID << ",";
			mOutputStream << "\"ts\":" << result.mStart;
			mOutputStream << "}";

			mOutputStream.flush();
		}

		/*!***********************************************************************
			\brief
				Writes the header of the output stream
		*************************************************************************/
		void WriteHeader()
		{
			mOutputStream << "{\"otherData\": {},\"traceEvents\":[";
			mOutputStream.flush();
		}

		/*!***********************************************************************
			\brief
				Writes the footer of the output stream
		*************************************************************************/
		void WriteFooter()
		{
			mOutputStream << "]}";
			mOutputStream.flush();
		}

		/*!***********************************************************************
			\brief
				Returns the instance of the Instrumentor
		*************************************************************************/
		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		InstrumentationScope* mScope; // The current scope
		std::ofstream mOutputStream; // The output stream
		int mProfileCount; // The number of profiles
	};

	class InstrumentationTimer
	{
		public:

		/*!***********************************************************************
			\brief
				Default constructor of the InstrumentationTimer
		*************************************************************************/
		InstrumentationTimer(const char* name) : mName(name), mStopped(false)
		{
			mStartTimepoint = std::chrono::high_resolution_clock::now();
		}

		/*!***********************************************************************
			\brief
				Default destructor of the InstrumentationTimer
		*************************************************************************/
		~InstrumentationTimer()
		{
			if (!mStopped)
				Stop();
		}

		/*!***********************************************************************
			\brief
				Stops the timer
		*************************************************************************/
		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ mName, start, end, threadID });

			mStopped = true;
		}

		private:
			const char* mName; // The name of the timer
			std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimepoint; // The start timepoint
			bool mStopped; // Whether the timer has stopped

	};
}

// Macros for profiling
#if ENGINE_PROFILE
#define PROFILE_START(name, filepath) ::Borealis::Instrumentor::Get().Start(name, filepath)
#define PROFILE_END() ::Borealis::Instrumentor::Get().End()
#define PROFILE_SCOPE(name) ::Borealis::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_START(name, filepath) 
#define PROFILE_END() 
#define PROFILE_FUNCTION()
#define PROFILE_SCOPE(name)
#endif

#endif