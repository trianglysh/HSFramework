#include "CorePCH.h"
#include "Application.h"

#include "Core/Managers/SplashManager.h"
#include "Core/Managers/MenuManager.h"

#include "Core/StaticData/Project.h"

namespace HSFramework
{
	Application::Application(const CommandLineArgs& args)
		: m_Args(args)
	{
		HS_CORE_ASSERT(Project::ActiveProject, "The project hasn't been set up yet, it must be loaded before the construction of the Application!");
		HS_CORE_ASSERT(!s_Instance, "An application instance alredy exists!");
		s_Instance = this;

		WindowProps props =
		{
			Project::ActiveProject->MainWindowInfo.Title,
			Project::ActiveProject->MainWindowInfo.xSize,
			Project::ActiveProject->MainWindowInfo.ySize,
			Project::ActiveProject->MainWindowInfo.Resizable,
			Project::ActiveProject->MainWindowInfo.Fullscreen,
			Project::ActiveProject->MainWindowInfo.vSync,
		};
		if (!Window::Init(props))
		{
			HS_CORE_FATAL("Main window creation failure!");
		}
	}

	Application::~Application()
	{
		Window::Destroy();

		if (this == s_Instance)
		{
			s_Instance = nullptr;
		}
	}

	void Application::SetState(ManagementState state)
	{
		if (GetManagementState() == state)
		{
			return;
		}

		if (m_ActiveManager)
		{
			m_ActiveManager->OnStop();
			delete m_ActiveManager;
		}

		switch (state)
		{
		#define IMPLEMENT_SWITCH_CASE_FOR_MST(st) case ManagementState::##st: m_ActiveManager = new st##Manager(); break;
			IMPLEMENT_SWITCH_CASE_FOR_MST(Splash);
			IMPLEMENT_SWITCH_CASE_FOR_MST(Menu);
		#undef IMPLEMENT_SWITCH_CASE_FOR_MST
		default: m_ActiveManager = nullptr; break;
		}

		if (m_ActiveManager)
		{
			m_ActiveManager->OnStart();
		}
	}

	void Application::Update()
	{
		// TODO: Calculate delta time
		m_ActiveManager->OnUpdate(0.0f);

		Window::Update();
	}
}
