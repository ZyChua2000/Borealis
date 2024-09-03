/******************************************************************************/
/*!
\file		Shader.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Implements the functions for Generic Shader Class of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/Shader.hpp>
#include <Core/LoggerSystem.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/ShaderOpenGLImpl.hpp>

namespace Borealis
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ENGINE_LOG_ERROR("RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return MakeRef<OpenGLShader>(filepath);
		}
		ENGINE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: ENGINE_LOG_ERROR("RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return MakeRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		ENGINE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;
	}
	void ShaderAPI::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		if (hasShader(name))
		{
			ENGINE_LOG_WARN("Shader {} already exists!", shader->GetName());
		}
		mShaders[name] = shader;

	}
	void ShaderAPI::Add(const Ref<Shader>& shader, const std::string& name)
	{
		if (hasShader(name))
		{
			ENGINE_LOG_WARN("Shader {} already exists!", shader->GetName());
		}
		mShaders[name] = shader;
	}
	Ref<Shader> ShaderAPI::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderAPI::Load(const std::string& filepath, const std::string& name)
	{
		auto shader = Shader::Create(filepath);
		Add(shader, name);
		return shader;
	}
	Ref<Shader> ShaderAPI::Get(const std::string& name)
	{
		if (!hasShader(name))
		{
			ENGINE_LOG_ERROR("Shader name not found in library!");
			return nullptr;
		}
		return mShaders[name];
	}
	bool ShaderAPI::hasShader(const std::string& name) const
	{
		return mShaders.find(name) != mShaders.end();
	}
}