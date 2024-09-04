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

		/*!***********************************************************************
			\brief
				Constructor for a Mesh
		*************************************************************************/
		Mesh();

		/*!***********************************************************************
			\brief
				Constructor for a Mesh
			\param vertices
				Vertices of the mesh
			\param indices
				Indices of the mesh
			\param normals
				Normals of the mesh
			\param texCoords
				Texture coordinates of the mesh
		*************************************************************************/
		Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords);

		/*!***********************************************************************
			\brief
				Destructor for a Mesh
		*************************************************************************/
		~Mesh();

		/*!***********************************************************************
			\brief
				Set the Vertices of a Mesh
			\param[in] vertices
				Vertices of the mesh
		*************************************************************************/
		void SetVertices(const std::vector<glm::vec3>& vertices);

		/*!***********************************************************************
			\brief
				Set the Indices of a Mesh
			\param[in] indices
				Indices of the mesh
		*************************************************************************/
		void SetIndices(const std::vector<unsigned int>& indices);

		/*!***********************************************************************
			\brief
				Set the Normals of a Mesh
			\param[in] normals
				Normals of the mesh
		*************************************************************************/
		void SetNormals(const std::vector<glm::vec3>& normals);

		/*!***********************************************************************
			\brief
				Set the Texture Coordinates of a Mesh
			\param[in] texCoords
				Texture coordinates of the mesh
		*************************************************************************/
		void SetTexCoords(const std::vector<glm::vec2>& texCoords);

		/*!***********************************************************************
			\brief
				Get the Vertices of a Mesh
			\return
				Vertices of the mesh
		*************************************************************************/
		const glm::vec3* GetVertices() const;

		/*!***********************************************************************
			\brief
				Get the Indices of a Mesh
			\return
				Indices of the mesh
		*************************************************************************/
		const unsigned int* GetIndices() const;

		/*!***********************************************************************
			\brief
				Get the Normals of a Mesh
			\return
				Normals of the mesh
		*************************************************************************/
		const glm::vec3* GetNormals() const;

		/*!***********************************************************************
			\brief
				Get the Texture Coordinates of a Mesh
			\return
				Texture coordinates of the mesh
		*************************************************************************/
		const glm::vec2* GetTexCoords() const;


		/*!***********************************************************************
			\brief
				Get the Number of Vertices of a Mesh
			\return
				Number of vertices of the mesh
		*************************************************************************/
		uint32_t GetVerticesCount() const;

		/*!***********************************************************************
			\brief
				Get the Number of Indices of a Mesh
			\return
				Number of indices of the mesh
		*************************************************************************/
		uint32_t GetIndicesCount() const;

		/*!***********************************************************************
			\brief
				Get the Number of Normals of a Mesh
			\return
				Number of normals of the mesh
		*************************************************************************/
		uint32_t GetNormalsCount() const;

		/*!***********************************************************************
			\brief
				Get the Number of Texture Coordinates of a Mesh
			\return
				Number of texture coordinates of the mesh
		*************************************************************************/
		uint32_t GetTexCoordsCount() const;

	private:
		glm::vec3* mVertices; // Vertex array
		unsigned int* mIndices; // Index array
		glm::vec3* mNormals; // Normal array
		glm::vec2* mTexCoords; // Texture coordinate array

		uint32_t mVerticesCount; // Number of vertices
		uint32_t mIndicesCount; // Number of indices
		uint32_t mNormalsCount; // Number of normals
		uint32_t mTexCoordsCount; // Number of texture coordinates
	}; // class Mesh
} // namespace Borealis
#endif