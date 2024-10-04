/******************************************************************************
/*!
\file       AssetManager.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 27, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef AssetManager_HPP
#define AssetManager_HPP

#include <Core/Core.hpp>
#include <Core/Project.hpp>
#include <Core/ApplicationManager.hpp>

namespace Borealis
{
	class AssetManager
	{
	public:
		template<typename T>
		static Ref<T> GetAsset(AssetHandle handle)
		{
			Ref<Asset> asset = Project::GetEditorAssetsManager()->GetAsset(handle);
			return std::static_pointer_cast<T>(asset);

			//Ref<Asset> asset = ApplicationManager::Get()
		}

		static AssetMetaData const& GetMetaData(AssetHandle handle)
		{
			return Project::GetEditorAssetsManager()->GetMetaData(handle);
		}
	};
}

#endif
