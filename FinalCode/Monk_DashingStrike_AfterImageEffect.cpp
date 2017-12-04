#include "StdAfx.h"
#include "Monk_DashingStrike_AfterImageEffect.h"

CMonk_DashingStrike_AfterImageEffect::CMonk_DashingStrike_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SevenSidedStrike"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 14;
	AddComponent(pRenderCom);

	m_fAlpha = 0.5f;
	m_fTime = 0.f;
}

CMonk_DashingStrike_AfterImageEffect::~CMonk_DashingStrike_AfterImageEffect(void)
{
	Release();
}

void CMonk_DashingStrike_AfterImageEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_DashingStrike_AfterImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
		Destroy();

	return 0;
}

void CMonk_DashingStrike_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CMonk_DashingStrike_AfterImageEffect::Release()
{

}
