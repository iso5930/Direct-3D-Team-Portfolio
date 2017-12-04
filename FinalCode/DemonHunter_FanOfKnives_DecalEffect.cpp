#include "StdAfx.h"
#include "DemonHunter_FanOfKnives_DecalEffect.h"

CDemonHunter_FanOfKnives_DecalEffect::CDemonHunter_FanOfKnives_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_FanOfKnives_Decal"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_FanOfKnives_DecalEffect::~CDemonHunter_FanOfKnives_DecalEffect(void)
{
	Release();
}

void CDemonHunter_FanOfKnives_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(500.f, 500.f, 500.f);
}

int CDemonHunter_FanOfKnives_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.6f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_FanOfKnives_DecalEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_FanOfKnives_DecalEffect::Release()
{

}