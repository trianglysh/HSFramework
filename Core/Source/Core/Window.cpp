#include "CorePCH.h"
#include "Window.h"

#include "Core/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace HSFramework
{
	static void GLFWErrorCallback(int errorcode, const char* description)
	{
		HS_CORE_ERROR("GLFW Error ({}): {}", errorcode, description);
	}

	bool Window::Init(const WindowProps& props)
	{
		s_Props = props;

		if (s_Handle)
		{
			if (!ShouldClose())
			{
				HS_CORE_WARN("Got a call to Window::Init - but the window is already initialized and running, because of this the window will be recreated.");
			}

			Destroy();
		}

		HS_CORE_INFO("Creating window '{}' ({}x{})", s_Props.Title, s_Props.Width, s_Props.Height);

		if (!glfwInit())
		{
			const char* errorDesc;
			int errorCode = glfwGetError(&errorDesc);

			HS_CORE_ERROR("Window initialization failed because glfwInit() failed. glfwGetError returned with an error code of {} and the description: {}", errorCode, errorDesc);
			return false;
		}
		glfwSetErrorCallback(GLFWErrorCallback);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_RESIZABLE, s_Props.Resizable);
		
		s_Handle = glfwCreateWindow
		(
			s_Props.Width,
			s_Props.Height,
			s_Props.Title.c_str(),
			s_Props.Fullscreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		);

		if (!s_Handle)
		{
			HS_CORE_ERROR("Window initialization failed because glfwCreateWindow() returned NULL!");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(s_Handle);
		SetVSync(s_Props.VSync); // Flush vSync value

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			HS_CORE_ERROR("Window initialization failed, couldn't initialize Glad (OpenGL function import failure)!");

			glfwDestroyWindow(s_Handle);
			glfwTerminate();

			return false;
		}

		glfwSetWindowCloseCallback(s_Handle, [](GLFWwindow* window)
		{
			Application::Get()->SetState(ManagementState::None);
		});

		glfwSetWindowSizeCallback(s_Handle, [](GLFWwindow* window, int width, int height)
		{
			s_Props.Width = width;
			s_Props.Height = height;
		});

		HS_CORE_TRACE("Window creation successful!");
		return true;
	}

	bool Window::ShouldClose()
	{
		return s_Handle && glfwWindowShouldClose(s_Handle);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(s_Handle);
	}

	bool Window::Destroy()
	{
		if (!s_Handle)
		{
			return false;
		}

		glfwDestroyWindow(s_Handle);
		glfwTerminate();

		s_Handle = nullptr;
		return true;
	}

	void Window::SetTitle(std::string_view title)
	{
		s_Props.Title = title;
		glfwSetWindowTitle(s_Handle, title.data());
	}

	void Window::SetSize(int width, int height)
	{
		// We don't update s_Props' Width and Heigth fields here, they are done in the SizeCallback.
		glfwSetWindowSize(s_Handle, width, height);
	}

	void Window::SetWidth(int width)
	{
		SetSize(width, s_Props.Height);
	}

	void Window::SetHeight(int height)
	{
		SetSize(s_Props.Width, height);
	}

	void Window::SetVSync(bool vSync)
	{
		s_Props.VSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}

	void Window::Minimize()
	{
		glfwIconifyWindow(s_Handle);
	}

	void Window::Restore()
	{
		glfwRestoreWindow(s_Handle);
	}

	void Window::Maximize()
	{
		glfwMaximizeWindow(s_Handle);
	}

	void Window::RequestAttention()
	{
		glfwRequestWindowAttention(s_Handle);
	}

	void Window::Focus()
	{
		glfwFocusWindow(s_Handle);
	}

	bool Window::HasFocus()
	{
		if (!s_Handle)
		{
			return false;
		}

		return glfwGetWindowAttrib(s_Handle, GLFW_FOCUSED);
	}
}