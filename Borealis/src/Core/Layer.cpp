/******************************************************************************/
/*!
\file		Layer.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 18, 2024
\brief		Defines the Layer Class to be used by Layer System in Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Core/Layer.hpp>

namespace Borealis
{
#ifndef _DIST
	/*!***********************************************************************
		\brief
			Constructor for Layer
		\param[in] name
			Name of the layer
		\note
			Layer name is used for debugging purposes, not available in
			distribution build
	*************************************************************************/
	Layer::Layer(const std::string& name) : mName(new std::string(name))
	{
	}
#else
	/*!***********************************************************************
		\brief
			Default Constructor for Layer
		\note
			Used in distribution build. Layer name is not available in
			non Distribution build.
	*************************************************************************/
	Layer::Layer()
	{
	}
#endif
	/*!***********************************************************************
		\brief
			Destructor for Layer
	*************************************************************************/
	Layer::~Layer()
	{
#ifndef _DIST
		delete mName;
#endif
	}
}