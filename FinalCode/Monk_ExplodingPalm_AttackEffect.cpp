#include "StdAfx.h"
#include "Monk_ExplodingPalm_AttackEffect.h"

CMonk_ExplodingPalm_AttackEffect::CMonk_ExplodingPalm_AttackEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_CripplingWave_Attack3"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 21;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_CripplingWave_Attack3_Alpha"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CMonk_ExplodingPalm_AttackEffect::~CMonk_ExplodingPalm_AttackEffect(void)
{
	Release();
}

void CMonk_ExplodingPalm_AttackEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CMonk_ExplodingPalm_AttackEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_ExplodingPalm_AttackEffect::Render()
{
	CEffect::Render();
}

void CMonk_ExplodingPalm_AttackEffect::Release()
{

}
