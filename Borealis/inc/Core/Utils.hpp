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
#include <glm/gtc/quaternion.hpp>
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

		static bool IsDepthFormat(FramebufferTextureFormat format);
		static unsigned TextureTarget(bool multiSampled);
		static void CreateTextures(bool multiSampled, uint32_t* colorAttachmentData, size_t colorAttachmentSize);
		static void BindTexture(bool multiSampled, uint32_t id);
		static void AttachColorTexture(uint32_t id, int samples, unsigned internalformat, unsigned format, uint32_t width, uint32_t height, int index);
		static void AttachDepthTexture(uint32_t id, int samples, unsigned format, unsigned attachmentType, uint32_t width, uint32_t height);
	};

	struct Math
	{
		static glm::vec3 QuatToEuler(glm::quat quat, bool radians = false);
		static glm::quat EulerToQuat(glm::vec3 euler, bool radians = false);
	};
}

#endif