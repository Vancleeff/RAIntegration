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

    static const BoolModelProperty ShowASCIIForAllSizesProperty;

    void Initialize();
    void Commit();
    bool GetShowASCIIForAllSizes() const;
    void SetShowASCIIForAllSizes(bool bValue);
};

} // namespace viewmodels
} // namespace ui
} // namespace ra

#endif // !RA_UI_VANCLEEFDEVTOOLSVIEWMODEL_H
