#include "StdAfx.h"
#include "DemonHunter_SpikeTrap_DecalEffect.h"

CDemonHunter_SpikeTrap_DecalEffect::CDemonHunter_SpikeTrap_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
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
	m_iPrevHate = 0;
}

CDemonHunter_SpikeTrap_DecalEffect::~CDemonHunter_SpikeTrap_DecalEffect(void)
{
	Release();
}	

void CDemonHunter_SpikeTrap_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(250.f, 250.f, 250.f);
}

int CDemonHunter_SpikeTrap_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 10.f)
	{
		Destroy();
	}
	
	return 0;
}

void CDemonHunter_SpikeTrap_DecalEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SpikeTrap_DecalEffect::Release()
{

}