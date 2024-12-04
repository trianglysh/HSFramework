#include "RuntimePCH.h"

#include "Core/Application.h"
#include "Core/StaticData/Project.h"
#include "Core/Log.h"

#include "Core/Renderer/Renderer.h"

namespace HSFramework::Runtime
{
	bool LoadProject();

	int RtMain(int argc, char** argv)
	{
		Log::Init();
		HS_RUNTIME_INFO("Initialized logging.");

		// Cannot make this string_view because the current directory check stage's string would go out of scope by the time this variable is referred to.
		std::string projectFilePath;

		if (argc == 2)
		{
			projectFilePath = argv[1];

			if (!std::filesystem::is_regular_file(projectFilePath))
			{
				HS_RUNTIME_FATAL("The specified project filepath '{}' via the command line arguments doesn't resolve into a valid regular file system file.", projectFilePath);
				return EXIT_FAILURE;
			}

			// Change directory for correct path leads
			std::filesystem::current_path(std::filesystem::path(projectFilePath).remove_filename());
		}
		else if (argc > 2)
		{
			HS_RUNTIME_FATAL("HSFramework Runtime only accepts a maximum of one command line argument (excluding execute path) that can only specify the project file to load.");
			return EXIT_FAILURE;
		}
		else
		{
			for (const std::filesystem::path& path : std::filesystem::directory_iterator("."))
			{
				// The great & mighty C++17 lacks the ends_with() functions. Implement a quirky lambda, maybe put this into something like StringUtils later on.
				auto strEndsWith = [](std::string_view str, std::string_view cluster) -> bool
				{
					if (cluster.size() > str.size()) return false;
					if (cluster.size() == str.size()) return str == cluster;

					for (size_t i = str.size() - 1, ci = cluster.size() - 1; ci > 0; i--, ci--)
					{
						if (str[i] != cluster[ci]) return false;
					}

					return true;
				};

				std::string pathStr = path.u8string();
				if (!std::filesystem::is_symlink(path) && std::filesystem::is_regular_file(path) && strEndsWith(pathStr, ".hsproj.json"))
				{
					projectFilePath = std::move(pathStr);
					break;
				}
			}

			if (projectFilePath.empty())
			{
				HS_RUNTIME_FATAL("No project files found in the current working directory!");
				return EXIT_FAILURE;
			}
		}

		if (!Project::LoadFromFile(projectFilePath))
		{
			HS_RUNTIME_FATAL("Project load failed, terminating program.");
			return EXIT_FAILURE;
		}

		Application application({ argv, argc });
		application.SetState(ManagementState::Splash);

		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		Ref<Shader> shader = MakeRef<Shader>
		(
			"TestShader",

			"#version 330 core\n"
			"layout (location = 0) in vec3 a_Position;\n"
			"void main() {\n"
			"	gl_Position = vec4(a_Position, 1.0);\n"
			"}",

			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"	FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
			"}"
		);
		shader->Bind();

		Ref<VertexArray> vertexArray = MakeRef<VertexArray>();
		vertexArray->Bind();

		Ref<VertexBuffer> vertexBuffer = MakeRef<VertexBuffer>(vertices, (uint32_t) sizeof(vertices));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		Ref<IndexBuffer> indexBuffer = MakeRef<IndexBuffer>(indices, 6);
		indexBuffer->Bind();

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		Renderer::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
		while (application.GetManagementState() != ManagementState::None)
		{
			Renderer::Clear();
			Renderer::DrawIndexed(vertexArray);

			application.Update();
		}

		return 0;
	}
}

#if defined HS_SHIPPING && defined HS_PLATFORM_WINDOWS

int CALLBACK WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
)
{
	return HSFramework::Runtime::RtMain(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return HSFramework::Runtime::RtMain(argc, argv);
}

#endif
