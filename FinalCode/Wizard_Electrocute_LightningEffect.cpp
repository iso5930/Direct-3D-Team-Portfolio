#include "StdAfx.h"
#include "Wizard_Electrocute_LightningEffect.h"

CWizard_Electrocute_LightningEffect::CWizard_Electrocute_LightningEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Lightning_Strike_Blue0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Lightning_Strike_Blue1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Lightning_Strike_Blue2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Lightning_Strike_Blue3")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 3;
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

CWizard_Electrocute_LightningEffect::~CWizard_Electrocute_LightningEffect(void)
{
	Release();
}

void CWizard_Electrocute_LightningEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize.x = 200.f;

	int iRand = rand() % 4;
	m_Frame.iCur = iRand;
}

int CWizard_Electrocute_LightningEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.05f)
	{
		Destroy();
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	return 0;
}

void CWizard_Electrocute_LightningEffect::Render()
{
	CEffect::Render();
}

void CWizard_Electrocute_LightningEffect::Release()
{

}
