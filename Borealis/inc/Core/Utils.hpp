/***************************************************************************** /
/*!
\file		Utils.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 15, 2024
\brief		Declares the functions for Utilities

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <glm/glm.hpp>
#include <Graphics/Framebuffer.hpp>
namespace Borealis
{
	struct FileDialogs
	{
		/*!***********************************************************************
			\brief
				Opens a dialog box to open a file
			\param[in] filter
				The filter for the file dialog box
		*************************************************************************/
		static std::string OpenFile(const char* filter);

		/*!***********************************************************************
			\brief
				Opens a dialog box to save a file
			\param[in] filter
				The filter for the file dialog box
		*************************************************************************/
		static std::string SaveFile(const char* filter);
	};


	struct GraphicsUtils
	{
		/*!***********************************************************************
			\brief
				Checks if the format is a depth format
			\return
				True if the format is a depth format, false otherwise
		*************************************************************************/
		static bool IsDepthFormat(FramebufferTextureFormat format);

		/*!***********************************************************************
			\brief
				Switch between texture targets
			\param[in] multiSampled
				Whether the texture is multi-sampled
			\return
				The texture target
		*************************************************************************/
		static unsigned TextureTarget(bool multiSampled);

		/*!***********************************************************************
			\brief
				Creates textures using oipengl
			\param[in] multiSampled
				Whether the texture is multi-sampled
			\param[in] colorAttachmentData
				The data for the color attachment
			\param[in] colorAttachmentSize
				The size of the color attachment data
		*************************************************************************/
		static void CreateTextures(bool multiSampled, uint32_t* colorAttachmentData, size_t colorAttachmentSize);

		/*!***********************************************************************
			\brief
				Binds a texture
			\param[in] multiSampled
				Whether the texture is multi-sampled
			\param[in] id
				The id of the texture
		*************************************************************************/
		static void BindTexture(bool multiSampled, uint32_t id);

		/*!***********************************************************************
			\brief
				Attaches a color texture to the framebuffer
			\param[in] id
				The id of the texture
			\param[in] samples
				The number of samples
			\param[in] internalformat
				The internal format of the texture
			\param[in] format
				The format of the texture
			\param[in] width
				The width of the texture
			\param[in] height
				The height of the texture
			\param[in] index
				The index of the texture
		*************************************************************************/
		static void AttachColorTexture(uint32_t id, int samples, unsigned internalformat, unsigned format, uint32_t width, uint32_t height, int index);
		
		/*!***********************************************************************
			\brief
				Attaches a depth texture to the framebuffer
			\param[in] id
				The id of the texture
			\param[in] samples
				The number of samples
			\param[in] format
				The format of the texture
			\param[in] attachmentType
				The attachment type of the texture
			\param[in] width
				The width of the texture
			\param[in] height
				The height of the texture
		*************************************************************************/
		static void AttachDepthTexture(uint32_t id, int samples, unsigned format, unsigned attachmentType, uint32_t width, uint32_t height);
	};
}

#endif