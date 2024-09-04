/******************************************************************************/
/*!
\file		EditorApp.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Entry point of level editor

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/


#include <Borealis.hpp>
#include <Core/EntryPoint.hpp>
#include <EditorLayer.hpp>
namespace Borealis
{
	class LevelEditor : public ApplicationManager
	{
	public:
		LevelEditor() : ApplicationManager("Level Editor")
		{
#ifndef _DIST
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
			//PushLayer(new gameLayer());
			PushLayer(new EditorLayer());
		}

		~LevelEditor()
		{


		}

	};


	ApplicationManager* CreateApplication()
	{
		return new LevelEditor();
	}
}