#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_PLAYER);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_PLAYER);
	AddComponent(pRenderCom);

	// BufferCom
	m_pBufferCom = new CBufferCom;
	AddComponent(m_pBufferCom);

	// Time
	m_fTime = 0.0f;

	// State
	m_pState = NULL;

	// DynamicMesh
	ZeroMemory(m_pDynamicMesh, sizeof(m_pDynamicMesh));

	// CollisionCom
	m_pCollisionCom = NULL;

	// MainWeapon
	m_pMainWeapon = NULL;

	// SubWeapon
	m_pSubWeapon = NULL;

	// Helm
	m_pHelm = NULL;

	// Shoulder
	m_pShoulder = NULL;

	// PickObject
	m_pPickObject = NULL;

	// PickType
	m_iPickType = MOUSE_OVER_TYPE_NONE;

	// LastPushSlotNum
	m_iLastPushSlotNum = SLOT_PUSH_TYPE_NONE;

	// Begin
	CItemMgr::GetInstance()->Begin();
	CSettingMgr::GetInstance()->Begin();
	CQuestMgr::GetInstance()->Begin();
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CObject::Initialize();

	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

	// Follower
	if(pAccount->bHaveFollower)
	{
		if(pAccount->followerInfo.eFollowerType == FOLLOWER_TYPE_ENCHANTRESS)
		{
			CFollower* pFollower = new CEnchantress(_T("Follower"), OBJ_TYPE_STATIC, this, &pAccount->followerInfo);
			m_pLayer->AddObject(pFollower, LAYER_TYPE_FOLLOWER);
			pFollower->Initialize();

			CTransformCom* pTransformCom = (CTransformCom*)pFollower->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = pAccount->vFollowerPos;
			pTransformCom->m_vAngle = pAccount->vFollowerAngle;
			pTransformCom->m_vSize = pAccount->vFollowerSize;
		}
	}

	// Renew
	Renew();
}

int CPlayer::Update()
{
	// PickObject
	if (m_pPickObject != NULL && m_pPickObject->IsDestroy() == true)
	{
		m_pPickObject = NULL;
		m_iPickType = MOUSE_OVER_TYPE_NONE;
	}

	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON) || CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) )
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pLayer->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_NONE)
		{
			m_pPickObject = NULL;
			m_iPickType = MOUSE_OVER_TYPE_NONE;	
		}
		else
		{	
			m_pPickObject = pMouse->GetOverObject();
			m_iPickType = pMouse->GetMouseOverType();
		}
	}

	// Action
	CPlayerState* pState = NULL;

	if(m_pState != NULL)
		pState = m_pState->Action();

	if(pState != NULL)
	{
		delete m_pState;
		m_pState = pState;
		m_pState->SetOwner(this);
		m_pState->Initialize();
	}

	// Slot
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
			m_pSlot[i]->Update();
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Q))
	{
		if(m_pSlot[6] != NULL)
			m_pSlot[6]->Begin(0);
	}

	// Buff
	for(size_t i = 0; i < m_BuffVec.size(); ++i)
	{
		m_BuffVec[i]->fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_BuffVec[i]->fAccTime > m_BuffVec[i]->fFrameTime)
		{
			delete m_BuffVec[i];
			m_BuffVec[i] = m_BuffVec.back();
			m_BuffVec.pop_back();
		}
	}

	// Buff
	for(size_t i = 0; i < m_MezVec.size(); ++i)
	{
		m_MezVec[i]->fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_MezVec[i]->fAccTime > m_MezVec[i]->fFrameTime)
		{
			delete m_MezVec[i];
			m_MezVec[i] = m_MezVec.back();
			m_MezVec.pop_back();
		}
	}

	// Light
	CLight* pLight = CLightMgr::GetInstance()->GetLight(2);
	if(pLight != NULL)
	{
		D3DXVECTOR4* pLightPos = pLight->GetPos();
		pLightPos->x = m_pTransformCom->m_vPos.x;
		pLightPos->y = m_pTransformCom->m_vPos.y + 100.0f;
		pLightPos->z = m_pTransformCom->m_vPos.z;
	}

	CObject::Update();

	return 0;
}

void CPlayer::Render()
{
	CObject::Render();
}

