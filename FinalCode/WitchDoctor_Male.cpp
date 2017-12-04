#include "StdAfx.h"
#include "WitchDoctor_Male.h"

CWitchDoctor_Male::CWitchDoctor_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
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
		case SLOT_ID_WITCHDOCTOR_OPEN:
			m_pSlot[i] = new CWitchDoctorOpenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_CLOSE:
			m_pSlot[i] = new CWitchDoctorCloseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_POTION:
			m_pSlot[i] = new CWitchDoctorPotionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_POISON_DART:
			m_pSlot[i] = new CWitchDoctorPoisonDartSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:
			m_pSlot[i] = new CWitchDoctorCorpseSpidersSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:
			m_pSlot[i] = new CWitchDoctorPlagueOfToadsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_FIREBOMB:
			m_pSlot[i] = new CWitchDoctorFirebombSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_PUNCH:
			m_pSlot[i] = new CWitchDoctorPunchSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:
			m_pSlot[i] = new CWitchDoctorNearAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:
			m_pSlot[i] = new CWitchDoctorFarAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:
			m_pSlot[i] = new CWitchDoctorMagicAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:
			m_pSlot[i] = new CWitchDoctorGraspOfTheDeadSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_FIREBATS:
			m_pSlot[i] = new CWitchDoctorFirebatsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_HAUNT:
			m_pSlot[i] = new CWitchDoctorHauntSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:
			m_pSlot[i] = new CWitchDoctorLocustSwarmSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:
			m_pSlot[i] = new CWitchDoctorSummonZombieDogsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_HORRIFY:
			m_pSlot[i] = new CWitchDoctorHorrifySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:
			m_pSlot[i] = new CWitchDoctorSpiritWalkSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_HEX:
			m_pSlot[i] = new CWitchDoctorHexSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:
			m_pSlot[i] = new CWitchDoctorSoulHarvestSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_SACRIFICE:
			m_pSlot[i] = new CWitchDoctorSacrificeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:
			m_pSlot[i] = new CWitchDoctorMassConfusionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:
			m_pSlot[i] = new CWitchDoctorZombieChargerSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:
			m_pSlot[i] = new CWitchDoctorSpiritBarrageSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:
			m_pSlot[i] = new CWitchDoctorAcidCloudSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:
			m_pSlot[i] = new CWitchDoctorWallOfDeathSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_GARGANTUAN:
			m_pSlot[i] = new CWitchDoctorGargantuanSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:
			m_pSlot[i] = new CWitchDoctorBigBadVoodooSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:
			m_pSlot[i] = new CWitchDoctorFetishArmySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		}
	}
}

CWitchDoctor_Male::~CWitchDoctor_Male()
{
	Release();
}

void CWitchDoctor_Male::Initialize()
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

int CWitchDoctor_Male::Update()
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

		m_stat.iMana += GetManaRecoveryOfSecond();
		if(m_stat.iMana > m_stat.iMaxMana)
			m_stat.iMana = m_stat.iMaxMana;
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

void CWitchDoctor_Male::Render()
{
	CPlayer::Render();
}

void CWitchDoctor_Male::Release()
{
}

int CWitchDoctor_Male::Attack()
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

void CWitchDoctor_Male::LevelUp()
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
		m_pSlot[0] = new CWitchDoctorOpenSlot;
		m_pSlot[0]->SetOwner(this);
	}
	else if(m_stat.iLevel == 9)
	{
		delete m_pSlot[1];
		m_pSlot[1] = new CWitchDoctorOpenSlot;
		m_pSlot[1]->SetOwner(this);
	}
	else if(m_stat.iLevel == 14)
	{
		delete m_pSlot[2];
		m_pSlot[2] = new CWitchDoctorOpenSlot;
		m_pSlot[2]->SetOwner(this);
	}
	else if(m_stat.iLevel == 19)
	{
		delete m_pSlot[3];
		m_pSlot[3] = new CWitchDoctorOpenSlot;
		m_pSlot[3]->SetOwner(this);
	}

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SKILL);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_PRIMARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_SECONDARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_TERROR);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_DECAY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_WITCHDOCTOR_VOODOO);
}

