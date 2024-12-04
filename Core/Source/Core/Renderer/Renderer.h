#pragma once

#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/Shader.h"

namespace HSFramework
{
	struct Renderer
	{
		static void SetViewport(int x, int y, int width, int height);
		static void SetClearColor(float r, float g, float b, float a);
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t count);
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0);
	};
}
