/******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 10, 2024
\brief		Defines the class for Graphics Renderer2D

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include "Graphics/Renderer2D.hpp"
#include <Graphics/VertexArray.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/RenderCommand.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Borealis
{
	struct QuadData
	{
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TexCoord;
		uint32_t TexIndex;
		float TilingFactor;

		//Editor only
		int EntityID;
	};

	struct CircleData
	{
		glm::vec3 WorldPosition;
		glm::vec2 LocalPosition;
		glm::vec4 Colour;
		float Thickness;
		float Fade;

		//Editor only
		int EntityID;
	};

	struct LineData
	{
		glm::vec3 Position;
		glm::vec4 Colour;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxCircles = 1000;
		static const uint32_t MaxLines = 100;
		static const uint32_t MaxCircleVertices = MaxCircles * 4;
		static const uint32_t MaxLineVertices = MaxLines * 2;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;


		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		QuadData* QuadBufferBase = nullptr;
		QuadData* QuadBufferPtr = nullptr;

		CircleData* CircleBufferBase = nullptr;
		CircleData* CircleBufferPtr = nullptr;

		LineData* LineBufferBase = nullptr;
		LineData* LineBufferPtr = nullptr;
		
		glm::vec4 VertexPos[4];

		Ref<VertexArray> mQuadVAO;
		Ref<VertexBuffer> mQuadVBO;
		Ref<Shader> mQuadShader; 
		Ref<Texture2D> mWhiteTexture;

		Ref<VertexArray> mCircleVAO;
		Ref<VertexBuffer> mCircleVBO;
		Ref<Shader> mCircleShader;

		Ref<VertexArray> mLineVAO;
		Ref<VertexBuffer> mLineVBO;
		Ref<Shader> mLineShader;
		
		
		Renderer2D::Statistics mStats;
		uint32_t QuadIndexCount = 0;
		uint32_t CircleIndexCount = 0;
		uint32_t LineVertexCount = 0;
		uint32_t TextureSlotIndex = 1; // 0: White texture
	};
	
	
	static Renderer2DData* sData;

	void Renderer2D::Init()
	{
		PROFILE_FUNCTION();

		sData = new Renderer2DData();
		sData->mQuadVAO = VertexArray::Create();

		sData->mQuadVBO = VertexBuffer::Create(sData->MaxVertices * sizeof(QuadData));
		sData->mQuadVBO->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour" },
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float, "a_TexIndex"},
			{ ShaderDataType::Float, "a_TilingFactor"},
			{ ShaderDataType::Int, "a_EntityID"}
			});
		sData->mQuadVAO->AddVertexBuffer(sData->mQuadVBO);

		sData->QuadBufferBase = new QuadData[sData->MaxVertices];
		sData->QuadBufferPtr = sData->QuadBufferBase;

		uint32_t* indices = new uint32_t[sData->MaxIndices];

		for (uint32_t i = 0, offset = 0; i < sData->MaxIndices; i += 6, offset += 4)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
		}

		Ref<ElementBuffer> EBO = ElementBuffer::Create(indices, sData->MaxIndices);
		sData->mQuadVAO->SetElementBuffer(EBO);
		delete[] indices;


		sData->mCircleVAO = VertexArray::Create();

		sData->mCircleVBO = VertexBuffer::Create(sData->MaxCircleVertices * sizeof(CircleData));
		sData->mCircleVBO->SetLayout({
			{ ShaderDataType::Float3, "a_WorldPosition" },
			{ ShaderDataType::Float2, "a_LocalPosition" },
			{ ShaderDataType::Float4, "a_Colour" },
			{ ShaderDataType::Float, "a_Thickness"},
			{ ShaderDataType::Float, "a_Float"},
			{ ShaderDataType::Int, "a_EntityID"}
			});
		sData->mCircleVAO->AddVertexBuffer(sData->mCircleVBO);
		sData->mCircleVAO->SetElementBuffer(EBO);
		sData->CircleBufferBase = new CircleData[sData->MaxCircleVertices];
		sData->CircleBufferPtr = sData->CircleBufferBase;

		sData->mLineVAO = VertexArray::Create();

		sData->mLineVBO = VertexBuffer::Create(sData->MaxLines * sizeof(LineData));
		sData->mLineVBO->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour" },
			});
		sData->mLineVAO->AddVertexBuffer(sData->mLineVBO);
		sData->LineBufferBase = new LineData[sData->MaxLines];
		sData->LineBufferPtr = sData->LineBufferBase;



		sData->mWhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTexData = 0xFFFFFFFF;
		sData->mWhiteTexture->SetData(&whiteTexData, sizeof(uint32_t));

		int samplers[Renderer2DData::MaxTextureSlots];
		for (int i = 0; i < Renderer2DData::MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		sData->mQuadShader = Shader::Create("assets/shaders/Renderer2D_Quad.glsl");
		sData->mQuadShader->Bind();
		sData->mQuadShader->Set("u_Texture", samplers, Renderer2DData::MaxTextureSlots);

		sData->mCircleShader = Shader::Create("assets/shaders/Renderer2D_Circle.glsl");
		sData->mLineShader = Shader::Create("assets/shaders/Renderer2D_Line.glsl");

		sData->TextureSlots[0] = sData->mWhiteTexture;

		sData->VertexPos[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		sData->VertexPos[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		sData->VertexPos[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		sData->VertexPos[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
	}
	void Renderer2D::Free()
	{
		PROFILE_FUNCTION();
		delete[] sData->QuadBufferBase;	
		delete[] sData->CircleBufferBase;
		delete[] sData->LineBufferBase;
		delete sData;	
	}
	void Renderer2D::Begin(const OrthographicCamera& camera)
	{
		PROFILE_FUNCTION();

		sData->mQuadShader->Bind();
		sData->mQuadShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->QuadIndexCount = 0;
		sData->QuadBufferPtr = sData->QuadBufferBase;

		sData->mCircleShader->Bind();
		sData->mCircleShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->CircleIndexCount = 0;
		sData->CircleBufferPtr = sData->CircleBufferBase;

		sData->mLineShader->Bind();
		sData->mLineShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->LineVertexCount = 0;
		sData->LineBufferPtr = sData->LineBufferBase;

		sData->TextureSlotIndex = 1;
	}

	void Renderer2D::Begin(const EditorCamera& camera)
	{
		PROFILE_FUNCTION();

		sData->mQuadShader->Bind();
		sData->mQuadShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->QuadIndexCount = 0;
		sData->QuadBufferPtr = sData->QuadBufferBase;

		sData->mCircleShader->Bind();
		sData->mCircleShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->CircleIndexCount = 0;
		sData->CircleBufferPtr = sData->CircleBufferBase;

		sData->mLineShader->Bind();
		sData->mLineShader->Set("u_ViewProjection", camera.GetViewProjectionMatrix());

		sData->LineVertexCount = 0;
		sData->LineBufferPtr = sData->LineBufferBase;
		 
		sData->TextureSlotIndex = 1;
	}


	void Renderer2D::Begin(const Camera& camera, const glm::mat4& transform)
	{
		PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjectionMatrix() * glm::inverse(transform);

		sData->mQuadShader->Bind();
		sData->mQuadShader->Set("u_ViewProjection", viewProj);

		sData->QuadIndexCount = 0;
		sData->QuadBufferPtr = sData->QuadBufferBase;

		sData->mCircleShader->Bind();
		sData->mCircleShader->Set("u_ViewProjection", viewProj);

		sData->CircleIndexCount = 0;
		sData->CircleBufferPtr = sData->CircleBufferBase;

		sData->mLineShader->Bind();
		sData->mLineShader->Set("u_ViewProjection", viewProj);

		sData->LineVertexCount = 0;
		sData->LineBufferPtr = sData->LineBufferBase;

		sData->TextureSlotIndex = 1;
	}

	void Renderer2D::End()
	{
		PROFILE_FUNCTION();
		Flush();

	}
	void Renderer2D::Flush()
	{
		PROFILE_FUNCTION();
		if (sData->QuadIndexCount)
		{
			uint32_t size = (uint32_t)((uint8_t*)sData->QuadBufferPtr - (uint8_t*)sData->QuadBufferBase);
			sData->mQuadVBO->SetData(sData->QuadBufferBase, size);
			for (uint32_t i = 0; i < sData->TextureSlotIndex; i++)
			{
				sData->TextureSlots[i]->Bind(i);
			}
			sData->mQuadShader->Bind();
			RenderCommand::DrawElements(sData->mQuadVAO, sData->QuadIndexCount);
			sData->mStats.DrawCalls++;
		}

		if (sData->CircleIndexCount)
		{
			uint32_t size = (uint32_t)((uint8_t*)sData->CircleBufferPtr - (uint8_t*)sData->CircleBufferBase);
			sData->mCircleVBO->SetData(sData->CircleBufferBase, size);
			sData->mCircleShader->Bind();
			RenderCommand::DrawElements(sData->mCircleVAO, sData->CircleIndexCount);
			sData->mStats.DrawCalls++;
		}

		if (sData->LineVertexCount)
		{
			uint32_t size = (uint32_t)((uint8_t*)sData->LineBufferPtr - (uint8_t*)sData->LineBufferBase);
			sData->mLineVBO->SetData(sData->LineBufferBase, size);
			sData->mLineShader->Bind();
			RenderCommand::DrawLines(sData->mLineVAO, sData->LineVertexCount);
			sData->mStats.DrawCalls++;
		}

	}

	static void FlushReset()
	{
		Renderer2D::End();
		sData->QuadBufferPtr = sData->QuadBufferBase;
		sData->QuadIndexCount = 0;
		sData->TextureSlotIndex = 1;
	}
	void Renderer2D::DrawSprite(const glm::mat4& transform, const SpriteRendererComponent& sprite, int entityID)
	{
		PROFILE_FUNCTION();
		if (sprite.Texture)
		{
			DrawQuad(transform, sprite.Texture, sprite.TilingFactor, sprite.Colour, entityID);
		}
		DrawQuad(transform, sprite.Colour, entityID);
	}

	void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& colour, float thickness, float fade, int entityID)
	{
		PROFILE_FUNCTION();

		//if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
		//	FlushReset();

		for (int i = 0; i < 4; i++)
		{
			sData->CircleBufferPtr->WorldPosition = transform * sData->VertexPos[i];
			sData->CircleBufferPtr->LocalPosition = sData->VertexPos[i] * 2.0f;
			sData->CircleBufferPtr->Colour = colour;
			sData->CircleBufferPtr->Thickness = thickness;
			sData->CircleBufferPtr->Fade = fade;
			sData->CircleBufferPtr->EntityID = entityID;
			sData->CircleBufferPtr++;
		}

		sData->CircleIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		PROFILE_FUNCTION();

		glm::vec3 p0 = glm::vec3(position.x - size.x / 2, position.y - size.y / 2, position.z);
		glm::vec3 p1 = glm::vec3(position.x + size.x / 2, position.y - size.y / 2, position.z);
		glm::vec3 p2 = glm::vec3(position.x + size.x / 2, position.y + size.y / 2, position.z);
		glm::vec3 p3 = glm::vec3(position.x - size.x / 2, position.y + size.y / 2, position.z);

		DrawLine(p0, p1, colour);
		DrawLine(p1, p2, colour);
		DrawLine(p2, p3, colour);
		DrawLine(p3, p0, colour);

	}
	void Renderer2D::DrawRect(const glm::mat4& transform, const glm::vec4& colour)
	{
		PROFILE_FUNCTION();
		glm::vec3 lineVertices[4];

		for (int i = 0; i < 4; i++)
		{
			lineVertices[i] = transform * sData->VertexPos[i];
		}

		DrawLine(lineVertices[0], lineVertices[1], colour);
		DrawLine(lineVertices[1], lineVertices[2], colour);
		DrawLine(lineVertices[2], lineVertices[3], colour);
		DrawLine(lineVertices[3], lineVertices[0], colour);

	}

	void Renderer2D::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& colour)
	{
		PROFILE_FUNCTION();

		//if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
		//	FlushReset();

		sData->LineBufferPtr->Position = p0;
		sData->LineBufferPtr->Colour = colour;
		sData->LineBufferPtr++;

		sData->LineBufferPtr->Position = p1;
		sData->LineBufferPtr->Colour = colour;
		sData->LineBufferPtr++;

		sData->LineVertexCount += 2;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawRotatedQuad({ position.x,position.y,0 }, rotation, size, colour);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size,  const glm::vec4& colour)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount+6 >= Renderer2DData::MaxIndices)
			FlushReset();

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

		constexpr uint32_t texIndex = 0;
		constexpr glm::vec2 texCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = colour;
			sData->QuadBufferPtr->TexCoord = texCoords[i];
			sData->QuadBufferPtr->TexIndex = texIndex;
			sData->QuadBufferPtr->TilingFactor = 1.0f;
			sData->QuadBufferPtr++;
		}
		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		DrawRotatedQuad({ position.x,position.y,0 }, rotation, size, texture, tilingFactor, tintColour);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		uint32_t textureUnit = 0;

		for (uint32_t i = 1; i < sData->TextureSlotIndex; i++)
		{
			if (*sData->TextureSlots[i].get() == *texture.get())
			{
				textureUnit = i;
				break;
			}
		}

		if (textureUnit == 0)
		{
			if (sData->TextureSlotIndex + 1 == sData->MaxTextureSlots)
			{
				FlushReset();
			}
			textureUnit = sData->TextureSlotIndex;
			sData->TextureSlots[textureUnit] = texture;
			sData->TextureSlotIndex++;
		}

		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * 
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

		constexpr glm::vec4 colour = { 1.0f,1.0f,1.0f,1.0f };
		constexpr glm::vec2 texCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = colour;
			sData->QuadBufferPtr->TexCoord = texCoords[i];
			sData->QuadBufferPtr->TexIndex = textureUnit;
			sData->QuadBufferPtr->TilingFactor = tilingFactor;
			sData->QuadBufferPtr++;
		}

		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		DrawRotatedQuad({ position.x,position.y,0 }, rotation, size, subtexture, tilingFactor, tintColour);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		uint32_t textureUnit = 0;

		for (uint32_t i = 1; i < sData->TextureSlotIndex; i++)
		{
			if (*sData->TextureSlots[i].get() == *subtexture->GetTexture().get())
			{
				textureUnit = i;
				break;
			}
		}

		if (textureUnit == 0)
		{
			if (sData->TextureSlotIndex + 1 == sData->MaxTextureSlots)
			{
				FlushReset();
			}
			textureUnit = sData->TextureSlotIndex;
			sData->TextureSlots[textureUnit] = subtexture->GetTexture();
			sData->TextureSlotIndex++;
		}

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

		constexpr glm::vec4 colour = { 1.0f,1.0f,1.0f,1.0f };

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = colour;
			sData->QuadBufferPtr->TexCoord = subtexture->GetTexCoords()[i];
			sData->QuadBufferPtr->TexIndex = textureUnit;
			sData->QuadBufferPtr->TilingFactor = tilingFactor;
			sData->QuadBufferPtr++;
		}

		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawQuad({ position.x,position.y,0 }, size, colour);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& colour, int entityID)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		constexpr glm::vec2 texCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };
		constexpr uint32_t texIndex = 0;

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = colour;
			sData->QuadBufferPtr->TexCoord = texCoords[i];
			sData->QuadBufferPtr->TexIndex = texIndex;
			sData->QuadBufferPtr->TilingFactor = 1.0f;
			sData->QuadBufferPtr->EntityID = entityID;
			sData->QuadBufferPtr++;
		}

		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
	
		DrawQuad(transform, colour);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		DrawQuad({ position.x,position.y,0 }, size, texture, tilingFactor, tintColour);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		PROFILE_FUNCTION();
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

		DrawQuad(transform, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const float& tilingFactor, const glm::vec4& tint, int entityID)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		uint32_t textureUnit = 0;

		for (uint32_t i = 1; i < sData->TextureSlotIndex; i++)
		{
			if (*sData->TextureSlots[i].get() == *texture.get())
			{
				textureUnit = i;
				break;
			}
		}

		if (textureUnit == 0)
		{
			if (sData->TextureSlotIndex + 1 == sData->MaxTextureSlots)
			{
				FlushReset();
			}
			textureUnit = sData->TextureSlotIndex;
			sData->TextureSlots[textureUnit] = texture;
			sData->TextureSlotIndex++;
		}

		
		constexpr glm::vec2 texCoords[] = { {0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f} };

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = tint;
			sData->QuadBufferPtr->TexCoord = texCoords[i];
			sData->QuadBufferPtr->TexIndex = textureUnit;
			sData->QuadBufferPtr->TilingFactor = tilingFactor;
			sData->QuadBufferPtr->EntityID = entityID;
			sData->QuadBufferPtr++;
		}

		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		DrawQuad({ position.x,position.y,0 }, size, subtexture, tilingFactor, tintColour);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, const float& tilingFactor, const glm::vec4& tintColour)
	{
		PROFILE_FUNCTION();

		if (sData->QuadIndexCount + 6 >= Renderer2DData::MaxIndices)
			FlushReset();

		uint32_t textureUnit = 0;

		for (uint32_t i = 1; i < sData->TextureSlotIndex; i++)
		{
			if (*sData->TextureSlots[i].get() == *subtexture->GetTexture().get())
			{
				textureUnit = i;
				break;
			}
		}

		if (textureUnit == 0)
		{
			if (sData->TextureSlotIndex + 1 == sData->MaxTextureSlots)
			{
				FlushReset();
			}
			textureUnit = sData->TextureSlotIndex;
			sData->TextureSlots[textureUnit] = subtexture->GetTexture();
			sData->TextureSlotIndex++;
		}

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

		constexpr glm::vec4 colour = { 1.0f,1.0f,1.0f,1.0f };

		for (int i = 0; i < 4; i++)
		{
			sData->QuadBufferPtr->Position = transform * sData->VertexPos[i];
			sData->QuadBufferPtr->Colour = colour;
			sData->QuadBufferPtr->TexCoord = subtexture->GetTexCoords()[i];
			sData->QuadBufferPtr->TexIndex = textureUnit;
			sData->QuadBufferPtr->TilingFactor = tilingFactor;
			sData->QuadBufferPtr++;
		}

		sData->QuadIndexCount += 6;

		sData->mStats.QuadCount++;
	}

	void Renderer2D::ResetStats()
	{
		sData->mStats.QuadCount = 0;
		sData->mStats.DrawCalls = 0;
	}

	Renderer2D::Statistics& Renderer2D::GetStats()
	{
		return sData->mStats;
	}

}