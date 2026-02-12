#include "VancleefDevToolsDialog.hh"
#include "RA_Resource.h"
#include "ui\viewmodels\WindowManager.hh"
#include "services\IConfiguration.hh"

namespace ra {
namespace ui {
namespace win32 {

bool VancleefDevToolsDialog::Presenter::IsSupported(const ra::ui::WindowViewModelBase& vmViewModel) noexcept
{
    return (dynamic_cast<const ra::ui::viewmodels::VancleefDevToolsViewModel*>(&vmViewModel) != nullptr);
}

void VancleefDevToolsDialog::Presenter::ShowWindow(ra::ui::WindowViewModelBase& vmViewModel)
{
    ShowModal(vmViewModel, nullptr);
}

void VancleefDevToolsDialog::Presenter::ShowModal(ra::ui::WindowViewModelBase& vmViewModel, HWND hParentWnd)
{
    auto* vmVancleefDevTools = dynamic_cast<ra::ui::viewmodels::VancleefDevToolsViewModel*>(&vmViewModel);
    Expects(vmVancleefDevTools != nullptr);

    if (!m_pDialog)
        m_pDialog.reset(new VancleefDevToolsDialog(*vmVancleefDevTools));

    m_pDialog->CreateModalWindow(MAKEINTRESOURCE(IDD_RA_VANCLEEF_DEVTOOLS), this, hParentWnd);
}

void VancleefDevToolsDialog::Presenter::OnClosed() noexcept
{
    if (m_pDialog)
        m_pDialog.reset();
}

// ===================================================

VancleefDevToolsDialog::VancleefDevToolsDialog(ra::ui::viewmodels::VancleefDevToolsViewModel& vmVancleefDevTools) :
    DialogBase(vmVancleefDevTools), m_bindShowASCIIForAllSizes(vmVancleefDevTools)
{
    m_bindWindow.SetInitialPosition(RelativePosition::Center, RelativePosition::Center, "Vancleef DevTools");

    m_bindShowASCIIForAllSizes.BindCheck(ra::ui::viewmodels::VancleefDevToolsViewModel::ShowASCIIForAllSizesProperty);
}

BOOL VancleefDevToolsDialog::OnInitDialog()
{
    m_bindShowASCIIForAllSizes.SetControl(*this, IDC_CHK_VANCLEEF_ASCII_ALL);

    return DialogBase::OnInitDialog();
}

BOOL VancleefDevToolsDialog::OnCommand(WORD nCommand)
{
    switch (nCommand)
    {
        case IDOK: {
            auto* vmVancleefDevTools = dynamic_cast<viewmodels::VancleefDevToolsViewModel*>(&m_vmWindow);
            if (vmVancleefDevTools)
            {
                auto& pWindowManager = ra::services::ServiceLocator::GetMutable<ra::ui::viewmodels::WindowManager>();
                auto& vmMemoryInspector = pWindowManager.MemoryInspector;
                auto& pConfiguration = ra::services::ServiceLocator::GetMutable<ra::services::IConfiguration>();
                pConfiguration.SetFeatureEnabled(ra::services::Feature::VancleefAsciiAllSizes,
                                                 vmVancleefDevTools->GetShowASCIIForAllSizes());
                vmVancleefDevTools->Commit();
            }
            return DialogBase::OnCommand(nCommand);
        }

        case IDCANCEL:
            return DialogBase::OnCommand(nCommand);
    }

    return DialogBase::OnCommand(nCommand);
}

} // namespace win32
} // namespace ui
} // namespace ra
