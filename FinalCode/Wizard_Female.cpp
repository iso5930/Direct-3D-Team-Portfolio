#include "StdAfx.h"
#include "Wizard_Female.h"

CWizard_Female::CWizard_Female(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
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
		case SLOT_ID_WIZARD_OPEN:
			m_pSlot[i] = new CWizardOpenSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_CLOSE:
			m_pSlot[i] = new CWizardCloseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_POTION:
			m_pSlot[i] = new CWizardPotionSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_MAGIC_MISSILE:
			m_pSlot[i] = new CWizardMagicMissileSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_SHOCK_PULSE:
			m_pSlot[i] = new CWizardShockPulseSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_SPECTRAL_BLADE:
			m_pSlot[i] = new CWizardSpectralBladeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ELECTROCUTE:
			m_pSlot[i] = new CWizardElectrocuteSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_PUNCH:
			m_pSlot[i] = new CWizardPunchSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_NEAR_ATTACK:
			m_pSlot[i] = new CWizardNearAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_FAR_ATTACK:
			m_pSlot[i] = new CWizardFarAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_MAGIC_ATTACK:
			m_pSlot[i] = new CWizardMagicAttackSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_RAY_OF_FROST:
			m_pSlot[i] = new CWizardRayOfFrostSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ARCANE_ORB:
			m_pSlot[i] = new CWizardArcaneOrbSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ARCANE_TORRENT:
			m_pSlot[i] = new CWizardArcaneTorrentSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_DISINTEGRATE:
			m_pSlot[i] = new CWizardDisintegrateSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_FROST_NOVA:
			m_pSlot[i] = new CWizardFrostNovaSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_DIAMOND_SKIN:
			m_pSlot[i] = new CWizardDiamondSkinSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_SLOW_TIME:
			m_pSlot[i] = new CWizardSlowTimeSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_TELEPORT:
			m_pSlot[i] = new CWizardTeleportSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_WAVE_OF_FORCE:
			m_pSlot[i] = new CWizardWaveOfForceSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ENERGY_TWISTER:
			m_pSlot[i] = new CWizardEnergyTwisterSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_HYDRA:
			m_pSlot[i] = new CWizardHydraSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_METEOR:
			m_pSlot[i] = new CWizardMeteorSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_BLIZZARD:
			m_pSlot[i] = new CWizardBlizzardSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ICE_ARMOR:
			m_pSlot[i] = new CWizardIceArmorSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_STORM_ARMOR:
			m_pSlot[i] = new CWizardStormArmorSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_MAGIC_WEAPON:
			m_pSlot[i] = new CWizardMagicWeaponSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_FAMILIAR:
			m_pSlot[i] = new CWizardFamiliarSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ENERGY_ARMOR:
			m_pSlot[i] = new CWizardEnergyArmorSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_EXPLOSIVE_BLAST:
			m_pSlot[i] = new CWizardExplosiveBlastSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_MIRROR_IMAGE:
			m_pSlot[i] = new CWizardMirrorImageSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		case SLOT_ID_WIZARD_ARCHON:
			m_pSlot[i] = new CWizardArchonSlot;
			m_pSlot[i]->SetOwner(this);
			break;
		}
	}
}

CWizard_Female::~CWizard_Female()
{
	Release();
}

void CWizard_Female::Initialize()
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

int CWizard_Female::Update()
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

void CWizard_Female::Render()
{
	CPlayer::Render();
}

void CWizard_Female::Release()
{
}

int CWizard_Female::Attack()
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
	return iAtt = int(iAtt * (1.0f + fRand));
}

void CWizard_Female::LevelUp()
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

void CWizard_Female::Damage(CMonster* _pMonster)
{
	// Damage
	CPlayer::Damage(_pMonster);
}

