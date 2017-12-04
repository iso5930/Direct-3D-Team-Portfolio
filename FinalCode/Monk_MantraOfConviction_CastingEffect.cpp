#include "StdAfx.h"
#include "Monk_MantraOfConviction_CastingEffect.h"

CMonk_MantraOfConviction_CastingEffect::CMonk_MantraOfConviction_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	m_fAlpha = 0.f;
	m_iMode = 0;
}

CMonk_MantraOfConviction_CastingEffect::~CMonk_MantraOfConviction_CastingEffect(void)
{
	Release();
}

void CMonk_MantraOfConviction_CastingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize.x = 30.f;
}

int CMonk_MantraOfConviction_CastingEffect::Update()
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

void CMonk_MantraOfConviction_CastingEffect::Render()
{
	CEffect::Render();
}

void CMonk_MantraOfConviction_CastingEffect::Release()
{

}

void CMonk_MantraOfConviction_CastingEffect::Mode1()
{
	if(m_fTime >= 0.2f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	D3DXVECTOR3 vDeltaSize = D3DXVECTOR3(0.f, 1.f, 0.f) * 300.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += vDeltaSize;
	m_pTransformCom->m_vPos.y += D3DXVec3Length(&vDeltaSize) / 2.f; 
}

void CMonk_MantraOfConviction_CastingEffect::Mode2()
{
	if(m_fTime >= 0.2f)
	{	
		Destroy();
	}

	D3DXVECTOR3 vDeltaSize = D3DXVECTOR3(0.f, 1.f, 0.f) * 300.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize -= vDeltaSize;
	m_pTransformCom->m_vPos.y -= D3DXVec3Length(&vDeltaSize) / 2.f; 
}