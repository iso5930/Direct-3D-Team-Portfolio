#include "StdAfx.h"
#include "Monk_CripplingWave_Attack2DummyEffect.h"

CMonk_CripplingWave_Attack2DummyEffect::CMonk_CripplingWave_Attack2DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_iMode = 0;

	m_pTrailEffect = NULL;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 110.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 110.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 1.55f;
}

CMonk_CripplingWave_Attack2DummyEffect::~CMonk_CripplingWave_Attack2DummyEffect(void)
{	
	Release();
}

void CMonk_CripplingWave_Attack2DummyEffect::Initialize()
{
	CEffect::Initialize();	
}

int CMonk_CripplingWave_Attack2DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_mWorld = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;

	case 2:
		Mode3();
		break;
	}

	return 0;
}

void CMonk_CripplingWave_Attack2DummyEffect::Render()
{
	CEffect::Render();
}

void CMonk_CripplingWave_Attack2DummyEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}	
}

void CMonk_CripplingWave_Attack2DummyEffect::Mode1()
{

	if(m_fTime >= 0.2f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}
}

void CMonk_CripplingWave_Attack2DummyEffect::Mode2()
{
	(CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	ZeroMemory(&m_Bone, sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	m_Bone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	m_Bone.mWorld = m_Bone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	//»ý¼º
	m_pTrailEffect = new CMonk_CripplingWave_Attack2TrailEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_Bone.mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	++m_iMode;
}

void CMonk_CripplingWave_Attack2DummyEffect::Mode3()
{
	(CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	ZeroMemory(&m_Bone, sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	m_Bone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	m_Bone.mWorld = m_Bone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	if(m_fTime >= 0.25f)
	{
		Destroy();
	}
}