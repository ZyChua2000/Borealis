/******************************************************************************/
/*!
\file		Scripting System.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 06, 2024
\brief		Declares the class for the Scripting System: Singleton Class

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCRIPTING_SYSTEM_HPP
#define SCRIPTING_SYSTEM_HPP
namespace Borealis
{
	class ScriptingSystem
	{
	public:
		/*!***********************************************************************
			\brief
				Init function for the Scripting System
		*************************************************************************/
		static void Init();

		/*!***********************************************************************
			\brief
				Free function for the Scripting System
		*************************************************************************/
		static void Free();

		static void Update(float deltaTime);

	private:

		/*!***********************************************************************
			\brief
				Initialises the Mono Runtime
		*************************************************************************/
		static void InitMono();

		/*!***********************************************************************
			\brief
				Frees the Mono Runtime
		*************************************************************************/
		static void FreeMono();
	};
}
#endif

