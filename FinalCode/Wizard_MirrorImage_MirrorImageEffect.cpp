#include "StdAfx.h"
#include "Wizard_MirrorImage_MirrorImageEffect.h"

CWizard_MirrorImage_MirrorImageEffect::CWizard_MirrorImage_MirrorImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	m_pBufferCom = new CBufferCom;
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Boots"));
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Hair"));
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Hands"));
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Pants"));
	m_pBufferCom->AddBuffer(_T("Wizard_Female_Base_Upper"));
	AddComponent(m_pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 11;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
	m_iMode = 0;
}

CWizard_MirrorImage_MirrorImageEffect::~CWizard_MirrorImage_MirrorImageEffect(void)
{
	Release();
}

void CWizard_MirrorImage_MirrorImageEffect::Initialize()
{
	CEffect::Initialize();

	for(size_t i = 0; i < m_pBufferCom->m_BufferVec.size(); ++i)
	{
		((CDynamicMesh*)(m_pBufferCom->m_BufferVec[i]))->m_pAnimController->SetAnimation(0);
	}
}

int CWizard_MirrorImage_MirrorImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 15.f)
	{
		Destroy();
	}

	switch(m_iMode)
	{
	case 0:
		break;

	case 1:
		break;
	}

	return 0;
}

void CWizard_MirrorImage_MirrorImageEffect::Render()
{
	CEffect::Render();
}

void CWizard_MirrorImage_MirrorImageEffect::Release()
{

}
