#include "VancleefDevToolsViewModel.hh"

#include "services\IConfiguration.hh"
#include "services\ServiceLocator.hh"

namespace ra {
namespace ui {
namespace viewmodels {

const BoolModelProperty VancleefDevToolsViewModel::ShowASCIIForAllSizesProperty("VancleefDevToolsViewModel", "ShowASCIIForAllSizes", false);

VancleefDevToolsViewModel::VancleefDevToolsViewModel() noexcept
{
    SetWindowTitle(L"Vancleef's DevTools");
}

void VancleefDevToolsViewModel::Initialize()
{
    const auto& pConfiguration = ra::services::ServiceLocator::Get<ra::services::IConfiguration>();
    SetShowASCIIForAllSizes(pConfiguration.IsFeatureEnabled(ra::services::Feature::VancleefAsciiAllSizes));
}

void VancleefDevToolsViewModel::Commit()
{
    auto& pConfiguration = ra::services::ServiceLocator::GetMutable<ra::services::IConfiguration>();
    pConfiguration.SetFeatureEnabled(ra::services::Feature::VancleefAsciiAllSizes, GetShowASCIIForAllSizes());
    pConfiguration.Save();
}

bool VancleefDevToolsViewModel::GetShowASCIIForAllSizes() const
{
    return GetValue(ShowASCIIForAllSizesProperty);
}

void VancleefDevToolsViewModel::SetShowASCIIForAllSizes(bool bValue)
{
    SetValue(ShowASCIIForAllSizesProperty, bValue);
}

} // namespace viewmodels
} // namespace ui
} // namespace ra
