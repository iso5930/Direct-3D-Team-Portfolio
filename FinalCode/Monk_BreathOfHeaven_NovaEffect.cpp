#include "StdAfx.h"
#include "Monk_BreathOfHeaven_NovaEffect.h"

CMonk_BreathOfHeaven_NovaEffect::CMonk_BreathOfHeaven_NovaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_HealingNova"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 17;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_BreathOfHeaven_Alpha"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CMonk_BreathOfHeaven_NovaEffect::~CMonk_BreathOfHeaven_NovaEffect(void)
{
	Release();
}

void CMonk_BreathOfHeaven_NovaEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CMonk_BreathOfHeaven_NovaEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 20.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.4f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_BreathOfHeaven_NovaEffect::Render()
{
	CEffect::Render();
}

void CMonk_BreathOfHeaven_NovaEffect::Release()
{

}
