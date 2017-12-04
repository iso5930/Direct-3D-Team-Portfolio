#include "StdAfx.h"
#include "ZombieFemale_PukeDummy.h"

CZombieFemale_PukeDummy::CZombieFemale_PukeDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f));
	AddComponent(pCollisionCom);

	m_fDestroyTime = 0.0f;
	m_fEffectTime = 0.0f;
	m_fDecalTime = 0.0f;
	m_bCreate = false;
}	

CZombieFemale_PukeDummy::~CZombieFemale_PukeDummy(void)
{
	Release();
}

void CZombieFemale_PukeDummy::Initialize()
{
	CEffect::Initialize();
}

int CZombieFemale_PukeDummy::Update()
{
	CEffect::Update();

	m_fEffectTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fDestroyTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fDestroyTime > 0.5f)
		m_fDecalTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectTime > 0.005f)
	{
		int iRand = rand() % 10 + 10;

		CZombieFemale_PukeBase* pPukeBase = new CZombieFemale_PukeBase(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_vDir);
		m_pOwner->GetLayer()->AddObject(pPukeBase, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pPukeBase->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CZombie_Female*)m_pOwner)->m_JawBone.mWorld);		
		pTransformCom->m_vSize = D3DXVECTOR3((float)iRand, (float)iRand, (float)iRand);
		pPukeBase->Initialize();
		m_fEffectTime = 0.0f;
	}

	if(m_fDecalTime > 0.05f)
	{
		int iRand = rand() % 20 + 50;

		CZombieFemale_PukeGroundDecal* pPukeDecal = new CZombieFemale_PukeGroundDecal(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pPukeDecal, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pPukeDecal->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CZombie_Female*)m_pOwner)->m_PukeGroundBone.mWorld);		
		pTransformCom->m_vSize = D3DXVECTOR3((float)iRand, (float)iRand, (float)iRand);
		pPukeDecal->Initialize();
	}	

	if(m_fDestroyTime > 1.f && !m_bCreate)
	{
		CZombie_Skinny_Male_White* pMonster = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, ((CMonster*)m_pOwner)->GetStat()->iLevel);
		m_pOwner->GetLayer()->AddObject(pMonster, LAYER_TYPE_MONSTER);
		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos - (m_vDir * 85.f);

		pMonster->Initialize();
		pMonster->SetState(new CZombie_Skinny_Male_White_Spawn);
		m_bCreate = true;
	}

	if(m_fDestroyTime > 1.518f)
	{
		Destroy();
	}

	return 0;
}

void CZombieFemale_PukeDummy::Render()
{
	CEffect::Render();
}

void CZombieFemale_PukeDummy::Release()
{

}
