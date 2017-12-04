#include "StdAfx.h"
#include "SkillButton.h"

CSkillButton::CSkillButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, SLOT_TYPE _eSlotType, SLOT_ID _eSlotID)
: CButtonUI(_tszObjKey, _eObjType, NULL, NULL, NULL, NULL)
{
	// SlotType
	m_eSlotType = _eSlotType;

	// SlotID
	m_eSlotID = _eSlotID;

	// SlotMessage
	m_pSlotMessage = NULL;

	// Texture
	switch(m_eSlotID)
	{
	case SLOT_ID_BARBARIAN_OPEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Open"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Open"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Open"));
		break;
	case SLOT_ID_BARBARIAN_CLOSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Close"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Close"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Close"));
		break;
	case SLOT_ID_BARBARIAN_BASH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Bash"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Bash"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Bash"));
		break;
	case SLOT_ID_BARBARIAN_CLEAVE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Cleave"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Cleave"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Cleave"));
		break;
	case SLOT_ID_BARBARIAN_FRENZY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Frenzy"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Frenzy"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Frenzy"));
		break;
	case SLOT_ID_BARBARIAN_WEAPON_THROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_WeaponThrow"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_WeaponThrow"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_WeaponThrow"));
		break;
	case SLOT_ID_BARBARIAN_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Punch"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Punch"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Punch"));
		break;
	case SLOT_ID_BARBARIAN_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_NearAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_NearAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_NearAttack"));
		break;
	case SLOT_ID_BARBARIAN_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_FarAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_FarAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_FarAttack"));
		break;
	case SLOT_ID_BARBARIAN_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_MagicAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_MagicAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_MagicAttack"));
		break;
	case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_HammerOfTheAncients"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_HammerOfTheAncients"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_HammerOfTheAncients"));
		break;
	case SLOT_ID_BARBARIAN_REND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Rend"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Rend"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Rend"));
		break;
	case SLOT_ID_BARBARIAN_SEISMIC_SLAM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_SeismicSlam"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_SeismicSlam"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_SeismicSlam"));
		break;
	case SLOT_ID_BARBARIAN_WHIRLWIND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Whirlwind"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Whirlwind"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Whirlwind"));
		break;
	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_AncientSpear"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_AncientSpear"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_AncientSpear"));
		break;
	case SLOT_ID_BARBARIAN_GROUND_STOMP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_GroundStomp"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_GroundStomp"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_GroundStomp"));
		break;
	case SLOT_ID_BARBARIAN_LEAP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Leap"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Leap"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Leap"));
		break;
	case SLOT_ID_BARBARIAN_SPRINT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Sprint"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Sprint"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Sprint"));
		break;
	case SLOT_ID_BARBARIAN_IGNORE_PAIN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_IgnorePain"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_IgnorePain"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_IgnorePain"));
		break;
	case SLOT_ID_BARBARIAN_OVERPOWER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Overpower"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Overpower"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Overpower"));
		break;
	case SLOT_ID_BARBARIAN_REVENGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Revenge"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Revenge"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Revenge"));
		break;
	case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_FuriousCharge"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_FuriousCharge"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_FuriousCharge"));
		break;
	case SLOT_ID_BARBARIAN_THREATENING_SHOUT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_ThreateningShout"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_ThreateningShout"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_ThreateningShout"));
		break;
	case SLOT_ID_BARBARIAN_BATTLE_RAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_BattleRage"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_BattleRage"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_BattleRage"));
		break;
	case SLOT_ID_BARBARIAN_WAR_CRY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_WarCry"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_WarCry"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_WarCry"));
		break;
	case SLOT_ID_BARBARIAN_EARTHQUAKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_Earthquake"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_Earthquake"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_Earthquake"));
		break;
	case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_CallOfTheAncients"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_CallOfTheAncients"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_CallOfTheAncients"));
		break;
	case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Back_WrathOfTheBerserker"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Over_WrathOfTheBerserker"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Barbarian_Down_WrathOfTheBerserker"));
		break;
	case SLOT_ID_DEMONHUNTER_OPEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Open"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Open"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Open"));
		break;
	case SLOT_ID_DEMONHUNTER_CLOSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Close"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Close"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Close"));
		break;
	case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_HungeringArrow"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_HungeringArrow"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_HungeringArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_EntanglingShot"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_EntanglingShot"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_EntanglingShot"));
		break;
	case SLOT_ID_DEMONHUNTER_BOLA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Bola"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Bola"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Bola"));
		break;
	case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_EvasiveFire"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_EvasiveFire"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_EvasiveFire"));
		break;
	case SLOT_ID_DEMONHUNTER_GRENADES:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Grenades"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Grenades"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Grenades"));
		break;
	case SLOT_ID_DEMONHUNTER_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Punch"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Punch"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Punch"));
		break;
	case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_NearAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_NearAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_NearAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_FarAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_FarAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_FarAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_MagicAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_MagicAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_MagicAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_IMPALE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Impale"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Impale"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Impale"));
		break;
	case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_RapidFire"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_RapidFire"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_RapidFire"));
		break;
	case SLOT_ID_DEMONHUNTER_CHAKRAM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Chakram"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Chakram"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Chakram"));
		break;
	case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_ElementalArrow"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_ElementalArrow"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_ElementalArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_CALTROPS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Caltrops"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Caltrops"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Caltrops"));
		break;
	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_SmokeScreen"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_SmokeScreen"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_SmokeScreen"));
		break;
	case SLOT_ID_DEMONHUNTER_SHADOW_POWER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_ShadowPower"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_ShadowPower"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_ShadowPower"));
		break;
	case SLOT_ID_DEMONHUNTER_VAULT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Vault"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Vault"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Vault"));
		break;
	case SLOT_ID_DEMONHUNTER_PREPARATION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Preparation"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Preparation"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Preparation"));
		break;
	case SLOT_ID_DEMONHUNTER_COMPANION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Companion"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Companion"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Companion"));
		break;
	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_MarkedForDeath"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_MarkedForDeath"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_MarkedForDeath"));
		break;
	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_FanOfKnives"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_FanOfKnives"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_FanOfKnives"));
		break;
	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_SpikeTrap"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_SpikeTrap"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_SpikeTrap"));
		break;
	case SLOT_ID_DEMONHUNTER_SENTRY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Sentry"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Sentry"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Sentry"));
		break;
	case SLOT_ID_DEMONHUNTER_STRAFE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Strafe"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Strafe"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Strafe"));
		break;
	case SLOT_ID_DEMONHUNTER_MULTISHOT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_Multishot"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_Multishot"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_Multishot"));
		break;
	case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_ClusterArrow"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_ClusterArrow"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_ClusterArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Back_RainOfVengeance"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Over_RainOfVengeance"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_DemonHunter_Down_RainOfVengeance"));
		break;
	case SLOT_ID_MONK_OPEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_Open"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_Open"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_Open"));
		break;
	case SLOT_ID_MONK_CLOSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_Close"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_Close"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_Close"));
		break;
	case SLOT_ID_MONK_FISTS_OF_THUNDER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_FistsOfThunder"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_FistsOfThunder"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_FistsOfThunder"));
		break;
	case SLOT_ID_MONK_DEADLY_REACH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_DeadlyReach"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_DeadlyReach"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_DeadlyReach"));
		break;
	case SLOT_ID_MONK_CRIPPLING_WAVE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_CripplingWave"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_CripplingWave"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_CripplingWave"));
		break;
	case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_WayOfTheHundredFists"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_WayOfTheHundredFists"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_WayOfTheHundredFists"));
		break;
	case SLOT_ID_MONK_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_Punch"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_Punch"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_Punch"));
		break;
	case SLOT_ID_MONK_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_NearAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_NearAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_NearAttack"));
		break;
	case SLOT_ID_MONK_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_FarAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_FarAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_FarAttack"));
		break;
	case SLOT_ID_MONK_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MagicAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MagicAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MagicAttack"));
		break;
	case SLOT_ID_MONK_LASHING_TAIL_KICK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_LashingTailKick"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_LashingTailKick"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_LashingTailKick"));
		break;
	case SLOT_ID_MONK_TEMPEST_RUSH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_TempestRush"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_TempestRush"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_TempestRush"));
		break;
	case SLOT_ID_MONK_WAVE_OF_LIGHT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_WaveOfLight"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_WaveOfLight"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_WaveOfLight"));
		break;
	case SLOT_ID_MONK_BLINDING_FLASH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_BlindingFlash"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_BlindingFlash"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_BlindingFlash"));
		break;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_BreathOfHeaven"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_BreathOfHeaven"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_BreathOfHeaven"));
		break;
	case SLOT_ID_MONK_SERENITY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_Serenity"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_Serenity"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_Serenity"));
		break;
	case SLOT_ID_MONK_INNER_SANCTUARY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_InnerSanctuary"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_InnerSanctuary"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_InnerSanctuary"));
		break;
	case SLOT_ID_MONK_DASHING_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_DashingStrike"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_DashingStrike"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_DashingStrike"));
		break;
	case SLOT_ID_MONK_EXPLODING_PALM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_ExplodingPalm"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_ExplodingPalm"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_ExplodingPalm"));
		break;
	case SLOT_ID_MONK_SWEEPING_WIND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_SweepingWind"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_SweepingWind"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_SweepingWind"));
		break;
	case SLOT_ID_MONK_CYCLONE_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_CycloneStrike"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_CycloneStrike"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_CycloneStrike"));
		break;
	case SLOT_ID_MONK_SEVEN_SIDED_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_SevenSidedStrike"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_SevenSidedStrike"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_SevenSidedStrike"));
		break;
	case SLOT_ID_MONK_MYSTIC_ALLY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MysticAlly"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MysticAlly"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MysticAlly"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_SALVATION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MantraOfSalvation"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MantraOfSalvation"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MantraOfSalvation"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MantraOfRetribution"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MantraOfRetribution"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MantraOfRetribution"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_HEALING:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MantraOfHealing"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MantraOfHealing"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MantraOfHealing"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Back_MantraOfConviction"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Over_MantraOfConviction"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Monk_Down_MantraOfConviction"));
		break;
	case SLOT_ID_WITCHDOCTOR_OPEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Open"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Open"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Open"));
		break;
	case SLOT_ID_WITCHDOCTOR_CLOSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Close"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Close"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Close"));
		break;
	case SLOT_ID_WITCHDOCTOR_POISON_DART:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_PoisonDart"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_PoisonDart"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_PoisonDart"));
		break;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_CorpseSpiders"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_CorpseSpiders"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_CorpseSpiders"));
		break;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_PlagueOfToads"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_PlagueOfToads"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_PlagueOfToads"));
		break;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Firebomb"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Firebomb"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Firebomb"));
		break;
	case SLOT_ID_WITCHDOCTOR_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Punch"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Punch"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Punch"));
		break;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_NearAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_NearAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_NearAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_FarAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_FarAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_FarAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_MagicAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_MagicAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_MagicAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_GraspOfTheDead"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_GraspOfTheDead"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_GraspOfTheDead"));
		break;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Firebats"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Firebats"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Firebats"));
		break;
	case SLOT_ID_WITCHDOCTOR_HAUNT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Haunt"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Haunt"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Haunt"));
		break;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_LocustSwarm"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_LocustSwarm"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_LocustSwarm"));
		break;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_SummonZombieDogs"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_SummonZombieDogs"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_SummonZombieDogs"));
		break;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Horrify"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Horrify"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Horrify"));
		break;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_SpiritWalk"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_SpiritWalk"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_SpiritWalk"));
		break;
	case SLOT_ID_WITCHDOCTOR_HEX:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Hex"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Hex"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Hex"));
		break;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_SoulHarvest"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_SoulHarvest"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_SoulHarvest"));
		break;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Sacrifice"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Sacrifice"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Sacrifice"));
		break;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_MassConfusion"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_MassConfusion"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_MassConfusion"));
		break;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_ZombieCharger"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_ZombieCharger"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_ZombieCharger"));
		break;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_SpiritBarrage"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_SpiritBarrage"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_SpiritBarrage"));
		break;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_AcidCloud"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_AcidCloud"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_AcidCloud"));
		break;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_WallOfDeath"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_WallOfDeath"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_WallOfDeath"));
		break;
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_Gargantuan"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_Gargantuan"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_Gargantuan"));
		break;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_BigBadVoodoo"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_BigBadVoodoo"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_BigBadVoodoo"));
		break;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Back_FetishArmy"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Over_FetishArmy"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_WitchDoctor_Down_FetishArmy"));
		break;
	case SLOT_ID_WIZARD_OPEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Open"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Open"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Open"));
		break;
	case SLOT_ID_WIZARD_CLOSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Close"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Close"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Close"));
		break;
	case SLOT_ID_WIZARD_MAGIC_MISSILE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_MagicMissile"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_MagicMissile"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_MagicMissile"));
		break;
	case SLOT_ID_WIZARD_SHOCK_PULSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_ShockPulse"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_ShockPulse"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_ShockPulse"));
		break;
	case SLOT_ID_WIZARD_SPECTRAL_BLADE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_SpectralBlade"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_SpectralBlade"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_SpectralBlade"));
		break;
	case SLOT_ID_WIZARD_ELECTROCUTE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Electrocute"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Electrocute"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Electrocute"));
		break;
	case SLOT_ID_WIZARD_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Punch"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Punch"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Punch"));
		break;
	case SLOT_ID_WIZARD_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_NearAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_NearAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_NearAttack"));
		break;
	case SLOT_ID_WIZARD_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_FarAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_FarAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_FarAttack"));
		break;
	case SLOT_ID_WIZARD_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_MagicAttack"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_MagicAttack"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_MagicAttack"));
		break;
	case SLOT_ID_WIZARD_RAY_OF_FROST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_RayOfFrost"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_RayOfFrost"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_RayOfFrost"));
		break;
	case SLOT_ID_WIZARD_ARCANE_ORB:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_ArcaneOrb"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_ArcaneOrb"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_ArcaneOrb"));
		break;
	case SLOT_ID_WIZARD_ARCANE_TORRENT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_ArcaneTorrent"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_ArcaneTorrent"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_ArcaneTorrent"));
		break;
	case SLOT_ID_WIZARD_DISINTEGRATE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Disintegrate"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Disintegrate"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Disintegrate"));
		break;
	case SLOT_ID_WIZARD_FROST_NOVA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_FrostNova"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_FrostNova"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_FrostNova"));
		break;
	case SLOT_ID_WIZARD_DIAMOND_SKIN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_DiamondSkin"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_DiamondSkin"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_DiamondSkin"));
		break;
	case SLOT_ID_WIZARD_SLOW_TIME:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_SlowTime"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_SlowTime"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_SlowTime"));
		break;
	case SLOT_ID_WIZARD_TELEPORT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Teleport"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Teleport"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Teleport"));
		break;
	case SLOT_ID_WIZARD_WAVE_OF_FORCE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_WaveOfForce"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_WaveOfForce"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_WaveOfForce"));
		break;
	case SLOT_ID_WIZARD_ENERGY_TWISTER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_EnergyTwister"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_EnergyTwister"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_EnergyTwister"));
		break;
	case SLOT_ID_WIZARD_HYDRA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Hydra"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Hydra"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Hydra"));
		break;
	case SLOT_ID_WIZARD_METEOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Meteor"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Meteor"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Meteor"));
		break;
	case SLOT_ID_WIZARD_BLIZZARD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Blizzard"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Blizzard"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Blizzard"));
		break;
	case SLOT_ID_WIZARD_ICE_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_IceArmor"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_IceArmor"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_IceArmor"));
		break;
	case SLOT_ID_WIZARD_STORM_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_StormArmor"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_StormArmor"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_StormArmor"));
		break;
	case SLOT_ID_WIZARD_MAGIC_WEAPON:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_MagicWeapon"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_MagicWeapon"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_MagicWeapon"));
		break;
	case SLOT_ID_WIZARD_FAMILIAR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Familiar"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Familiar"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Familiar"));
		break;
	case SLOT_ID_WIZARD_ENERGY_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_EnergyArmor"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_EnergyArmor"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_EnergyArmor"));
		break;
	case SLOT_ID_WIZARD_EXPLOSIVE_BLAST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_ExplosiveBlast"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_ExplosiveBlast"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_ExplosiveBlast"));
		break;
	case SLOT_ID_WIZARD_MIRROR_IMAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_MirrorImage"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_MirrorImage"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_MirrorImage"));
		break;
	case SLOT_ID_WIZARD_ARCHON:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Back_Archon"));
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Over_Archon"));
		m_pDownTexture = CTextureMgr::GetInstance()->GetTexture(_T("Skill_Wizard_Down_Archon"));
		break;
	}
}

