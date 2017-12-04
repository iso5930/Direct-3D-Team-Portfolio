#include "StdAfx.h"
#include "Wizard_StormArmor_LightningEffect.h"

CWizard_StormArmor_LightningEffect::CWizard_StormArmor_LightningEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	m_Frame.fFrameTime = 0.1f;

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
}

CWizard_StormArmor_LightningEffect::~CWizard_StormArmor_LightningEffect(void)
{
	Release();
}

void CWizard_StormArmor_LightningEffect::Initialize()
{
	CEffect::Initialize();

	m_Frame.iCur = rand() % (m_Frame.iEnd + 1);

	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 1.f);

	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CWizard_StormArmor_LightningEffect::Update()
{
	CEffect::Update();

	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		Destroy();
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	return 0;
}

void CWizard_StormArmor_LightningEffect::Render()
{
	CEffect::Render();
}

void CWizard_StormArmor_LightningEffect::Release()
{

}
