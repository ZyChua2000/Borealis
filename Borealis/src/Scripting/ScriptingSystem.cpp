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
#include <typeinfo>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <Scripting/ScriptingSystem.hpp>
#include <Scripting/ScriptingUtils.hpp>
#include <Scripting/ScriptingExposedInternal.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scene/SceneManager.hpp>
#include <Scene/Components.hpp>
#include <Scene/Entity.hpp>

namespace Borealis
{
	 Ref<Scene> SceneManager::mActiveScene;
	 std::vector<Ref<Scene>> SceneManager::mScenes;

	struct ScriptingSystemData
	{
		MonoDomain* mRootDomain = nullptr;
		MonoDomain* mAppDomain = nullptr;
		MonoAssembly* mRoslynAssembly = nullptr;
		std::vector<MonoAssembly*> mAssemblies;
	};

	static ScriptingSystemData* sData;

	template <typename T>
	static void RegisterComponent()
	{
		std::string typeName = typeid(T).name();
		

		if (typeName.find("::") != std::string::npos)
		{
			typeName = "Borealis." + typeName.substr(typeName.find("::") + 2);
		}
		if (typeName.find("Component") != std::string::npos)
		{
			typeName = typeName.substr(0, typeName.find("Component"));
		}
		MonoType* managedType = mono_reflection_type_from_name(typeName.data(), mono_assembly_get_image(sData->mRoslynAssembly));

		if (managedType)
		{
			GCFM::mHasComponentFunctions[managedType] = [](Entity& entity) { return entity.HasComponent<T>(); };
			GCFM::mAddComponentFunctions[managedType] = [](Entity& entity) { entity.AddComponent<T>(); };
			GCFM::mRemoveComponentFunctions[managedType] = [](Entity& entity) { entity.GetComponent<T>(); };
		}
		else
		{
			BOREALIS_CORE_WARN("Failed to register component {0}", typeName);
		}
	}

	static void RegisterComponents()
	{
		RegisterComponent<TransformComponent>();
		//RegisterComponent<CameraComponent>();
		RegisterComponent<SpriteRendererComponent>();
		//RegisterComponent<IDComponent>();
		//RegisterComponent<TagComponent>();
		//RegisterComponent<CircleRendererComponent>();
		//RegisterComponent<MeshFilterComponent>();
		//RegisterComponent<MeshRendererComponent>();
		//RegisterComponent<BoxColliderComponent>();
		//RegisterComponent<CapsuleColliderComponent>();
		//RegisterComponent<RigidBodyComponent>();
		//RegisterComponent<LightComponent>();

	}

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
		InstantiateClass(sData->mRoslynAssembly, sData->mAppDomain, "Borealis", "RoslynCompiler");
	}

	template <typename T>
	static void GetComponent(UUID id, T* component)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		Entity entity = scene->GetEntityByUUID(id);
		*component = entity.GetComponent<T>();
	}


	void ScriptingSystem::InitMono()
	{
		mono_set_assemblies_path("mono/lib/4.5");
		sData->mRootDomain = mono_jit_init("BorealisJitRuntime");
		
		BOREALIS_CORE_ASSERT(sData->mRootDomain, "Failed to initialize Mono runtime");

		char friendlyName[] = "BorealisAppDomain";
		sData->mAppDomain = mono_domain_create_appdomain(friendlyName, nullptr);
		mono_domain_set(sData->mAppDomain, true);

		RegisterInternals();

		sData->mRoslynAssembly = LoadCSharpAssembly("resources/scripts/core/BorealisScriptCore.dll");
		
		// Add all internal functions here
		RegisterComponents();
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