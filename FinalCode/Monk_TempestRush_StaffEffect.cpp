#include "StdAfx.h"
#include "Monk_TempestRush_StaffEffect.h"

CMonk_TempestRush_StaffEffect::CMonk_TempestRush_StaffEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_TempestRush_Staff"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	m_pTrailEffect = NULL;
	m_pTrailEffect2 = NULL;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f));
	AddComponent(m_pCollisionCom);

	m_iMaxCnt = 99999;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 1.33f;
}

CMonk_TempestRush_StaffEffect::~CMonk_TempestRush_StaffEffect(void)
{
	Release();
}

void CMonk_TempestRush_StaffEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CMonk_TempsetRush_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	m_pTrailEffect2 = new CMonk_TempsetRush_DownTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect2, LAYER_TYPE_EFFECT);
	m_pTrailEffect2->Initialize();
}

int CMonk_TempestRush_StaffEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		m_fTime = 0.f;
		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}

	Bone tBone;
	ZeroMemory(&tBone, sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	tBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	tBone.mWorld = tBone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	m_pTransformCom->m_mWorld *= tBone.mWorld;

	return 0;
}

void CMonk_TempestRush_StaffEffect::Render()
{
	CEffect::Render();
}

void CMonk_TempestRush_StaffEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}

	if(m_pTrailEffect2 != NULL)
	{
		m_pTrailEffect2->Destroy();
		m_pTrailEffect2 = NULL;
	}
}