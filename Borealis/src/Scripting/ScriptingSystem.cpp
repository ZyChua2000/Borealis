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
#include <Core/LoggerSystem.hpp>

namespace Borealis
{


	char* ReadBytes(const std::string& path, uint32_t* outSize)
	{
		std::ifstream stream(path, std::ios::binary | std::ios::ate);
		BOREALIS_CORE_ASSERT(stream.is_open(), "Failed to open file");

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = end - stream.tellg();

		if (size == 0)
		{
			BOREALIS_CORE_ERROR("File is empty: {0}", path);
			return nullptr;
		}

		char* buffer = new char[size];
		stream.read(buffer, size);
		stream.close();

		*outSize = size;
		return buffer;
	}

	MonoAssembly* LoadCSharpAssembly(const std::string& path)
	{
		uint32_t size;
		char* buffer = ReadBytes(path, &size);
		BOREALIS_CORE_ASSERT(buffer, "Failed to read file");

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(buffer, size, 1, &status, 0);
		BOREALIS_CORE_ASSERT(!status, mono_image_strerror(status));

		MonoAssembly* assembly = mono_assembly_load_from_full(image, path.c_str(), &status, 0);
		mono_image_close(image);

		delete[] buffer;
		return assembly;
	}

	void PrintAssemblyTypes(MonoAssembly* assembly)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* table = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(table);

		for (int32_t i = 0; i < numTypes; ++i)
		{
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(table, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			BOREALIS_CORE_TRACE("Type: {0}::{1}", nameSpace, name);
		}
	}

	struct ScriptingSystemData
	{
		MonoDomain* rootDomain = nullptr;
		MonoDomain* appDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
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

	void ScriptingSystem::InitMono()
	{
		mono_set_assemblies_path("mono/lib/4.5");
		sData->rootDomain = mono_jit_init("BorealisJitRuntime");
		
		BOREALIS_CORE_ASSERT(sData->rootDomain, "Failed to initialize Mono runtime");

		char friendlyName[] = "BorealisAppDomain";
		sData->appDomain = mono_domain_create_appdomain(friendlyName, nullptr);
		mono_domain_set(sData->appDomain, true);
	}
	void ScriptingSystem::FreeMono()
	{
		mono_domain_set(mono_get_root_domain(), false);

		mono_domain_unload(sData->appDomain);
		sData->appDomain = nullptr;

		mono_jit_cleanup(sData->rootDomain);
		sData->rootDomain = nullptr;
	}

}