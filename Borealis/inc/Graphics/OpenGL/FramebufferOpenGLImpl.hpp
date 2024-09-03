/******************************************************************************/
/*!
\file		FramebufferOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Declares the OpenGL class for Frame buffers

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef FRAME_BUFFER_OPENGL_IMPL_HPP
#define FRAME_BUFFER_OPENGL_IMPL_HPP
#include <Core/Core.hpp>
#include <Graphics/Framebuffer.hpp>
namespace Borealis
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferProperties& props);
		~OpenGLFrameBuffer();

		void Bind() override;
		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;
		int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		void ClearAttachment(uint32_t attachmentIndex, int value) override;
		const FrameBufferProperties& GetProperties() const override { return mProps; }

		uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const { return mColorAttachments[index]; }


		void Recreate();
	private:
		FrameBufferProperties mProps;
		uint32_t mRendererID;

		std::vector<FrameBufferTextureProperties> mColorAttachmentProps;
		FrameBufferTextureProperties mDepthAttachmentProp;
		std::vector<uint32_t> mColorAttachments;
		uint32_t mDepthAttachment;

	};
}

#endif