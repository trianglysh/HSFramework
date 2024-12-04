#include "CorePCH.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace HSFramework
{
	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, count);
	}

	void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		HS_CORE_ASSERT(vertexArray->GetIndexBuffer(), "Vertex array has no index buffer, yet a call to Renderer::DrawIndexed was made!");

		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count ? count : vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
