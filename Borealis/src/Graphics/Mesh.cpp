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

namespace Borealis
{
	Mesh::Mesh() : mVertices(nullptr), mIndices(nullptr), mNormals(nullptr), mTexCoords(nullptr), mVerticesCount(0), mIndicesCount(0), mNormalsCount(0), mTexCoordsCount(0)
	{
	}
	Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords)
	{
		SetVertices(vertices);
		SetIndices(indices);
		SetNormals(normals);
		SetTexCoords(texCoords);
	}
	Mesh::~Mesh()
	{
		if (mTexCoordsCount)
		{
			delete[] mTexCoords;
		}
		if (mNormalsCount)
		{
			delete[] mNormals;
		}
		if (mIndicesCount)
		{
			delete[] mIndices;
		}
		if (mVerticesCount)
		{
			delete[] mVertices;
		}
	}
	void Mesh::SetVertices(const std::vector<glm::vec3>& vertices)
	{
		const size_t& size = vertices.size();
		if (size > 0)
		{
			if (mVerticesCount == 0)
			{
				mVertices = new glm::vec3[size];
				memcpy(mVertices, vertices.data(), size * sizeof(glm::vec3));
			}
			else
			{
				delete[] mVertices;
				mVertices = new glm::vec3[size];
				memcpy(mVertices, vertices.data(), size * sizeof(glm::vec3));
			}
		}
		else
		{
			ENGINE_LOG_WARN("Mesh::SetVertices() - No vertices to set");
			return;
		}
		mVerticesCount = (uint32_t)size;
	}
	void Mesh::SetIndices(const std::vector<unsigned int>& indices)
	{
		const size_t& size = indices.size();
		if (size > 0)
		{
			if (mIndicesCount == 0)
			{
				mIndices = new unsigned[size];
				memcpy(mIndices, indices.data(), size * sizeof(unsigned));
			}
			else
			{
				delete[] mIndices;
				mIndices = new unsigned[size];
				memcpy(mIndices, indices.data(), size * sizeof(unsigned));
			}
		}
		else
		{
			ENGINE_LOG_WARN("Mesh::SetIndices() - No index to set");
			return;
		}
		mIndicesCount = (uint32_t)size;
	}
	void Mesh::SetNormals(const std::vector<glm::vec3>& normals)
	{
		const size_t& size = normals.size();
		if (size > 0)
		{
			if (mNormalsCount == 0)
			{
				mNormals = new glm::vec3[size];
				memcpy(mNormals, normals.data(), size * sizeof(glm::vec3));
			}
			else
			{
				delete[] mNormals;
				mNormals = new glm::vec3[size];
				memcpy(mNormals, normals.data(), size * sizeof(glm::vec3));
			}
		}
		else
		{
			ENGINE_LOG_WARN("Mesh::SetNormals() - No normals to set");
			return;
		}
		mNormalsCount = (uint32_t)size;
	}
	void Mesh::SetTexCoords(const std::vector<glm::vec2>& texCoords)
	{
		const size_t& size = texCoords.size();
		if (size > 0)
		{
			if (mTexCoordsCount == 0)
			{
				mTexCoords = new glm::vec2[size];
				memcpy(mTexCoords, texCoords.data(), size * sizeof(glm::vec2));
			}
			else
			{
				delete[] mTexCoords;
				mTexCoords = new glm::vec2[size];
				memcpy(mTexCoords, texCoords.data(), size * sizeof(glm::vec2));
			}
		}
		else
		{
			ENGINE_LOG_WARN("Mesh::SetTexCoords() - No TexCoords to set");
			return;
		}
		mTexCoordsCount = (uint32_t)size;
	}
	const glm::vec3* Mesh::GetVertices() const
	{
		return mVertices;
	}
	const unsigned int* Mesh::GetIndices() const
	{
		return mIndices;
	}
	const glm::vec3* Mesh::GetNormals() const
	{
		return mNormals;
	}
	const glm::vec2* Mesh::GetTexCoords() const
	{
		return mTexCoords;
	}
	uint32_t Mesh::GetVerticesCount() const
	{
		return mVerticesCount;
	}
	uint32_t Mesh::GetIndicesCount() const
	{
		return mIndicesCount;
	}
	uint32_t Mesh::GetNormalsCount() const
	{
		return mNormalsCount;
	}
	uint32_t Mesh::GetTexCoordsCount() const
	{
		return mTexCoordsCount;
	}
}