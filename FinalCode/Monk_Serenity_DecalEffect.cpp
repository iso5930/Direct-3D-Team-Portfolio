#include "StdAfx.h"
#include "Monk_Serenity_DecalEffect.h"

CMonk_Serenity_DecalEffect::CMonk_Serenity_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 7; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Serenity_Decal"));
	AddComponent(pMaterialCom);
}

CMonk_Serenity_DecalEffect::~CMonk_Serenity_DecalEffect(void)
{
	Release();
}

void CMonk_Serenity_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);

	m_fAlpha = 0.f;
}

int CMonk_Serenity_DecalEffect::Update()
{
	CEffect::Update();
	
	m_fAlpha += 1.5f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(300.f, 0.f, 300.f) * CTimeMgr::GetInstance()->GetDeltaTime();	

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CMonk_Serenity_DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_Serenity_DecalEffect::Release()
{

}
