/******************************************************************************/
/*!
\file		LayerSystem.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 18, 2024
\brief		Declares the Layer System in Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef LAYER_SYSTEM_HPP
#define LAYER_SYSTEM_HPP
#include <Core/Core.hpp>
#include <Core/Layer.hpp>
#include <vector>
namespace Borealis
{
	class BOREALIS_API LayerSystem
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor of Layer System. Initializes the Layer System
		*************************************************************************/
		LayerSystem();

		/*!***********************************************************************
			\brief
				Destructor of Layer System. Frees the Layer System
		*************************************************************************/
		~LayerSystem();

		void Clear();

		/*!***********************************************************************
			\brief
				Pushes a layer into the system
			\param[in] layer
				Address of the layer to be pushed into the system
		*************************************************************************/
		void PushLayer(Layer* layer);

		/*!***********************************************************************
			\brief
				Pushes an overlay into the system
			\param[in] overlay
				Address of the overlay to be pushed into the system
		*************************************************************************/
		void PushOverlay(Layer* overlay);

		/*!***********************************************************************
			\brief
				Pops a layer from the system
			\param[in] layer
				Address of the layer to be popped from the system
		*************************************************************************/
		void PopLayer(Layer* layer);

		/*!***********************************************************************
			\brief
				Pops an overlay from the system
			\param[in] overlay
				Address of the overlay to be popped from the system
		*************************************************************************/
		void PopOverlay(Layer* overlay);

		// Begin and End iterators for the layers
		std::vector<Layer*>::iterator begin() { return mLayers->begin(); }
		std::vector<Layer*>::iterator end() { return mLayers->end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return mLayers->rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return mLayers->rend(); }

	private:
		std::vector<Layer*>* mLayers;
		unsigned mLayerInsertIndex = 0;

	}; // End of LayerSystem Class

} // End of namespace Borealis
#endif