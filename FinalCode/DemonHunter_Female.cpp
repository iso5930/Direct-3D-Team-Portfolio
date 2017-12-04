#include "StdAfx.h"
#include "DemonHunter_Female.h"

CDemonHunter_Female::CDemonHunter_Female(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CPlayer(_tszObjKey, _eObjType)
{
	// RightWeaponBone
	m_RightWeaponBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_RightWeaponBone.mWorld);

	// LeftWeaponBone
	m_LeftWeaponBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_LeftWeaponBone.mWorld);

	// LeftShieldBone
	m_LeftShieldBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_LeftShieldBone.mWorld);

	// HeadBone
	m_HeadBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_HeadBone.mWorld);

	// RightShoulder
	m_RightShoulderBone.pFrame = NULL;
	D3DXMatrixIdentity(&m_RightShoulderBone.mWorld);

	// CollisionCom 
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 15.0f, 50.0f, 15.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_PLAYER, 250.0f);
	AddComponent(pPathFindCom);

	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

	// TransformCom
	m_pTransformCom->m_vPos = pAccount->vPos;
	m_pTransformCom->m_vAngle = pAccount->vAngle;
	m_pTransformCom->m_vSize = pAccount->vSize;

	// Info
	memcpy_s(&m_info, sizeof(Info), &pAccount->info, sizeof(Info));

	// Stat
	memcpy_s(&m_stat , sizeof(Stat), &pAccount->stat, sizeof(Stat));

	// Slot
	ZeroMemory(m_pSlot, sizeof(m_pSlot));
	for(int i = 0; i < 7; ++i)
	{
		switch(pAccount->eSlotID[i])
		{
		case SLOT_ID_DEMONHUNTER_OPEN:
			m_pSlot[i] = new CDemonHunterOpenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_CLOSE:
			m_pSlot[i] = new CDemonHunterCloseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_POTION:
			m_pSlot[i] = new CDemonHunterPotionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
			m_pSlot[i] = new CDemonHunterHungeringArrowSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
			m_pSlot[i] = new CDemonHunterEntanglingShotSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_BOLA:
			m_pSlot[i] = new CDemonHunterBolaSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
			m_pSlot[i] = new CDemonHunterEvasiveFireSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_GRENADES:
			m_pSlot[i] = new CDemonHunterGrenadesSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_PUNCH:
			m_pSlot[i] = new CDemonHunterPunchSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
			m_pSlot[i] = new CDemonHunterNearAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
			m_pSlot[i] = new CDemonHunterFarAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
			m_pSlot[i] = new CDemonHunterMagicAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_IMPALE:
			m_pSlot[i] = new CDemonHunterImpaleSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
			m_pSlot[i] = new CDemonHunterRapidFireSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_CHAKRAM:
			m_pSlot[i] = new CDemonHunterChakramSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
			m_pSlot[i] = new CDemonHunterElementalArrowSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_CALTROPS:
			m_pSlot[i] = new CDemonHunterCaltropsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN:
			m_pSlot[i] = new CDemonHunterSmokeScreenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_SHADOW_POWER:
			m_pSlot[i] = new CDemonHunterShadowPowerSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_VAULT:
			m_pSlot[i] = new CDemonHunterVaultSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_PREPARATION:
			m_pSlot[i] = new CDemonHunterPreparationSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_COMPANION:
			m_pSlot[i] = new CDemonHunterCompanionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH:
			m_pSlot[i] = new CDemonHunterMarkedForDeathSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:
			m_pSlot[i] = new CDemonHunterFanOfKnivesSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_SPIKE_TRAP:
			m_pSlot[i] = new CDemonHunterSpikeTrapSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_SENTRY:
			m_pSlot[i] = new CDemonHunterSentrySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_STRAFE:
			m_pSlot[i] = new CDemonHunterStrafeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_MULTISHOT:
			m_pSlot[i] = new CDemonHunterMultishotSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
			m_pSlot[i] = new CDemonHunterClusterArrowSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
			m_pSlot[i] = new CDemonHunterRainOfVengeanceSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		}
	}
}

