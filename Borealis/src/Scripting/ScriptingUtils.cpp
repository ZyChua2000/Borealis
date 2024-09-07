/******************************************************************************/
/*!
\file		ScriptingUtils.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for the Scripting Utilities

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scripting/ScriptingUtils.hpp>
#include <mono/metadata/assembly.h>

namespace Borealis
{
	char* ReadBytes(const std::string& path, uint32_t* outSize)
	{
		std::ifstream stream(path, std::ios::binary | std::ios::ate);
		BOREALIS_CORE_ASSERT(stream.is_open(), "Failed to open file");

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = static_cast<uint32_t>(end - stream.tellg());

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

	MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		MonoClass* klass = mono_class_from_name(image, namespaceName, className);

		if (klass == nullptr)
		{
			// Log error here
			return nullptr;
		}

		return klass;
	}

	MonoObject* InstantiateClass(MonoAssembly* assembly, MonoDomain* appDomain, const char* namespaceName, const char* className)
	{
		// Get a reference to the class we want to instantiate
		MonoClass* testingClass = GetClassInAssembly(assembly, namespaceName, className);

		// Allocate an instance of our class
		MonoObject* classInstance = mono_object_new(appDomain, testingClass);

		if (classInstance == nullptr)
		{
			// Log error here and abort
		}

		// Call the parameterless (default) constructor
		mono_runtime_object_init(classInstance);
		return classInstance;
	}
	
	std::vector<uint8_t> mono_array_to_vector(MonoArray* monoArray)
	{
		uintptr_t length = mono_array_length(monoArray);
		std::vector<uint8_t> result(static_cast<uint8_t>(length));
		void* data = mono_array_addr_with_size(monoArray, sizeof(uint8_t), 0);
		memcpy(result.data(), data, length);
		return result;
	}


}