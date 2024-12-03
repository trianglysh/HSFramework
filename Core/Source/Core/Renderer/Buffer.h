#pragma once

#include "Core/Assert.h"

namespace HSFramework
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};
	uint32_t SizeOfShaderDataType(ShaderDataType type);

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		uint32_t Size = 0;
		size_t Offset = 0;
		bool Normalized = false;

		BufferElement() = default;
		BufferElement(ShaderDataType type, std::string_view name, bool normalized = false)
			: Name(name), Type(type), Size(SizeOfShaderDataType(type)), Offset(0), Normalized(normalized)
		{
		}

		uint8_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3;
			case ShaderDataType::Mat4:   return 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Bool:   return 1;
			}

			HS_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return m_Elements.rend(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return m_Elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return m_Elements.rend(); }
		std::vector<BufferElement>::const_iterator cbegin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator cend() const { return m_Elements.cend(); }
		std::vector<BufferElement>::const_reverse_iterator crbegin() const { return m_Elements.crbegin(); }
		std::vector<BufferElement>::const_reverse_iterator crend() const { return m_Elements.crend(); }
	private:
		void CalculateOffsetsAndStride()
		{
			m_Stride = 0; // Reset stride
			for (BufferElement& element : m_Elements)
			{
				element.Offset = m_Stride; // Current point thus far
				m_Stride += element.Size; // Increase stride for next iteration start offset
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(const float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, uint32_t size);
		void SetLayout(const BufferLayout& layout);

		const BufferLayout& GetLayout() const { return m_Layout; }
	private:
		uint32_t m_RendererID = 0;
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* indices, uint32_t count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;
	};
}
