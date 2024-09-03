/******************************************************************************/
/*!
\file		Buffer.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Declares the Generic class for Graphics Buffer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <Core/LoggerSystem.hpp>
#include <Core/Core.hpp>
namespace Borealis
{
	// Virtual classes for if we ever expand to non OpenGL APIs such as DX

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		BOREALIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string mName;
		size_t mOffset;
		uint32_t mSize;
		ShaderDataType mType;
		bool mNormalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: mName(name), mType(type), mSize(ShaderDataTypeSize(type)), mOffset(0), mNormalized(normalized) {}

		uint32_t GetComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements)
			: mElements(elements)
		{
			CalculateOffsetsAndStride();
		}
		BufferLayout() {};

		std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

		inline const std::vector<BufferElement>& GetElements() const { return mElements; }
		inline uint32_t GetStride() const { return mStride; }


	private:
		void CalculateOffsetsAndStride();
		std::vector<BufferElement> mElements;
		uint32_t mStride;
	};
	class VertexBuffer
	{
	public :
		virtual ~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class ElementBuffer
	{
	public: 
		virtual ~ElementBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static Ref<ElementBuffer> Create(uint32_t* indices, uint32_t count);
	};
}

#endif