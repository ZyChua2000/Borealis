/******************************************************************************/
/*!
\file		LoggerSystem.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 15, 2024
\brief		Declares the functions for Logger System of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef LOGGER_SYSTEM_HPP
#define LOGGER_SYSTEM_HPP

#include <Core/Core.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

// Define the log levels
#define ENGINE_LOGLEVEL_INFO spdlog::level::info
#define ENGINE_LOGLEVEL_TRACE spdlog::level::trace
#define ENGINE_LOGLEVEL_WARN spdlog::level::warn
#define ENGINE_LOGLEVEL_ERROR spdlog::level::err
#define ENGINE_LOGLEVEL_CRITICAL spdlog::level::critical

namespace Borealis {

	/*!***********************************************************************
		\brief
			Class for Logger System of the Borealis
	*************************************************************************/
	class BOREALIS_API LoggerSystem
	{
	public:
		/*!***********************************************************************
			\brief
				Initializes the Logger System
			\param[in] level
				The log level to be set for the Borealis Logger
		*************************************************************************/
		static void Init(spdlog::level::level_enum = ENGINE_LOGLEVEL_TRACE);

		/*!***********************************************************************
			\brief
				Shuts down the Logger System
		*************************************************************************/
		static void Shutdown();

		/*!***********************************************************************
			\brief
				Returns the Borealis Logger
			\return
				The Borealis Logger
		*************************************************************************/
		inline static spdlog::logger*& GetEngineLogger() { return sEngineLogger; }

		/*!***********************************************************************
			\brief
				Returns the Application Logger
			\return
				The Application Logger
		*************************************************************************/
		inline static spdlog::logger*& GetApplicationLogger() { return sApplicationLogger; }

		/*!***********************************************************************
			\brief
				Sets the log level for the Borealis Logger
			\param[in] level
				The log level to be set
		*************************************************************************/
		void SetEngineLogLevel(spdlog::level::level_enum level);

		/*!***********************************************************************
			\brief
				Sets the log level for the Application Logger
			\param[in] level
				The log level to be set
		*************************************************************************/
		void SetApplicationLogLevel(spdlog::level::level_enum level);

	private:
		static spdlog::logger* sEngineLogger;
		static spdlog::logger* sApplicationLogger;
	}; // End of Class LoggerSystem

}

// Define the log macros
#define ENGINE_LOG_INFO(...)     ::Borealis::LoggerSystem::GetEngineLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...)    ::Borealis::LoggerSystem::GetEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_WARN(...)     ::Borealis::LoggerSystem::GetEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...)    ::Borealis::LoggerSystem::GetEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_CRITICAL(...) ::Borealis::LoggerSystem::GetEngineLogger()->critical(__VA_ARGS__)

#define APP_LOG_INFO(...)        ::Borealis::LoggerSystem::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_LOG_TRACE(...)       ::Borealis::LoggerSystem::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_LOG_WARN(...)        ::Borealis::LoggerSystem::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...)       ::Borealis::LoggerSystem::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...)    ::Borealis::LoggerSystem::GetApplicationLogger()->critical(__VA_ARGS__)

#endif