/******************************************************************************
/*!
\file       ResourceManager.hpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 22, 2024
\brief      Declares Resource manager class for the editor's resources

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ResourceManager_HPP
#define ResourceManager_HPP
#include <Core/Core.hpp>
#include <Graphics/Texture.hpp>
namespace Borealis
{
	struct ResourceManager
	{
		enum class FileIcon
		{
			Directory,
			Scene,
			Script,
			Shader,
			Audio,
			Font,
			Unknown
		};

		enum class ButtonIcon
		{

		};

		enum class PrimitiveEntities
		{
			Cube,
			Sphere,
			Cylinder,
			Cone,
			Plane,
			Quad,
			Unknown
		};

		enum class EditorFonts // Used for editor UI
		{
			Normal,
			Bold,
			Italic
		};

		enum class EngineFonts // Used for text components in the default engine
		{
			Normal,
			Bold,
			Italic
		};

		//static void LoadResources();
		//static Ref<Texture2D> GetFileIcon(FileIcon icon);
		//static Ref<Texture2D> GetButtonIcon(ButtonIcon icon);
	};
}

#endif
