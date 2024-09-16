/******************************************************************************/
/*!
\file		Scene.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Implements the class for Scene

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <glm/glm.hpp>
#include <Scene/Scene.hpp>
#include <Scene/Entity.hpp>
#include <Scene/ScriptEntity.hpp>
#include <Scene/Components.hpp>
#include <Graphics/Renderer2D.hpp>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}
	void Scene::UpdateRuntime(float dt)
	{

		{
			mRegistry.view<NativeScriptComponent>().each([=](auto entity, auto& component)
			{
				if (!component.Instance)
				{
					component.Instance = component.Init();
					component.Instance->mEntity = Entity{ entity, this };
					component.Instance->Start();
				}
				component.Instance->Update(dt);
			});
		}
		Camera* mainCamera = nullptr;
		glm::mat4 mainCameratransform(1.f);
	
		{
			auto group = mRegistry.group<>(entt::get<TransformComponent, CameraComponent>);
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameratransform = transform;
					break;
				}
			}
		}


		if (mainCamera)
		{
			{
				Renderer2D::Begin(*mainCamera, mainCameratransform);
				auto group = mRegistry.group<>(entt::get<TransformComponent, SpriteRendererComponent>);
				for (auto& entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
					Renderer2D::DrawQuad(transform, sprite.Colour);
				}
				Renderer2D::End();
			}

			{
				Renderer2D::Begin(*mainCamera, mainCameratransform);
				auto group = mRegistry.group<>(entt::get<TransformComponent, CircleRendererComponent>);
				for (auto& entity : group)
				{
					auto [transform, circle] = group.get<TransformComponent, CircleRendererComponent>(entity);
					Renderer2D::DrawCircle(transform, circle.Colour, circle.thickness, circle.fade);
				}
				Renderer2D::End();
			}
			
		}
	}
	void Scene::UpdateEditor(float dt, EditorCamera& camera)
	{

		Renderer2D::Begin(camera);
		{
			auto group = mRegistry.group<>(entt::get<TransformComponent, SpriteRendererComponent>);
			for (auto& entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform, sprite, (int)entity);
			}
		}
		{
			auto group = mRegistry.group<>(entt::get<TransformComponent, CircleRendererComponent>);
			for (auto& entity : group)
			{
				auto [transform, circle] = group.get<TransformComponent, CircleRendererComponent>(entity);
				Renderer2D::DrawCircle(transform, circle.Colour, circle.thickness, circle.fade, (int)entity);
			}
		}

		Renderer2D::End();

	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		static unsigned unnamedID = 1;
		auto entity = Entity(mRegistry.create(), this);
		entity.AddComponent<IDComponent>();
		name == "" ? entity.AddComponent<TagComponent>("unnamedEntity" + std::to_string(unnamedID++)) : entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		mEntityMap[entity.GetUUID()] = entity;
		return entity;
	}
	Entity Scene::CreateEntityWithUUID(const std::string& name, uint64_t UUID)
	{
		static unsigned unnamedID = 1;
		auto entity = Entity(mRegistry.create(), this);
		entity.AddComponent<IDComponent>(UUID);
		name == "" ? entity.AddComponent<TagComponent>("unnamedEntity" + std::to_string(unnamedID++)) : entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		mEntityMap[UUID] = entity;
		return entity;
	}
	Entity Scene::GetEntityByUUID(UUID uuid)
	{
		if (mEntityMap.find(uuid) != mEntityMap.end())
			return { mEntityMap.at(uuid), this };

		return {};
	}
	void Scene::DestroyEntity(Entity entity)
	{		
		mEntityMap.erase(entity.GetUUID());
		mRegistry.destroy(entity);
	}

	template <typename Component>
	static void CopyComponent(Entity dst, Entity src)
	{
		if (src.HasComponent<Component>())
			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
	}

	void Scene::DuplicateEntity(Entity entity)
	{
		std::string name = entity.GetName();
		name+= " (clone)";
		Entity newEntity = CreateEntity(name);
		CopyComponent<TransformComponent>(newEntity, entity);
		CopyComponent<SpriteRendererComponent>(newEntity, entity);
		CopyComponent<CameraComponent>(newEntity, entity);
		CopyComponent<NativeScriptComponent>(newEntity, entity);
		CopyComponent<MeshFilterComponent>(newEntity,entity);
		CopyComponent<MeshRendererComponent>(newEntity,entity);
		CopyComponent<BoxColliderComponent>(newEntity,entity);
		CopyComponent<CapsuleColliderComponent>(newEntity,entity);
		CopyComponent<RigidBodyComponent>(newEntity, entity);
		CopyComponent<LightComponent>(newEntity, entity);
		CopyComponent<CircleRendererComponent>(newEntity, entity);
	}

	void Scene::ResizeViewport(const uint32_t& width, const uint32_t& height)
	{
		mViewportWidth = width;
		mViewportHeight = height;

		auto view = mRegistry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

	template <typename Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID,entt::entity>& entitymap)
	{
		auto view = src.view<Component>();
		for (auto srcEntity : view)
		{
			UUID uuid = src.get<IDComponent>(srcEntity).ID;
			auto dstEntity = entitymap.at(uuid);

			auto srcComponent = view.get<Component>(srcEntity);
			dst.emplace_or_replace<Component>(dstEntity, srcComponent);
		}
	}

	Ref<Scene> Scene::Copy(const Ref<Scene>& other)
	{
		Ref<Scene> newScene = MakeRef<Scene>();
		newScene->mViewportWidth = other->mViewportWidth;
		newScene->mViewportHeight = other->mViewportHeight;

		std::unordered_map<UUID, entt::entity> UUIDtoENTT;

		auto& originalRegistry = other->mRegistry;
		auto& newRegistry = newScene->mRegistry;
		auto idView = originalRegistry.view<IDComponent>();
		for (auto entity : idView)
		{
			UUID uuid = originalRegistry.get<IDComponent>(entity).ID;
			const auto& name = originalRegistry.get<TagComponent>(entity).Tag;
			UUIDtoENTT[uuid] = newScene->CreateEntityWithUUID(name, uuid);
		}

		CopyComponent<TransformComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<SpriteRendererComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<CameraComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<NativeScriptComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<MeshFilterComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<MeshRendererComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<BoxColliderComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<CapsuleColliderComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<RigidBodyComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<LightComponent>(newRegistry, originalRegistry, UUIDtoENTT);
		CopyComponent<CircleRendererComponent>(newRegistry, originalRegistry, UUIDtoENTT);

		return newScene;
	}

	void Scene::RuntimeStart()
	{
	}

	void Scene::RuntimeEnd()
	{
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = mRegistry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (cameraComponent.Primary)
			{
				return Entity{ entity, this };
			}
		}
		return Entity{};
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(mViewportWidth, mViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
		
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<MeshFilterComponent>(Entity entity, MeshFilterComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<MeshRendererComponent>(Entity entity, MeshRendererComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<BoxColliderComponent>(Entity entity, BoxColliderComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<CapsuleColliderComponent>(Entity entity, CapsuleColliderComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<RigidBodyComponent>(Entity entity, RigidBodyComponent& component)
	{

	}
	template<>
	void Scene::OnComponentAdded<LightComponent>(Entity entity, LightComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<ScriptComponent>(Entity entity, ScriptComponent& component)
	{

	}
}
