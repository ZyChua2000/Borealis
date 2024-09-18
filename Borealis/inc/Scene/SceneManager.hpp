/******************************************************************************/
/*!
\file		SceneManager.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Declares the class for Scene

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP
#include <Scene/Scene.hpp>
#include <Scene/Entity.hpp>
namespace Borealis
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		static Ref<Scene> CreateScene(const std::string& name);
		static void DestroyScene(Ref<Scene> scene);
		static void SetActiveScene(Ref<Scene> scene);
		static Ref<Scene> GetActiveScene() { return mActiveScene; };
		static void Update(float deltaTime);
		static void Render();
		static Entity GetEntity(uint64_t entityID);
	private:
		static Ref<Scene> mActiveScene;
		static std::vector<Ref<Scene>> mScenes;
	};
}

#endif