/******************************************************************************
/*!
\file       ScriptInstance.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 15, 2024
\brief      Defines the Script Instance class which is an instance of a script
			component that is attached to an entity.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Scripting/ScriptInstance.hpp>
#include <mono/metadata/object.h>

namespace Borealis
{
	ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass)
	{
		mScriptClass = scriptClass;
		mInstance = scriptClass->Instantiate();
		//mScriptClass->InvokeMethod(mInstance, mConstructor, &param);
	}

	Ref<ScriptClass> ScriptInstance::GetScriptClass()
	{
		return mScriptClass;
	}
	MonoClass* ScriptInstance::GetMonoClass() const
	{
		return mScriptClass->GetMonoClass();
	}
	MonoObject* ScriptInstance::GetInstance()
	{
		return mInstance;
	}
	std::string ScriptInstance::GetKlassName() const
	{
		return mScriptClass->GetKlassName();
	}
	bool ScriptInstance::SetFieldValueInternal(const std::string& name, void* value)
	{
		const auto& fields = mScriptClass->mFields;
		auto it = fields.find(name);
		if (it == fields.end())
		{
			BOREALIS_CORE_ERROR("Field {0} not found in class {1}", name, mScriptClass->GetKlassName());
			return false;
		}

		const ScriptField& field = it->second;
		mono_field_set_value(mInstance, field.mMonoFieldType, value);
		return true;
	}
	bool ScriptInstance::GetFieldValueInternal(const std::string& name, const void* value)
	{
		const auto& fields = mScriptClass->mFields;
		auto it = fields.find(name);
		if (it == fields.end())
		{
			BOREALIS_CORE_ERROR("Field {0} not found in class {1}", name, mScriptClass->GetKlassName());
			return false;
		}

		const ScriptField& field = it->second;
		mono_field_get_value(mInstance, field.mMonoFieldType, s_fieldValueBuffer);
		return true;
	}
	void ScriptInstance::Awake()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("Awake", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("Awake", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::Start()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("Start", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("Start", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::Update()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("Update", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("Update", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::FixedUpdate()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("FixedUpdate", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("FixedUpdate", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::LateUpdate()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("LateUpdate", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("LateUpdate", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnEnable()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnEnable", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnEnable", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnDisable()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDisable", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDisable", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnDestroy()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDestroy", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDestroy", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnApplicationQuit()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationQuit", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationQuit", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnApplicationPause()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationPause", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationPause", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnApplicationFocus()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationFocus", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnApplicationFocus", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnGUI()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnGUI", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnGUI", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnDrawGizmos()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDrawGizmos", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDrawGizmos", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnDrawGizmosSelected()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDrawGizmosSelected", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnDrawGizmosSelected", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnValidate()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnValidate", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnValidate", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::Reset()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnReset", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnReset", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnBecameVisible()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnBecameVisible", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnBecameVisible", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnBecameInvisible()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnBecameInvisible", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnBecameInvisible", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnPreCull()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPreCull", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPreCull", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnPreRender()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPreRender", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPreRender", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnPostRender()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPostRender", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnPostRender", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnRenderObject()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnRenderObject", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnRenderObject", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnWillRenderObject()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnWillRenderObject", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnWillRenderObject", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnRenderImage()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnRenderImage", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnRenderImage", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnAudioFilterRead()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAudioFilterRead", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAudioFilterRead", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnParticleCollision()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnParticleCollision", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnParticleCollision", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnJointBreak()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnJointBreak", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnJointBreak", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnAnimatorMove()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAnimatorMove", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAnimatorMove", 0), mInstance, nullptr, nullptr);
#endif
	}
	void ScriptInstance::OnAnimatorIK()
	{
#ifdef _DEB
		MonoObject* exception = nullptr;
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAnimatorIK", 0), mInstance, nullptr, &exception);
		if (exception)
		{
			mono_print_unhandled_exception(exception);
		}
#else
		mono_runtime_invoke_array(mScriptClass->GetMethod("OnAnimatorIK", 0), mInstance, nullptr, nullptr);
#endif
	}
}

