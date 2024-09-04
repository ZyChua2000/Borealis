/******************************************************************************/
/*!
\file		Serialiser.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 14, 2024
\brief		Declares the class for Serialiser

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SERIALISER_HPP
#define SERIALISER_HPP
#include <Core/Core.hpp>
#include <Scene/Scene.hpp>
namespace Borealis
{
	class Serialiser
	{
	public:
		/*!***********************************************************************
			\brief
				Default constructor for Serialiser
			\param scene
				The scene to serialise
		*************************************************************************/
		Serialiser(const Ref<Scene>& scene);

		/*!***********************************************************************
			\brief
				Serialises the scene to a file
			\param filepath
				The file path to serialise the scene to
			\return
				True if serialisation is successful, false otherwise
		*************************************************************************/
		bool SerialiseScene(const std::string& filepath);

		/*!***********************************************************************
			\brief
				Deserialises the scene from a file
			\param filepath
				The file path to deserialise the scene from
			\return
				True if deserialisation is successful, false otherwise
		*************************************************************************/
		bool DeserialiseScene(const std::string& filepath);

		/*!***********************************************************************
			\brief
				Serialises the editor style to a file
			\return
				True if serialisation is successful, false otherwise
		*************************************************************************/
		static bool SerialiseEditorStyle();

		/*!***********************************************************************
			\brief
				Deserialises the editor style from a file
			\return
				True if deserialisation is successful, false otherwise
		*************************************************************************/
		static bool DeserialiseEditorStyle();
	private:

		Ref<Scene> mScene; //!< The scene to serialise

	};
}

#endif