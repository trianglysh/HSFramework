project "Core"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir "%{OutputDir.Intermediates}/%{prj.name}"
	
	pchheader "CorePCH.h"
	pchsource "Source/CorePCH.cpp"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"Source"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HS_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		defines
		{
			"HS_PLATFORM_LINUX"
		}
	
	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		defines
		{
			"HS_DEVELOPMENT",
			"HS_RUNTIME_DEBUG"
		}
		
	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_PREVIEW",
			"HS_RUNTIME_RELEASE"
		}
	
	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_SHIPPING",
			"HS_RUNTIME_RELEASE"
		}
	