#include "StdAfx.h"
#include "Monk_MantraOfHealing_NovaEffect.h"

CMonk_MantraOfHealing_NovaEffect::CMonk_MantraOfHealing_NovaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
	m_fAlpha = 0.5f;
}

CMonk_MantraOfHealing_NovaEffect::~CMonk_MantraOfHealing_NovaEffect(void)
{
	Release();
}

void CMonk_MantraOfHealing_NovaEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
}

int CMonk_MantraOfHealing_NovaEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 10.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_MantraOfHealing_NovaEffect::Render()
{
	CEffect::Render();
}

void CMonk_MantraOfHealing_NovaEffect::Release()
{

}
