/******************************************************************************/
/*!
\file		VertexBone.hpp
\author 	Vanesius Faith Cheong
\par    	email: vanesiusfaith.c\@digipen.edu
\date   	September 15, 2024
\brief		Declares the class for Vertex Bone

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef VERTEXBONE_HPP
#define VERTEXBONE_HPP

#include <Core/Core.hpp>

#define MAX_NUM_BONES_PER_VERTEX 4

namespace Borealis 
{
	struct VertexBoneData 
	{
		uint32_t mBoneIds[MAX_NUM_BONES_PER_VERTEX] = {};
		float mWeights[MAX_NUM_BONES_PER_VERTEX] = {};

		VertexBoneData() {}

		void AddBoneData(uint32_t boneid, float weight) {

			for (uint32_t i{}; i < MAX_NUM_BONES_PER_VERTEX; ++i)
			{
				if (mWeights[i] == 0.f)
				{
					mBoneIds[i] = boneid;
					mWeights[i] = weight;
					//printf("bone %d weight %f index %i\n", boneid, weight, i);
					return;
				}
			}
		}
	};
}
#endif