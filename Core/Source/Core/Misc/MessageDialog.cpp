#include "CorePCH.h"
#include "MessageDialog.h"

#include "Platform/Windows/WindowsMessageDialog.h"
#include "Platform/Linux/LinuxMessageDialog.h"

namespace HSFramework
{
	Scope<MessageDialog> MessageDialog::New(std::string_view caption, std::string_view content, DialogControls controls, DialogIcon icon)
	{
		return MakeScope<HS_ConcatWithPlatformName(MessageDialog)>(caption, content, controls, icon);
	}
}
