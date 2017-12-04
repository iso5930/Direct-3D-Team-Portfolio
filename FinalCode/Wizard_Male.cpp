#include "StdAfx.h"
#include "Wizard_Male.h"

CWizard_Male::CWizard_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
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

CWizard_Male::~CWizard_Male()
{
	Release();
}

void CWizard_Male::Initialize()
{
	CPlayer::Initialize();
}

int CWizard_Male::Update()
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

		m_stat.iVision += GetVisionRecoveryOfSecond();
		if(m_stat.iVision > m_stat.iMaxVision)
			m_stat.iVision = m_stat.iMaxVision;
	}

	return 0;
}

void CWizard_Male::Render()
{
	CPlayer::Render();
}

void CWizard_Male::Release()
{
}

int CWizard_Male::Attack()
{
	// Attack
	CPlayer::Attack();

	// Intelligence
	int iIntelligence = GetIntelligence();

	// Att
	int iAtt = GetAtt() + iIntelligence;

	// Intelligence
	iAtt = int(iAtt * (1.0f + iIntelligence / 100.0f));

	float fRand = (rand() % 1000) / 1000.0f;
	if(fRand < GetCriticalProbability())
		iAtt = int(iAtt * (1.0f + GetCriticalDamage()));

	fRand = ((rand() % 400) - 200) / 1000.0f;
	return int(iAtt * (1.0f + fRand));
}

void CWizard_Male::LevelUp()
{
	// Stat
	m_stat.iStrength += 1;
	m_stat.iAgility += 1;
	m_stat.iIntelligence += 3;
	m_stat.iVitality += 2;

	// LevelUp
	CPlayer::LevelUp();

	// Slot
	if(m_stat.iLevel == 4)
	{
		delete m_pSlot[0];
		m_pSlot[0] = new CWizardOpenSlot;
		m_pSlot[0]->SetOwner(this);
	}
	else if(m_stat.iLevel == 9)
	{
		delete m_pSlot[1];
		m_pSlot[1] = new CWizardOpenSlot;
		m_pSlot[1]->SetOwner(this);
	}
	else if(m_stat.iLevel == 14)
	{
		delete m_pSlot[2];
		m_pSlot[2] = new CWizardOpenSlot;
		m_pSlot[2]->SetOwner(this);
	}
	else if(m_stat.iLevel == 19)
	{
		delete m_pSlot[3];
		m_pSlot[3] = new CWizardOpenSlot;
		m_pSlot[3]->SetOwner(this);
	}

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SKILL);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_PRIMARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_SECONDARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_DEFENSIVE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_FORCE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_CONJURATION);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WIZARD_MASTERY);
}

void CWizard_Male::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CWizard_Male::Damage(CEffect* _pEffect)
{
	// Damage
	CPlayer::Damage(_pEffect);
}

void CWizard_Male::Renew()
{
	// Renew
	CPlayer::Renew();
}

void CWizard_Male::CreateAttack()
{
	// CreateAttack
	CPlayer::CreateAttack();
}

void CWizard_Male::SetSlot(int _iIndex, CSlot* _pSlot)
{
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
		{
			if(m_pSlot[i]->GetSlotID() == _pSlot->GetSlotID())
			{
				delete m_pSlot[i];
				m_pSlot[i] = new CWizardOpenSlot;
				m_pSlot[i]->SetOwner(this);
				break;
			}
		}
	}

	// SetSlot
	CPlayer::SetSlot(_iIndex, _pSlot);
}

int CWizard_Male::TotalStat1()
{
	// Intelligence
	int iIntelligence = GetIntelligence();

	// Attack
	int iAttack = GetAtt() + iIntelligence;

	// Intelligence
	iAttack = int(iAttack * (1.0f + iIntelligence / 100.0f));

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

int CWizard_Male::TotalStat2()
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

int CWizard_Male::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}