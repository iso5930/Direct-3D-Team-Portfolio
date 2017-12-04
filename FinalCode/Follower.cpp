#include "StdAfx.h"
#include "Follower.h"

CFollower::CFollower(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner, FollowerInfo* _pFollowerInfo)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_FOLLOWER);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_FOLLOWER);
	AddComponent(pRenderCom);

	// PathFindCom
	m_pPathFindCom = new CPathFindCom(PATH_TYPE_FOLLOWER, 250.0f);
	AddComponent(m_pPathFindCom);

	// BufferCom
	m_pBufferCom = new CBufferCom;
	AddComponent(m_pBufferCom);

	// Owner
	m_pOwner = _pOwner;

	// OwnerTransformCom
	m_pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	// FollowerInfo
	memcpy_s(&m_FollowerInfo, sizeof(FollowerInfo), _pFollowerInfo, sizeof(FollowerInfo));

	// State
	m_pState = NULL;

	// DynamicMesh
	m_pDynamicMesh = NULL;

	// MainWeapon
	m_pMainWeapon = NULL;

	// SubWeapon
	m_pSubWeapon = NULL;
}

CFollower::~CFollower()
{
	Release();
}

void CFollower::Initialize()
{
	CObject::Initialize();

	// DynamicMesh
	m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[0];
}

int CFollower::Update()
{
	// Speed
	if(m_pOwner != NULL)
	{
		// Dst
		D3DXVECTOR3 vDst = m_pOwnerTransformCom->m_vPos + m_pOwnerTransformCom->m_vAxisZ * 200.0f;

		if(D3DXVec3Length(&(vDst - m_pTransformCom->m_vPos)) > 300.0f)
			m_pPathFindCom->m_fSpeed = 300.0f;
		else
			m_pPathFindCom->m_fSpeed = 250.0f;
	}

	// Action
	CFollowerState* pState = NULL;

	if(m_pState != NULL)
		pState = m_pState->Action();

	if(pState != NULL)
	{
		delete m_pState;
		m_pState = pState;
		m_pState->SetOwner(this);
		m_pState->Initialize();
	}

	CObject::Update();

	return 0;
}

void CFollower::Render()
{
	CObject::Render();
}

void CFollower::Release()
{
	// State
	if(m_pState != NULL)
	{
		delete m_pState;
		m_pState = NULL;
	}

	// MainWeapon
	if(m_pMainWeapon != NULL)
	{
		m_pMainWeapon->Destroy();
		m_pMainWeapon = NULL;
	}

	// SubWeapon
	if(m_pSubWeapon != NULL)
	{
		m_pSubWeapon->Destroy();
		m_pSubWeapon = NULL;
	}
}

void CFollower::Renew()
{
	// MainWeapon
	if(m_pMainWeapon != NULL)
	{
		m_pMainWeapon->Destroy();
		m_pMainWeapon = NULL;
	}

	// SubWeapon
	if(m_pSubWeapon != NULL)
	{
		m_pSubWeapon->Destroy();
		m_pSubWeapon = NULL;
	}
}

int CFollower::TotalStat1()
{
	return 0;
}

int CFollower::TotalStat2()
{
	return 0;
}

int CFollower::TotalStat3()
{
	return 0;
}

void CFollower::SetState(CFollowerState* _pState)
{
	if(m_pState != NULL)
	{
		delete m_pState;
		m_pState = NULL;
	}

	m_pState = _pState;
	m_pState->SetOwner(this);
	m_pState->Initialize();
}

void CFollower::SetAnimation(int _iIndex)
{
	m_pDynamicMesh->m_pAnimController->SetAnimation(_iIndex);
}

