#include "StdAfx.h"
#include "Warden_Entangle.h"

CWarden_Entangle::CWarden_Entangle(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = *_pDir;
	m_fTime = 0.f;
	m_iMode = 0;
	m_fSizeChangeTime = 0.f;

	
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Warden_Entangle"));
	AddComponent(pMaterialCom);
}

CWarden_Entangle::~CWarden_Entangle(void)
{
	Release();
}

void CWarden_Entangle::Initialize()
{
	CEffect::Initialize();
}

int CWarden_Entangle::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAlpha = m_fTime / 2.f;
	m_fSizeChangeTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime > 2.f)
		Destroy();

	switch(m_iMode)
	{
	case 0 :
		Mode0();
		break;

	case 1 :
		Mode1();
		break;
	}
		
	return 0;
}

void CWarden_Entangle::Render()
{
	CEffect::Render();
}

void CWarden_Entangle::Release()
{

}

void CWarden_Entangle::Mode0()
{
	float fDeltaSizeY = 0.5f * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vSize.y += fDeltaSizeY;
	m_pTransformCom->m_vPos.y += fDeltaSizeY / 2.f;
	
	if(m_fSizeChangeTime > 0.2f)
	{
		m_fSizeChangeTime = 0.0f;
		++m_iMode;
	}
}

void CWarden_Entangle::Mode1()
{
	float fDeltaSizeY = 0.5f * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vSize.y -= fDeltaSizeY;
	m_pTransformCom->m_vPos.y -= fDeltaSizeY / 2.f;

	if(m_fSizeChangeTime > 0.2f)
	{
		m_fSizeChangeTime = 0.0f;
		--m_iMode;
	}
}

