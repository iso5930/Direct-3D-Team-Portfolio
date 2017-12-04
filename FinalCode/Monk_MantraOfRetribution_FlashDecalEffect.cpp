#include "StdAfx.h"
#include "Monk_MantraOfRetribution_FlashDecalEffect.h"

CMonk_MantraOfRetribution_FlashDecalEffect::CMonk_MantraOfRetribution_FlashDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_MantraOfRetribution_DecalGlow"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
}

CMonk_MantraOfRetribution_FlashDecalEffect::~CMonk_MantraOfRetribution_FlashDecalEffect(void)
{
	Release();
}

void CMonk_MantraOfRetribution_FlashDecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CMonk_MantraOfRetribution_FlashDecalEffect::Update()
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

	m_pTransformCom->m_vAngle.y += D3DXToRadian(60.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
	m_pTransformCom->m_mWorld *= pTransformCom->m_mTrans;

	return 0;
}

void CMonk_MantraOfRetribution_FlashDecalEffect::Render()
{
	CEffect::Render();	
}

void CMonk_MantraOfRetribution_FlashDecalEffect::Release()
{

}

void CMonk_MantraOfRetribution_FlashDecalEffect::Mode1()
{
	if(m_pTransformCom->m_vSize.x <= 100.f)
	{
		++m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 0.f, 1.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_MantraOfRetribution_FlashDecalEffect::Mode2()
{
	if(m_pTransformCom->m_vSize.x >= 200.f)
	{
		--m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 0.f, 1.f) * 70.f * CTimeMgr::GetInstance()->GetDeltaTime();
}