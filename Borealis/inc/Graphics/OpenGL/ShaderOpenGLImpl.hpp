/******************************************************************************/
/*!
\file		ShaderOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 8, 2024
\brief		Declares the functions for OpenGL Shader Class of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SHADER_OPENGL_IMPLHPP
#define SHADER_OPENGL_IMPLHPP
#include <Graphics/Shader.hpp>
namespace Borealis
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetName() const override { return mName; }

		void Set(const char* name, const int& value) override;
		void Set(const char* name, const int* values, const uint32_t& count) override;
		void Set(const char* name, const float& value) override;
		void Set(const char* name, const glm::vec2& value) override;
		void Set(const char* name, const glm::vec3& value) override;
		void Set(const char* name, const glm::vec4& value) override;
		void Set(const char* name, const glm::mat3& value) override;
		void Set(const char* name, const glm::mat4& value) override;

	private:
		using GLenum = unsigned int;

		void PushUniform(const char* name, const int& value);
		void PushUniform(const char* name, const int* values, const uint32_t count);
		void PushUniform(const char* name, const float& value);
		void PushUniform(const char* name, const glm::vec2& value);
		void PushUniform(const char* name, const glm::vec3& value);
		void PushUniform(const char* name, const glm::vec4& value);
		void PushUniform(const char* name, const glm::mat3& value);
		void PushUniform(const char* name, const glm::mat4& value);

		GLenum ShaderTypeFromString(const std::string& type);
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		std::string mName;
		unsigned int mRendererID;
	};

}
#endif