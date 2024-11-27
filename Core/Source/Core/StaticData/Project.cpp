#include "CorePCH.h"
#include "Project.h"

#include <json/json.h>

namespace HSFramework
{
	bool Project::LoadFromFile(std::string_view filepath)
	{
		std::ifstream file(filepath.data());
		if (!file)
		{
			// TODO: Log this
			return false;
		}

		Json::Value root;
		try
		{
			file >> root;
		}
		catch (const std::exception& e)
		{
			// TODO: Log this
			return false;
		}
		ActiveProject = MakeScope<Project>();

		ActiveProject->Name = root["Name"].asString();
		ActiveProject->Abb  = root["Abb"].asString();
		ActiveProject->Desc = root["Desc"].asString();

		if (root.isMember("MainWindowInfo"))
		{
			const Json::Value& mainWindowInfo = root["MainWindowInfo"];
			ActiveProject->MainWindowInfo.Title = mainWindowInfo["Title"].asString();
			ActiveProject->MainWindowInfo.xSize = mainWindowInfo["xSize"].asInt();
			ActiveProject->MainWindowInfo.ySize = mainWindowInfo["ySize"].asInt();
			ActiveProject->MainWindowInfo.Resizable = mainWindowInfo["Resizable"].asBool();
			ActiveProject->MainWindowInfo.Fullscreen = mainWindowInfo["Fullscreen"].asBool();
			ActiveProject->MainWindowInfo.vSync = mainWindowInfo["VSync"].asBool();
		}
		if (root.isMember("SplashData"))
		{
			const Json::Value& splashData = root["SplashData"];
			ActiveProject->SplashData.DoSplash = splashData["DoSplash"].asBool();
			ActiveProject->SplashData.SplashImg = splashData["SplashImg"].asString();
			ActiveProject->SplashData.FadeInDelay = splashData["FadeInDelay"].asFloat();
			ActiveProject->SplashData.FadeInSpeed = splashData["FadeInSpeed"].asFloat();
			ActiveProject->SplashData.FadeStayDuration = splashData["FadeStayDuration"].asFloat();
			ActiveProject->SplashData.FadeOutSpeed = splashData["FadeOutSpeed"].asFloat();
			ActiveProject->SplashData.FadeAftermathDuration = splashData["FadeAftermathDuration"].asFloat();
		}
		if (root.isMember("LoadEpisodes"))
		{
			const Json::Value& loadEpisodes = root["LoadEpisodes"];
			if (loadEpisodes.isArray())
			{
				for (const Json::Value& loadEpisode : loadEpisodes)
				{
					// Abnormal array member check, all must be strings
					if (!loadEpisode.isString())
					{
						break;
					}

					ActiveProject->LoadEpisodes.push_back(loadEpisode.asString());
				}
			}
		}

		return true;
	}
}
