#pragma once

#include "Core/Base.h"

#include <string>

namespace HSFramework
{
	struct Project
	{
		std::string Name;
		std::string Abb;
		std::string Desc;

		struct MainWindowInfoObject
		{
			std::string Title;
			int xSize = 0, ySize = 0;
			bool Resizable = false;
			bool Fullscreen = false;
			bool vSync = false;
		} MainWindowInfo;

		struct SplashDataObject
		{
			bool DoSplash = false;
			std::string SplashImg;
			float FadeInDelay = 0.0f;
			float FadeInSpeed = 0.0f;
			float FadeStayDuration = 0.0f;
			float FadeOutSpeed = 0.0f;
			float FadeAftermathDuration = 0.0f;
		} SplashData;

		std::vector<std::string> LoadEpisodes;

		inline static Scope<Project> ActiveProject;

		static bool LoadFromFile(std::string_view filepath);
	};
}
