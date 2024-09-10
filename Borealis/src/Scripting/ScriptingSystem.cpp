/******************************************************************************/
/*!
\file		Scripting System.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 06, 2024
\brief		Defines the class for the Scripting System

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#include <BorealisPCH.hpp>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <Scripting/ScriptingSystem.hpp>
#include <Scripting/ScriptingUtils.hpp>
#include <Scripting/MonoBehaviour.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scene/SceneManager.hpp>

namespace Borealis
{
	 Ref<Scene> SceneManager::mActiveScene;
	 std::vector<Ref<Scene>> SceneManager::mScenes;
	 int Object::mInstanceCounter = 0;

	struct ScriptingSystemData
	{
		MonoDomain* mRootDomain = nullptr;
		MonoDomain* mAppDomain = nullptr;
		MonoAssembly* mRoslynAssembly = nullptr;
		std::vector<MonoAssembly*> mAssemblies;
	};

	static ScriptingSystemData* sData;

	

	void ScriptingSystem::Init()
	{
		sData = new ScriptingSystemData();
		InitMono();
	}
	void ScriptingSystem::Free()
	{
		FreeMono();
		delete sData;
	}

	void ScriptingSystem::Update(float deltaTime)
	{
		auto entities = SceneManager::GetActiveScene()->GetRegistry().view<MonoBehaviour>();
		for (auto entity : entities)
		{
			auto& monoBehaviour = entities.get<MonoBehaviour>(entity);
			// Update via invoke
		}
	}

	void ScriptingSystem::InitMono()
	{
		mono_set_assemblies_path("mono/lib/4.5");
		sData->mRootDomain = mono_jit_init("BorealisJitRuntime");
		
		BOREALIS_CORE_ASSERT(sData->mRootDomain, "Failed to initialize Mono runtime");

		char friendlyName[] = "BorealisAppDomain";
		sData->mAppDomain = mono_domain_create_appdomain(friendlyName, nullptr);
		mono_domain_set(sData->mAppDomain, true);
	}
	void ScriptingSystem::FreeMono()
	{
		mono_domain_set(mono_get_root_domain(), false);

		mono_domain_unload(sData->mAppDomain);
		sData->mAppDomain = nullptr;

		mono_jit_cleanup(sData->mRootDomain);
		sData->mRootDomain = nullptr;
	}

}