#include "StdAfx.h"
#include "Monk_Male.h"

CMonk_Male::CMonk_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
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
		case SLOT_ID_MONK_OPEN:
			m_pSlot[i] = new CMonkOpenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_CLOSE:
			m_pSlot[i] = new CMonkCloseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_POTION:
			m_pSlot[i] = new CMonkPotionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_FISTS_OF_THUNDER:
			m_pSlot[i] = new CMonkFistsOfThunderSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_DEADLY_REACH:
			m_pSlot[i] = new CMonkDeadlyReachSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_CRIPPLING_WAVE:
			m_pSlot[i] = new CMonkCripplingWaveSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS:
			m_pSlot[i] = new CMonkWayOfTheHundredFistsSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_PUNCH:
			m_pSlot[i] = new CMonkPunchSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_NEAR_ATTACK:
			m_pSlot[i] = new CMonkNearAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_FAR_ATTACK:
			m_pSlot[i] = new CMonkFarAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MAGIC_ATTACK:
			m_pSlot[i] = new CMonkMagicAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_LASHING_TAIL_KICK:
			m_pSlot[i] = new CMonkLashingTailKickSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_TEMPEST_RUSH:
			m_pSlot[i] = new CMonkTempestRushSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_WAVE_OF_LIGHT:
			m_pSlot[i] = new CMonkWaveOfLightSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_BLINDING_FLASH:
			m_pSlot[i] = new CMonkBlindingFlashSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_BREATH_OF_HEAVEN:
			m_pSlot[i] = new CMonkBreathOfHeavenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_SERENITY:
			m_pSlot[i] = new CMonkSerenitySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_INNER_SANCTUARY:
			m_pSlot[i] = new CMonkInnerSanctuarySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_DASHING_STRIKE:
			m_pSlot[i] = new CMonkDashingStrikeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_EXPLODING_PALM:
			m_pSlot[i] = new CMonkExplodingPalmSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_SWEEPING_WIND:
			m_pSlot[i] = new CMonkSweepingWindSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_CYCLONE_STRIKE:
			m_pSlot[i] = new CMonkCycloneStrikeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_SEVEN_SIDED_STRIKE:
			m_pSlot[i] = new CMonkSevenSidedStrikeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MYSTIC_ALLY:
			m_pSlot[i] = new CMonkMysticAllySlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MANTRA_OF_SALVATION:
			m_pSlot[i] = new CMonkMantraOfSalvationSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION:
			m_pSlot[i] = new CMonkMantraOfRetributionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MANTRA_OF_HEALING:
			m_pSlot[i] = new CMonkMantraOfHealingSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_MONK_MANTRA_OF_CONVICTION:
			m_pSlot[i] = new CMonkMantraOfConvictionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		}
	}
}

CMonk_Male::~CMonk_Male()
{
	Release();
}

void CMonk_Male::Initialize()
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
	m_LeftShieldBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_Shield");

	// HeadBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[1];
	m_HeadBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Head");

	// RightShoulder
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[4];
	m_RightShoulderBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_shoulder");
}

int CMonk_Male::Update()
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

		m_stat.iEffort += GetEffortRecoveryOfSecond();
		if(m_stat.iEffort > m_stat.iMaxEffort)
			m_stat.iEffort = m_stat.iMaxEffort;
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

void CMonk_Male::Render()
{
	CPlayer::Render();
}

void CMonk_Male::Release()
{
}

int CMonk_Male::Attack()
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

void CMonk_Male::LevelUp()
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
		m_pSlot[0] = new CMonkOpenSlot;
		m_pSlot[0]->SetOwner(this);
	}
	else if(m_stat.iLevel == 9)
	{
		delete m_pSlot[1];
		m_pSlot[1] = new CMonkOpenSlot;
		m_pSlot[1]->SetOwner(this);
	}
	else if(m_stat.iLevel == 14)
	{
		delete m_pSlot[2];
		m_pSlot[2] = new CMonkOpenSlot;
		m_pSlot[2]->SetOwner(this);
	}
	else if(m_stat.iLevel == 19)
	{
		delete m_pSlot[3];
		m_pSlot[3] = new CMonkOpenSlot;
		m_pSlot[3]->SetOwner(this);
	}

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SKILL);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_PRIMARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_SECONDARY);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_DEFENSIVE);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_TECHNIQUES);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_FOCUS);
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_MONK_MANTRAS);
}

