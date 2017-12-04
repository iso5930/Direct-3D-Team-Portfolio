#include "StdAfx.h"
#include "HitEffect.h"

CHitEffect::CHitEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fCreateTime)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;
	m_fCreateTime = _fCreateTime;
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
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Hit"));
	AddComponent(pMaterialCom);
}

CHitEffect::~CHitEffect(void)
{
	Release();
}

void CHitEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 1.f;

	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}	

int CHitEffect::Update()
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

	case 2:
		Mode3();
		break;
	}

	return 0;
}

void CHitEffect::Render()
{
	CEffect::Render();
}

void CHitEffect::Release()
{

}

void CHitEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fCreateTime)
	{
		++m_iMode;
		m_fTime = 0.f;
		m_fAlpha = 0.f;
	}
}

void CHitEffect::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CHitEffect::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
	{
		Destroy();
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}