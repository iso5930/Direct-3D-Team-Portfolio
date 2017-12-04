#include "StdAfx.h"
#include "Wizard_Meteor_MeteorEffect.h"

CWizard_Meteor_MeteorEffect::CWizard_Meteor_MeteorEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, D3DXVECTOR3 _vDestPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;
	m_vDestPos = _vDestPos;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Meteor"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 7.4f;
}

CWizard_Meteor_MeteorEffect::~CWizard_Meteor_MeteorEffect(void)
{
	Release();
}

void CWizard_Meteor_MeteorEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
}

int CWizard_Meteor_MeteorEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir, &m_vDir);

	D3DXVECTOR3 vDestDir = m_vDestPos - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&vDestDir, &vDestDir);
	
	float fDot = D3DXVec3Dot(&vDir, &vDestDir);

	if(fDot == -1)
	{
		Destroy();

		CWizard_Meteor_DecalEffect* pDecalEffect = new CWizard_Meteor_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pDecalEffect->Initialize();


		CWizard_Meteor_DecalGlowEffect* pDecalGlowEffect = new CWizard_Meteor_DecalGlowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDecalGlowEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDecalGlowEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pDecalGlowEffect->Initialize();

		CWizard_Meteor_DestoryEffect* pDestoryEffect = new CWizard_Meteor_DestoryEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDestoryEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDestoryEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
		pDestoryEffect->Initialize();
	}

	return 0;
}

void CWizard_Meteor_MeteorEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_MeteorEffect::Release()
{

}
