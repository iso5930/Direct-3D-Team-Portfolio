#include "StdAfx.h"
#include "Wizard_Blizzard_IceEffect.h"

CWizard_Blizzard_IceEffect::CWizard_Blizzard_IceEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fDestY)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Blizzard"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	m_fTime = 0.f;

	m_vDir = (*_pDir);

	m_fDestY = _fDestY;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 65.0f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 1.79f;
}

CWizard_Blizzard_IceEffect::~CWizard_Blizzard_IceEffect(void)
{
	Release();
}

void CWizard_Blizzard_IceEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(3.f, 3.f, 3.f);
}

int CWizard_Blizzard_IceEffect::Update()
{
	CEffect::Update();

	if(m_pTransformCom->m_vPos.y <= m_fDestY + 80.f)
	{
		Destroy();

		CWizard_Blizzard_DestoryEffect* pEffect = new CWizard_Blizzard_DestoryEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pEffect->Initialize();

		CWizard_Blizzard_DecalEffect* pDecalEffect = new CWizard_Blizzard_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pDecalEffect->Initialize();
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_Blizzard_IceEffect::Render()
{
	CEffect::Render();
}

void CWizard_Blizzard_IceEffect::Release()
{

}