CSkillButton::~CSkillButton()
{
	Release();
}

void CSkillButton::Initialize()
{
	CButtonUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CSkillButton::Update()
{
	CButtonUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	if(m_dwState & UI_OVER)
	{
		if(m_eSlotID == SLOT_ID_BARBARIAN_CLOSE || m_eSlotID == SLOT_ID_BARBARIAN_OPEN ||
			m_eSlotID == SLOT_ID_DEMONHUNTER_CLOSE || m_eSlotID == SLOT_ID_DEMONHUNTER_OPEN ||
			m_eSlotID == SLOT_ID_MONK_CLOSE || m_eSlotID == SLOT_ID_MONK_OPEN ||
			m_eSlotID == SLOT_ID_WITCHDOCTOR_CLOSE || m_eSlotID == SLOT_ID_WITCHDOCTOR_OPEN ||
			m_eSlotID == SLOT_ID_WIZARD_CLOSE || m_eSlotID == SLOT_ID_WIZARD_OPEN)
			return 0;

		if(m_pSlotMessage == NULL) 
		{
			m_pSlotMessage = new CSlotMessage(NULL, OBJ_TYPE_STATIC, m_eSlotID);
			m_pLayer->AddObject(m_pSlotMessage, LAYER_TYPE_UI);

			float fFlag  = 1.f;
			if(m_pTransformCom->m_vPos.y > 0.0f)
				fFlag = -1.f;

			CTransformCom* pTransformCom = (CTransformCom*)m_pSlotMessage->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos.x  = m_pTransformCom->m_vPos.x;

			switch(m_eSlotID)
			{
			case SLOT_ID_BARBARIAN_BASH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2962f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_CLEAVE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_FRENZY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_WEAPON_THROW:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4074f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_PUNCH:
				pTransformCom->m_vSize = D3DXVECTOR3(0.4458f  , 0.3222f ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_NEAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_FAR_ATTACK:				
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_MAGIC_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_REND:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_SEISMIC_SLAM:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2944f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_WHIRLWIND:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_GROUND_STOMP:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3685f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_LEAP:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3685f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_SPRINT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2944f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_IGNORE_PAIN:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_OVERPOWER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4018f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_REVENGE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_THREATENING_SHOUT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_BATTLE_RAGE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_WAR_CRY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_EARTHQUAKE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5148f  ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5148f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_BOLA:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4074f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5148f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_GRENADES:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_PUNCH:
				pTransformCom->m_vSize = D3DXVECTOR3(0.4458f  , 0.3222f ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_IMPALE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3648f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_CHAKRAM:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3277f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3703f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_CALTROPS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_SHADOW_POWER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_VAULT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_PREPARATION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2944f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_COMPANION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2944f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_SPIKE_TRAP:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_SENTRY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_STRAFE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3648f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_MULTISHOT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4018f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3685f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_FISTS_OF_THUNDER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_DEADLY_REACH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3648f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_CRIPPLING_WAVE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3203f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_PUNCH:
				pTransformCom->m_vSize = D3DXVECTOR3(0.4458f  , 0.3222f ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_NEAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_FAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MAGIC_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_LASHING_TAIL_KICK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_TEMPEST_RUSH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_WAVE_OF_LIGHT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_BLINDING_FLASH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_BREATH_OF_HEAVEN:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_SERENITY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_INNER_SANCTUARY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_DASHING_STRIKE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4018f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_EXPLODING_PALM:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_SWEEPING_WIND:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_CYCLONE_STRIKE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_SEVEN_SIDED_STRIKE:	
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4777f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MYSTIC_ALLY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MANTRA_OF_SALVATION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4777f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5129f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MANTRA_OF_HEALING:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5129f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_MONK_MANTRA_OF_CONVICTION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.5129f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_POISON_DART:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4074f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_FIREBOMB:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4425f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_PUNCH:
				pTransformCom->m_vSize = D3DXVECTOR3(0.4458f  , 0.3222f ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_FIREBATS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_HAUNT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2944f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_HORRIFY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_HEX:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_SACRIFICE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2740f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3277f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3277f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_GARGANTUAN:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_MAGIC_MISSILE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4037f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_SHOCK_PULSE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_SPECTRAL_BLADE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ELECTROCUTE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4055f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_PUNCH:
				pTransformCom->m_vSize = D3DXVECTOR3(0.4458f  , 0.3222f ,1.f  );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_NEAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_FAR_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3333f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_MAGIC_ATTACK:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3388f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_RAY_OF_FROST:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3277f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ARCANE_ORB:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ARCANE_TORRENT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2888f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_DISINTEGRATE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_FROST_NOVA:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_DIAMOND_SKIN:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_SLOW_TIME:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_TELEPORT:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2907f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_WAVE_OF_FORCE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.2925f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ENERGY_TWISTER:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_HYDRA:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_METEOR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_BLIZZARD:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3277f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ICE_ARMOR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4370f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_STORM_ARMOR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4407f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_MAGIC_WEAPON:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3666f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_FAMILIAR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ENERGY_ARMOR:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.4370f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_EXPLOSIVE_BLAST:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3648f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_MIRROR_IMAGE:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3314f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			case SLOT_ID_WIZARD_ARCHON:
				pTransformCom->m_vSize = D3DXVECTOR3( 0.4458f , 0.3296f , 1.f );
				pTransformCom->m_vPos.y  = m_pTransformCom->m_vPos.y + ((m_pTransformCom->m_vSize.y / 2.f + pTransformCom->m_vSize.y /2.f + 0.02f )  * fFlag) ;
				break;
			}

			m_pSlotMessage->Initialize();
		}
	}
	else
	{
		if(m_pSlotMessage != NULL)
		{
			m_pSlotMessage->Destroy();
			m_pSlotMessage = NULL;
		}
	}

	return 0;
}

void CSkillButton::Render()
{
	CButtonUI::Render();
}

void CSkillButton::Release()
{
	// SlotMessage
	if(m_pSlotMessage != NULL)
	{
		m_pSlotMessage->Destroy();
		m_pSlotMessage = NULL;
	}
}