void CPlayer::Release()
{
	// Renew
	CDataMgr::GetInstance()->Renew();

	// Save
	CDataMgr::GetInstance()->Save();

	// Reset
	CDataMgr::GetInstance()->Reset();

	// End
	CItemMgr::GetInstance()->End();
	CSettingMgr::GetInstance()->End();
	CQuestMgr::GetInstance()->End();

	// Slot
	for(int i = 0; i < 7; ++i)
	{
		if(m_pSlot[i] != NULL)
			delete m_pSlot[i];
	}

	// BuffVec
	for(size_t i = 0; i < m_BuffVec.size(); ++i)
	{
		delete m_BuffVec[i];
		m_BuffVec[i] = NULL;
	}
	m_BuffVec.clear();
	
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

	// Helm
	if(m_pHelm != NULL)
	{
		m_pHelm->Destroy();
		m_pHelm = NULL;
	}

	// Shoulder
	if(m_pShoulder != NULL)
	{
		m_pShoulder->Destroy();
		m_pShoulder = NULL;
	}

	// State
	if(m_pState != NULL)
		delete m_pState;
}

void CPlayer::Run()
{
	// Add UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_PLAYER);
	AddComponent(pUpdateCom);
	pUpdateCom->Initialize();

	// Follower
	CObject* pFindFollower = NULL;
	m_pLayer->FindObject(pFindFollower, _T("Follower"), LAYER_TYPE_FOLLOWER);
	if(pFindFollower != NULL)
	{
		pUpdateCom = new CUpdateCom(UPDATE_TYPE_FOLLOWER);
		pFindFollower->AddComponent(pUpdateCom);
		pUpdateCom->Initialize();

		CFollowerEnergy* pFollowerEnergy = new CFollowerEnergy(_T("FollowerEnergy"), OBJ_TYPE_STATIC, (CFollower*)pFindFollower);
		m_pLayer->AddObject(pFollowerEnergy, LAYER_TYPE_UI);
		pFollowerEnergy->Initialize();
	}

	// PlayerEnergy
	CPlayerEnergy* pPlayerEnergy = new CPlayerEnergy(_T("PlayerEnergy"), OBJ_TYPE_STATIC, this);
	m_pLayer->AddObject(pPlayerEnergy, LAYER_TYPE_UI);
	pPlayerEnergy->Initialize();
}

void CPlayer::Stop()
{
	// Remove UpdateCom
	RemoveComponent(COM_TYPE_UPDATE);

	CPathFindCom* pPathFindCom = (CPathFindCom*)m_pComponent[COM_TYPE_PATH_FIND];
	pPathFindCom->m_pCell = NULL;

	CObject* pFindFollower = NULL;
	m_pLayer->FindObject(pFindFollower, _T("Follower"), LAYER_TYPE_FOLLOWER);
	if(pFindFollower != NULL)
		pFindFollower->RemoveComponent(COM_TYPE_UPDATE);

	CObject* pFindFollowerEnergy = NULL;
	m_pLayer->FindObject(pFindFollowerEnergy, _T("FollowerEnergy"), LAYER_TYPE_UI);
	if(pFindFollowerEnergy != NULL)
		pFindFollowerEnergy->Destroy();

	CObject* pFindPlayerEnergy = NULL;
	m_pLayer->FindObject(pFindPlayerEnergy, _T("PlayerEnergy"), LAYER_TYPE_UI);
	if(pFindPlayerEnergy != NULL)
		pFindPlayerEnergy->Destroy();
}

void CPlayer::Kill(int _iExp)
{
	if(m_stat.iLevel == 70)
		return;

	m_stat.iExp += int(_iExp * GetExperience());
	if(m_stat.iExp >= m_stat.iMaxExp)
	{
		// LevelUp
		LevelUp();
	}
}

int CPlayer::Attack()
{
	int iMaxLife = int((m_stat.iMaxLife + GetVitality() * 10) * GetRestoresBonus());
	m_stat.iLife += GetLifeRecoveryOfHit();
	if(m_stat.iLife > iMaxLife)
		m_stat.iLife = iMaxLife;

	return 0;
}

void CPlayer::LevelUp()
{
	// Stat
	m_stat.iLevel += 1;
	m_stat.iControl = m_stat.iMaxControl;
	m_stat.iEffort = m_stat.iMaxEffort;
	m_stat.iHate = m_stat.iMaxHate;
	m_stat.iLife = int((m_stat.iMaxLife + GetVitality() * 10) * GetRestoresBonus());
	m_stat.iMana = m_stat.iMaxMana;
	m_stat.iRage = m_stat.iMaxRage;
	m_stat.iVision = m_stat.iMaxVision;
	m_stat.iExp = 0; m_stat.iMaxExp = m_stat.iLevel * m_stat.iLevel * 280;

	// LevelUpEffect
	CLevelUpEffect* pLevelUpEffect = new CLevelUpEffect(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer->AddObject(pLevelUpEffect, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)pLevelUpEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f);

	pLevelUpEffect->Initialize();

	// LevelUpAlarmMessage
	CLevelUpAlarmMessage* pLevelUpAlarmMessage = new CLevelUpAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, m_stat.iLevel);
	m_pLayer->AddObject(pLevelUpAlarmMessage, LAYER_TYPE_UI);
	pLevelUpAlarmMessage->Initialize();
}

