#pragma once

#include "Core/Managers/Manager.h"

namespace HSFramework
{
	class SplashManager : public Manager
	{
	public:
		virtual void OnStart() override;
		virtual void OnUpdate(float delta) override;
		virtual void OnStop() override;

		static ManagementState GetStaticUnitState() { return ManagementState::Splash; }
		virtual ManagementState GetUnitState() const override { return GetStaticUnitState(); }
	};
}
