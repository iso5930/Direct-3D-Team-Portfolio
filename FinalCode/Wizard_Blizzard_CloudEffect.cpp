#include "StdAfx.h"
#include "Wizard_Blizzard_CloudEffect.h"

CWizard_Blizzard_CloudEffect::CWizard_Blizzard_CloudEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Blizzard_Cloud"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 14;
	AddComponent(pRenderCom);

	m_vDir = _vDir;
	m_fTime = 0.f;
}

CWizard_Blizzard_CloudEffect::~CWizard_Blizzard_CloudEffect(void)
{
	Release();
}

void CWizard_Blizzard_CloudEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.1f;
}

int CWizard_Blizzard_CloudEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_Blizzard_CloudEffect::Render()
{
	CEffect::Render();
}

void CWizard_Blizzard_CloudEffect::Release()
{

}
