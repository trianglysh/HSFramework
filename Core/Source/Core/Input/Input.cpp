#include "CorePCH.h"
#include "Input.h"

#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace HSFramework
{
	static InputState GLFWInputStateToHSFWState(int state)
	{
		switch (state)
		{
		case GLFW_PRESS:   return InputState::Press;
		case GLFW_REPEAT:  return InputState::Repeat;
		case GLFW_RELEASE: return InputState::Release;
		}

		HS_CORE_ASSERT("Unknown input state!");
		return (InputState)0;
	}

	InputState Input::GetKeyState(KeyCode keycode)
	{
		int state = glfwGetKey(Window::GetHandle(), keycode);
		return GLFWInputStateToHSFWState(state);
	}

	InputState Input::GetMouseButtonState(MouseCode button)
	{
		int state = glfwGetMouseButton(Window::GetHandle(), button);
		return GLFWInputStateToHSFWState(state);
	}

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		return GetKeyState(keycode) == InputState::Press;
	}

	bool Input::IsKeyRepeated(KeyCode keycode)
	{
		return GetKeyState(keycode) == InputState::Repeat;
	}

	bool Input::IsKeyDown(KeyCode keycode)
	{
		InputState state = GetKeyState(keycode);
		return state == InputState::Press || state == InputState::Repeat;
	}

	bool Input::IsKeyReleased(KeyCode keycode)
	{
		return GetKeyState(keycode) == InputState::Release;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		return GetMouseButtonState(button) == InputState::Press;
	}

	bool Input::IsMouseButtonReleased(MouseCode button)
	{
		return GetMouseButtonState(button) == InputState::Release;
	}

	glm::vec2 Input::GetCursorPos()
	{
		double xpos, ypos;
		glfwGetCursorPos(Window::GetHandle(), &xpos, &ypos);

		return { (float) xpos, (float) ypos };
	}

	float Input::GetCursorX()
	{
		return GetCursorPos().x;
	}

	float Input::GetCursorY()
	{
		return GetCursorPos().y;
	}
}
