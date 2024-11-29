project "Runtime"
	language "C++"
	cppdialect "C++17"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir "%{OutputDir.Intermediates}/%{prj.name}"
	
	pchheader "RuntimePCH.h"
	pchsource "Source/RuntimePCH.cpp"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"%{IncludeDir.Core}",
		"Source",

		"%{IncludeDir.jsoncpp}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.fmtlib}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"Core",

		-- Vendors
		"GLFW",
		"Glad",
		"jsoncpp"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HS_PLATFORM_WINDOWS",

			-- MSVC bullshit
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "system:linux"
		defines
		{
			"HS_PLATFORM_LINUX"
		}
	
	filter "configurations:Development"
		kind "ConsoleApp"
		runtime "Debug"
		symbols "On"
		defines
		{
			"HS_DEVELOPMENT",
			"HS_RUNTIME_DEBUG"
		}
		
	filter "configurations:Preview"
		kind "ConsoleApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_PREVIEW",
			"HS_RUNTIME_RELEASE"
		}
	
	filter "configurations:Shipping"
		kind "WindowedApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_SHIPPING",
			"HS_RUNTIME_RELEASE"
		}