void CPlayer::Damage(CMonster* _pMonster)
{
	float fCoef1 = 1000.0f / GetPhysicalResistance();
	if(fCoef1 > 1.0f)
		fCoef1 = 1.0f;

	float fCoef2 = 1.0f - GetReducedNearDamage();
	if(fCoef2 < 0.0f)
		fCoef2 = 0.0f;

	int iDamage = int(_pMonster->Attack() * fCoef1 * fCoef2) - GetDef();
	if(iDamage < 1)
		iDamage = 1;

	m_stat.iLife -= iDamage;

	// DamageMessage
	CDamageMessage* pDamageMessage = new CDamageMessage(NULL, OBJ_TYPE_DYNAMIC, iDamage, &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pLayer->AddObject(pDamageMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)pDamageMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f);

	pDamageMessage->Initialize();

	// BloodDecalEffect
	if(rand() % 1000 < 100)
	{
		// vRand
		D3DXVECTOR3 vRand = D3DXVECTOR3(rand() % 1000 - 500.0f, 0.0f, rand() % 1000 - 500.0f);
		if(Equals(vRand.x, 0.0f, MIN_EPSILON) && Equals(vRand.z, 0.0f, MIN_EPSILON))
			vRand += D3DXVECTOR3(1.0f, 0.0f, 1.0f);

		D3DXVec3Normalize(&vRand, &vRand);

		CBloodDecalEffect* pBloodDecalEffect = new CBloodDecalEffect(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pBloodDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pBloodDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + (rand() % 100 + 50.0f) * vRand;

		pBloodDecalEffect->Initialize();
	}
}

void CPlayer::Damage(CEffect* _pEffect)
{
	float fCoef1;
	if(_pEffect->GetAttrType() == ATTR_TYPE_PHYSICAL)
		fCoef1 = 1000.0f / GetPhysicalResistance();
	else if(_pEffect->GetAttrType() == ATTR_TYPE_COLD)
		fCoef1 = 1000.0f / GetColdResistance();
	else if(_pEffect->GetAttrType() == ATTR_TYPE_FLAME)
		fCoef1 = 1000.0f / GetFlameResistance();
	else if(_pEffect->GetAttrType() == ATTR_TYPE_LIGHTNING)
		fCoef1 = 1000.0f / GetLightningResistance();
	else if(_pEffect->GetAttrType() == ATTR_TYPE_POISON)
		fCoef1 = 1000.0f / GetPoisonResistance();
	else if(_pEffect->GetAttrType() == ATTR_TYPE_HOLY)
		fCoef1 = 1000.0f / GetHolyResistance();

	if(fCoef1 > 1.0f)
		fCoef1 = 1.0f;

	float fCoef2 = 1.0f - GetReducedFarDamage();
	if(fCoef2 < 0.0f)
		fCoef2 = 0.0f;

	CMonster* pMonster = (CMonster*)_pEffect->GetOwner();
	int iDamage = int(pMonster->Attack() * _pEffect->GetCoef() * fCoef1 * fCoef2) - GetDef();
	if(iDamage < 1)
		iDamage = 1;

	m_stat.iLife -= iDamage;

	// DamageMessage
	CDamageMessage* pDamageMessage = new CDamageMessage(NULL, OBJ_TYPE_DYNAMIC, iDamage, &D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pLayer->AddObject(pDamageMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)pDamageMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f);

	pDamageMessage->Initialize();

	// BloodDecalEffect
	if(rand() % 1000 < 100)
	{
		// vRand
		D3DXVECTOR3 vRand = D3DXVECTOR3(rand() % 1000 - 500.0f, 0.0f, rand() % 1000 - 500.0f);
		if(Equals(vRand.x, 0.0f, MIN_EPSILON) && Equals(vRand.z, 0.0f, MIN_EPSILON))
			vRand += D3DXVECTOR3(1.0f, 0.0f, 1.0f);

		D3DXVec3Normalize(&vRand, &vRand);

		CBloodDecalEffect* pBloodDecalEffect = new CBloodDecalEffect(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pBloodDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pBloodDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + (rand() % 100 + 50.0f) * vRand;

		pBloodDecalEffect->Initialize();
	}
}

void CPlayer::Renew()
{
	// BufferCom
	for(size_t i = 0; i < m_pBufferCom->m_BufferVec.size(); ++i)
	{
		delete m_pBufferCom->m_BufferVec[i];
		m_pBufferCom->m_BufferVec[i] = NULL;
	}
	m_pBufferCom->m_BufferVec.clear();

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

	// Helm
	if(m_pHelm != NULL)
	{
		m_pHelm->Destroy();
		m_pHelm = NULL;
	}

	// Shoulder
	if(m_pShoulder != NULL)
	{
		m_pShoulder->Destroy();
		m_pShoulder = NULL;
	}
}

void CPlayer::CreateAttack()
{
}

void CPlayer::SetSlot(int _iIndex, CSlot* _pSlot)
{
	// Clear
	if(m_pSlot[_iIndex] != NULL)
	{
		delete m_pSlot[_iIndex];
		m_pSlot[_iIndex] = NULL;
	}

	// Set
	m_pSlot[_iIndex] = _pSlot;
	m_pSlot[_iIndex]->SetOwner(this);

	// Renew
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_SLOT);
}

int CPlayer::TotalStat1()
{
	return 0;
}

int CPlayer::TotalStat2()
{
	return 0;
}

int CPlayer::TotalStat3()
{
	return 0;
}

void CPlayer::SetState(CPlayerState* _pState)
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

void CPlayer::RemoveAttack()
{
	for(size_t i = 0; i < m_pCollisionCom->m_CollisionVec.size(); ++i)
	{
		if(m_pCollisionCom->m_CollisionVec[i]->dwType & COLLISION_ATTACK)
		{
			delete m_pCollisionCom->m_CollisionVec[i];
			m_pCollisionCom->m_CollisionVec[i] = m_pCollisionCom->m_CollisionVec[m_pCollisionCom->m_CollisionVec.size() - 1];
			m_pCollisionCom->m_CollisionVec.pop_back();
			--i;
		}
	}
}

void CPlayer::AddBuff(Buff* _pBuff)
{
	for(size_t i = 0; i < m_BuffVec.size(); ++i)
	{
		if(m_BuffVec[i]->eBuffType == _pBuff->eBuffType)
		{
			delete m_BuffVec[i];
			m_BuffVec[i] = m_BuffVec.back();
			m_BuffVec.pop_back();
			break;
		}
	}

	m_BuffVec.push_back(_pBuff);
}

void CPlayer::AddMez(Mez* _pMez)
{
	for(size_t i = 0; i < m_MezVec.size(); ++i)
	{
		if(m_MezVec[i]->eSkillType == _pMez->eSkillType)
		{
			delete _pMez;
			return ;
		}
	}

	m_MezVec.push_back(_pMez);
}

bool CPlayer::IsMez(int _iMez)
{
	for(size_t i = 0; i < m_MezVec.size(); ++i)
	{
		if(m_MezVec[i]->eSkillType == (SKILL_TYPE)_iMez)
		{
			return true;
		}
	}
	
	return false;
}

void CPlayer::SetAnimation(int _iIndex)
{
	for(int i = 0; i < 5; ++i)
	{
		if(m_pDynamicMesh[i] != NULL)
			m_pDynamicMesh[i]->m_pAnimController->SetAnimation(_iIndex);
	}
}

void CPlayer::SetAnimationMode(int _iMode)
{
	for(int i = 0; i < 5; ++i)
	{
		if(m_pDynamicMesh[i] != NULL)
			m_pDynamicMesh[i]->m_iMode = _iMode;
	}
}

// Value
int CPlayer::GetAtt()
{
	float fAtt = 10.0f;
	DWORD dw = WEAPON_ID_AXE | WEAPON_ID_BOW | WEAPON_ID_CEREMONIAL_DAGGER	| WEAPON_ID_FIST | WEAPON_ID_HANDXBOW |	WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_QUIVER | WEAPON_ID_MIGHTY1H | WEAPON_ID_MIGHTY2H | WEAPON_ID_SPEAR | WEAPON_ID_STAFF | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_WAND | WEAPON_ID_MOJO | WEAPON_ID_CROSSBOW | WEAPON_ID_ORB;
	if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & dw))
		fAtt += CItemMgr::GetInstance()->GetItemInEquip(9)->iAtt;
	else if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(11)->dwItemID & dw))
		fAtt += CItemMgr::GetInstance()->GetItemInEquip(11)->iAtt;

	return int(fAtt);
}
int CPlayer::GetDef()
{
	float fDef = 0.0f;
	DWORD dw = ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_BELT | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(i)->dwItemType & dw))
			fDef += CItemMgr::GetInstance()->GetItemInEquip(i)->iDef;
	}
	return int(fDef);
}

