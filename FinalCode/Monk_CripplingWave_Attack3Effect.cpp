#include "StdAfx.h"
#include "Monk_CripplingWave_Attack3Effect.h"

CMonk_CripplingWave_Attack3Effect::CMonk_CripplingWave_Attack3Effect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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

CMonk_CripplingWave_Attack3Effect::~CMonk_CripplingWave_Attack3Effect(void)
{
	Release();
}

void CMonk_CripplingWave_Attack3Effect::Initialize()
{		
	CEffect::Initialize();
}

int CMonk_CripplingWave_Attack3Effect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_CripplingWave_Attack3Effect::Render()
{	
	CEffect::Render();
}

void CMonk_CripplingWave_Attack3Effect::Release()
{

}
