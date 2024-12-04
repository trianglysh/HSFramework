#include "CorePCH.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace HSFramework
{
	static std::string_view ShaderTypeToString(GLenum type)
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
		case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
		default: break;
		}

		HS_CORE_ASSERT(false, "Unknown shader type!");
		return "";
	}

	Shader::Shader(std::string_view name, std::string_view vertSrc, std::string_view fragSrc)
		: m_Name(name), m_Sources { { GL_VERTEX_SHADER, std::string(vertSrc) }, { GL_FRAGMENT_SHADER, std::string(fragSrc) } }
	{
		GLuint program = glCreateProgram();

		auto CreateShader = [this](GLenum type) -> GLuint
		{
			GLuint shader = glCreateShader(type);

			const char* src = m_Sources.at(type).data();
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);

			int status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (!status)
			{
				int infoLogLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog(infoLogLength, '\n');
				glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog.data());

				HS_CORE_ERROR("Failed to compile the {} shader of the shader whose name is '{}', info log:\n{}", ShaderTypeToString(type), m_Name, infoLog);
				glDeleteShader(shader);
			}

			return shader;
		};

		GLuint vertexShader = CreateShader(GL_VERTEX_SHADER), fragmentShader = CreateShader(GL_FRAGMENT_SHADER);
		if (!vertexShader || !fragmentShader)
		{
			return;
		}

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		int status;
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (!status)
		{
			int infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, '\n');
			glGetProgramInfoLog(program, infoLogLength, &infoLogLength, infoLog.data());

			HS_CORE_ERROR("Failed to link the shader whose name is '{}', info log:\n{}", m_Name, infoLog);
			glDeleteProgram(program);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_RendererID = program;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetBool(std::string_view name, bool value)
	{
		glUniform1i(GetUniformLocation(name), (int) value);
	}

	void Shader::SetInt(std::string_view name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetInt2(std::string_view name, const glm::ivec2& value)
	{
		glUniform2i(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetInt3(std::string_view name, const glm::ivec3& value)
	{
		glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetInt4(std::string_view name, const glm::ivec4& value)
	{
		glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetFloat(std::string_view name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetFloat2(std::string_view name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetFloat3(std::string_view name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetFloat4(std::string_view name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(std::string_view name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	int Shader::GetUniformLocation(std::string_view name) const
	{
		return glGetUniformLocation(m_RendererID, name.data());
	}
}
