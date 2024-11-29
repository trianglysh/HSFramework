#pragma once

namespace HSFramework
{
	using KeyCode = unsigned short;

	namespace Key
	{
		enum : KeyCode
		{
			// All values here were taken from glfw3.h
			Space              = 32,
			Apostrophe         = 39, /* ' */
			Comma              = 44, /* , */
			Minus              = 45, /* - */
			Period             = 46, /* . */
			Slash              = 47, /* / */
			D0                 = 48,
			D1                 = 49,
			D2                 = 50,
			D3                 = 51,
			D4                 = 52,
			D5                 = 53,
			D6                 = 54,
			D7                 = 55,
			D8                 = 56,
			D9                 = 57,
			Semicolon          = 59, /* ; */
			Equal              = 61, /* = */
			A                  = 65,
			B                  = 66,
			C                  = 67,
			D                  = 68,
			E                  = 69,
			F                  = 70,
			G                  = 71,
			H                  = 72,
			I                  = 73,
			J                  = 74,
			K                  = 75,
			L                  = 76,
			M                  = 77,
			N                  = 78,
			O                  = 79,
			P                  = 80,
			Q                  = 81,
			R                  = 82,
			S                  = 83,
			T                  = 84,
			U                  = 85,
			V                  = 86,
			W                  = 87,
			X                  = 88,
			Y                  = 89,
			Z                  = 90,
			LeftBracket        = 91, /* [ */
			Backslash          = 92, /* \ */
			RightBracket       = 93, /* ] */
			GraveAccent        = 96, /* ` */
			World1             = 16, /* non-US #1 */
			World2             = 16, /* non-US #2 */
			
			Escape             = 25,
			Enter              = 25,
			Tab                = 25,
			Backspace          = 25,
			Insert             = 26,
			Delete             = 26,
			Right              = 26,
			Left               = 26,
			Down               = 26,
			Up                 = 26,
			PageUp             = 26,
			PageDown           = 26,
			Home               = 26,
			End                = 26,
			CapsLock           = 28,
			ScrollLock         = 28,
			NumLock            = 28,
			PrintScreen        = 28,
			Pause              = 28,
			F1                 = 29,
			F2                 = 29,
			F3                 = 29,
			F4                 = 29,
			F5                 = 29,
			F6                 = 29,
			F7                 = 29,
			F8                 = 29,
			F9                 = 29,
			F10                = 29,
			F11                = 30,
			F12                = 30,
			F13                = 30,
			F14                = 30,
			F15                = 30,
			F16                = 30,
			F17                = 30,
			F18                = 30,
			F19                = 30,
			F20                = 30,
			F21                = 31,
			F22                = 31,
			F23                = 31,
			F24                = 31,
			F25                = 31,
			Kp0                = 32,
			Kp1                = 32,
			Kp2                = 32,
			Kp3                = 32,
			Kp4                = 32,
			Kp5                = 32,
			Kp6                = 32,
			Kp7                = 32,
			Kp8                = 32,
			Kp9                = 32,
			KpDecimal          = 33,
			KpDivide           = 33,
			KpMultiply         = 33,
			KpSubtract         = 33,
			KpAdd              = 33,
			KpEnter            = 33,
			KpEqual            = 33,
			LeftShift          = 34,
			LeftControl        = 34,
			LeftAlt            = 34,
			LeftSuper          = 34,
			RightShift         = 34,
			RightControl       = 34,
			RightAlt           = 34,
			RightSuper         = 34,
			Menu               = 348
		};
	}
}
