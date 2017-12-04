#include "StdAfx.h"
#include "Monster.h"

CMonster::CMonster(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_MONSTER);
	AddComponent(pUpdateCom);

	// RenderCom
	m_pRenderCom = new CRenderCom(RENDER_TYPE_MONSTER);
	AddComponent(m_pRenderCom);

	// CollisionCom
	m_pCollisionCom = NULL;

	// Level
	m_stat.iLevel = _iLevel;
	m_stat.iExp = _iLevel * 100;

	// State
	m_pState = NULL;

	// DynamicMesh
	m_pDynamicMesh = NULL;

	// AnimController
	m_pAnimController = NULL;

	// Width
	m_fWidth = 60.0f;

	// Height
	m_fHeight = 100.0f;

	// Depth
	m_fDepth = 60.0f;

	// Ray
	ZeroMemory(&m_ray, sizeof(Ray));

	// IsOver
	m_bIsOver = false;

	// Line
	D3DXCreateLine(CDeviceMgr::GetInstance()->GetDevice(), &m_pLine);

	// Point
	ZeroMemory(m_vPoint, sizeof(m_vPoint));

	// Energy
	m_pEnergy = NULL;
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	// AnimController
	CBufferCom* pBufferCom = (CBufferCom*)m_pComponent[COM_TYPE_BUFFER];
	m_pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_pAnimController = m_pDynamicMesh->m_pAnimController;

	CObject::Initialize();
}

int CMonster::Update()
{
	// Action
	CMonsterState* pState = NULL;

	if(m_pState != NULL)
		pState = m_pState->Action();

	if(pState != NULL)
	{
		delete m_pState;
		m_pState = pState;
		m_pState->SetOwner(this);
		m_pState->Initialize();
	}

	// Is In?
	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 400.0f) == false)
	{
		// IsOver
		m_bIsOver = false;

		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		// Energy
		if(m_pEnergy != NULL)
		{
			m_pEnergy->Destroy();
			m_pEnergy = NULL;
		}

		return 0;
	}

	// IsOver
	m_bIsOver = false;

	// Find Mouse
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Mouse"), LAYER_TYPE_MOUSE);
	if(pFindObject != NULL)
	{
		// Mouse
		CMouse* pMouse = (CMouse*)pFindObject;

		// Check
		bool bCheck = false;
		if(pMouse->GetMouseOverType() != MOUSE_OVER_TYPE_NONE)
		{
			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);

			if(D3DXVec3Length(&(pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())) > D3DXVec3Length(&(m_pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())))
				bCheck = true;
		}

		if(pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_NONE || bCheck)
		{
			// Intersect
			m_vPoint[0] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
			m_vPoint[1] = D3DXVECTOR3(-m_fWidth / 2.0f, m_fHeight, -m_fDepth / 2.0f);
			m_vPoint[2] = D3DXVECTOR3(m_fWidth / 2.0f, m_fHeight, -m_fDepth / 2.0f);
			m_vPoint[3] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
			m_vPoint[4] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
			m_vPoint[5] = D3DXVECTOR3(-m_fWidth / 2.0f, m_fHeight, m_fDepth / 2.0f);
			m_vPoint[6] = D3DXVECTOR3(m_fWidth / 2.0f, m_fHeight, m_fDepth / 2.0f);
			m_vPoint[7] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);

			// TransformCoord
			for(int i = 0; i < 8; ++i)
				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_pTransformCom->m_mWorld);

			// ScreenToWorld
			ScreenToWorld(&m_ray, CInputMgr::GetInstance()->GetMousePos(), CCameraMgr::GetInstance()->GetProj(), CCameraMgr::GetInstance()->GetInvView());

			// Intersect
			float u, v, dist;
			if(D3DXIntersectTri(&m_vPoint[0], &m_vPoint[1], &m_vPoint[2], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[0], &m_vPoint[2], &m_vPoint[3], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[5], &m_vPoint[1], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[1], &m_vPoint[0], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[7], &m_vPoint[6], &m_vPoint[5], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[7], &m_vPoint[5], &m_vPoint[4], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[3], &m_vPoint[2], &m_vPoint[6], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[3], &m_vPoint[6], &m_vPoint[7], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[1], &m_vPoint[5], &m_vPoint[6], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[1], &m_vPoint[6], &m_vPoint[2], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[6], &m_vPoint[3], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[3], &m_vPoint[7], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
		}
	}

	if(m_bIsOver)
	{
		// Over
		CMouse* pMouse = (CMouse*)pFindObject;
		pMouse->Over(MOUSE_OVER_TYPE_MONSTER, this);

		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

		// Energy
		if(m_pEnergy == NULL)
		{
			m_pEnergy = new CMonsterEnergy(NULL, OBJ_TYPE_STATIC, this);
			m_pLayer->AddObject(m_pEnergy, LAYER_TYPE_UI);
			m_pEnergy->Initialize();
		}
	}
	else
	{
		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		// Energy
		if(m_pEnergy != NULL)
		{
			m_pEnergy->Destroy();
			m_pEnergy = NULL;
		}
	}

	CObject::Update();

	return 0;
}

