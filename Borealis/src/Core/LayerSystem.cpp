/******************************************************************************/
/*!
\file		LayerSystem.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 18, 2024
\brief		Defines the Layer System in Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/
#include <BorealisPCH.hpp>
#include <Core/LayerSystem.hpp>

namespace Borealis
{
	/*!***********************************************************************
		\brief
			Constructor of Layer System. Initializes the Layer System
	*************************************************************************/
	LayerSystem::LayerSystem() : mLayers(new std::vector<Layer*>()), mLayerInsertIndex(0) {}

	/*!***********************************************************************
		\brief
			Destructor of Layer System. Frees the Layer System
	*************************************************************************/
	LayerSystem::~LayerSystem()
	{
		for (Layer* layer : *mLayers)
		{
			layer->Free();
			delete layer;
		}

		delete mLayers;
	}

	void LayerSystem::Clear()
	{
		for (Layer* layer : *mLayers)
		{
			layer->Free();
			delete layer;
		}

		mLayers->clear();
		mLayerInsertIndex = 0;
	}

	/*!***********************************************************************
		\brief
			Pushes a layer into the system
		\param[in] layer
			Address of the layer to be pushed into the system
	*************************************************************************/
	void LayerSystem::PushLayer(Layer* layer)
	{
		mLayers->emplace(mLayers->begin() + mLayerInsertIndex, layer);
		mLayerInsertIndex++;
	}

	/*!***********************************************************************
		\brief
			Pushes an overlay into the system
		\param[in] overlay
			Address of the overlay to be pushed into the system
	*************************************************************************/
	void LayerSystem::PushOverlay(Layer* overlay)
	{
		mLayers->emplace_back(overlay);
	}

	/*!***********************************************************************
		\brief
			Pops a layer from the system
		\param[in] layer
			Address of the layer to be popped from the system
	*************************************************************************/
	void LayerSystem::PopLayer(Layer* layer)
	{
		auto it = std::find(mLayers->begin(), mLayers->end(), layer);
		if (it != mLayers->end())
		{
			mLayers->erase(it);
			mLayerInsertIndex--;
		}
		layer->Free();
	}

	/*!***********************************************************************
		\brief
			Pops an overlay from the system
		\param[in] overlay
			Address of the overlay to be popped from the system
	*************************************************************************/
	void LayerSystem::PopOverlay(Layer* overlay)
	{
		auto it = std::find(mLayers->begin(), mLayers->end(), overlay);
		if (it != mLayers->end())
			mLayers->erase(it);

		overlay->Free();
	}
} // End of namespace Borealis
