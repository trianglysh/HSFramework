#pragma once

#include "Core/Log.h"

#ifndef HS_SHIPPING
	#ifdef HS_PLATFORM_WINDOWS
		#define HS_DEBUGBREAK() __debugbreak()
	#elif defined HS_PLATFORM_LINUX
		#include <signal.h>
		#define HS_DEBUGBREAK() raise(SIGTRAP)
	#endif
#else
	#define HS_DEBUGBREAK()
#endif

#ifndef HS_SHIPPING
	#define HS_ASSERT_BASE(logger, expression, ...) if (!(expression)) { HS_##logger##_ERROR("Assertion failed in file '" __FILE__ "' at line " HS_STRINGIFY(__LINE__) "! Expression '" #expression "' evaluated to false: " __VA_ARGS__); HS_DEBUGBREAK(); }
#else
	#define HS_ASSERT_BASE(logger, expression, ...)
#endif

#define HS_CORE_ASSERT(expression, ...) HS_ASSERT_BASE(CORE, expression, __VA_ARGS__)
#define HS_RUNTIME_ASSERT(expression, ...) HS_ASSERT_BASE(RUNTIME, expression, __VA_ARGS__)
#define HS_EDITOR_ASSERT(expression, ...) HS_ASSERT_BASE(EDITOR, expression, __VA_ARGS__)
