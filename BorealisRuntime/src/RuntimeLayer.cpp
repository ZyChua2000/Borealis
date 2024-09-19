/******************************************************************************
/*!
\file       RuntimeLayer.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 19, 2024
\brief      Defines the Runtime Layer class

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <filesystem>
#include <RuntimeLayer.hpp>
namespace BorealisRuntime
{
	void RuntimeLayer::Init()
	{
		// Search for extension in current directory
		std::filesystem::path path = std::filesystem::current_path();
		std::string extension = ".brls";
		std::string projectPath = "";
		bool found = false;
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.path().extension() == extension)
			{
				if (found == true)
				{
					APP_LOG_WARN("Multiple Project Files found!", entry.path().string());
				}
				projectPath = entry.path().string();
				found = true;
			}
		}

		BOREALIS_CORE_ASSERT(found, "No Project File found!");

		Borealis::Project::SetProjectPath(projectPath);
		Borealis::ScriptingSystem::InitCoreAssembly();
	}
	void RuntimeLayer::UpdateFn(float dt)
	{
		// Update for scripts -> make it more effecient by doing event-based and
		// overridden-based rather than running every script every loop.
		auto view = Borealis::SceneManager::GetActiveScene()->GetRegistry().view<Borealis::ScriptComponent>();
		for (auto entity : view)
		{
			auto& scriptComponent = view.get<Borealis::ScriptComponent>(entity);
			for (auto& [name, script] : scriptComponent.mScripts)
			{
				script->Update();
			}
		}

		int timeStep = dt / 1.66667f;
		for (auto entity : view)
		{
			auto& scriptComponent = view.get<Borealis::ScriptComponent>(entity);
			for (auto& [name, script] : scriptComponent.mScripts)
			{
				for (int i = 0; i < timeStep; i++)
					script->FixedUpdate();
			}
		}

		//------------------------
		// Physics Simulation here
		//------------------------


		for (auto entity : view)
		{
			auto& scriptComponent = view.get<Borealis::ScriptComponent>(entity);
			for (auto& [name, script] : scriptComponent.mScripts)
			{
				script->LateUpdate();
			}
		}


		Borealis::Camera* mainCamera = nullptr;
		glm::mat4 mainCameratransform(1.f);

		{
			auto group = Borealis::SceneManager::GetActiveScene()->GetRegistry().group<>(entt::get<Borealis::TransformComponent, Borealis::CameraComponent>);
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<Borealis::TransformComponent, Borealis::CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameratransform = transform;
					break;
				}
			}
		}

		// Pre-Render
		if (mainCamera)
		{
			{
				Borealis::Renderer2D::Begin(*mainCamera, mainCameratransform);
				auto group = Borealis::SceneManager::GetActiveScene()->GetRegistry().group<>(entt::get<Borealis::TransformComponent, Borealis::SpriteRendererComponent>);
				for (auto& entity : group)
				{
					auto [transform, sprite] = group.get<Borealis::TransformComponent, Borealis::SpriteRendererComponent>(entity);
					Borealis::Renderer2D::DrawQuad(transform, sprite.Colour);
				}
				Borealis::Renderer2D::End();
			}

			{
				Borealis::Renderer2D::Begin(*mainCamera, mainCameratransform);
				auto group = Borealis::SceneManager::GetActiveScene()->GetRegistry().group<>(entt::get < Borealis::TransformComponent, Borealis::CircleRendererComponent > );
				for (auto& entity : group)
				{
					auto [transform, circle] = group.get<Borealis::TransformComponent, Borealis::CircleRendererComponent>(entity);
					Borealis::Renderer2D::DrawCircle(transform, circle.Colour, circle.thickness, circle.fade);
				}
				Borealis::Renderer2D::End();
			}

		}

		//Post-Render
	}
	void RuntimeLayer::Free()
	{
	}
}

