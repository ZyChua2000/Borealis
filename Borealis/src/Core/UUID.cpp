/******************************************************************************/
/*!
\file		UUID.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 21, 2024
\brief		Defines the UUID class for IDs for each object

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include <random>
#include <limits>
#include <Core/UUID.hpp>

namespace Borealis
{
	static std::random_device sRandomDevice;
	static std::mt19937_64 sGenerator(sRandomDevice());
	static std::uniform_int_distribution<uint64_t> sDistribution;
	UUID::UUID() : mUUID(sDistribution(sGenerator)){}
	UUID::UUID(uint64_t id) : mUUID(id){

	}

}