void CWitchDoctor_Male::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CWitchDoctor_Male::Damage(CEffect* _pEffect)
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
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FASTCAST:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FIREBALL:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_HORRIFY:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_BLOW:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_CHANNEL:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FLAYERARMY:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SUMMON:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_ATTACK:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_HIT:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_STUNNED:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_RUN:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HS_IDLE:
		SetState(new CWitchDoctor_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FASTCAST:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FIREBALL:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_HORRIFY:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_BLOW:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_CHANNEL:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FLAYERARMY:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SUMMON:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_ATTACK:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_HIT:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_STUNNED:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_RUN:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_1HT_IDLE:
		SetState(new CWitchDoctor_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FASTCAST:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FIREBALL:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_HORRIFY:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_BLOW:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_CHANNEL:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FLAYERARMY:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SUMMON:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_ATTACK:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_HIT:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_KNOCKBACK:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_KNOCKBACK_END:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_STUNNED:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_RUN:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_IDLE:
		SetState(new CWitchDoctor_Male_Mojo_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FASTCAST:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FIREBALL:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_HORRIFY:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_BLOW:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_CHANNEL:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FLAYERARMY:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SUMMON:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_ATTACK:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_HIT:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_STUNNED:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_RUN:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_IDLE:
		SetState(new CWitchDoctor_Male_Mojo_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FASTCAST:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FIREBALL:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_HORRIFY:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_BLOW:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_CHANNEL:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FLAYERARMY:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SUMMON:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_ATTACK:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_HIT:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_STUNNED:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_RUN:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HS_IDLE:
		SetState(new CWitchDoctor_Male_2HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FASTCAST:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FIREBALL:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_HORRIFY:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_BLOW:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_CHANNEL:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FLAYERARMY:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SUMMON:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_ATTACK:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_HIT:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_STUNNED:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_RUN:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_2HT_IDLE:
		SetState(new CWitchDoctor_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_FASTCAST:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_FIREBALL:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_HORRIFY:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_BLOW:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_CHANNEL:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_FLAYERARMY:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_ATTACK:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_HIT:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_STUNNED:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_RUN:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_STF_IDLE:
		SetState(new CWitchDoctor_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FASTCAST:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FIREBALL:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_HORRIFY:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_BLOW:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_CHANNEL:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FLAYERARMY:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SUMMON:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_ATTACK:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_HIT:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_KNOCKBACK:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_KNOCKBACK_END:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_STUNNED:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_RUN:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_BOW_IDLE:
		SetState(new CWitchDoctor_Male_Bow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ACIDCLOUD_BARF:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FASTCAST:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FIREBALL:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_HORRIFY:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SOUL_HARVEST:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_BLOW:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_CHANNEL:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FLAYERARMY:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SUMMON:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SUMMON_CHARGER:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ATTACK:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_HIT:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_STUNNED:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_RUN:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_IDLE:
		SetState(new CWitchDoctor_Male_XBow_Mez(_pEffect->GetSkillType() , vDir));
		break;
	}


}

void CWitchDoctor_Male::Renew()
{
	// Renew
	CPlayer::Renew();

	// Boots
	Item* pBoots = CItemMgr::GetInstance()->GetItemInEquip(12);
	if(pBoots == NULL || _tcscmp(pBoots->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("WitchDoctor_Male_Base_Boots"));
	else
		m_pBufferCom->AddBuffer(pBoots->tszBufKey);

	// Helms
	Item* pHelms = CItemMgr::GetInstance()->GetItemInEquip(1);
	m_pBufferCom->AddBuffer(_T("WitchDoctor_Male_Base_Hair"));

	// Gloves
	Item* pGloves = CItemMgr::GetInstance()->GetItemInEquip(3);
	if(pGloves == NULL || _tcscmp(pGloves->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("WitchDoctor_Male_Base_Hands"));
	else
		m_pBufferCom->AddBuffer(pGloves->tszBufKey);

	// Pants
	Item* pPants = CItemMgr::GetInstance()->GetItemInEquip(10);
	if(pPants == NULL || _tcscmp(pPants->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("WitchDoctor_Male_Base_Pants"));
	else
		m_pBufferCom->AddBuffer(pPants->tszBufKey);

	// ChestArmor
	Item* pChestArmor = CItemMgr::GetInstance()->GetItemInEquip(4);
	if(pChestArmor == NULL || _tcscmp(pChestArmor->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("WitchDoctor_Male_Base_Upper"));
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
	DWORD dwOneHandT = WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_SPEAR;
	DWORD dwTwoHandS = WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwTwoHandT = WEAPON_ID_POLEARM;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CWitchDoctor_Male_1HS_Idle);
	}
	// X / 방패
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWitchDoctor_Male_1HS_Idle);
	}
	// X / 액막이
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_MOJO))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWitchDoctor_Male_Mojo_1HS_Idle);
	}
	// 한손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_1HS_Idle);
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

		SetState(new CWitchDoctor_Male_1HS_Idle);
	}
	// 한손스윙무기 / 액막이
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandS) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_MOJO))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWitchDoctor_Male_Mojo_1HS_Idle);
	}
	// 한손찌르기무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandT) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_1HT_Idle);
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

		SetState(new CWitchDoctor_Male_1HT_Idle);
	}
	// 한손찌르기무기 / 액막이
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandT) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_MOJO))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWitchDoctor_Male_Mojo_1HT_Idle);
	}
	// 양손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_2HS_Idle);
	}
	// 양손찌르기무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandT) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_2HT_Idle);
	}
	// 양손거대무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_STAFF) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_STF_Idle);
	}
	// 석궁 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_CROSSBOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_XBow_Idle);
	}
	// 활 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_BOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pMainWeapon->Initialize();

		SetState(new CWitchDoctor_Male_Bow_Idle);
	}

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(4, new CWitchDoctorNearAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(5, new CWitchDoctorNearAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(4, new CWitchDoctorFarAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(5, new CWitchDoctorFarAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
			SetSlot(4, new CWitchDoctorMagicAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
			SetSlot(5, new CWitchDoctorMagicAttackSlot);
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(4, new CWitchDoctorPunchSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			SetSlot(5, new CWitchDoctorPunchSlot);
	}
}

void CWitchDoctor_Male::CreateAttack()
{
	switch(m_pState->GetStateType())
	{
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HS_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_1HT_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HS_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_2HT_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_STF_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_BOW_IDLE:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ACIDCLOUD_BARF:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FASTCAST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FIREBALL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_HORRIFY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SOUL_HARVEST:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_BLOW:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_CHANNEL:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FLAYERARMY:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SUMMON:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_SUMMON_CHARGER:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ATTACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_HIT:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_KNOCKBACK:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_KNOCKBACK_END:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_STUNNED:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_RUN:
			break;
		case STATE_TYPE_WITCHDOCTOR_MALE_XBOW_IDLE:
			break;
	}

	// CreateAttack
	CPlayer::CreateAttack();
}

void CWitchDoctor_Male::SetSlot(int _iIndex, CSlot* _pSlot)
{
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
		{
			if(m_pSlot[i]->GetSlotID() == _pSlot->GetSlotID())
			{
				delete m_pSlot[i];
				m_pSlot[i] = new CWitchDoctorOpenSlot;
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
	DWORD dwFarAttack = WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WITCHDOCTOR_NEAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWitchDoctorNearAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WITCHDOCTOR_NEAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWitchDoctorNearAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWitchDoctorFarAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWitchDoctorFarAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWitchDoctorMagicAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWitchDoctorMagicAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WITCHDOCTOR_PUNCH)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWitchDoctorPunchSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WITCHDOCTOR_PUNCH)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWitchDoctorPunchSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
}

int CWitchDoctor_Male::TotalStat1()
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
	float fCoef2 = GetReducedManaConsumption();
	float fCoef3 = GetManaRecoveryOfSecond() / 750.0f;

	// TotalAttack
	int iTotalAttack = iAttack + iCriticalAttack;
	iTotalAttack = int(iTotalAttack * (1.0f + fCoef1 + fCoef2 + fCoef3));

	return iTotalAttack;
}

int CWitchDoctor_Male::TotalStat2()
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

int CWitchDoctor_Male::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}