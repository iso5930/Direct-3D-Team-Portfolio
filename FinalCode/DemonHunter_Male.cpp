#include "StdAfx.h"
#include "DemonHunter_Female.h"

CDemonHunter_Male::CDemonHunter_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CPlayer(_tszObjKey, _eObjType)
{
	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 15.0f, 50.0f, 15.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_PLAYER, 250.0f);
	AddComponent(pPathFindCom);
}

CDemonHunter_Male::~CDemonHunter_Male()
{
	Release();
}

void CDemonHunter_Male::Initialize()
{
	CPlayer::Initialize();
}

int CDemonHunter_Male::Update()
{
	CPlayer::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_fTime = 0.0f;

		int iMaxLife = int((m_stat.iMaxLife + GetVitality() * 10) * GetRestoresBonus());

		m_stat.iLife += GetLifeRecoveryOfSecond();
		if(m_stat.iLife > iMaxLife)
			m_stat.iLife = iMaxLife;

		m_stat.iHate += GetHateRecoveryOfSecond();
		if(m_stat.iHate > m_stat.iMaxHate)
			m_stat.iHate = m_stat.iMaxHate;

		m_stat.iControl += GetHateRecoveryOfSecond();
		if(m_stat.iControl > m_stat.iMaxControl)
			m_stat.iControl = m_stat.iMaxControl;
	}

	return 0;
}

void CDemonHunter_Male::Render()
{
	CPlayer::Render();
}

void CDemonHunter_Male::Release()
{
}

int CDemonHunter_Male::Attack()
{
	// Attack
	CPlayer::Attack();

	// Agility
	int iAgility = GetAgility();

	// Att
	int iAtt = GetAtt() + iAgility;

	// Agility
	iAtt = int(iAtt * (1.0f + iAgility / 100.0f));

	float fRand = (rand() % 1000) / 1000.0f;
	if(fRand < GetCriticalProbability())
		iAtt = int(iAtt * (1.0f + GetCriticalDamage()));

	fRand = ((rand() % 400) - 200) / 1000.0f;
	return int(iAtt * (1.0f + fRand));
}

void CDemonHunter_Male::LevelUp()
{
	// Stat
	m_stat.iStrength += 1;
	m_stat.iAgility += 3;
	m_stat.iIntelligence += 1;
	m_stat.iVitality += 2;

	// LevelUp
	CPlayer::LevelUp();

	// Slot
	if(m_stat.iLevel == 4)
	{
		delete m_pSlot[0];
		m_pSlot[0] = new CDemonHunterOpenSlot;
		m_pSlot[0]->SetOwner(this);
	}
	else if(m_stat.iLevel == 9)
	{
		delete m_pSlot[1];
		m_pSlot[1] = new CDemonHunterOpenSlot;
		m_pSlot[1]->SetOwner(this);
	}
	else if(m_stat.iLevel == 14)
	{
		delete m_pSlot[2];
		m_pSlot[2] = new CDemonHunterOpenSlot;
		m_pSlot[2]->SetOwner(this);
	}
	else if(m_stat.iLevel == 19)
	{
		delete m_pSlot[3];
		m_pSlot[3] = new CDemonHunterOpenSlot;
		m_pSlot[3]->SetOwner(this);
	}

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SKILL);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_SECONDARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_DEFENSIVE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_HUNTING);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_DEMONHUNTER_ARCHERY);
}

void CDemonHunter_Male::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CDemonHunter_Male::Damage(CEffect* _pEffect)
{
	// Damage
	CPlayer::Damage(_pEffect);
}

void CDemonHunter_Male::Renew()
{
	// Renew
	CPlayer::Renew();
}

void CDemonHunter_Male::CreateAttack()
{
	// CreateAttack
	CPlayer::CreateAttack();
}

void CDemonHunter_Male::SetSlot(int _iIndex, CSlot* _pSlot)
{
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
		{
			if(m_pSlot[i]->GetSlotID() == _pSlot->GetSlotID())
			{
				delete m_pSlot[i];
				m_pSlot[i] = new CDemonHunterOpenSlot;
				m_pSlot[i]->SetOwner(this);
				break;
			}
		}
	}

	// SetSlot
	CPlayer::SetSlot(_iIndex, _pSlot);
}

int CDemonHunter_Male::TotalStat1()
{
	// Agility
	int iAgility = GetAgility();

	// Attack
	int iAttack = GetAtt() + iAgility;

	// Agility
	iAttack = int(iAttack * (1.0f + iAgility / 100.0f));

	// CriticalAttack
	int iCriticalAttack = int(iAttack * GetCriticalDamage());
	iCriticalAttack = int(iCriticalAttack * GetCriticalProbability());

	// Coef
	float fCoef1 = GetReducedCooldownTime();
	float fCoef2 = (GetReducedHateConsumption() + GetReducedControlConsumption()) / 2.0f;
	float fCoef3 = (GetHateRecoveryOfSecond() / 125.0f + GetControlRecoveryOfSecond() / 30.0f) / 2.0f;

	// TotalAttack
	int iTotalAttack = iAttack + iCriticalAttack;
	iTotalAttack = int(iTotalAttack * (1.0f + fCoef1 + fCoef2 + fCoef3));

	return iTotalAttack;
}

int CDemonHunter_Male::TotalStat2()
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

int CDemonHunter_Male::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}