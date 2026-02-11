#ifndef RA_UI_VANCLEEFDEVTOOLSVIEWMODEL_H
#define RA_UI_VANCLEEFDEVTOOLSVIEWMODEL_H
#pragma once

#include "ui\WindowViewModelBase.hh"

namespace ra {
namespace ui {
namespace viewmodels {

class VancleefDevToolsViewModel : public WindowViewModelBase
{
public:
    GSL_SUPPRESS_F6 VancleefDevToolsViewModel() noexcept;
    ~VancleefDevToolsViewModel() = default;

    VancleefDevToolsViewModel(const VancleefDevToolsViewModel&) noexcept = delete;
    VancleefDevToolsViewModel& operator=(const VancleefDevToolsViewModel&) noexcept = delete;
    VancleefDevToolsViewModel(VancleefDevToolsViewModel&&) noexcept = delete;
    VancleefDevToolsViewModel& operator=(VancleefDevToolsViewModel&&) noexcept = delete;

    /// <summary>
    /// The <see cref="ModelProperty" /> for whether ASCII should be shown for all memory sizes.
    /// </summary>
    static const BoolModelProperty ShowASCIIForAllSizesProperty;

    /// <summary>
    /// Gets whether ASCII should be shown for all memory sizes in Memory Viewer.
    /// </summary>
    bool GetShowASCIIForAllSizes() const { return GetValue(ShowASCIIForAllSizesProperty); }

    /// <summary>
    /// Sets whether ASCII should be shown for all memory sizes in Memory Viewer.
    /// </summary>
    void SetShowASCIIForAllSizes(bool value) { SetValue(ShowASCIIForAllSizesProperty, value); }
};

} // namespace viewmodels
} // namespace ui
} // namespace ra

#endif // !RA_UI_VANCLEEFDEVTOOLSVIEWMODEL_H
