#ifndef RA_UI_WIN32_VANCLEEF_DEVTOOLS_DIALOG_HH
#define RA_UI_WIN32_VANCLEEF_DEVTOOLS_DIALOG_HH
#pragma once

#include "ui/viewmodels/VancleefDevToolsViewModel.hh"
#include "ui/win32/DialogBase.hh"
#include "ui/win32/bindings/CheckBoxBinding.hh"

namespace ra {
namespace ui {
namespace win32 {

class VancleefDevToolsDialog : public DialogBase
{
public:
    explicit VancleefDevToolsDialog(ra::ui::viewmodels::VancleefDevToolsViewModel& vmVancleefDevTools);
    virtual ~VancleefDevToolsDialog() noexcept = default;
    VancleefDevToolsDialog(const VancleefDevToolsDialog&) noexcept = delete;
    VancleefDevToolsDialog& operator=(const VancleefDevToolsDialog&) noexcept = delete;
    VancleefDevToolsDialog(VancleefDevToolsDialog&&) noexcept = delete;
    VancleefDevToolsDialog& operator=(VancleefDevToolsDialog&&) noexcept = delete;

    class Presenter : public IClosableDialogPresenter
    {
    public:
        bool IsSupported(const ra::ui::WindowViewModelBase& vmViewModel) noexcept override;
        void ShowWindow(ra::ui::WindowViewModelBase& vmViewModel) override;
        void ShowModal(ra::ui::WindowViewModelBase& vmViewModel, HWND hParentWnd) override;
        void OnClosed() noexcept override;

    private:
        std::unique_ptr<VancleefDevToolsDialog> m_pDialog;
    };

protected:
    BOOL OnInitDialog() override;
    BOOL OnCommand(WORD nCommand) override;

private:
    ra::ui::win32::bindings::CheckBoxBinding m_bindShowASCIIForAllSizes;
};

} // namespace win32
} // namespace ui
} // namespace ra

#endif // !RA_UI_WIN32_VANCLEEF_DEVTOOLS_DIALOG_HH