// MainStat
int CPlayer::GetStrength()
{
	int iStrength = m_stat.iStrength;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
		{
			iStrength += CItemMgr::GetInstance()->GetItemInEquip(i)->tMainStat.iStrength;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInEquip(i)->iSockCnt; ++j)
				iStrength += CItemMgr::GetInstance()->GetItemInEquip(i)->SockArr[j]->tMainStat.iStrength;
		}
	}
	return iStrength;
}
int CPlayer::GetAgility()
{
	int iAgility = m_stat.iAgility;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
		{
			iAgility += CItemMgr::GetInstance()->GetItemInEquip(i)->tMainStat.iAgility;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInEquip(i)->iSockCnt; ++j)
				iAgility += CItemMgr::GetInstance()->GetItemInEquip(i)->SockArr[j]->tMainStat.iAgility;
		}
	}
	return iAgility;
}
int CPlayer::GetIntelligence()
{
	int iIntelligence = m_stat.iIntelligence;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
		{
			iIntelligence += CItemMgr::GetInstance()->GetItemInEquip(i)->tMainStat.iIntelligence;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInEquip(i)->iSockCnt; ++j)
				iIntelligence += CItemMgr::GetInstance()->GetItemInEquip(i)->SockArr[j]->tMainStat.iIntelligence;
		}
	}
	return iIntelligence;
}
int CPlayer::GetVitality()
{
	int iVitality = m_stat.iVitality;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
		{
			iVitality += CItemMgr::GetInstance()->GetItemInEquip(i)->tMainStat.iVitality;
			for(int j = 0; j < CItemMgr::GetInstance()->GetItemInEquip(i)->iSockCnt; ++j)
				iVitality += CItemMgr::GetInstance()->GetItemInEquip(i)->SockArr[j]->tMainStat.iVitality;
		}
	}
	return iVitality;
}

