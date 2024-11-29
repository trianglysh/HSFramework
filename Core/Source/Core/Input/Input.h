#pragma once

#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseCodes.h"
#include "Core/Input/InputState.h"

#include <glm/glm.hpp>

namespace HSFramework
{
	class Input
	{
	public:
		static InputState GetKeyState(KeyCode keycode);
		static InputState GetMouseButtonState(MouseCode button);

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsKeyRepeated(KeyCode keycode);
		static bool IsKeyDown(KeyCode keycode);
		static bool IsKeyReleased(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static bool IsMouseButtonReleased(MouseCode button);

		static glm::vec2 GetCursorPos();
		static float GetCursorX();
		static float GetCursorY();
	};
}
