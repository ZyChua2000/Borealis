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
#include <unordered_map>
#include <unordered_set>
#include <Scene/Scene.hpp>
#include <Scene/Entity.hpp>
namespace Borealis
{
	class SceneManager
	{
	public:
		static void CreateScene(std::string sceneName, std::string scenePath);
		static void AddScene(std::string sceneName, std::string scenePath);
		static void RemoveScene(std::string sceneName);
		static void SetActiveScene(std::string sceneName);
		static void SetActiveScene(Ref<Scene> scene) {mActiveScene = scene;}
		static Ref<Scene> GetActiveScene() { return mActiveScene; };
		static Entity GetEntity(uint64_t entityID);
		static std::unordered_set<std::string> GetSceneNames();
		static std::unordered_map<std::string, std::string>& GetSceneLibrary() { return mSceneLibrary; }
		static void ClearSceneLibrary() { mSceneLibrary.clear(); }
		static void SaveActiveScene();
	private:
		static Ref<Scene> mActiveScene;
		static std::unordered_map<std::string, std::string> mSceneLibrary; // Key: Scene Name, Value: Scene Path
	};
}

#endif