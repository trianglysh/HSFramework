#pragma once

#include "Core/Managers/Manager.h"
#include "Core/Window.h"

namespace HSFramework
{
	struct CommandLineArgs
	{
		char** List = nullptr;
		int    Size = 0;
	};

	class Application
	{
	public:
		Application(const CommandLineArgs& args);
		~Application();

		void SetState(ManagementState state);
		void Update();

		Manager* GetActiveManager() const { return m_ActiveManager; }
		ManagementState GetManagementState() const { return m_ActiveManager ? m_ActiveManager->GetUnitState() : ManagementState::None; }
		const CommandLineArgs& GetArgs() const { return m_Args; }

		static Application* Get() { return s_Instance; }
	private:
		Manager* m_ActiveManager = nullptr;
		CommandLineArgs m_Args;
	private:
		inline static Application* s_Instance = nullptr;
	};
}
