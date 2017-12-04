#include "StdAfx.h"
#include "Monk_CripplingWave_Attack2DecalEffect.h"

CMonk_CripplingWave_Attack2DecalEffect::CMonk_CripplingWave_Attack2DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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

CMonk_CripplingWave_Attack2DecalEffect::~CMonk_CripplingWave_Attack2DecalEffect(void)
{
	Release();
}

void CMonk_CripplingWave_Attack2DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 150.f);

	m_fAlpha = 0.3f;
}

int CMonk_CripplingWave_Attack2DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_CripplingWave_Attack2DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_CripplingWave_Attack2DecalEffect::Release()
{

}