void CMonster::Render()
{
	CObject::Render();
}

void CMonster::Release()
{
	// State
	if(m_pState != NULL)
	{
		delete m_pState;
		m_pState = NULL;
	}

	// Line
	if(m_pLine != NULL)
	{
		m_pLine->Release();
		m_pLine = NULL;
	}

	// Energy
	if(m_pEnergy != NULL)
	{
		m_pEnergy->Destroy();
		m_pEnergy = NULL;
	}
}

void CMonster::Damage(CPlayer* _pPlayer)
{
	// Attack
	int iDamage = _pPlayer->Attack();

	// Damage
	m_stat.iLife -= iDamage;

	// Death
	if(m_stat.iLife <= 0)
	{
		// Kill
		_pPlayer->Kill(m_stat.iExp);

		// DropGold
		while(rand() % 3 >= 2)
			DropGold();

		// DropItem
		while(rand() % 100 >= 80)
			DropItem();
	}

	// DamageMessage
	CDamageMessage* pDamageMessage = new CDamageMessage(NULL, OBJ_TYPE_DYNAMIC, iDamage, &D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
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

void CMonster::Damage(CEffect* _pEffect)
{
	// Player
	CPlayer* pPlayer = (CPlayer*)_pEffect->GetOwner();

	// Attack
	int iDamage = int(pPlayer->Attack() * _pEffect->GetCoef());

	// Damage
	m_stat.iLife -= iDamage;

	// Death
	if(m_stat.iLife <= 0)
	{
		// Kill
		pPlayer->Kill(m_stat.iExp);

		// DropGold
		while(rand() % 3 >= 2)
			DropGold();

		// DropItem
		while(rand() % 100 >= 80)
			DropItem();
	}

	// DamageMessage
	CDamageMessage* pDamageMessage = new CDamageMessage(NULL, OBJ_TYPE_DYNAMIC, iDamage, &D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
	m_pLayer->AddObject(pDamageMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)pDamageMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f);

	pDamageMessage->Initialize();

	D3DXVECTOR3 vRand;

	// BloodDecalEffect
	if(rand() % 1000 < 100)
	{
		// vRand
		vRand = D3DXVECTOR3(rand() % 1000 - 500.0f, 0.0f, rand() % 1000 - 500.0f);
		if(Equals(vRand.x, 0.0f, MIN_EPSILON) && Equals(vRand.z, 0.0f, MIN_EPSILON))
			vRand += D3DXVECTOR3(1.0f, 0.0f, 1.0f);

		D3DXVec3Normalize(&vRand, &vRand);

		CBloodDecalEffect* pBloodDecalEffect = new CBloodDecalEffect(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pBloodDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pBloodDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + (rand() % 100 + 50.0f) * vRand;

		pBloodDecalEffect->Initialize();
	}
	else
	{
		// vRand
		vRand = D3DXVECTOR3(rand() % 1000 - 500.0f, 0.0f, rand() % 1000 - 500.0f);
		if(Equals(vRand.x, 0.0f, MIN_EPSILON) && Equals(vRand.z, 0.0f, MIN_EPSILON))
			vRand += D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	}

	CHitEffect* pHitEffect = new CHitEffect(NULL, OBJ_TYPE_DYNAMIC, NULL, 0.f);
	m_pLayer->AddObject(pHitEffect, LAYER_TYPE_EFFECT);
	
	pTransformCom = (CTransformCom*)pHitEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + (rand() % 100 + 50.0f) * vRand;
	pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 1.f);
	pHitEffect->Initialize();

}

void CMonster::CreateAttack()
{
}

int CMonster::Attack()
{
	int iAtt = m_stat.iStrength;

	float fRand = (rand() % 1000) / 1000.0f;
	if(fRand < 0.5f)
		iAtt = int(iAtt * 1.5f);

	fRand = ((rand() % 400) - 200) / 1000.0f;
	return int(iAtt * (1.0f + fRand));
}

void CMonster::Death()
{
	RemoveComponent(COM_TYPE_COLLISION);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fDepth = 0.0f;
}

void CMonster::DisOver()
{
	// IsOver
	m_bIsOver = false;

	// RimColor
	m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	// Energy
	if(m_pEnergy != NULL)
	{
		m_pEnergy->Destroy();
		m_pEnergy = NULL;
	}
}

void CMonster::SetState(CMonsterState* _pState)
{
	if(m_pState != NULL)
		delete m_pState;

	m_pState = _pState;
	m_pState->SetOwner(this);
	m_pState->Initialize();
}

void CMonster::SetAnimation(int _iIndex)
{
	m_pAnimController->SetAnimation(_iIndex);
}

void CMonster::SetAnimationMode(int _iIndex)
{
	m_pDynamicMesh->m_pAnimController->SetAnimation(_iIndex);
}

void CMonster::RemoveAttack()
{
	CCollisionCom* pCollisionCom = (CCollisionCom*)m_pComponent[COM_TYPE_COLLISION];
	
	if(pCollisionCom == NULL)
		return;

	for(size_t i = 0; i < pCollisionCom->m_CollisionVec.size(); ++i)
	{
		if(pCollisionCom->m_CollisionVec[i]->dwType & COLLISION_ATTACK)
		{
			delete pCollisionCom->m_CollisionVec[i];
			pCollisionCom->m_CollisionVec[i] = pCollisionCom->m_CollisionVec[pCollisionCom->m_CollisionVec.size() - 1];
			pCollisionCom->m_CollisionVec.pop_back();
			--i;
		}
	}
}

void CMonster::Intersect(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst)
{
	// v
	D3DXVECTOR3 v[4];
	v[0] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
	v[1] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
	v[2] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
	v[3] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);

	// TransformCoord
	for(int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&v[i], &v[i], &m_pTransformCom->m_mWorld);

	// line
	CNaviLine line[4];
	line[0].Setup(&v[0], &v[1]);
	line[1].Setup(&v[1], &v[2]);
	line[2].Setup(&v[2], &v[3]);
	line[3].Setup(&v[3], &v[0]);

	// Move
	CNaviLine MoveLine;
	MoveLine.Setup(_pSrc, _pDst);

	// IntersectPoint
	D3DXVECTOR3 vIntersectPoint;

	for(int i = 0; i < 4; ++i)
	{
		if(line[i].Classify(&MoveLine, &vIntersectPoint) == LINE_CLASS_SEGMENT)
		{
			POINT_CLASS ePointClass = line[i].Classify(_pSrc);
			if(ePointClass == POINT_CLASS_ON_LINE || ePointClass == POINT_CLASS_LEFT_SIDE)
			{
				_pDst->x = vIntersectPoint.x;
				_pDst->z = vIntersectPoint.z;
				break;
			}
		}
	}
}

void CMonster::DropItem()
{
	// Find Player
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

	// Player
	CPlayer* pPlayer = (CPlayer*)pFindObject;

	int iRand = rand() % 13;
	DWORD dwItemType;
	if(iRand == 0)
		dwItemType = ITEM_TYPE_MAIN_WEAPON;
	else if(iRand == 1)
		dwItemType = ITEM_TYPE_HELMS;
	else if(iRand == 2)
		dwItemType = ITEM_TYPE_SHOULDERS;
	else if(iRand == 3)
		dwItemType = ITEM_TYPE_CHESTARMOR;
	else if(iRand == 4)
		dwItemType = ITEM_TYPE_BRACERS;
	else if(iRand == 5)
		dwItemType = ITEM_TYPE_GLOVES;
	else if(iRand == 6)
		dwItemType = ITEM_TYPE_BELT;
	else if(iRand == 7)
		dwItemType = ITEM_TYPE_PANTS;
	else if(iRand == 8)
		dwItemType = ITEM_TYPE_BOOTS;
	else if(iRand == 9)
		dwItemType = ITEM_TYPE_AMULET;
	else if(iRand == 10)
		dwItemType = ITEM_TYPE_RING;
	else if(iRand == 11)
		dwItemType = ITEM_TYPE_SUB_WEAPON;
	else if(iRand == 12)
		dwItemType = (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON);

	float fRand = (rand() % 1000) / 1000.0f;
	float fMagicProb = pPlayer->GetMagicItemsFound() - 1.0f;

	DWORD dwItemClass;
	if(fRand >= 0.99f - fMagicProb)
		dwItemClass = ITEM_CLASS_SET;
	else if(fRand >= 0.97f - fMagicProb)
		dwItemClass = ITEM_CLASS_LEGEND;
	else if(fRand >= 0.93f - fMagicProb)
		dwItemClass = ITEM_CLASS_UNIQUE;
	else if(fRand >= 0.85f - fMagicProb)
		dwItemClass = ITEM_CLASS_MAGIC;
	else
		dwItemClass = ITEM_CLASS_NORMAL;

	int iLevel = m_stat.iLevel + (rand() % 10 - 5);
	if(iLevel < 1)
		iLevel = 1;

	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, CItemMgr::GetInstance()->CreateItem(dwItemClass, dwItemType, 0, iLevel));
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}

void CMonster::DropGold()
{
	// Gold
	int iGold = rand() % 30 * m_stat.iLevel + 1;

	// Find Player
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
	if(pFindObject != NULL)
	{
		// Player
		CPlayer* pPlayer = (CPlayer*)pFindObject;
		iGold = int(iGold * 1.0f + pPlayer->GetDiscoveryOfGoldCoins());
	}

	TCHAR tszGold[MIN_STR];
	ZeroMemory(tszGold, sizeof(tszGold));
	StringCbPrintf(tszGold, sizeof(tszGold), _T("%d °ñµå"), iGold);

	Item* pGold = new Item(tszGold, _T("Item_Gold"), NULL, 0, ITEM_TYPE_GOLD, GOLD_ID_GOLD, -1, -1, 1, 1, -1, -1, iGold, -1, -1, -1);
	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, pGold);
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}