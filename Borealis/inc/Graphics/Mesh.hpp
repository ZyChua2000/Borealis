/******************************************************************************/
/*!
\file		Mesh.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 22, 2024
\brief		Declares the class for Mesh for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MESH_HPP
#define MESH_HPP
#include <vector>
#include <glm/glm.hpp>
namespace Borealis
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords);
		~Mesh();

		void SetVertices(const std::vector<glm::vec3>& vertices);
		void SetIndices(const std::vector<unsigned int>& indices);
		void SetNormals(const std::vector<glm::vec3>& normals);
		void SetTexCoords(const std::vector<glm::vec2>& texCoords);

		const glm::vec3* GetVertices() const;
		const unsigned int* GetIndices() const;
		const glm::vec3* GetNormals() const;
		const glm::vec2* GetTexCoords() const;

		uint32_t GetVerticesCount() const;
		uint32_t GetIndicesCount() const;
		uint32_t GetNormalsCount() const;
		uint32_t GetTexCoordsCount() const;

	private:
		glm::vec3* mVertices;
		unsigned int* mIndices;
		glm::vec3* mNormals;
		glm::vec2* mTexCoords;

		uint32_t mVerticesCount;
		uint32_t mIndicesCount;
		uint32_t mNormalsCount;
		uint32_t mTexCoordsCount;
	};
}
#endif