void CWizard_Female::Damage(CEffect* _pEffect)
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
		case STATE_TYPE_WIZARD_FEMALE_STF_SUMMON:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_SUMMON:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_SUMMON:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_SUMMON:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_SUMMON: 
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_SUMMON: 
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_DIRECTED:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_DIRECTED:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_DIRECTED:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_DIRECTED: 
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_DIRECTED:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_DIRECTED: 
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_CHANNEL:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_CHANNEL:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_CHANNEL:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_CHANNEL: 
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_CHANNEL: 
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_CHANNEL: 
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_AOE2:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_AOE2:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_AOE2:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_AOE2: 
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_AOE2: 
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_AOE2: 
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_AOE:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_AOE:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_AOE:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_AOE:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_AOE:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_AOE:
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_RUN:
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_RUN:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_RUN:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_RUN:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_RUN:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_RUN:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_IDLE:
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_IDLE:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_IDLE:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_IDLE:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_IDLE:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_IDLE:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_HIT:
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_HIT:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_HIT:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_HIT:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_HIT:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_HIT:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_ATTACK:
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_RANGE_ATTACK:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_ATTACK:
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_ATTACK:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_ATTACK:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ATTACK:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_WAND_ORB_ATTACK:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_WAND_ATTACK:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_ATTACK:
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_XBOW_RECOLL: 
			SetState(new CWizard_Female_XBow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_STF_RECOLL: 
			SetState(new CWizard_Female_STF_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_BOW_RECOLL: 
			SetState(new CWizard_Female_Bow_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_2HS_RECOLL:
			SetState(new CWizard_Female_2HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_RECOLL:
			SetState(new CWizard_Female_1HS_Orb_Mez(_pEffect->GetSkillType() , vDir));
			break;
		case STATE_TYPE_WIZARD_FEMALE_1HS_RECOLL:
			SetState(new CWizard_Female_1HS_Mez(_pEffect->GetSkillType() , vDir));
			break;
	}		
}			

void CWizard_Female::Renew()
{
	// Renew
	CPlayer::Renew();

	// Boots
	Item* pBoots = CItemMgr::GetInstance()->GetItemInEquip(12);
	if(pBoots == NULL || _tcscmp(pBoots->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Boots"));
	else
		m_pBufferCom->AddBuffer(pBoots->tszBufKey);

	// Helms
	Item* pHelms = CItemMgr::GetInstance()->GetItemInEquip(1);
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Hair"));

	// Gloves
	Item* pGloves = CItemMgr::GetInstance()->GetItemInEquip(3);
	if(pGloves == NULL || _tcscmp(pGloves->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Hands"));
	else
		m_pBufferCom->AddBuffer(pGloves->tszBufKey);

	// Pants
	Item* pPants = CItemMgr::GetInstance()->GetItemInEquip(10);
	if(pPants == NULL || _tcscmp(pPants->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Pants"));
	else
		m_pBufferCom->AddBuffer(pPants->tszBufKey);

	// ChestArmor
	Item* pChestArmor = CItemMgr::GetInstance()->GetItemInEquip(4);
	if(pChestArmor == NULL || _tcscmp(pChestArmor->tszBufKey, _T("")) == 0)
		m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Upper"));
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
	DWORD dwTwoHand = WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;

	// X / X
	if(pMainWeapon == NULL && pSubWeapon == NULL)
	{
		SetState(new CWizard_Female_1HS_Idle);
	}
	// X / 방패
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Idle);
	}
	// X / 오브
	else if(pMainWeapon == NULL && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_ORB))
	{
		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Orb_Idle);
	}
	// 완드 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_WAND) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Idle);
	}
	// 완드 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_WAND) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Idle);
	}
	// 완드 / 오브
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_WAND) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_ORB))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Orb_Idle);
	}
	// 한손 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Idle);
	}
	// 한손 / 방패
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_SHIELD))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftShieldBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Idle);
	}
	// 한손 / 오브
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwOneHand) && pSubWeapon != NULL && (pSubWeapon->dwItemID & WEAPON_ID_ORB))
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		m_pSubWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pSubWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pSubWeapon, LAYER_TYPE_ITEM);
		m_pSubWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pSubWeapon->Initialize();

		SetState(new CWizard_Female_1HS_Orb_Idle);
	}
	// 스태프 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_STAFF) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_STF_Idle);
	}
	// 활 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_BOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_LeftWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->SetMatrix(0.0f, 0.0f, 180.0f);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_Bow_Idle);
	}
	// 석궁 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & WEAPON_ID_CROSSBOW) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_XBow_Idle);
	}
	// 두손 / X
	else if(pMainWeapon != NULL && (pMainWeapon->dwItemID & dwTwoHand) && pSubWeapon == NULL)
	{
		m_pMainWeapon = new CEquipItem(NULL, OBJ_TYPE_STATIC, pMainWeapon, &m_RightWeaponBone);
		m_pLayer->AddObject(m_pMainWeapon, LAYER_TYPE_ITEM);
		m_pMainWeapon->Initialize();

		SetState(new CWizard_Female_2HS_Idle);
	}

	// ID
	DWORD dwNearAttack = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
	DWORD dwFarAttack = WEAPON_ID_CROSSBOW | WEAPON_ID_BOW | WEAPON_ID_CROSSBOW;
	DWORD dwMagicAttack = WEAPON_ID_WAND | WEAPON_ID_STAFF;

	// Check
	if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwNearAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwNearAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(4, new CWizardNearAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(5, new CWizardNearAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(4, new CWizardFarAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(5, new CWizardFarAttackSlot);
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK)
			SetSlot(4, new CWizardMagicAttackSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK)
			SetSlot(5, new CWizardMagicAttackSlot);
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(4, new CWizardPunchSlot);
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
			SetSlot(5, new CWizardPunchSlot);
	}
}

