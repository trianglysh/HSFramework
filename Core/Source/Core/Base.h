#pragma once

#include <memory>

#define HS_CONCAT_IMPL(l, r) l##r
#define HS_CONCAT(l, r)      HS_CONCAT_IMPL(l, r)

#define HS_STRINGIFY_IMPL(x) #x
#define HS_STRINGIFY(x)      HS_STRINGIFY_IMPL(x)

#define HS_BIT(x) (1 << x)

#ifdef HS_PLATFORM_WINDOWS
	#define HS_PLATFORM_NAME Windows
#elif defined HS_PLATFORM_LINUX
	#define HS_PLATFORM_NAME Linux
#else
	#error Unknown platform!
#endif

#define HS_PLATFORM_NAME_STRING HS_STRINGIFY(HS_PLATFORM_NAME)
#define HS_ConcatWithPlatformName(x) HS_CONCAT(HS_PLATFORM_NAME, x)

namespace HSFramework
{
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename... Args>
	constexpr Scope<T> MakeScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
