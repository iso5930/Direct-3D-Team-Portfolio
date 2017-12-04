#include "StdAfx.h"
#include "Monk_MantraOfConviction_DecalEffect.h"

CMonk_MantraOfConviction_DecalEffect::CMonk_MantraOfConviction_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 4; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_MantraOfConviction_Decal"));
	AddComponent(pMaterialCom);
}

CMonk_MantraOfConviction_DecalEffect::~CMonk_MantraOfConviction_DecalEffect(void)
{
	Release();
}

void CMonk_MantraOfConviction_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CMonk_MantraOfConviction_DecalEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vAngle.y += D3DXToRadian(60.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
	m_pTransformCom->m_mWorld *= pTransformCom->m_mTrans;

	return 0;
}

void CMonk_MantraOfConviction_DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_MantraOfConviction_DecalEffect::Release()
{

}