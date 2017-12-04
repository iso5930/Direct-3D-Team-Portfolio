#include "StdAfx.h"
#include "Barbarian_Male.h"

CBarbarian_Male::CBarbarian_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
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
	for(int i = 0; i < 7; ++i)
	{
		m_pSlot[i] = NULL;

		switch(pAccount->eSlotID[i])
		{
		case SLOT_ID_BARBARIAN_OPEN:
			m_pSlot[i] = new CBarbarianOpenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_CLOSE:
			m_pSlot[i] = new CBarbarianCloseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_POTION:
			m_pSlot[i] = new CBarbarianPotionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_BASH:
			m_pSlot[i] = new CBarbarianBashSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_CLEAVE:
			m_pSlot[i] = new CBarbarianCleaveSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_FRENZY:
			m_pSlot[i] = new CBarbarianFrenzySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_WEAPON_THROW:
			m_pSlot[i] = new CBarbarianWeaponThrowSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_PUNCH:
			m_pSlot[i] = new CBarbarianPunchSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_NEAR_ATTACK:
			m_pSlot[i] = new CBarbarianNearAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_FAR_ATTACK:
			m_pSlot[i] = new CBarbarianFarAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_MAGIC_ATTACK:
			m_pSlot[i] = new CBarbarianMagicAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:
			m_pSlot[i] = new CBarbarianHammerOfTheAncientsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_REND:
			m_pSlot[i] = new CBarbarianRendSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_SEISMIC_SLAM:
			m_pSlot[i] = new CBarbarianSeismicSlamSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_WHIRLWIND:
			m_pSlot[i] = new CBarbarianWhirlwindSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:
			m_pSlot[i] = new CBarbarianAncientSpearSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_GROUND_STOMP:
			m_pSlot[i] = new CBarbarianGroundStompSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_LEAP:
			m_pSlot[i] = new CBarbarianLeapSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_SPRINT:
			m_pSlot[i] = new CBarbarianSprintSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_IGNORE_PAIN:
			m_pSlot[i] = new CBarbarianIgnorePainSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_OVERPOWER:
			m_pSlot[i] = new CBarbarianOverpowerSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_REVENGE:
			m_pSlot[i] = new CBarbarianRevengeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:
			m_pSlot[i] = new CBarbarianFuriousChargeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_THREATENING_SHOUT:
			m_pSlot[i] = new CBarbarianThreateningShoutSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_BATTLE_RAGE:
			m_pSlot[i] = new CBarbarianBattleRageSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_WAR_CRY:
			m_pSlot[i] = new CBarbarianWarCrySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_EARTHQUAKE:
			m_pSlot[i] = new CBarbarianEarthquakeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:
			m_pSlot[i] = new CBarbarianCallOfTheAncientsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:
			m_pSlot[i] = new CBarbarianWrathOfTheBerserkerSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		}
	}
}

CBarbarian_Male::~CBarbarian_Male()
{
	Release();
}

void CBarbarian_Male::Initialize()
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

int CBarbarian_Male::Update()
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

		m_stat.iRage += GetRageRecoveryOfSecond();
		if(m_stat.iRage > m_stat.iMaxRage)
			m_stat.iRage = m_stat.iMaxRage;
		else if(m_stat.iRage < 0)
			m_stat.iRage = 0;
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

void CBarbarian_Male::Render()
{
	CPlayer::Render();
}

void CBarbarian_Male::Release()
{
}

int CBarbarian_Male::Attack()
{
	// Attack
	CPlayer::Attack();

	// Strength
	int iStrength = GetStrength();

	// Att
	int iAtt = GetAtt() + iStrength;

	// Strength
	iAtt = int(iAtt * (1.0f + iStrength / 100.0f));

	float fRand = (rand() % 1000) / 1000.0f;
	if(fRand < GetCriticalProbability())
		iAtt = int(iAtt * (1.0f + GetCriticalDamage()));

	fRand = ((rand() % 400) - 200) / 1000.0f;
	return int(iAtt * (1.0f + fRand));
}

void CBarbarian_Male::LevelUp()
{
	// Stat
	m_stat.iStrength += 3;
	m_stat.iAgility += 1;
	m_stat.iIntelligence += 1;
	m_stat.iVitality += 2;

	// LevelUp
	CPlayer::LevelUp();

	// Slot
	if(m_stat.iLevel == 4)
	{
		delete m_pSlot[0];
		m_pSlot[0] = new CBarbarianOpenSlot;
		m_pSlot[0]->SetOwner(this);
	}
	else if(m_stat.iLevel == 9)
	{
		delete m_pSlot[1];
		m_pSlot[1] = new CBarbarianOpenSlot;
		m_pSlot[1]->SetOwner(this);
	}
	else if(m_stat.iLevel == 14)
	{
		delete m_pSlot[2];
		m_pSlot[2] = new CBarbarianOpenSlot;
		m_pSlot[2]->SetOwner(this);
	}
	else if(m_stat.iLevel == 19)
	{
		delete m_pSlot[3];
		m_pSlot[3] = new CBarbarianOpenSlot;
		m_pSlot[3]->SetOwner(this);
	}

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SKILL);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_PRIMARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_SECONDARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_MIGHT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_TACTICS);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_BARBARIAN_RAGE);
}