void CWizard_Female::CreateAttack()
{
	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_WIZARD_FEMALE_STF_SUMMON:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_SUMMON:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_SUMMON:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_SUMMON:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_DIRECTED:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_DIRECTED:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_DIRECTED:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_CHANNEL:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_CHANNEL:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_CHANNEL:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_AOE2:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_AOE2:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_AOE2:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_AOE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_AOE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_AOE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_AOE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_XBOW_RUN:
		break;
	case STATE_TYPE_WIZARD_FEMALE_BOW_RUN:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_RUN:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_RUN:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_RUN:
		break;
	case STATE_TYPE_WIZARD_FEMALE_XBOW_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_BOW_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_IDLE:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_KNOCKBACK_END:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_KNOCKBACK_END:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_KNOCKBACK_END:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_KNOCKBACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_KNOCKBACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_KNOCKBACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_XBOW_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_STF_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_BOW_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_HIT:
		break;
	case STATE_TYPE_WIZARD_FEMALE_XBOW_ATTACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_WAND_ORB_ATTACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_WAND_ATTACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_BOW_RANGE_ATTACK:
		break;
	case STATE_TYPE_WIZARD_FEMALE_BOW_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_WIZARD_FEMALE_2HS_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ORB_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f),  20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f),  20.0f, 20.0f, 20.0f));
		break;
	case STATE_TYPE_WIZARD_FEMALE_1HS_TELEPORT:
		break;
	}

	// CreateAttack
	CPlayer::CreateAttack();
}

void CWizard_Female::SetSlot(int _iIndex, CSlot* _pSlot)
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
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WIZARD_NEAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWizardNearAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WIZARD_NEAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWizardNearAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwFarAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwFarAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WIZARD_FAR_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWizardFarAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WIZARD_FAR_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWizardFarAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else if((pMainWeapon != NULL && (pMainWeapon->dwItemID & dwMagicAttack)) || (pSubWeapon != NULL && (pSubWeapon->dwItemID & dwMagicAttack)))
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WIZARD_MAGIC_ATTACK)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWizardMagicAttackSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_PUNCH || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WIZARD_MAGIC_ATTACK)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWizardMagicAttackSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
	else
	{
		if(m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[4]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[5]->GetSlotID() != SLOT_ID_WIZARD_PUNCH)
			{
				delete m_pSlot[4];
				m_pSlot[4] = new CWizardPunchSlot;
				m_pSlot[4]->SetOwner(this);
			}
		}
		else if(m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_OPEN || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_FAR_ATTACK || m_pSlot[5]->GetSlotID() == SLOT_ID_WIZARD_MAGIC_ATTACK)
		{
			if(m_pSlot[4]->GetSlotID() != SLOT_ID_WIZARD_PUNCH)
			{
				delete m_pSlot[5];
				m_pSlot[5] = new CWizardPunchSlot;
				m_pSlot[5]->SetOwner(this);
			}
		}
	}
}

int CWizard_Female::TotalStat1()
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

int CWizard_Female::TotalStat2()
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

int CWizard_Female::TotalStat3()
{
	// LifeRecovery
	int iLifeRecovery1 = GetLifeRecoveryOfSecond();
	int iLifeRecovery2 = GetLifeRecoveryOfHit() * 10;

	return iLifeRecovery1 + iLifeRecovery2;
}