// GetValue
int CFollower::GetAtt()
{
	int iCnt = 0;
	float fAtt = 10.0f;
	DWORD dw = WEAPON_ID_AXE | WEAPON_ID_BOW | WEAPON_ID_CEREMONIAL_DAGGER	| WEAPON_ID_FIST | WEAPON_ID_HANDXBOW |	WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_QUIVER | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_STAFF | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_WAND | WEAPON_ID_MOJO | WEAPON_ID_CROSSBOW | WEAPON_ID_ORB;
	if(CItemMgr::GetInstance()->GetItemInFollowerEquip(0) != NULL && (CItemMgr::GetInstance()->GetItemInFollowerEquip(0)->dwItemID & dw))
		fAtt += CItemMgr::GetInstance()->GetItemInFollowerEquip(9)->iValue;

	return int(fAtt);
}
int CFollower::GetDef()
{
	return 0;
}

// MainStat
int CFollower::GetStrength()
{
	int iStrength = m_FollowerInfo.stat.iStrength;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
		{
			iStrength += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tMainStat.iStrength;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->iSockCnt; ++j)
				iStrength += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->SockArr[j]->tMainStat.iStrength;
		}
	}
	return iStrength;
}
int CFollower::GetAgility()
{
	int iAgility = m_FollowerInfo.stat.iAgility;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
		{
			iAgility += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tMainStat.iAgility;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->iSockCnt; ++j)
				iAgility += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->SockArr[j]->tMainStat.iAgility;
		}
	}
	return iAgility;
}
int CFollower::GetIntelligence()
{
	int iIntelligence = m_FollowerInfo.stat.iIntelligence;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
		{
			iIntelligence += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tMainStat.iIntelligence;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->iSockCnt; ++j)
				iIntelligence += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->SockArr[j]->tMainStat.iIntelligence;
		}
	}
	return iIntelligence;
}
int CFollower::GetVitality()
{
	int iVitality = m_FollowerInfo.stat.iVitality;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
		{
			iVitality += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tMainStat.iVitality;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->iSockCnt; ++j)
				iVitality += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->SockArr[j]->tMainStat.iVitality;
		}
	}
	return iVitality;
}

// AttackStat
float CFollower::GetReducedCooldownTime()
{
	float fReducedCooldownTime = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedCooldownTime += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAttackStat.fReducedCooldownTime;
	}
	return fReducedCooldownTime;
}
float CFollower::GetCriticalProbability()
{
	float fCriticalProbability = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fCriticalProbability += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAttackStat.fCriticalProbability;
	}
	return fCriticalProbability;
}
float CFollower::GetCriticalDamage()
{
	float fCriticalDamage = 1.5f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fCriticalDamage += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAttackStat.fCriticalDamage;
	}
	return fCriticalDamage;
}

// DefenseStat
int CFollower::GetPhysicalResistance()
{
	int iPhysicalResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iPhysicalResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iPhysicalResistance;
	}
	return iPhysicalResistance;
}
int CFollower::GetColdResistance()
{
	int iColdResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iColdResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iColdResistance;
	}
	return iColdResistance;
}
int CFollower::GetFlameResistance()
{
	int iFlameResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iFlameResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iFlameResistance;
	}
	return iFlameResistance;
}
int CFollower::GetLightningResistance()
{
	int iLightningResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iLightningResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iLightningResistance;
	}
	return iLightningResistance;
}
int CFollower::GetPoisonResistance()
{
	int iPoisonResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iPoisonResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iPoisonResistance;
	}
	return iPoisonResistance;
}
int CFollower::GetHolyResistance()
{
	int iHolyResistance = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iHolyResistance += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.iHolyResistance;
	}
	return iHolyResistance;
}
float CFollower::GetReducedNearDamage()
{
	float fReducedNearDamage = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedNearDamage += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.fReducedNearDamage;
	}
	return fReducedNearDamage;
}
float CFollower::GetReducedFarDamage()
{
	float fReducedFarDamage = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedFarDamage += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tDefenseStat.fReducedFarDamage;
	}
	return fReducedFarDamage;
}

