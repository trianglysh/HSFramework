#include "CorePCH.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace HSFramework
{
	uint32_t SizeOfShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		}

		HS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static GLuint CreateBuffer(GLenum type, const void* data, uint32_t size, GLenum usage)
	{
		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(type, buffer);
		glBufferData(type, size, data, usage);
		return buffer;
	}

	VertexBuffer::VertexBuffer(uint32_t size)
	{
		m_RendererID = CreateBuffer(GL_ARRAY_BUFFER, nullptr, size, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(const float* vertices, uint32_t size)
	{
		m_RendererID = CreateBuffer(GL_ARRAY_BUFFER, vertices, size, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		m_RendererID = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(uint32_t), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
