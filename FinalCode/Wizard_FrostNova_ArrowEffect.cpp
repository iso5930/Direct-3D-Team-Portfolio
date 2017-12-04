#include "StdAfx.h"
#include "Wizard_FrostNova_ArrowEffect.h"

CWizard_FrostNova_ArrowEffect::CWizard_FrostNova_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fDelayTime)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_NovaArrow"));
	AddComponent(pMaterialCom);

	m_vDir = (*_pDir);

	m_fTime = 0.f;
	m_fDelayTime = _fDelayTime;

	m_iMode = 0;
}

CWizard_FrostNova_ArrowEffect::~CWizard_FrostNova_ArrowEffect(void)
{
	Release();
}

void CWizard_FrostNova_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_pTransformCom->m_vSize = D3DXVECTOR3(40.f, 80.f, 1.f);
}

int CWizard_FrostNova_ArrowEffect::Update()
{
	CEffect::Update();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	return 0;
}

void CWizard_FrostNova_ArrowEffect::Render()
{
	CEffect::Render();
}

void CWizard_FrostNova_ArrowEffect::Release()
{

}

void CWizard_FrostNova_ArrowEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fDelayTime)
	{
		m_fTime = 0.f;
		++m_iMode;
	}
}

void CWizard_FrostNova_ArrowEffect::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();


	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();
}