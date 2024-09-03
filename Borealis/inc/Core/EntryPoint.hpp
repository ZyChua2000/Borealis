/******************************************************************************/
/*!
\file		EntryPoint.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 15, 2024
\brief		This header abstracts the entry point of the engine

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include <Core/ApplicationManager.hpp>
#include <Core/LoggerSystem.hpp>

	int main(int argc, char** argv)
	{
		Borealis::LoggerSystem::Init();
		BOREALIS_CORE_INFO("Logger System Initialized");
		BOREALIS_CORE_TRACE("Welcome to the Borealis");

		PROFILE_START("Borealis Startup", "Profile-Startup.json");
		auto app = Borealis::CreateApplication();
		PROFILE_END();

		PROFILE_START("Borealis Runtime", "Profile-Runtime.json");
		app->Run();
		PROFILE_END();

		PROFILE_START("Borealis Shutdown", "Profile-Shutdown.json");
		delete app;
		PROFILE_END();
	}

#endif

