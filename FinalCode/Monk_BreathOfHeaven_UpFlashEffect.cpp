#include "StdAfx.h"
#include "Monk_BreathOfHeaven_UpFlashEffect.h"

CMonk_BreathOfHeaven_UpFlashEffect::CMonk_BreathOfHeaven_UpFlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_BreathOfHeaven_UpFlash"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
}

CMonk_BreathOfHeaven_UpFlashEffect::~CMonk_BreathOfHeaven_UpFlashEffect(void)
{
	Release();
}

void CMonk_BreathOfHeaven_UpFlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(30.f, 300.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CMonk_BreathOfHeaven_UpFlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

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

void CMonk_BreathOfHeaven_UpFlashEffect::Render()
{
	CEffect::Render();
}

void CMonk_BreathOfHeaven_UpFlashEffect::Release()
{

}

void CMonk_BreathOfHeaven_UpFlashEffect::Mode1()
{
	if(m_fTime >= 0.2f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 0.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_BreathOfHeaven_UpFlashEffect::Mode2()
{
	if(m_fTime >= 0.2f)
	{
		Destroy();
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 0.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}