// AttackStat
float CPlayer::GetReducedCooldownTime()
{
	float fReducedCooldownTime = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedCooldownTime += CItemMgr::GetInstance()->GetItemInEquip(i)->tAttackStat.fReducedCooldownTime;
	}
	return fReducedCooldownTime;
}
float CPlayer::GetCriticalProbability()
{
	float fCriticalProbability = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fCriticalProbability += CItemMgr::GetInstance()->GetItemInEquip(i)->tAttackStat.fCriticalProbability;
	}
	return fCriticalProbability;
}
float CPlayer::GetCriticalDamage()
{
	float fCriticalDamage = 1.5f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fCriticalDamage += CItemMgr::GetInstance()->GetItemInEquip(i)->tAttackStat.fCriticalDamage;
	}
	return fCriticalDamage;
}

// DefenseStat
int CPlayer::GetPhysicalResistance()
{
	int iPhysicalResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iPhysicalResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iPhysicalResistance;
	}
	return iPhysicalResistance;
}
int CPlayer::GetColdResistance()
{
	int iColdResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iColdResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iColdResistance;
	}
	return iColdResistance;
}
int CPlayer::GetFlameResistance()
{
	int iFlameResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iFlameResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iFlameResistance;
	}
	return iFlameResistance;
}
int CPlayer::GetLightningResistance()
{
	int iLightningResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iLightningResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iLightningResistance;
	}
	return iLightningResistance;
}
int CPlayer::GetPoisonResistance()
{
	int iPoisonResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iPoisonResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iPoisonResistance;
	}
	return iPoisonResistance;
}
int CPlayer::GetHolyResistance()
{
	int iHolyResistance = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iHolyResistance += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.iHolyResistance;
	}
	return iHolyResistance;
}
float CPlayer::GetReducedNearDamage()
{
	float fReducedNearDamage = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedNearDamage += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.fReducedNearDamage;
	}
	return fReducedNearDamage;
}
float CPlayer::GetReducedFarDamage()
{
	float fReducedFarDamage = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedFarDamage += CItemMgr::GetInstance()->GetItemInEquip(i)->tDefenseStat.fReducedFarDamage;
	}
	return fReducedFarDamage;
}

