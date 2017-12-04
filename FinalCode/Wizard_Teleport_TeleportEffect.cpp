#include "StdAfx.h"
#include "Wizard_Teleport_TeleportEffect.h"

CWizard_Teleport_TeleportEffect::CWizard_Teleport_TeleportEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;
	m_iMode = 0;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Teleport_Flash"));
	AddComponent(pMaterialCom);	
}

CWizard_Teleport_TeleportEffect::~CWizard_Teleport_TeleportEffect(void)
{
	Release();
}

void CWizard_Teleport_TeleportEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 250.f, 0.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CWizard_Teleport_TeleportEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.15f)
	{
		Destroy();
	}

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

void CWizard_Teleport_TeleportEffect::Render()
{
	CEffect::Render();
}

void CWizard_Teleport_TeleportEffect::Release()
{

}

void CWizard_Teleport_TeleportEffect::Mode1()
{
	if(m_fTime >= 0.05f)
	{
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 0.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_Teleport_TeleportEffect::Mode2()
{
	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 0.f, 0.f) * 500.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.x <= 0.f)
	{
		Destroy();
	}
}