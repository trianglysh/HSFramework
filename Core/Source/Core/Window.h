#pragma once

#include "Core/Base.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

// Forward declaration of GLFWwindow.
struct GLFWwindow;

namespace HSFramework
{
	struct WindowProps
	{
		std::string Title;
		int Width, Height;
		bool Resizable, Fullscreen, VSync;

		WindowProps(std::string_view title = "HSFramework",
					int width = 1600,
					int height = 900,
					bool resizable = true,
					bool fullscreen = false,
					bool vSync = true)
			: Title(title), Width(width), Height(height), Resizable(resizable), Fullscreen(fullscreen), VSync(vSync) { }
	};

	class Window
	{
	public:
		static bool Init(const WindowProps& props = {});
		static bool ShouldClose();
		static void Update();
		static bool Destroy();

		static void SetTitle(std::string_view title);
		static void SetSize(int width, int height);
		static void SetWidth(int width);
		static void SetHeight(int height);
		static void SetVSync(bool vSync);

		static void Minimize();
		static void Restore();
		static void Maximize();

		// Makes a request attention to the operating system. For example, in Windows, it will make the application's logo on the taskbar flush orange.
		static void RequestAttention();

		// Forcefully makes the window the focused one.
		static void Focus();

		// Checks if the window has the current focus.
		static bool HasFocus();

		static const WindowProps& GetProps() { return s_Props; }
		static const std::string& GetTitle() { return s_Props.Title; }
		static int GetWidth() { return s_Props.Width; }
		static int GetHeight() { return s_Props.Height; }
		static bool IsResizable() { return s_Props.Resizable; }
		static bool IsFullscreen() { return s_Props.Fullscreen; }
		static bool IsVSync() { return s_Props.VSync; }
	private:
		inline static WindowProps s_Props;
		inline static GLFWwindow* s_Handle = nullptr;
	};
}
