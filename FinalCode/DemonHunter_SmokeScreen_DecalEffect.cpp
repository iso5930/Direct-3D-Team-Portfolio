#include "StdAfx.h"
#include "DemonHunter_SmokeScreen_DecalEffect.h"

CDemonHunter_SmokeScreen_DecalEffect::CDemonHunter_SmokeScreen_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Grenades_Decal"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_SmokeScreen_DecalEffect::~CDemonHunter_SmokeScreen_DecalEffect(void)
{
	Release();
}

void CDemonHunter_SmokeScreen_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);
}

int CDemonHunter_SmokeScreen_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_SmokeScreen_DecalEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SmokeScreen_DecalEffect::Release()
{

}