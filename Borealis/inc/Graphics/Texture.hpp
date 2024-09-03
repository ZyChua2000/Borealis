/******************************************************************************/
/*!
\file		Texture.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 8, 2024
\brief		Declares the Generic class for Texture primitives for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <Core/Core.hpp>
namespace Borealis
{
	// Base Class for Textures, Completely Virtual
	class Texture 
	{
	public:
		virtual ~Texture() {};
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t unit = 0) const = 0;
		virtual bool operator== (const Texture& other) const = 0;
	};

	// Virtual Class for 2D Textures
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const uint32_t& width, const uint32_t& height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}

#endif