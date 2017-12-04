#include "StdAfx.h"
#include "Wizard_Blizzard_DecalEffect.h"

CWizard_Blizzard_DecalEffect::CWizard_Blizzard_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_blizzard_splash"));
	AddComponent(pMaterialCom);
}

CWizard_Blizzard_DecalEffect::~CWizard_Blizzard_DecalEffect(void)
{
	Release();
}

void CWizard_Blizzard_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);
}

int CWizard_Blizzard_DecalEffect::Update()
{
	CEffect::Update();

	float fRand = float(rand() % 10) * 0.5f;

	m_fAlpha += fRand * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Blizzard_DecalEffect::Render()
{
	CEffect::Render();
}

void CWizard_Blizzard_DecalEffect::Release()
{

}
