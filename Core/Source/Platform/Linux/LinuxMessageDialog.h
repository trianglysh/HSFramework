#pragma once

#include "Core/Misc/MessageDialog.h"

namespace HSFramework
{
	class LinuxMessageDialog : public MessageDialog
	{
	public:
		LinuxMessageDialog(std::string_view caption, std::string_view content, DialogControls controls, DialogIcon icon);

		virtual DialogResult Create() const override;

		virtual void SetCaption(std::string_view caption) override;
		virtual void SetContent(std::string_view content) override;
		virtual void SetControls(DialogControls controls) override;
		virtual void SetIcon(DialogIcon icon) override;

		virtual const std::string& GetCaption() const override { return m_Caption; }
		virtual const std::string& GetContent() const override { return m_Content; }
		virtual DialogControls GetControls() const override { return m_Controls; }
		virtual DialogIcon GetIcon() const override { return m_Icon; }
	private:
		std::string m_Caption, m_Content;
		DialogControls m_Controls = DialogControls::None;
		DialogIcon m_Icon = DialogIcon::None;
	};
}