void CBarbarian_Male::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CBarbarian_Male::Damage(CEffect* _pEffect)
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
	case 	STATE_TYPE_BARBARIAN_MALE_1HS_ATTACK: SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_BUFF: SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_CLEAVE01:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_CLEAVE02:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_FOOTSTOMP:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_HIRLWIND:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_HIRLWIND_END:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_HIT:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_IDLE:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_END:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_LOOP:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_LEAPATTACK_AIR:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_LEAPATTACK_END:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_PARRY:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_REVENGE:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HS_RUN:SetState(new CBarbarian_Male_1HS_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_BARBARIAN_MALE_1HT_ATTACK:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_BUFF:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_CLEAVE01:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_CLEAVE02:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_FOOTSTOMP:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND_END:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_HIT:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_IDLE:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_KNOCKBACK_END:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_KNOCKBACK_LOOP:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_LEAPATTACK_AIR:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_LEAPATTACK_END:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_PARRY:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_REVENGE:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_1HT_RUN:SetState(new CBarbarian_Male_1HT_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_BARBARIAN_MALE_2HS_ATTACK:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_BUFF:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_CLEAVE01:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_CLEAVE02:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_FOOTSTOMP:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_FURIOUS_CHARGE_END:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_FURIOUS_CHARGE_LOOP:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_HIRLWIND:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_HIRLWIND_END:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_HIT:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_IDLE:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_LEAPATTACK_AIR:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_LEAPATTACK_END:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_PARRY:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_REVENGE:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HS_RUN:SetState(new CBarbarian_Male_2HS_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_BARBARIAN_MALE_2HT_ATTACK:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_BUFF:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_CLEAVE01:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_CLEAVE02:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_FOOTSTOMP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_FURIOUS_CHARGE_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_FURIOUS_CHARGE_LOOP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_HIRLWIND:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_HIRLWIND_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_HIT:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_IDLE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_LEAPATTACK_AIR:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_LEAPATTACK_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_PARRY:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_REVENGE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_2HT_RUN:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_BARBARIAN_MALE_STF_ATTACK:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_BUFF:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_CLEAVE01:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_CLEAVE02:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_FOOTSTOMP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_FURIOUS_CHARGE_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_FURIOUS_CHARGE_LOOP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_HIRLWIND:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_HIRLWIND_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_HIT:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_IDLE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_LEAPATTACK_AIR:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_LEAPATTACK_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_PARRY:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_REVENGE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_STF_RUN:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;

	case	STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_L:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_R:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_BUFF:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_CLEAVE01:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_CLEAVE02:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_FOOTSTOMP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_FURIOUS_CHARGE_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_FURIOUS_CHARGE_LOOP:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_HIT:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_IDLE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_LEAPATTACK_AIR:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_LEAPATTACK_END:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_PARRY:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_REVENGE:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	case	STATE_TYPE_BARBARIAN_MALE_DW_RUN:SetState(new CBarbarian_Male_2HT_Mez (_pEffect->GetSkillType() , vDir)); break;
	}


}

void CBarbarian_Male::Renew()
{
	// Renew
	CPlayer::Renew();

	// Boots
	Item* pBoots = CItemMgr::GetInstance()->GetItemInEquip(12);
	if(pBoots == NULL || _tcscmp(pBoots->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Barbarian_Male_Base_Boots"));
	else
		m_pBufferCom->AddBuffer(pBoots->tszBufKey);

	// Helms
	Item* pHelms = CItemMgr::GetInstance()->GetItemInEquip(1);
	m_pBufferCom->AddBuffer(_T("Barbarian_Male_Base_Hair"));

	// Gloves
	Item* pGloves = CItemMgr::GetInstance()->GetItemInEquip(3);
	if(pGloves == NULL || _tcscmp(pGloves->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Barbarian_Male_Base_Hands"));
	else
		m_pBufferCom->AddBuffer(pGloves->tszBufKey);

	// Pants
	Item* pPants = CItemMgr::GetInstance()->GetItemInEquip(10);
	if(pPants == NULL || _tcscmp(pPants->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Barbarian_Male_Base_Pants"));
	else
		m_pBufferCom->AddBuffer(pPants->tszBufKey);

	// ChestArmor
	Item* pChestArmor = CItemMgr::GetInstance()->GetItemInEquip(4);
	if(pChestArmor == NULL || _tcscmp(pChestArmor->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Barbarian_Male_Base_Upper"));
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
	DWORD dwOneHandS = WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SWORD;
	DWORD dwOneHandT = WEAPON_ID_SPEAR;
	DWORD dwTwoHandS = WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwTwoHandT = WEAPON_ID_POLEARM;
	DWORD dwBigOneHand = WEAPON_ID_MIGHTY1H;
	DWORD dwBigTwoHand = WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CBarbarian_Male_1HS_Idle);
	}
	// X / 방패
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_1HS_Idle);
	}
	// 한손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_1HS_Idle);
	}
	// X / 한손스윙무기
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & dwOneHandS))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_1HS_Idle);
	}
	// 한손스윙무기 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandS) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_1HS_Idle);
	}
	// 한손찌르기무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandT) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_1HT_Idle);
	}
	// X / 한손찌르기무기
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & dwOneHandT))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_1HT_Idle);
	}
	// 한손찌르기무기 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandT) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_1HT_Idle);
	}
	// 한손거대무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwBigOneHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_2HS_Idle);
	}
	// X / 한손거대무기
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & dwBigOneHand))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_2HS_Idle);
	}
	// 한손거대무기 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwBigOneHand) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_2HS_Idle);
	}
	// 한손무기 / 한손무기
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & (dwOneHandS | dwOneHandT | dwBigOneHand)) && pSubWeapon != NULL && (pSubWeapon->dwItemID & (dwOneHandS | dwOneHandT | dwBigOneHand)))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CBarbarian_Male_DW_Idle);
	}
	// 양손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_2HS_Idle);
	}
	// 양손찌르기무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandT) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_2HT_Idle);
	}
	// 양손거대무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwBigTwoHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CBarbarian_Male_STF_Idle);
	}

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_HANDXBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(4, new CBarbarianNearAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(5, new CBarbarianNearAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(4, new CBarbarianFarAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(5, new CBarbarianFarAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK)
			SetSlot(4, new CBarbarianMagicAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK)
			SetSlot(5, new CBarbarianMagicAttackSlot);
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(4, new CBarbarianPunchSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			SetSlot(5, new CBarbarianPunchSlot);
	}
}

void CBarbarian_Male::CreateAttack()
{
	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_BARBARIAN_MALE_1HS_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_CLEAVE01:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_CLEAVE02:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_FURIOUS_CHARGE_LOOP:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_HIRLWIND:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_LEAPATTACK_END:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_REVENGE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, -50.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HS_RUN:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_ATTACK:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_CLEAVE01:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_CLEAVE02:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_FURIOUS_CHARGE_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_LEAPATTACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_REVENGE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_1HT_RUN:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_ATTACK:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_CLEAVE01:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_CLEAVE02:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_FURIOUS_CHARGE_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_HIRLWIND:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_LEAPATTACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_REVENGE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HS_RUN:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_ATTACK:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_CLEAVE01:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_CLEAVE02:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_FURIOUS_CHARGE_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_HIRLWIND:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_LEAPATTACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_REVENGE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_2HT_RUN:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_ATTACK:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_CLEAVE01:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_CLEAVE02:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_FURIOUS_CHARGE_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_HIRLWIND:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_LEAPATTACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_REVENGE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_STF_RUN:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_L:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_R:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_BUFF:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_CLEAVE01:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_CLEAVE02:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_FOOTSTOMP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_FURIOUS_CHARGE_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_FURIOUS_CHARGE_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_HIT:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_IDLE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_KNOCKBACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_KNOCKBACK_LOOP:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_LEAPATTACK_AIR:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_LEAPATTACK_END:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_PARRY:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_REVENGE:
		break;
	case STATE_TYPE_BARBARIAN_MALE_DW_RUN:
		break;
	}

	// CreateAttack
	CPlayer::CreateAttack();
}

void CBarbarian_Male::SetSlot(int _iIndex, CSlot* _pSlot)
{
	// Clear
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
		{
			if(m_pSlot[i]->GetSlotID() == _pSlot->GetSlotID())
			{
				delete m_pSlot[i];
				m_pSlot[i] = new CBarbarianOpenSlot;
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
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_BARBARIAN_NEAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CBarbarianNearAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_BARBARIAN_NEAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CBarbarianNearAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_BARBARIAN_FAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CBarbarianFarAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_BARBARIAN_FAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CBarbarianFarAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CBarbarianMagicAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_BARBARIAN_MAGIC_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CBarbarianMagicAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_BARBARIAN_PUNCH)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CBarbarianPunchSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_BARBARIAN_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_BARBARIAN_PUNCH)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CBarbarianPunchSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
}

int CBarbarian_Male::TotalStat1()
{
	// Strength
	int iStrength = GetStrength();

	// Attack
	int iAttack = GetAtt() + iStrength;

	// Strength
	iAttack = int(iAttack * (1.0f + iStrength / 100.0f));

	// CriticalAttack
	int iCriticalAttack = int(iAttack * GetCriticalDamage());
	iCriticalAttack = int(iCriticalAttack * GetCriticalProbability());

	// Coef
	float fCoef1 = GetReducedCooldownTime();
	float fCoef2 = GetReducedRageConsumption();
	float fCoef3 = GetRageRecoveryOfSecond() / 100.0f;

	// TotalAttack
	int iTotalAttack = iAttack + iCriticalAttack;
	iTotalAttack = int(iTotalAttack * (1.0f + fCoef1 + fCoef2 + fCoef3));

	return iTotalAttack;
}

int CBarbarian_Male::TotalStat2()
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

int CBarbarian_Male::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}