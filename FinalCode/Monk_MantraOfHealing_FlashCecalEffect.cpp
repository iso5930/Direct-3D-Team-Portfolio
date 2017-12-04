#include "StdAfx.h"
#include "Monk_MantraOfHealing_FlashCecalEffect.h"

CMonk_MantraOfHealing_FlashCecalEffect::CMonk_MantraOfHealing_FlashCecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 7;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_MantraOfHealing_DecalGlow"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
}

CMonk_MantraOfHealing_FlashCecalEffect::~CMonk_MantraOfHealing_FlashCecalEffect(void)
{
	Release();
}

void CMonk_MantraOfHealing_FlashCecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CMonk_MantraOfHealing_FlashCecalEffect::Update()
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

void CMonk_MantraOfHealing_FlashCecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_MantraOfHealing_FlashCecalEffect::Release()
{

}

void CMonk_MantraOfHealing_FlashCecalEffect::Mode1()
{
	if(m_fAlpha <= 0.f)
	{
		++m_iMode;
	}

	m_fAlpha -= 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_MantraOfHealing_FlashCecalEffect::Mode2()
{
	if(m_fAlpha >= 0.4f)
	{
		--m_iMode;
	}

	m_fAlpha += 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}