void CMonk_Male::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CMonk_Male::Damage(CEffect* _pEffect)
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

	switch (m_pState->GetStateType())
	{	
	case STATE_TYPE_MONK_MALE_1HS_ATTACK:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_BUFF:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_CELESTIALWHEEL:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_01:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_02:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_03_1:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_03_2:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_HIT:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_HOBBLE_RUN:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_RUN:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_IDLE:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LASHINGTAIL:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LETGAL_DECOY:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_01:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_02:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_03:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_01:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_02:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_03:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_01:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_02:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_03:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_STUNNED:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_WAVEOFLIGHT:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_ATTACK:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_BUFF:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_CELESTIALWHEEL:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_01:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_02:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_03_1:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_03_2:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;		
	case STATE_TYPE_MONK_MALE_1HT_HIT:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;		
	case STATE_TYPE_MONK_MALE_1HT_HOBBLE_RUN:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_IDLE:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_RUN:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_KNOCKBACK:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_KNOCKBACK_END:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LASHINGTAIL:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LETGAL_DECOY:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_01:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_02:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_03:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_01:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_02:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_03:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_01:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_02:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_03:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_STUNNED:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_WAVEOFLIGHT:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_ATTACK:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_BUFF:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_CELESTIALWHEEL:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_01:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_02:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_03_1:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_03_2:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_HIT:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_HOBBLE_RUN:
		SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_RUN:
		SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_IDLE:
		SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LASHINGTAIL:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LETGAL_DECOY:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_01:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_02:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_03:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_01:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_02:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_03:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_01:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_02:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_03:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_STUNNED:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_WAVEOFLIGHT:SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_ATTACK:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_BUFF:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_CELESTIALWHEEL:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_01:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_02:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_03_1:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_03_2:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_HIT:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_HOBBLE_RUN:
		SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_RUN:
		SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_IDLE:
		SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LASHINGTAIL:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LETGAL_DECOY:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_01:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_02:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_03:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_01:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_02:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_03:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_01:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_02:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_03:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_STUNNED:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_WAVEOFLIGHT:SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_ATTACK_R:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_ATTACK_L:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_BUFF:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_CELESTIALWHEEL:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_03_1:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_03_2:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_HIT:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_HOBBLE_RUN:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RUN:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_IDLE:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LASHINGTAIL:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LETGAL_DECOY:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_STUNNED:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_WAVEOFLIGHT:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_ATTACK_R:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_ATTACK_L:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_BUFF:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_CELESTIALWHEEL:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_03_1:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_03_2:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_HIT:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_HOBBLE_RUN:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RUN:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_IDLE:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));	
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LASHINGTAIL:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LETGAL_DECOY:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_01:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_02:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_03:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_STUNNED:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_WAVEOFLIGHT:SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_ATTACK_R:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_ATTACK_L:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_BUFF:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_CELESTIALWHEEL:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_01:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_02:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_03_1:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_03_2:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_HIT:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_HOBBLE_RUN:
		SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RUN:
		SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_IDLE:
		SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_KNOCKBACK:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_KNOCKBACK_END:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LASHINGTAIL:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LETGAL_DECOY:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_01:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_02:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_03:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_01:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_02:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_03:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_01:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_02:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_03:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_STUNNED:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_WAVEOFLIGHT:SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HS_DASHINGSTRIKE:
		SetState(new CMonk_Male_1HS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DASHINGSTRIKE:
		SetState(new CMonk_Male_1HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DASHINGSTRIKE:
		SetState(new CMonk_Male_2HT_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_STF_DASHINGSTRIKE:
		SetState(new CMonk_Male_STF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DASHINGSTRIKE:
		SetState(new CMonk_Male_DW_FF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DASHINGSTRIKE:
		SetState(new CMonk_Male_DW_SF_Mez(_pEffect->GetSkillType() , vDir));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DASHINGSTRIKE:
		SetState(new CMonk_Male_DW_SS_Mez(_pEffect->GetSkillType() , vDir));
		break;
	}
	
}

void CMonk_Male::Renew()
{
	// Renew
	CPlayer::Renew();

	// Boots
	Item* pBoots = CItemMgr::GetInstance()->GetItemInEquip(12);
	if(pBoots == NULL || _tcscmp(pBoots->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Monk_Male_Base_Boots"));
	else
		m_pBufferCom->AddBuffer(pBoots->tszBufKey);

	// Helms
	Item* pHelms = CItemMgr::GetInstance()->GetItemInEquip(1);
	m_pBufferCom->AddBuffer(_T("Monk_Male_Base_Hair"));

	// Gloves
	Item* pGloves = CItemMgr::GetInstance()->GetItemInEquip(3);
	if(pGloves == NULL || _tcscmp(pGloves->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Monk_Male_Base_Hands"));
	else
		m_pBufferCom->AddBuffer(pGloves->tszBufKey);

	// Pants
	Item* pPants = CItemMgr::GetInstance()->GetItemInEquip(10);
	if(pPants == NULL || _tcscmp(pPants->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Monk_Male_Base_Pants"));
	else
		m_pBufferCom->AddBuffer(pPants->tszBufKey);

	// ChestArmor
	Item* pChestArmor = CItemMgr::GetInstance()->GetItemInEquip(4);
	if(pChestArmor == NULL || _tcscmp(pChestArmor->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Monk_Male_Base_Upper"));
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
	m_LeftShieldBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_Shield");

	// HeadBone
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[1];
	m_HeadBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Head");

	// RightShoulder
	pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[4];
	m_RightShoulderBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_shoulder");

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

	//////////////////////////////////////////////////////////////////////////

	// ID
	DWORD dwOneHandS = WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SWORD | WEAPON_ID_SPEAR;
	DWORD dwTwoHandS = WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwTwoHandT = WEAPON_ID_POLEARM;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CMonk_Male_1HS_Idle);
	}
	// X / 방패
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_1HS_Idle);
	}
	// 한손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CMonk_Male_1HS_Idle);
	}
	// X / 한손스윙무기
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & dwOneHandS))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_1HS_Idle);
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

		SetState(new CMonk_Male_1HS_Idle);
	}
	// 주먹무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_FIST) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CMonk_Male_1HT_Idle);
	}
	// X / 주먹무기
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_FIST))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_1HT_Idle);
	}
	// 주먹무기 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_FIST) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_1HT_Idle);
	}
	
	// 한손무기 / 한손무기
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & (dwOneHandS)) && pSubWeapon != NULL && (pSubWeapon->dwItemID & (dwOneHandS)))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_DW_SS_Idle);
	}
	// 한손무기 / 주먹무기
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & (dwOneHandS)) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_FIST))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_DW_SF_Idle);
	}
	// 주먹무기 / 한손무기
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_FIST) && pSubWeapon != NULL && (pSubWeapon->dwItemID & (dwOneHandS )))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_DW_SF_Idle);
	}
	// 주먹무기 / 주먹무기
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_FIST) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_FIST))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CMonk_Male_DW_FF_Idle);
	}
	// 양손스윙무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandS) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CMonk_Male_STF_Idle);
	}
	// 양손찌르기무기 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHandT) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CMonk_Male_2HT_Idle);
	}

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(4, new CMonkNearAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(5, new CMonkNearAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(4, new CMonkFarAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(5, new CMonkFarAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK)
			SetSlot(4, new CMonkMagicAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK)
			SetSlot(5, new CMonkMagicAttackSlot);
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(4, new CMonkPunchSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
			SetSlot(5, new CMonkPunchSlot);
	}
}

void CMonk_Male::CreateAttack()
{
	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_MONK_MALE_1HS_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 30.0f));
		break;
	case STATE_TYPE_MONK_MALE_1HS_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_1HS_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_1HS_HIT:
		break;
	case STATE_TYPE_MONK_MALE_1HS_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_1HS_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_1HS_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_1HS_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_1HS_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_1HS_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_1HS_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_1HT_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_1HT_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_1HT_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_1HT_HIT:
		break;
	case STATE_TYPE_MONK_MALE_1HT_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_1HT_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_1HT_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_1HT_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_1HT_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_1HT_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_1HT_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_2HT_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_2HT_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_2HT_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_2HT_HIT:
		break;
	case STATE_TYPE_MONK_MALE_2HT_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_2HT_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_2HT_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_2HT_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_2HT_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_2HT_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_2HT_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_STF_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_STF_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_STF_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_STF_HIT:
		break;
	case STATE_TYPE_MONK_MALE_STF_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_STF_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_STF_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_STF_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_STF_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_STF_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_STF_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_STF_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_STF_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_STF_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_ATTACK_R:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_ATTACK_L:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_HIT:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_ATTACK_R:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_ATTACK_L:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_HIT:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_ATTACK_R:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_ATTACK_L:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_BUFF:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_CELESTIALWHEEL:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_03_1:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_03_2:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_HIT:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_HOBBLE_RUN:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_IDLE:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_KNOCKBACK:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_KNOCKBACK_END:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LASHINGTAIL:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LETGAL_DECOY:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_01:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_02:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_03:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_STUNNED:
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_WAVEOFLIGHT:
		break;
	case STATE_TYPE_MONK_MALE_1HS_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_1HT_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_2HT_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_STF_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_FF_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SF_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;
	case STATE_TYPE_MONK_MALE_DW_SS_DASHINGSTRIKE:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f));
		break;

	}

	// CreateAttack
	CPlayer::CreateAttack();
}

void CMonk_Male::SetSlot(int _iIndex, CSlot* _pSlot)
{
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
		{
			if(m_pSlot[i]->GetSlotID() == _pSlot->GetSlotID())
			{
				delete m_pSlot[i];
				m_pSlot[i] = new CMonkOpenSlot;
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
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_MONK_NEAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CMonkNearAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_MONK_NEAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CMonkNearAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_MONK_FAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CMonkFarAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_MONK_FAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CMonkFarAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_MONK_MAGIC_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CMonkMagicAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_MONK_MAGIC_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CMonkMagicAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_MONK_PUNCH)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CMonkPunchSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_MONK_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_MONK_PUNCH)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CMonkPunchSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
}

int CMonk_Male::TotalStat1()
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
	float fCoef2 = GetReducedEffortConsumption();
	float fCoef3 = GetEffortRecoveryOfSecond() / 250.0f;

	// TotalAttack
	int iTotalAttack = iAttack + iCriticalAttack;
	iTotalAttack = int(iTotalAttack * (1.0f + fCoef1 + fCoef2 + fCoef3));

	return iTotalAttack;
}

int CMonk_Male::TotalStat2()
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

int CMonk_Male::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}