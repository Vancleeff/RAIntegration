#include "AchievementViewModel.hh"

#include "services\AchievementRuntime.hh"
#include "services\IClock.hh"
#include "services\ServiceLocator.hh"

namespace ra {
namespace ui {
namespace viewmodels {

const IntModelProperty AchievementViewModel::PointsProperty("AchievementViewModel", "Points", 5);
const StringModelProperty AchievementViewModel::BadgeProperty("AchievementViewModel", "Badge", L"00000");
const BoolModelProperty AchievementViewModel::PauseOnResetProperty("AchievementViewModel", "PauseOnReset", false);
const BoolModelProperty AchievementViewModel::PauseOnTriggerProperty("AchievementViewModel", "PauseOnTrigger", false);
const IntModelProperty AchievementViewModel::TriggerProperty("AchievementViewModel", "Trigger", ra::etoi(AssetChanges::None));

AchievementViewModel::AchievementViewModel() noexcept
{
    GSL_SUPPRESS_F6 SetValue(TypeProperty, ra::etoi(AssetType::Achievement));

    SetTransactional(PointsProperty);
    SetTransactional(BadgeProperty);

    GSL_SUPPRESS_F6 AddAssetDefinition(m_pTrigger, TriggerProperty);
}

void AchievementViewModel::Activate()
{
    if (!IsActive())
        SetState(AssetState::Waiting);
}

void AchievementViewModel::Deactivate()
{
    SetState(AssetState::Inactive);
}

void AchievementViewModel::OnValueChanged(const IntModelProperty::ChangeArgs& args)
{
    if (args.Property == StateProperty)
    {
        const bool bWasActive = IsActive(ra::itoe<AssetState>(args.tOldValue));
        const bool bIsActive = IsActive(ra::itoe<AssetState>(args.tNewValue));
        if (bWasActive != bIsActive)
        {
            auto& pRuntime = ra::services::ServiceLocator::GetMutable<ra::services::AchievementRuntime>();
            const bool bRuntimeActive = (pRuntime.GetAchievementTrigger(GetID()) != nullptr);
            if (bRuntimeActive != bIsActive)
            {
                if (bIsActive)
                    pRuntime.ActivateAchievement(GetID(), GetTrigger());
                else
                    pRuntime.DeactivateAchievement(GetID());
            }
        }

        if (ra::itoe<AssetState>(args.tNewValue) == AssetState::Triggered)
        {
            const auto& pClock = ra::services::ServiceLocator::Get<ra::services::IClock>();
            m_tUnlock = pClock.Now();
        }
    }

    AssetViewModelBase::OnValueChanged(args);
}

void AchievementViewModel::DoFrame()
{
    const auto& pRuntime = ra::services::ServiceLocator::Get<ra::services::AchievementRuntime>();
    const auto* pTrigger = pRuntime.GetAchievementTrigger(GetID());
    if (pTrigger == nullptr)
    {
        if (GetState() != AssetState::Triggered)
            SetState(AssetState::Inactive);
    }
    else
    {
        switch (pTrigger->state)
        {
            case RC_TRIGGER_STATE_ACTIVE:
                SetState(AssetState::Active);
                break;
            case RC_TRIGGER_STATE_INACTIVE:
                SetState(AssetState::Inactive);
                break;
            case RC_TRIGGER_STATE_PAUSED:
                SetState(AssetState::Paused);
                break;
            case RC_TRIGGER_STATE_TRIGGERED:
                SetState(AssetState::Triggered);
                break;
            case RC_TRIGGER_STATE_WAITING:
                SetState(AssetState::Waiting);
                break;
        }
    }
}

void AchievementViewModel::Serialize(ra::services::TextWriter& pWriter) const
{
    WriteQuoted(pWriter, GetLocalAssetDefinition(m_pTrigger));
    WritePossiblyQuoted(pWriter, GetLocalValue(NameProperty));
    WritePossiblyQuoted(pWriter, GetLocalValue(DescriptionProperty));
    pWriter.Write("::::"); // progress/max/format/author
    WriteNumber(pWriter, GetLocalValue(PointsProperty));
    pWriter.Write("::::"); // created/modified/upvotes/downvotes
    WritePossiblyQuoted(pWriter, GetLocalValue(BadgeProperty));
}

bool AchievementViewModel::Deserialize(ra::Tokenizer& pTokenizer)
{
    // field 2: trigger
    std::string sTrigger;
    if (pTokenizer.PeekChar() == '"')
    {
        sTrigger = pTokenizer.ReadQuotedString();
    }
    else
    {
        // unquoted trigger requires special parsing because flags also use colons
        const char* pTrigger = pTokenizer.GetPointer(pTokenizer.CurrentPosition());
        const char* pScan = pTrigger;
        while (*pScan && (*pScan != ':' || strchr("ABCMNOPRTabcmnoprt", pScan[-1]) != nullptr))
            pScan++;

        sTrigger.assign(pTrigger, pScan - pTrigger);
        pTokenizer.Advance(sTrigger.length());
    }

    if (!pTokenizer.Consume(':'))
        return false;

    // field 3: title
    std::string sTitle;
    if (!ReadPossiblyQuoted(pTokenizer, sTitle))
        return false;

    // field 4: description
    std::string sDescription;
    if (!ReadPossiblyQuoted(pTokenizer, sDescription))
        return false;

    // field 5: progress (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 6: progress max (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 7: progress format (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 8: author (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 9: points
    uint32_t nPoints;
    if (!ReadNumber(pTokenizer, nPoints))
        return false;

    // field 10: created date (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 11: modified date (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 12: up votes (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 13: down votes (unused)
    pTokenizer.AdvanceTo(':');
    if (!pTokenizer.Consume(':'))
        return false;

    // field 14: badge
    std::string sBadge;
    if (!ReadPossiblyQuoted(pTokenizer, sBadge))
        return false;
    if (sBadge.length() < 5)
        sBadge.insert(0, 5 - sBadge.length(), '0');

    // line is valid
    SetName(ra::Widen(sTitle));
    SetDescription(ra::Widen(sDescription));
    SetPoints(nPoints);
    SetBadge(ra::Widen(sBadge));
    SetTrigger(sTrigger);

    return true;
}

} // namespace viewmodels
} // namespace ui
} // namespace ra