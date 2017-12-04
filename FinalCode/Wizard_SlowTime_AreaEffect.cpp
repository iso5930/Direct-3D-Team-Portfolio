#include "StdAfx.h"
#include "Wizard_SlowTime_AreaEffect.h"

CWizard_SlowTime_AreaEffect::CWizard_SlowTime_AreaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SlowTime"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
}

CWizard_SlowTime_AreaEffect::~CWizard_SlowTime_AreaEffect(void)
{
	Release();
}

void CWizard_SlowTime_AreaEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.9f;
}

int CWizard_SlowTime_AreaEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 10.f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_SlowTime_AreaEffect::Render()
{
	CEffect::Render();
}

void CWizard_SlowTime_AreaEffect::Release()
{

}