// LifeStat
float CFollower::GetRestoresBonus()
{
	float fRestoresBonus = 1.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fRestoresBonus += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tLifeStat.fRestoresBonus;
	}
	return fRestoresBonus;
}
int CFollower::GetLifeRecoveryOfSecond()
{
	int iLifeRecoveryOfSecond = 0;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iLifeRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tLifeStat.iLifeRecoveryOfSecond;
	}
	return iLifeRecoveryOfSecond;
}
int CFollower::GetLifeRecoveryOfHit()
{
	int iLifeRecoveryOfHit = 0;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iLifeRecoveryOfHit += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tLifeStat.iLifeRecoveryOfHit;
	}
	return iLifeRecoveryOfHit;
}

// ResourceStat
int CFollower::GetControlRecoveryOfSecond()
{
	int iControlRecoveryOfSecond = 1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iControlRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iControlRecoveryOfSecond;
	}
	return iControlRecoveryOfSecond;
}
int CFollower::GetEffortRecoveryOfSecond()
{
	int iEffortRecoveryOfSecond = 0;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iEffortRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iEffortRecoveryOfSecond;
	}
	return iEffortRecoveryOfSecond;
}
int CFollower::GetHateRecoveryOfSecond()
{
	int iHateRecoveryOfSecond = 4;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iHateRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iHateRecoveryOfSecond;
	}
	return iHateRecoveryOfSecond;
}
int CFollower::GetManaRecoveryOfSecond()
{
	int iManaRecoveryOfSecond = 50;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iManaRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iManaRecoveryOfSecond;
	}
	return iManaRecoveryOfSecond;
}
int CFollower::GetRageRecoveryOfSecond()
{
	int iRageRecoveryOfSecond = -1;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iRageRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iRageRecoveryOfSecond;
	}
	return iRageRecoveryOfSecond;
}
int CFollower::GetVisionRecoveryOfSecond()
{
	int iVisionRecoveryOfSecond = 10;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			iVisionRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.iVisionRecoveryOfSecond;
	}
	return iVisionRecoveryOfSecond;
}
float CFollower::GetReducedControlConsumption()
{
	float fReducedControlConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedControlConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedControlConsumption;
	}
	return fReducedControlConsumption;
}
float CFollower::GetReducedEffortConsumption()
{
	float fReducedEffortConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedEffortConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedEffortConsumption;
	}
	return fReducedEffortConsumption;
}
float CFollower::GetReducedHateConsumption()
{
	float fReducedHateConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedHateConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedHateConsumption;
	}
	return fReducedHateConsumption;
}
float CFollower::GetReducedManaConsumption()
{
	float fReducedManaConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedManaConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedManaConsumption;
	}
	return fReducedManaConsumption;
}
float CFollower::GetReducedRageConsumption()
{
	float fReducedRageConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedRageConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedRageConsumption;
	}
	return fReducedRageConsumption;
}
float CFollower::GetReducedVisionConsumption()
{
	float fReducedVisionConsumption = 0.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fReducedVisionConsumption += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tResourceStat.fReducedVisionConsumption;
	}
	return fReducedVisionConsumption;
}

// AdventureStat
float CFollower::GetExperience()
{
	float fExperience = 1.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fExperience += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAdventureStat.fExperience;
	}
	return fExperience;
}
float CFollower::GetMagicItemsFound()
{
	float fMagicItemsFound = 1.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fMagicItemsFound += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAdventureStat.fMagicItemsFound;
	}
	return fMagicItemsFound;
}
float CFollower::GetDiscoveryOfGoldCoins()
{
	float fDiscoveryOfGoldCoins = 1.0f;
	for(int i = 0; i < 5; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInFollowerEquip(i) != NULL)
			fDiscoveryOfGoldCoins += CItemMgr::GetInstance()->GetItemInFollowerEquip(i)->tAdventureStat.fDiscoveryOfGoldCoins;
	}
	return fDiscoveryOfGoldCoins;
}