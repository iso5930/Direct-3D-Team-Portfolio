#include "StdAfx.h"
#include "Enchantress.h"

CEnchantress::CEnchantress(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CPlayer* _pOwner, FollowerInfo* _pFollowerInfo)
: CFollower(_tszObjKey, _eObjType, _pOwner, _pFollowerInfo)
{
	// Time
	m_fTime = 0.0f;

	// RightWeaponBone
	m_RightWeaponBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_RightWeaponBone.mWorld);

	// BufferCom
	m_pBufferCom->AddBuffer(_T("Enchantress_Base"));
}

CEnchantress::~CEnchantress()
{
	Release();
}

void CEnchantress::Initialize()
{
	CFollower::Initialize();

	// RightWeaponBone
	m_RightWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(m_pDynamicMesh->m_pRootFrame, "right_weapon");

	// LeftWeaponBone
	m_LeftWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(m_pDynamicMesh->m_pRootFrame, "left_weapon");

	// LeftShieldBone
	m_LeftShieldBone.pFrame = (MeshFrame*)D3DXFrameFind(m_pDynamicMesh->m_pRootFrame, "left_shield");

	// Renew
	Renew();
}

int CEnchantress::Update()
{
	CFollower::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_fTime = 0.0f;

		int iMaxLife = int((m_FollowerInfo.stat.iMaxLife + GetVitality() * 10) * GetRestoresBonus());

		m_FollowerInfo.stat.iLife += GetLifeRecoveryOfSecond();
		if(m_FollowerInfo.stat.iLife > iMaxLife)
			m_FollowerInfo.stat.iLife = iMaxLife;

		m_FollowerInfo.stat.iVision += GetVisionRecoveryOfSecond();
		if(m_FollowerInfo.stat.iVision > m_FollowerInfo.stat.iMaxVision)
			m_FollowerInfo.stat.iVision = m_FollowerInfo.stat.iMaxVision;
	}

	// RightWeaponBone
	m_RightWeaponBone.mWorld = m_RightWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// LeftWeaponBone
	m_LeftWeaponBone.mWorld = m_LeftWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// LeftShieldBone
	m_LeftShieldBone.mWorld = m_LeftShieldBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CEnchantress::Render()
{
	CFollower::Render();
}

void CEnchantress::Release()
{
}

void CEnchantress::Renew()
{
	// Renew
	CFollower::Renew();

	// MainWeapon & SubWeapon
	Item* pMainWeapon = CItemMgr::GetInstance()->GetItemInFollowerEquip(0);
	Item* pSubWeapon = CItemMgr::GetInstance()->GetItemInFollowerEquip(1);

	// ID
	DWORD dwOneHand = WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD;
	DWORD dwStaff = WEAPON_ID_STAFF;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CEnchantress_1HS_Idle_01(0));
	}
	// 한손무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CEnchantress_1HS_Idle_01(0));
	}
	// 지팡이 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwStaff) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CEnchantress_HTH_Idle_01(0));
	}
}

int CEnchantress::TotalStat1()
{
	// Intelligence
	int iIntelligence = GetIntelligence();

	// Attack
	int iAttack = GetAtt() + iIntelligence;

	// CriticalAttack
	int iCriticalAttack = int(iAttack * GetCriticalDamage());
	iCriticalAttack = int(iCriticalAttack * GetCriticalProbability());

	// Coef
	float fCoef1 = GetReducedCooldownTime();
	float fCoef2 = GetReducedVisionConsumption();
	float fCoef3 = GetVisionRecoveryOfSecond() / 100.0f;

	// TotalAttack
	int iTotalAttack = iAttack + iCriticalAttack;
	iTotalAttack = int(iTotalAttack * (1.0f + fCoef1 + fCoef2 + fCoef3));

	return iTotalAttack;
}
int CEnchantress::TotalStat2()
{
	// Defense
	int iDefense = GetDef();

	// Coef
	float fCoef1 = GetPhysicalResistance() / 2000.0f;
	float fCoef2 = GetColdResistance() / 20000.0f;
	float fCoef3 = GetFlameResistance() / 20000.0f;
	float fCoef4 = GetLightningResistance() / 20000.0f;
	float fCoef5 = GetPoisonResistance() / 20000.0f;
	float fCoef6 = GetHolyResistance() / 20000.0f;

	// TotalDefense
	int iTotalDefense = int(iDefense * (1.0f + fCoef1 + fCoef2 + fCoef3 + fCoef4 + fCoef5 + fCoef6));

	return iTotalDefense;
}
int CEnchantress::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}