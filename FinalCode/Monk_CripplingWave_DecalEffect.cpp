#include "StdAfx.h"
#include "Monk_CripplingWave_DecalEffect.h"

CMonk_CripplingWave_DecalEffect::CMonk_CripplingWave_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_CripplingWave_Decal"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CMonk_CripplingWave_DecalEffect::~CMonk_CripplingWave_DecalEffect(void)
{
	Release();
}

void CMonk_CripplingWave_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.2f;

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);
}

int CMonk_CripplingWave_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_CripplingWave_DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_CripplingWave_DecalEffect::Release()
{

}
