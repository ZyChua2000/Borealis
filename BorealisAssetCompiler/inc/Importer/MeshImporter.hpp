/******************************************************************************
/*!
\file       MeshImporter.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 30, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MeshImporter_HPP
#define MeshImporter_HPP

#include <vector>
#include <filesystem>

#include <glm/glm.hpp>

namespace BorealisAssetCompiler
{
	struct Vertex 
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Mesh
	{
		std::vector<unsigned int> mIndices;
		std::vector<Vertex> mVertices;

		uint32_t mVerticesCount;
		uint32_t mIndicesCount; 
	};

	struct Model
	{
	public:
		std::vector<Mesh> mMeshes;
	};

	class MeshImporter
	{
	public:
		static void SaveFile(std::filesystem::path const& sourcePath, std::filesystem::path& cachePath);

	private:
		static void LoadFBXModel(Model & model, const std::string& path);
		static void SaveModel(Model const& model, std::filesystem::path& cachePath);
	};
}

#endif
