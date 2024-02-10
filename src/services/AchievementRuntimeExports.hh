#ifndef RA_SERVICES_ACHIEVEMENT_RUNTIME_EXPORTS_HH
#define RA_SERVICES_ACHIEVEMENT_RUNTIME_EXPORTS_HH
#pragma once

void SyncClientExternalRAIntegrationMenuItem(int nMenuItemId);
void SyncClientExternalHardcoreState();
bool IsExternalRcheevosClient() noexcept;
void ResetExternalRcheevosClient() noexcept;

#endif // !RA_SERVICES_ACHIEVEMENT_RUNTIME_EXPORTS_HH
