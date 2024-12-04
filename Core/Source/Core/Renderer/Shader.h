#pragma once

#include "Core/Base.h"

#include <glm/glm.hpp>

namespace HSFramework
{
	class Shader
	{
	public:
		Shader(std::string_view name, std::string_view vertSrc, std::string_view fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetBool(std::string_view name, bool value);
		void SetInt(std::string_view name, int value);
		void SetInt2(std::string_view name, const glm::ivec2& value);
		void SetInt3(std::string_view name, const glm::ivec3& value);
		void SetInt4(std::string_view name, const glm::ivec4& value);
		void SetFloat(std::string_view name, float value);
		void SetFloat2(std::string_view name, const glm::vec2& value);
		void SetFloat3(std::string_view name, const glm::vec3& value);
		void SetFloat4(std::string_view name, const glm::vec4& value);
		void SetMat4(std::string_view name, const glm::mat4& value);

		const std::string& GetName() const { return m_Name; }
	private:
		int GetUniformLocation(std::string_view name) const;
	private:
		uint32_t m_RendererID = 0;

		std::string m_Name;
		std::unordered_map<uint32_t, std::string> m_Sources;
	};
}
