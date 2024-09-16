/******************************************************************************/
/*!
\file		ScriptClass.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 15, 2024
\brief		Declares the class ScriptClass that handles a CS script that 
			is attached to an entity

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#ifndef SCRIPT_CLASS_HPP
#define SCRIPT_CLASS_HPP
#include <string>
#include <Scripting/ScriptField.hpp>

extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
	typedef struct _MonoAssembly MonoAssembly;
}


namespace Borealis
{

	class ScriptClass
	{
	public:
		friend class ScriptingSystem;

		ScriptClass(const std::string& namespaceName, const std::string& className, MonoAssembly* assembly);
		~ScriptClass() = default;
		MonoObject* Instantiate();
		MonoMethod* GetMethod(std::string methodName, int paramCount);
		MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** params);
		MonoClass* GetMonoClass() const;
		std::string GetKlassName() const;

		std::unordered_map<std::string, ScriptField> mFields;
	private:
		std::string mClassName;
		std::string mNamespaceName;
		MonoClass* mMonoClass;
	};
}
#endif