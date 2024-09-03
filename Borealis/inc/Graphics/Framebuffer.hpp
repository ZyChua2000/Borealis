/******************************************************************************/
/*!
\file		Framebuffer.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Declares the Generic class for Frame buffers

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP
#include <Core/Core.hpp>
namespace Borealis
{
	enum class FramebufferTextureFormat
	{
		None,

		//Color
		RGBA8,
		RedInteger,

		//Stencil
		Depth24Stencil8,

		//Default
		Depth = Depth24Stencil8
	};

	struct FrameBufferTextureProperties
	{
		FrameBufferTextureProperties() {};
		FrameBufferTextureProperties(FramebufferTextureFormat format)
			: mTextureFormat(format) {}
		FramebufferTextureFormat mTextureFormat = FramebufferTextureFormat::None;
	};

	struct FrameBufferAttachmentProperties
	{
		FrameBufferAttachmentProperties() = default;
		FrameBufferAttachmentProperties(std::initializer_list<FrameBufferTextureProperties> attachments)
			: mAttachments(attachments) {}
		std::vector<FrameBufferTextureProperties> mAttachments;
	};

	struct FrameBufferProperties
	{
		uint32_t Width, Height;	
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
		FrameBufferAttachmentProperties Attachments;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FrameBufferProperties& GetProperties() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferProperties& properties);

	};
}

#endif