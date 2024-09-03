/******************************************************************************/
/*!
\file		Shader.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Declares the functions for Generic Shader Class of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SHADER_HPP
#define SHADER_HPP
#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace Borealis
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Set(const char* name, const int& value) = 0;
		virtual void Set(const char* name, const int* values, const uint32_t& count) = 0;
		virtual void Set(const char* name, const float& value) = 0;
		virtual void Set(const char* name, const glm::vec2& value) = 0;
		virtual void Set(const char* name, const glm::vec3& value) = 0;
		virtual void Set(const char* name, const glm::vec4& value) = 0;
		virtual void Set(const char* name, const glm::mat3& value) = 0;
		virtual void Set(const char* name, const glm::mat4& value) = 0;
	};

	class ShaderAPI
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader, const std::string& name);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& filepath, const std::string& name);
		Ref<Shader> Get(const std::string& name);
		bool hasShader(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> mShaders;
	};

}
#endif