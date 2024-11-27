#include "CorePCH.h"
#include "Application.h"

#include "Core/Managers/SplashManager.h"
#include "Core/Managers/MenuManager.h"

namespace HSFramework
{
	Application::Application(const CommandLineArgs& args)
		: m_Args(args)
	{
		HS_CORE_ASSERT(!s_Instance, "An application instance alredy exists!");
		s_Instance = this;
	}

	Application::~Application()
	{
		if (this == s_Instance)
		{
			delete s_Instance;
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
	}
}
