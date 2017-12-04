#include "StdAfx.h"
#include "Wizard_ArcaneOrb_OrbEffect.h"

CWizard_ArcaneOrb_OrbEffect::CWizard_ArcaneOrb_OrbEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;

	for(int i = 0; i < 4; ++i)
	{
		m_pGalaxyEffect[i] = NULL;
	}

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Arcane_Orb"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);
	
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 4.35f;
}

CWizard_ArcaneOrb_OrbEffect::~CWizard_ArcaneOrb_OrbEffect(void)
{
	Release();
}

void CWizard_ArcaneOrb_OrbEffect::Initialize()
{
	CEffect::Initialize();

	for(int i = 0; i < 4; ++i)
	{
		m_pGalaxyEffect[i] = new CWizard_ArcaneOrb_GalaxyEffect(NULL, OBJ_TYPE_DYNAMIC, this);
		m_pLayer->AddObject(m_pGalaxyEffect[i], LAYER_TYPE_EFFECT);

		CTransformCom* pTrnasformCom = (CTransformCom*)m_pGalaxyEffect[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTrnasformCom->m_vAngle.y = D3DXToRadian(float(i * 90.f));
		m_pGalaxyEffect[i]->Initialize();
	}

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CWizard_ArcaneOrb_OrbEffect::Update()
{	
	CEffect::Update();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_ArcaneOrb_OrbEffect::Render()
{
	CEffect::Render();
}

void CWizard_ArcaneOrb_OrbEffect::Release()
{
	for(int i = 0; i < 4; ++i)
	{
		if(m_pGalaxyEffect[i] != NULL)
		{
			m_pGalaxyEffect[i]->Destroy();
			m_pGalaxyEffect[i] = NULL;
		}	
	}
}

void CWizard_ArcaneOrb_OrbEffect::Destroy()
{
	CEffect::Destroy();

	CWizard_ArcaneOrb_DestoryEffect* pDestoryEffect = new CWizard_ArcaneOrb_DestoryEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pDestoryEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDestoryEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDestoryEffect->Initialize();
}