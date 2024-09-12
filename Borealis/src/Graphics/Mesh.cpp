/******************************************************************************/
/*!
\file		Mesh.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 22, 2024
\brief		Declares the class for Mesh for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/Mesh.hpp>
#include <Core/LoggerSystem.hpp>

#include <Graphics/OpenGL/TextureOpenGLImpl.hpp>

namespace Borealis
{
	Mesh::Mesh()// : mVertices(nullptr), mIndices(nullptr), mNormals(nullptr), mTexCoords(nullptr), mVerticesCount(0), mIndicesCount(0), mNormalsCount(0), mTexCoordsCount(0)
	{
	}
	Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords)
	{
		//SetVertices(vertices);
		//SetIndices(indices);
		//SetNormals(normals);
		//SetTexCoords(texCoords);

		//mVertices = vertices;
		mIndices = indices;
		//mNormals = normals;

		for (int i{}; i < vertices.size(); i++)
		{
			Vertex vertex;
			vertex.Position = vertices[i];
			vertex.Normal = normals[i];
			vertex.TexCoords = texCoords[i];

			mVertices.push_back(vertex);
		}

		SetupMesh();

		//mTexCoords = texCoords;
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		mVertices = vertices;
		mIndices = indices;

		SetupMesh();
	}

	Mesh::~Mesh()
	{
		//if (mTexCoordsCount)
		//{
		//	delete[] mTexCoords;
		//}
		//if (mNormalsCount)
		//{
		//	delete[] mNormals;
		//}
		//if (mIndicesCount)
		//{
		//	delete[] mIndices;
		//}
		//if (mVerticesCount)
		//{
		//	delete[] mVertices;
		//}
	}

	void Mesh::Load(const std::string& path)
	{
		BOREALIS_CORE_TRACE("Mesh path is {0}", path);
	}

	void Mesh::SetupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int),
			&mIndices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void Mesh::Draw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	//void Mesh::SetVertices(const std::vector<glm::vec3>& vertices)
	//{
	//	const size_t& size = vertices.size();
	//	if (size > 0)
	//	{
	//		if (mVerticesCount == 0)
	//		{
	//			mVertices = new glm::vec3[size];
	//			memcpy(mVertices, vertices.data(), size * sizeof(glm::vec3));
	//		}
	//		else
	//		{
	//			delete[] mVertices;
	//			mVertices = new glm::vec3[size];
	//			memcpy(mVertices, vertices.data(), size * sizeof(glm::vec3));
	//		}
	//	}
	//	else
	//	{
	//		BOREALIS_CORE_WARN("Mesh::SetVertices() - No vertices to set");
	//		return;
	//	}
	//	mVerticesCount = (uint32_t)size;
	//}
	//void Mesh::SetIndices(const std::vector<unsigned int>& indices)
	//{
	//	const size_t& size = indices.size();
	//	if (size > 0)
	//	{
	//		if (mIndicesCount == 0)
	//		{
	//			mIndices = new unsigned[size];
	//			memcpy(mIndices, indices.data(), size * sizeof(unsigned));
	//		}
	//		else
	//		{
	//			delete[] mIndices;
	//			mIndices = new unsigned[size];
	//			memcpy(mIndices, indices.data(), size * sizeof(unsigned));
	//		}
	//	}
	//	else
	//	{
	//		BOREALIS_CORE_WARN("Mesh::SetIndices() - No index to set");
	//		return;
	//	}
	//	mIndicesCount = (uint32_t)size;
	//}
	//void Mesh::SetNormals(const std::vector<glm::vec3>& normals)
	//{
	//	const size_t& size = normals.size();
	//	if (size > 0)
	//	{
	//		if (mNormalsCount == 0)
	//		{
	//			mNormals = new glm::vec3[size];
	//			memcpy(mNormals, normals.data(), size * sizeof(glm::vec3));
	//		}
	//		else
	//		{
	//			delete[] mNormals;
	//			mNormals = new glm::vec3[size];
	//			memcpy(mNormals, normals.data(), size * sizeof(glm::vec3));
	//		}
	//	}
	//	else
	//	{
	//		BOREALIS_CORE_WARN("Mesh::SetNormals() - No normals to set");
	//		return;
	//	}
	//	mNormalsCount = (uint32_t)size;
	//}
	//void Mesh::SetTexCoords(const std::vector<glm::vec2>& texCoords)
	//{
	//	const size_t& size = texCoords.size();
	//	if (size > 0)
	//	{
	//		if (mTexCoordsCount == 0)
	//		{
	//			mTexCoords = new glm::vec2[size];
	//			memcpy(mTexCoords, texCoords.data(), size * sizeof(glm::vec2));
	//		}
	//		else
	//		{
	//			delete[] mTexCoords;
	//			mTexCoords = new glm::vec2[size];
	//			memcpy(mTexCoords, texCoords.data(), size * sizeof(glm::vec2));
	//		}
	//	}
	//	else
	//	{
	//		BOREALIS_CORE_WARN("Mesh::SetTexCoords() - No TexCoords to set");
	//		return;
	//	}
	//	mTexCoordsCount = (uint32_t)size;
	//}
	//const glm::vec3* Mesh::GetVertices() const
	//{
	//	return mVertices;
	//}
	//const unsigned int* Mesh::GetIndices() const
	//{
	//	return mIndices;
	//}
	//const glm::vec3* Mesh::GetNormals() const
	//{
	//	return mNormals;
	//}
	//const glm::vec2* Mesh::GetTexCoords() const
	//{
	//	return mTexCoords;
	//}
	//uint32_t Mesh::GetVerticesCount() const
	//{
	//	return mVerticesCount;
	//}
	//uint32_t Mesh::GetIndicesCount() const
	//{
	//	return mIndicesCount;
	//}
	//uint32_t Mesh::GetNormalsCount() const
	//{
	//	return mNormalsCount;
	//}
	//uint32_t Mesh::GetTexCoordsCount() const
	//{
	//	return mTexCoordsCount;
	//}
}