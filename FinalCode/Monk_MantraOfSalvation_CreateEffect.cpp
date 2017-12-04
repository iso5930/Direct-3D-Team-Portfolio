#include "StdAfx.h"
#include "Monk_MantraOfSalvation_CreateEffect.h"

CMonk_MantraOfSalvation_CreateEffect::CMonk_MantraOfSalvation_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Salvation_Nova"));
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

CMonk_MantraOfSalvation_CreateEffect::~CMonk_MantraOfSalvation_CreateEffect(void)
{
	Release();
}

void CMonk_MantraOfSalvation_CreateEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
}

int CMonk_MantraOfSalvation_CreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 3.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.25f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_MantraOfSalvation_CreateEffect::Render()
{
	CEffect::Render();
}

void CMonk_MantraOfSalvation_CreateEffect::Release()
{

}
