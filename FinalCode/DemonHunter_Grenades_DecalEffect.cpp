#include "StdAfx.h"
#include "DemonHunter_Grenades_DecalEffect.h"

CDemonHunter_Grenades_DecalEffect::CDemonHunter_Grenades_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 4;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_FanOfKnives_Decal")); //이거 바닥에 붙이는거 찾아야함...
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_Grenades_DecalEffect::~CDemonHunter_Grenades_DecalEffect(void)
{
	Release();
}

void CDemonHunter_Grenades_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);
}

int CDemonHunter_Grenades_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.6f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_Grenades_DecalEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Grenades_DecalEffect::Release()
{

}