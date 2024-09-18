/******************************************************************************/
/*!
\file		EditorLayer.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Declares the class for the layer for level editor

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/


#ifndef EDITOR_LAYER_HPP
#define EDITOR_LAYER_HPP
#include <vector>
#include <Borealis.hpp>
#include <Panels/SceneHierarchyPanel.hpp>
#include <Panels/ContentBrowserPanel.hpp>
#include <Graphics/EditorCamera.hpp>
namespace Borealis {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer() {}
		void Init() override;
		void Free() override;
		void UpdateFn(float dt) override;
		void EventFn(Event& e) override;
		void ImGuiRender() override;

		bool onKeyPressed(EventKeyPressed& e);
		bool onMousePressed(EventMouseButtonTriggered& e);
	private:

		void NewScene();
		void OpenScene();
		void OpenScene(const char * filename);
		void SaveScene();
		void SaveSceneAs();
		void ScenePlay();
		void SceneStop();
		void ScenePause();
		void SceneResume();

		void LoadProject();
		void NewProject();

		void UIToolbar();


		OrthographicCameraController mCamera;
		Ref<Texture2D> mTexture;
		Ref<SubTexture2D> mSubTexture;
		Ref<FrameBuffer> mViewportFrameBuffer;
		Ref<FrameBuffer> mRuntimeFrameBuffer;
		Ref<Scene> mEditorScene;

		glm::vec2 mViewportSize = { 0.0f, 0.0f };
		glm::vec2 mRuntimeSize = { 0.0f, 0.0f };
		glm::vec2 mViewportBounds[2];
		bool mViewportFocused = false;
		bool mViewportHovered = false;
		bool mRuntimeFocused = false;
		bool mRuntimeHovered = false;
		bool hasRuntimeCamera = false;

		Entity mRuntimeCamera;
		Entity mHoveredEntity;
		
		int mGizmoType = -1;
		float imGuizmoClipSpace = 0.1f;

		EditorCamera mEditorCamera;
		SceneHierarchyPanel SCPanel;
		ContentBrowserPanel CBPanel;
		std::string mLatestFilePath;
		bool mLightMode = true;

		enum class SceneState
		{
			Edit = 0,
			Play = 1,
			Pause = 2
		};

		SceneState mSceneState = SceneState::Edit;

		float mLineThickness = 1.0f;
	};
}

#endif