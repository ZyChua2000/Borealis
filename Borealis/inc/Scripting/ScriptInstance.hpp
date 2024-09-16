/******************************************************************************
/*!
\file       ScriptInstance.hpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 15, 2024
\brief      Declares the Script Instance class which is an instance of a script
			component that is attached to an entity.


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCRIPT_INSTANCE_HPP
#define SCRIPT_INSTANCE_HPP
#include <Core/Core.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scripting/ScriptClass.hpp>
#include <Scene/Entity.hpp>
namespace Borealis
{
	class ScriptInstance
	{
	public:
		ScriptInstance(Ref<ScriptClass> scriptClass);
		Ref<ScriptClass> GetScriptClass();
		MonoClass* GetMonoClass() const;
		MonoObject* GetInstance();
		std::string GetKlassName() const;

		template <typename T>
		T GetFieldValue(const std::string& name)
		{
			if (GetFieldValueInternal(name, s_fieldValueBuffer))
				return *reinterpret_cast<T*>(s_fieldValueBuffer);
			else
			{
				BOREALIS_CORE_WARN("Failed to get field {0} in class {1}", name, mScriptClass->GetKlassName());
				return T();
			}
		}

		void SetFieldValue(const std::string& name, void* value)
		{
			if (!SetFieldValueInternal(name, value))
			{
				BOREALIS_CORE_WARN("Failed to set field {0} in class {1}", name, mScriptClass->GetKlassName());
			}
		}
	private:

		bool SetFieldValueInternal(const std::string& name, void* value);
		bool GetFieldValueInternal(const std::string& name, const void* value);

		Ref<ScriptClass> mScriptClass;
		MonoObject* mInstance;

		MonoMethod* mConstructor = nullptr;

		inline static char s_fieldValueBuffer[16];
	};
}

#endif
