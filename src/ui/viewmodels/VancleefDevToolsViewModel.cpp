#include "VancleefDevToolsViewModel.hh"

namespace ra {
namespace ui {
namespace viewmodels {

const BoolModelProperty VancleefDevToolsViewModel::ShowASCIIForAllSizesProperty("VancleefDevToolsViewModel", "ShowASCIIForAllSizes", false);

VancleefDevToolsViewModel::VancleefDevToolsViewModel() noexcept
{
    SetWindowTitle(L"Vancleef's DevTools");
}

} // namespace viewmodels
} // namespace ui
} // namespace ra
