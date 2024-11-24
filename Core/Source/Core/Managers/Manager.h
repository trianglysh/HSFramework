#pragma once

#include "Core/Base.h"

namespace HSFramework
{
	enum class ManagementState
	{
		None = 0,
		Splash,
		Menu
	};

	class Manager
	{
	public:
		virtual ~Manager() = default;

		virtual void OnStart() {}
		virtual void OnUpdate(float delta) {}
		virtual void OnStop() {}

		virtual ManagementState GetUnitState() const = 0;
	};
}
