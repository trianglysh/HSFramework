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

group "Vendor"
	include "Vendor/jsoncpp"
group ""

group "Framework"
	include "Core"
	include "Runtime"
group ""
