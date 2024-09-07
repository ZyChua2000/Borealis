/******************************************************************************/
/*!
\file		ScriptingUtils.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for the Scripting Utilities

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCRIPTING_UTILS_HPP
#define SCRIPTING_UTILS_HPP
#include <string>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>

namespace Borealis
{
	char* ReadBytes(const std::string& path, uint32_t* outSize);
	MonoAssembly* LoadCSharpAssembly(const std::string& path);
	MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);
	MonoObject* InstantiateClass(MonoAssembly* assembly, MonoDomain* appDomain, const char* namespaceName, const char* className);
	std::vector<uint8_t> mono_array_to_vector(MonoArray* monoArray);

	// Debugging Tools
	void PrintAssemblyTypes(MonoAssembly* assembly);
}

#endif //SCRIPTING_UTILS_HPP