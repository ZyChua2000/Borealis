/******************************************************************************/
/*!
\file		Model.hpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 12, 2024
\brief		Declares the class for Model for rendering

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MODEL_HPP
#define MODEL_HPP
#include <vector>
#include <glm/glm.hpp>

#include <Assets/Asset.hpp>
#include <Core/Core.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Mesh.hpp>

namespace Borealis
{
	class Model : public Asset
	{
	public:
		void Draw(const glm::mat4& transform, Ref<Shader> shader);

		void LoadModel(std::filesystem::path const& path);
		void SaveModel();

		std::vector<Mesh> mMeshes;
	private:
	}; // class Model
} // namespace Borealis
#endif