CDemonHunter_Female::~CDemonHunter_Female()
{
	Release();
}

void CDemonHunter_Female::Initialize()
{
	CPlayer::Initialize();	

	// RightWeaponBone
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_RightWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");

	// LeftWeaponBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_LeftWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");

	// LeftShieldBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_LeftShieldBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_shield");

	// HeadBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[1];
	m_HeadBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Head");

	// RightShoulder
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[4];
	m_RightShoulderBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_shoulderPad");
}

int CDemonHunter_Female::Update()
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

	// RightWeaponBone
	m_RightWeaponBone.mWorld = m_RightWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// LeftWeaponBone
	m_LeftWeaponBone.mWorld = m_LeftWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// LeftShieldBone
	m_LeftShieldBone.mWorld = m_LeftShieldBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// HeadBone
	m_HeadBone.mWorld = m_HeadBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// RightShoulderBone
	m_RightShoulderBone.mWorld = m_RightShoulderBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CDemonHunter_Female::Render()
{
	CPlayer::Render();
}

void CDemonHunter_Female::Release()
{
}

int CDemonHunter_Female::Attack()
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

void CDemonHunter_Female::LevelUp()
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

void CDemonHunter_Female::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CDemonHunter_Female::Damage(CEffect* _pEffect)
{
	// Damage
	CPlayer::Damage(_pEffect);

	if (_pEffect->GetSkillType() == SKILL_TYPE_END)
	{
		return ;
	}
	
	D3DXVECTOR3 vDir = D3DXVECTOR3(0.f , 0.f ,0.f ); 

	switch(_pEffect->GetSkillType())
	{
	case SKILL_TYPE_ENTANGLE:
		AddMez(new Mez( SKILL_TYPE_ENTANGLE , 2.1f) );
		break;
	case SKILL_TYPE_FULL:
		vDir = ((CTransformCom*)_pEffect->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - m_pTransformCom->m_vPos;
		D3DXVec3Normalize(&vDir ,&vDir);
		break;
	case SKILL_TYPE_PUSH:
		vDir = m_pTransformCom->m_vPos -((CTransformCom*)_pEffect->m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos;
		D3DXVec3Normalize(&vDir ,&vDir);
		break;
	case SKILL_TYPE_STUN:
		AddMez(new Mez( SKILL_TYPE_STUN , 2.1f) );
		break;
	}


	switch(m_pState->GetStateType())
	{
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_ATTACK:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BOLASLOT:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BUFF:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_HIT:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_IDLE:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_MULTISHOT:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_RAINOFARROW:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_RUN:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_STUNNED:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BACKFLIP:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_COMPANION:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_STRAFE:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_CALTROP:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_FANOFKNIVES:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_IMPALE:SetState(new CDemonHunter_Female_BigBow_Mez (_pEffect->GetSkillType() , vDir)); break;
	
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_ATTACK:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BOLASLOT:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BUFF:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_HIT:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_IDLE:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_MULTISHOT:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_RAINOFARROW:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_RUN:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_STUNNED:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BACKFLIP:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_COMPANION:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_FANOFKNIVES:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;	
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_IMPALE:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;	
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_STRAFE:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;	
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BOW_CALTROP:SetState(new CDemonHunter_Female_Bow_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_ATTACK:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BOLASLOT:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BUFF:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_HIT:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_IDLE:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_MULTISHOT:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RAINOFARROW:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RUN:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_STUNNED:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BACKFLIP:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_COMPANION:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_CALTROP:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_IMPALE:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_FANOFKNIVES:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB1_STRAFE:SetState(new CDemonHunter_Female_CB1_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_LEFT:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_RIGHT:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BOLASLOT:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BUFF:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_HIT:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_IDLE:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_MULTISHOT:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_RAINOFARROW:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_RUN:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_STUNNED:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BACKFLIP:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_CALTROP:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_STRAFE:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_IMPALE:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_FANOFKNIVES:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CB2_COMPANION:SetState(new CDemonHunter_Female_CB2_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_DEMONHUNTER_FEMALE_IMPALE:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_STRAFE:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_ATTACK1:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_ATTACK2:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BACKFLIP:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_DEATH:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_HIT:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_IDLE:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_RUN:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_STUNNED:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_WAYPOINT:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_BUFF:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_CALTROP:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_COMPANION:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_DEMONHUNTER_FEMALE_FANOFKNIVES:SetState(new CDemonHunter_Female_Mez (_pEffect->GetSkillType() , vDir)); break;
	}
}

void CDemonHunter_Female::Renew()
{
	// Renew
	CPlayer::Renew();

	// Boots
	Item* pBoots = CItemMgr::GetInstance()->GetItemInEquip(12);
	if(pBoots == NULL || _tcscmp(pBoots->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Boots"));
	else
		m_pBufferCom->AddBuffer(pBoots->tszBufKey);

	// Helms
	Item* pHelms = CItemMgr::GetInstance()->GetItemInEquip(1);
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hair"));

	// Gloves
	Item* pGloves = CItemMgr::GetInstance()->GetItemInEquip(3);
	if(pGloves == NULL || _tcscmp(pGloves->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hands"));
	else
		m_pBufferCom->AddBuffer(pGloves->tszBufKey);

	// Pants
	Item* pPants = CItemMgr::GetInstance()->GetItemInEquip(10);
	if(pPants == NULL || _tcscmp(pPants->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Pants"));
	else
		m_pBufferCom->AddBuffer(pPants->tszBufKey);

	// ChestArmor
	Item* pChestArmor = CItemMgr::GetInstance()->GetItemInEquip(4);
	if(pChestArmor == NULL || _tcscmp(pChestArmor->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Upper"));
	else
		m_pBufferCom->AddBuffer(pChestArmor->tszBufKey);

	// DynamicMesh
	for(int i = 0; i < 5; ++i)
		m_pDynamicMesh[i] = (CDynamicMesh*)m_pBufferCom->m_BufferVec[i];

	// RightWeaponBone
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_RightWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");

	// LeftWeaponBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_LeftWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");

	// LeftShieldBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[2];
	m_LeftShieldBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_shield");

	// HeadBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[1];
	m_HeadBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Head");

	// RightShoulder
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[4];
	m_RightShoulderBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_shoulderPad");

	// Helm
	if(pHelms != NULL && _tcscmp(pHelms->tszBufKey, _T("")) != 0)
	{
		m_pHelm = new CEquipItem(NULL, OBJ_TYPE_STATIC, pHelms, &m_HeadBone);
		m_pLayer->AddObject(m_pHelm, LAYER_TYPE_ITEM);
		m_pHelm->Initialize();
	}

	// Shoulder
	Item* pShoulder = CItemMgr::GetInstance()->GetItemInEquip(0);
	if(pShoulder != NULL && _tcscmp(pShoulder->tszBufKey, _T("")) != 0)
	{
		m_pShoulder = new CEquipItem(NULL, OBJ_TYPE_STATIC, pShoulder, &m_RightShoulderBone);
		m_pLayer->AddObject(m_pShoulder, LAYER_TYPE_ITEM);
		m_pShoulder->Initialize();
	}

	// MainWeapon & SubWeapon
	Item* pMainWeapon = CItemMgr::GetInstance()->GetItemInEquip(9);
	Item* pSubWeapon = CItemMgr::GetInstance()->GetItemInEquip(11);

	// ID
	DWORD dwOneHand = WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CDemonHunter_Female_Idle);
	}
	// X / ¼Õ¼è³ú
	if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_HANDXBOW))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CDemonHunter_Female_CB1_Idle);
	}
	// X / È­»ìÅë
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_QUIVER))
	{
		SetState(new CDemonHunter_Female_Idle);
	}
	// X / ¹æÆÐ
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CDemonHunter_Female_Idle);
	}
	// ¼Õ¼è³ú / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_HANDXBOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_CB1_Idle);
	}
	// ¼Õ¼è³ú / ¼Õ¼è³ú
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_HANDXBOW) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_HANDXBOW))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CDemonHunter_Female_CB2_Idle);
	}
	// ¼Õ¼è³ú / È­»ìÅë
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_HANDXBOW) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_QUIVER))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_CB1_Idle);
	}
	// ¼Õ¼è³ú / ¹æÆÐ
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_HANDXBOW) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CDemonHunter_Female_CB1_Idle);
	}
	// ¼®±Ã / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_CROSSBOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_BigBow_Idle);
	}
	// ¼®±Ã / È­»ìÅë
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_CROSSBOW) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_QUIVER))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_BigBow_Idle);
	}
	// È° / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_BOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_Bow_Idle);
	}
	// È° / È­»ìÅë
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_BOW) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_QUIVER))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_Bow_Idle);
	}
	// ÇÑ¼Õ¹«±â / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_Idle);
	}
	// ÇÑ¼Õ¹«±â / ¹æÆÐ
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CDemonHunter_Female_Idle);
	}
	// ÇÑ¼Õ¹«±â / È­»ìÅë
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_QUIVER))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CDemonHunter_Female_Idle);
	}

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_HANDXBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(4, new CDemonHunterNearAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(5, new CDemonHunterNearAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(4, new CDemonHunterFarAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(5, new CDemonHunterFarAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
			SetSlot(4, new CDemonHunterMagicAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
			SetSlot(5, new CDemonHunterMagicAttackSlot);
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(4, new CDemonHunterPunchSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			SetSlot(5, new CDemonHunterPunchSlot);
	}
}

void CDemonHunter_Female::CreateAttack()
{
	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_DEMONHUNTER_FEMALE_ATTACK1:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_ATTACK2:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BACKFLIP:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_ATTACK:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BOLASLOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BUFF:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_HIT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_IDLE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_MULTISHOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_RAINOFARROW:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_RUN:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_STUNNED:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_ATTACK:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BOLASLOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BUFF:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_HIT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_IDLE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_MULTISHOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_RAINOFARROW:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_RUN:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BOW_STUNNED:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_BUFF:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CALTROP:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_ATTACK:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BOLASLOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BUFF:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_HIT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_IDLE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_MULTISHOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RAINOFARROW:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RUN:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB1_STUNNED:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_LEFT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_RIGHT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BOLASLOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BUFF:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_HIT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_IDLE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_MULTISHOT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_RAINOFARROW:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_RUN:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_CB2_STUNNED:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_COMPANION:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_DEATH:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_FANOFKNIVES:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_HIT:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_IDLE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_IMPALE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_RUN:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_STRAFE:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_STUNNED:
		break;
	case STATE_TYPE_DEMONHUNTER_FEMALE_WAYPOINT:
		break;
	}

	// CreateAttack
	CPlayer::CreateAttack();
}

void CDemonHunter_Female::SetSlot(int _iIndex, CSlot* _pSlot)
{
	// Clear
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

	// Weapon
	Item* pMainWeapon = CItemMgr::GetInstance()->GetItemInEquip(9);
	Item* pSubWeapon = CItemMgr::GetInstance()->GetItemInEquip(11);

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_HANDXBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_DEMONHUNTER_NEAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CDemonHunterNearAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_DEMONHUNTER_NEAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CDemonHunterNearAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_DEMONHUNTER_FAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CDemonHunterFarAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_DEMONHUNTER_FAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CDemonHunterFarAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CDemonHunterMagicAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CDemonHunterMagicAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_DEMONHUNTER_PUNCH)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CDemonHunterPunchSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_DEMONHUNTER_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_DEMONHUNTER_PUNCH)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CDemonHunterPunchSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
}

int CDemonHunter_Female::TotalStat1()
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

int CDemonHunter_Female::TotalStat2()
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

int CDemonHunter_Female::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}