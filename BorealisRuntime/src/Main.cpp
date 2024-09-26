/******************************************************************************
/*!
\file       Main.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 15, 2024
\brief      Defines the entry point of the runtime

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <Borealis.hpp>
#include <RuntimeLayer.hpp>
#include <Core/EntryPoint.hpp>

class Runtime : public Borealis::ApplicationManager
{
public:
	Runtime() : ApplicationManager("Game App")
	{
#ifndef _DIST
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
		//PushLayer(new gameLayer());
		PushLayer(new BorealisRuntime::RuntimeLayer());
	}

	~Runtime()
	{


	}

};


Borealis::ApplicationManager* Borealis::CreateApplication()
{
	return new Runtime();
}

