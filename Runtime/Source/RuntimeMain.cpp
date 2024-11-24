#include "RuntimePCH.h"

#include "Core/Application.h"

namespace HSFramework::Runtime
{
	int RtMain(int argc, char** argv)
	{
		Application application({ argv, argc });
		application.SetState(ManagementState::Splash);

		while (application.GetManagementState() != ManagementState::None)
		{
			application.Update();
		}

		return 0;
	}
}

#if defined HS_SHIPPING && defined HS_PLATFORM_WINDOWS

int CALLBACK WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
)
{
	return HSFramework::Runtime::RtMain(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return HSFramework::Runtime::RtMain(argc, argv);
}

#endif
