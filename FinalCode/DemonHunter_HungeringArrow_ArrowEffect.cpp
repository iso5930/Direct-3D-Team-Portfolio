#include "StdAfx.h"
#include "DemonHunter_HungeringArrow_ArrowEffect.h"

CDemonHunter_HungeringArrow_ArrowEffect::CDemonHunter_HungeringArrow_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Arrow0"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_fTime = 0.f;

	// Coef
	m_fCoef = 1.55f;
}

CDemonHunter_HungeringArrow_ArrowEffect::~CDemonHunter_HungeringArrow_ArrowEffect(void)
{	
	Release();
}

void CDemonHunter_HungeringArrow_ArrowEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_HungeringArrow_ArrowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.05f)
	{
		m_fTime = 0.f;

		CDemonHunter_HungeringArrow_AfterImageEffect* pEffect = new CDemonHunter_HungeringArrow_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y - D3DXToRadian(90.f);
		pEffect->Initialize();
	}

	return 0;
}

void CDemonHunter_HungeringArrow_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_HungeringArrow_ArrowEffect::Release()
{

}