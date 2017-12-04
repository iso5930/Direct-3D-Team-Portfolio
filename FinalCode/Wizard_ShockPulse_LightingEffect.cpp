#include "StdAfx.h"
#include "Wizard_ShockPulse_LightingEffect.h"

CWizard_ShockPulse_LightingEffect::CWizard_ShockPulse_LightingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning5")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning6")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_StormArmor_Lightning7")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 7;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.05f;

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);

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

	m_fTime = 0.f;
}

CWizard_ShockPulse_LightingEffect::~CWizard_ShockPulse_LightingEffect(void)
{
	Release();
}

void CWizard_ShockPulse_LightingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_Frame.iCur = rand() % (m_Frame.iEnd + 1);
	m_pTransformCom->m_vPos.y += 5.f;
}

int CWizard_ShockPulse_LightingEffect::Update()
{
	CEffect::Update();

	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 200.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.x <= 0.f)
	{
		Destroy();
	}
	
	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.f;

		m_Frame.iCur = rand() % (m_Frame.iEnd + 1);
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	return 0;
}

void CWizard_ShockPulse_LightingEffect::Render()
{
	CEffect::Render();
}

void CWizard_ShockPulse_LightingEffect::Release()
{

}
