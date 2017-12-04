#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_ShadowEffect.h"

CMonk_WayOfTheHundredFists_ShadowEffect::CMonk_WayOfTheHundredFists_ShadowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WayOfTheHundredFists_Shadow"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
}

CMonk_WayOfTheHundredFists_ShadowEffect::~CMonk_WayOfTheHundredFists_ShadowEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_ShadowEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_WayOfTheHundredFists_ShadowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_WayOfTheHundredFists_ShadowEffect::Render()
{
	CEffect::Render();
}

void CMonk_WayOfTheHundredFists_ShadowEffect::Release()
{

}
