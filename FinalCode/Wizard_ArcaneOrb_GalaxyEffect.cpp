#include "StdAfx.h"
#include "Wizard_ArcaneOrb_GalaxyEffect.h"

CWizard_ArcaneOrb_GalaxyEffect::CWizard_ArcaneOrb_GalaxyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//3개의 텍스쳐를 합성....
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Arcane_galaxy_Diff")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Arcane_galaxy_Alpha")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Arcane_galaxy_Blend")));
	
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 20; //합성패스
	AddComponent(pRenderCom);
}

CWizard_ArcaneOrb_GalaxyEffect::~CWizard_ArcaneOrb_GalaxyEffect(void)
{
	Release();
}

void CWizard_ArcaneOrb_GalaxyEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(250.f, 250.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CWizard_ArcaneOrb_GalaxyEffect::Update()
{
	m_pTransformCom->m_vPos = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos;

	CEffect::Update();

	m_pTransformCom->m_vAngle.y += D3DXToRadian(60.f) * 10.f * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_ArcaneOrb_GalaxyEffect::Render()
{
	CEffect::Render();
}

void CWizard_ArcaneOrb_GalaxyEffect::Release()
{

}