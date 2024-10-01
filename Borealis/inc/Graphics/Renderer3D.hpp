/******************************************************************************/
/*!
\file		Renderer3D.hpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 11, 2024
\brief		Declares the class for Graphics Renderer3D

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP
#include <Graphics/OrthographicCamera.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/EditorCamera.hpp>
#include <Scene/Components.hpp>

#include "Light.hpp"

namespace Borealis
{
	class Renderer3D
	{
	public:

		static void Init();
		static void Begin(const EditorCamera& camera);

		static void Begin(const Camera& camera, const glm::mat4& transform);

		static void DrawMesh(const glm::mat4& transform, const MeshFilterComponent& meshFilter, const MeshRendererComponent& meshRenderer, const Light* light, int entityID = -1);
	};
}

#endif