/******************************************************************************
/*!
\file       ScriptField.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 07, 2024
\brief      Defines the ScriptField structs which represents a field in a script.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/reflection.h>
#include <Scripting/ScriptField.hpp>
namespace Borealis
{
	bool ScriptField::isPublic() const
	{
		return mono_field_get_flags(mMonoFieldType) & MONO_FIELD_ATTR_PUBLIC;
	}
	bool ScriptField::isPrivate() const
	{
		return mono_field_get_flags(mMonoFieldType) & MONO_FIELD_ATTR_PRIVATE;
	}
	bool ScriptField::hasHideInInspector() const
	{
		return false;
	}
	bool ScriptField::hasSerializeField() const
	{
		return false;
	}
}