// LifeStat
float CPlayer::GetRestoresBonus()
{
	float fRestoresBonus = 1.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fRestoresBonus += CItemMgr::GetInstance()->GetItemInEquip(i)->tLifeStat.fRestoresBonus;
	}
	return fRestoresBonus;
}
int CPlayer::GetLifeRecoveryOfSecond()
{
	int iLifeRecoveryOfSecond = 0;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iLifeRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tLifeStat.iLifeRecoveryOfSecond;
	}
	return iLifeRecoveryOfSecond;
}
int CPlayer::GetLifeRecoveryOfHit()
{
	int iLifeRecoveryOfHit = 0;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iLifeRecoveryOfHit += CItemMgr::GetInstance()->GetItemInEquip(i)->tLifeStat.iLifeRecoveryOfHit;
	}
	return iLifeRecoveryOfHit;
}

// ResourceStat
int CPlayer::GetControlRecoveryOfSecond()
{
	int iControlRecoveryOfSecond = 1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iControlRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iControlRecoveryOfSecond;
	}
	return iControlRecoveryOfSecond;
}
int CPlayer::GetEffortRecoveryOfSecond()
{
	int iEffortRecoveryOfSecond = 0;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iEffortRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iEffortRecoveryOfSecond;
	}
	return iEffortRecoveryOfSecond;
}
int CPlayer::GetHateRecoveryOfSecond()
{
	int iHateRecoveryOfSecond = 4;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iHateRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iHateRecoveryOfSecond;
	}
	return iHateRecoveryOfSecond;
}
int CPlayer::GetManaRecoveryOfSecond()
{
	int iManaRecoveryOfSecond = 50;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iManaRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iManaRecoveryOfSecond;
	}
	return iManaRecoveryOfSecond;
}
int CPlayer::GetRageRecoveryOfSecond()
{
	int iRageRecoveryOfSecond = -1;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iRageRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iRageRecoveryOfSecond;
	}
	return iRageRecoveryOfSecond;
}
int CPlayer::GetVisionRecoveryOfSecond()
{
	int iVisionRecoveryOfSecond = 10;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			iVisionRecoveryOfSecond += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.iVisionRecoveryOfSecond;
	}
	return iVisionRecoveryOfSecond;
}
float CPlayer::GetReducedControlConsumption()
{
	float fReducedControlConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedControlConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedControlConsumption;
	}
	return fReducedControlConsumption;
}
float CPlayer::GetReducedEffortConsumption()
{
	float fReducedEffortConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedEffortConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedEffortConsumption;
	}
	return fReducedEffortConsumption;
}
float CPlayer::GetReducedHateConsumption()
{
	float fReducedHateConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedHateConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedHateConsumption;
	}
	return fReducedHateConsumption;
}
float CPlayer::GetReducedManaConsumption()
{
	float fReducedManaConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedManaConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedManaConsumption;
	}
	return fReducedManaConsumption;
}
float CPlayer::GetReducedRageConsumption()
{
	float fReducedRageConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedRageConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedRageConsumption;
	}
	return fReducedRageConsumption;
}
float CPlayer::GetReducedVisionConsumption()
{
	float fReducedVisionConsumption = 0.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fReducedVisionConsumption += CItemMgr::GetInstance()->GetItemInEquip(i)->tResourceStat.fReducedVisionConsumption;
	}
	return fReducedVisionConsumption;
}

// AdventureStat
float CPlayer::GetExperience()
{
	float fExperience = 1.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fExperience += CItemMgr::GetInstance()->GetItemInEquip(i)->tAdventureStat.fExperience;
	}
	return fExperience;
}
float CPlayer::GetMagicItemsFound()
{
	float fMagicItemsFound = 1.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fMagicItemsFound += CItemMgr::GetInstance()->GetItemInEquip(i)->tAdventureStat.fMagicItemsFound;
	}
	return fMagicItemsFound;
}
float CPlayer::GetDiscoveryOfGoldCoins()
{
	float fDiscoveryOfGoldCoins = 1.0f;
	for(int i = 0; i < 13; ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(i) != NULL)
			fDiscoveryOfGoldCoins += CItemMgr::GetInstance()->GetItemInEquip(i)->tAdventureStat.fDiscoveryOfGoldCoins;
	}
	return fDiscoveryOfGoldCoins;
}