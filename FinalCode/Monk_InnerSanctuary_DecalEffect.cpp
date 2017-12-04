#include "StdAfx.h"
#include "Monk_InnerSanctuary_DecalEffect.h"

CMonk_InnerSanctuary_DecalEffect::CMonk_InnerSanctuary_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_InnerSanctuary_Decal"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
}

CMonk_InnerSanctuary_DecalEffect::~CMonk_InnerSanctuary_DecalEffect(void)
{
	Release();
}

void CMonk_InnerSanctuary_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(350.f, 350.f, 350.f);
}

int CMonk_InnerSanctuary_DecalEffect::Update()
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

void CMonk_InnerSanctuary_DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_InnerSanctuary_DecalEffect::Release()
{

}

void CMonk_InnerSanctuary_DecalEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 5.f)
		++m_iMode;
}

void CMonk_InnerSanctuary_DecalEffect::Mode2()
{
	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
	{
		Destroy();
	}
}