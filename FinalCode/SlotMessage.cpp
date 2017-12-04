#include "StdAfx.h"
#include "SlotMessage.h"

CSlotMessage::CSlotMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, SLOT_ID _eSlotID)
: CMessageUI(_tszObjKey, _eObjType, NULL)
{
	// Texture
	switch(_eSlotID)
	{
	case SLOT_ID_BARBARIAN_POTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Potion"));
		break;
	case SLOT_ID_BARBARIAN_BASH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Bash"));
		break;
	case SLOT_ID_BARBARIAN_CLEAVE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Cleave"));
		break;
	case SLOT_ID_BARBARIAN_FRENZY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Frenzy"));
		break;
	case SLOT_ID_BARBARIAN_WEAPON_THROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WeaponThrow"));
		break;
	case SLOT_ID_BARBARIAN_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Punch"));
		break;
	case SLOT_ID_BARBARIAN_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_NearAttack"));
		break;
	case SLOT_ID_BARBARIAN_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FarAttack"));
		break;
	case SLOT_ID_BARBARIAN_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicAttack"));
		break;
	case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_HammerOfTheAncients"));
		break;
	case SLOT_ID_BARBARIAN_REND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Rend"));
		break;
	case SLOT_ID_BARBARIAN_SEISMIC_SLAM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SeismicSlam"));
		break;
	case SLOT_ID_BARBARIAN_WHIRLWIND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Whirlwind"));
		break;
	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_AncientSpear"));
		break;
	case SLOT_ID_BARBARIAN_GROUND_STOMP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_GroundStomp"));
		break;
	case SLOT_ID_BARBARIAN_LEAP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Leap"));
		break;
	case SLOT_ID_BARBARIAN_SPRINT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Sprint"));
		break;
	case SLOT_ID_BARBARIAN_IGNORE_PAIN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_IgnorePain"));
		break;
	case SLOT_ID_BARBARIAN_OVERPOWER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Overpower"));
		break;
	case SLOT_ID_BARBARIAN_REVENGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Revenge"));
		break;
	case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FuriousCharge"));
		break;
	case SLOT_ID_BARBARIAN_THREATENING_SHOUT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ThreateningShout"));
		break;
	case SLOT_ID_BARBARIAN_BATTLE_RAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_BattleRage"));
		break;
	case SLOT_ID_BARBARIAN_WAR_CRY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WarCry"));
		break;
	case SLOT_ID_BARBARIAN_EARTHQUAKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Earthquake"));
		break;
	case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_CallOfTheAncients"));
		break;
	case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WrathOfTheBerserker"));
		break;
	case SLOT_ID_DEMONHUNTER_POTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Potion"));
		break;
	case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_HungeringArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_EntanglingShot"));
		break;
	case SLOT_ID_DEMONHUNTER_BOLA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Bola"));
		break;
	case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_EvasiveFire"));
		break;
	case SLOT_ID_DEMONHUNTER_GRENADES:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Grenades"));
		break;
	case SLOT_ID_DEMONHUNTER_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Punch"));
		break;
	case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_NearAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FarAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicAttack"));
		break;
	case SLOT_ID_DEMONHUNTER_IMPALE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Impale"));
		break;
	case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_RapidFire"));
		break;
	case SLOT_ID_DEMONHUNTER_CHAKRAM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Chakram"));
		break;
	case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ElementalArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_CALTROPS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Caltrops"));
		break;
	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SmokeScreen"));
		break;
	case SLOT_ID_DEMONHUNTER_SHADOW_POWER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ShadowPower"));
		break;
	case SLOT_ID_DEMONHUNTER_VAULT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Vault"));
		break;
	case SLOT_ID_DEMONHUNTER_PREPARATION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Preparation"));
		break;
	case SLOT_ID_DEMONHUNTER_COMPANION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Companion"));
		break;
	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MarkedForDeath"));
		break;
	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FanOfKnives"));
		break;
	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SpikeTrap"));
		break;
	case SLOT_ID_DEMONHUNTER_SENTRY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Sentry"));
		break;
	case SLOT_ID_DEMONHUNTER_STRAFE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Strafe"));
		break;
	case SLOT_ID_DEMONHUNTER_MULTISHOT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Multishot"));
		break;
	case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ClusterArrow"));
		break;
	case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_RainOfVengeance"));
		break;
	case SLOT_ID_MONK_POTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Potion"));
		break;
	case SLOT_ID_MONK_FISTS_OF_THUNDER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FistsOfThunder"));
		break;
	case SLOT_ID_MONK_DEADLY_REACH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_DeadlyReach"));
		break;
	case SLOT_ID_MONK_CRIPPLING_WAVE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_CripplingWave"));
		break;
	case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WayOfTheHundredFists"));
		break;
	case SLOT_ID_MONK_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Punch"));
		break;
	case SLOT_ID_MONK_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_NearAttack"));
		break;
	case SLOT_ID_MONK_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FarAttack"));
		break;
	case SLOT_ID_MONK_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicAttack"));
		break;
	case SLOT_ID_MONK_LASHING_TAIL_KICK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_LashingTailKick"));
		break;
	case SLOT_ID_MONK_TEMPEST_RUSH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_TempestRush"));
		break;
	case SLOT_ID_MONK_WAVE_OF_LIGHT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WaveOfLight"));
		break;
	case SLOT_ID_MONK_BLINDING_FLASH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_BlindingFlash"));
		break;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_BreathOfHeaven"));
		break;
	case SLOT_ID_MONK_SERENITY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Serenity"));
		break;
	case SLOT_ID_MONK_INNER_SANCTUARY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_InnerSanctuary"));
		break;
	case SLOT_ID_MONK_DASHING_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_DashingStrike"));
		break;
	case SLOT_ID_MONK_EXPLODING_PALM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ExplodingPalm"));
		break;
	case SLOT_ID_MONK_SWEEPING_WIND:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SweepingWind"));
		break;
	case SLOT_ID_MONK_CYCLONE_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_CycloneStrike"));
		break;
	case SLOT_ID_MONK_SEVEN_SIDED_STRIKE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SevenSidedStrike"));
		break;
	case SLOT_ID_MONK_MYSTIC_ALLY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MysticAlly"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_SALVATION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MantraOfSalvation"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MantraOfRetribution"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_HEALING:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MantraOfHealing"));
		break;
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MantraOfConviction"));
		break;
	case SLOT_ID_WITCHDOCTOR_POTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Potion"));
		break;
	case SLOT_ID_WITCHDOCTOR_POISON_DART:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_PoisonDart"));
		break;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_CorpseSpiders"));
		break;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_PlagueOfToads"));
		break;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Firebomb"));
		break;
	case SLOT_ID_WITCHDOCTOR_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Punch"));
		break;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_NearAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FarAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicAttack"));
		break;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_GraspOfTheDead"));
		break;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Firebats"));
		break;
	case SLOT_ID_WITCHDOCTOR_HAUNT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Haunt"));
		break;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_LocustSwarm"));
		break;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SummonZombieDogs"));
		break;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Horrify"));
		break;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SpiritWalk"));
		break;
	case SLOT_ID_WITCHDOCTOR_HEX:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Hex"));
		break;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SoulHarvest"));
		break;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Sacrifice"));
		break;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MassConfusion"));
		break;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ZombieCharger"));
		break;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SpiritBarrage"));
		break;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_AcidCloud"));
		break;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WallOfDeath"));
		break;
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Gargantuan"));
		break;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_BigBadVoodoo"));
		break;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FetishArmy"));
		break;
	case SLOT_ID_WIZARD_POTION:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Potion"));
		break;
	case SLOT_ID_WIZARD_MAGIC_MISSILE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicMissile"));
		break;
	case SLOT_ID_WIZARD_SHOCK_PULSE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ShockPulse"));
		break;
	case SLOT_ID_WIZARD_SPECTRAL_BLADE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SpectralBlade"));
		break;
	case SLOT_ID_WIZARD_ELECTROCUTE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Electrocute"));
		break;
	case SLOT_ID_WIZARD_PUNCH:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Punch"));
		break;
	case SLOT_ID_WIZARD_NEAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_NearAttack"));
		break;
	case SLOT_ID_WIZARD_FAR_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FarAttack"));
		break;
	case SLOT_ID_WIZARD_MAGIC_ATTACK:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicAttack"));
		break;
	case SLOT_ID_WIZARD_RAY_OF_FROST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_RayOfFrost"));
		break;
	case SLOT_ID_WIZARD_ARCANE_ORB:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ArcaneOrb"));
		break;
	case SLOT_ID_WIZARD_ARCANE_TORRENT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ArcaneTorrent"));
		break;
	case SLOT_ID_WIZARD_DISINTEGRATE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Disintegrate"));
		break;
	case SLOT_ID_WIZARD_FROST_NOVA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_FrostNova"));
		break;
	case SLOT_ID_WIZARD_DIAMOND_SKIN:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_DiamondSkin"));
		break;
	case SLOT_ID_WIZARD_SLOW_TIME:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_SlowTime"));
		break;
	case SLOT_ID_WIZARD_TELEPORT:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Teleport"));
		break;
	case SLOT_ID_WIZARD_WAVE_OF_FORCE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_WaveOfForce"));
		break;
	case SLOT_ID_WIZARD_ENERGY_TWISTER:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_EnergyTwister"));
		break;
	case SLOT_ID_WIZARD_HYDRA:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Hydra"));
		break;
	case SLOT_ID_WIZARD_METEOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Meteor"));
		break;
	case SLOT_ID_WIZARD_BLIZZARD:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Blizzard"));
		break;
	case SLOT_ID_WIZARD_ICE_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_IceArmor"));
		break;
	case SLOT_ID_WIZARD_STORM_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_StormArmor"));
		break;
	case SLOT_ID_WIZARD_MAGIC_WEAPON:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MagicWeapon"));
		break;
	case SLOT_ID_WIZARD_FAMILIAR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Familiar"));
		break;
	case SLOT_ID_WIZARD_ENERGY_ARMOR:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_EnergyArmor"));
		break;
	case SLOT_ID_WIZARD_EXPLOSIVE_BLAST:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ExplosiveBlast"));
		break;
	case SLOT_ID_WIZARD_MIRROR_IMAGE:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_MirrorImage"));
		break;
	case SLOT_ID_WIZARD_ARCHON:
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_Archon"));
		break;
	}
}

CSlotMessage::~CSlotMessage()
{
	Release();
}

void CSlotMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CSlotMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CSlotMessage::Render()
{
	CMessageUI::Render();
}

void CSlotMessage::Release()
{
}