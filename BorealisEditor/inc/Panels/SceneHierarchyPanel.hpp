/******************************************************************************/
/*!
\file		SceneHierarchyPanel.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 13, 2024
\brief		Declares the class Scene Hierarchy in Level Editor

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef SCENE_HIERARCHY_PANEL_HPP
#define SCENE_HIERARCHY_PANEL_HPP

#include <Scene/scene.hpp>
#include <Core/core.hpp>
#include <Scene/Entity.hpp>

namespace Borealis {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() {};
		SceneHierarchyPanel(const Ref<Scene>& scene);
		void SetContext(const Ref<Scene>& scene);

		void ImGuiRender();
		Entity& GetSelectedEntity() { return mSelectedEntity; }
		void SetSelectedEntity(const Entity& entity) { mSelectedEntity = entity; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
		Ref<Scene> mContext;
		Entity mSelectedEntity;
	};
}

#endif