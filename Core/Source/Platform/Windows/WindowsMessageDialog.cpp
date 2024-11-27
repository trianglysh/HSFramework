#include "CorePCH.h"
#include "WindowsMessageDialog.h"

namespace HSFramework
{
	WindowsMessageDialog::WindowsMessageDialog(std::string_view caption, std::string_view content, DialogControls controls, DialogIcon icon)
		: m_Caption(caption), m_Content(content), m_Controls(controls), m_Icon(icon)
	{
	}

	DialogResult WindowsMessageDialog::Create() const
	{
		return (DialogResult) MessageBoxA(NULL, m_Content.c_str(), m_Caption.c_str(), (UINT)((LONG) m_Controls | (LONG) m_Icon));
	}

	void WindowsMessageDialog::SetCaption(std::string_view caption)
	{
		m_Caption = caption;
	}

	void WindowsMessageDialog::SetContent(std::string_view content)
	{
		m_Content = content;
	}

	void WindowsMessageDialog::SetControls(DialogControls controls)
	{
		m_Controls = controls;
	}

	void WindowsMessageDialog::SetIcon(DialogIcon icon)
	{
		m_Icon = icon;
	}
}
