workspace "HSFramework"
	architecture "x64"
	configurations
	{
		"Development",
		"Preview",
		"Shipping"
	}
	startproject "Runtime"

include "Dependencies.lua"

group "Framework"
	include "Core"
	include "Runtime"
group ""
