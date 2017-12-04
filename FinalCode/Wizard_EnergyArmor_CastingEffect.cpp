#include "StdAfx.h"
#include "Wizard_EnergyArmor_CastingEffect.h"

CWizard_EnergyArmor_CastingEffect::CWizard_EnergyArmor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting5")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_EnergyArmor_BuffCasting6")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 6;
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
}

CWizard_EnergyArmor_CastingEffect::~CWizard_EnergyArmor_CastingEffect(void)
{
	Release();
}

void CWizard_EnergyArmor_CastingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CWizard_EnergyArmor_CastingEffect::Update()
{
	CEffect::Update();

	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.f;

		if(++m_Frame.iCur > m_Frame.iEnd)
		{
			m_Frame.iCur = m_Frame.iStart;

			Destroy();
		}
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	return 0;
}

void CWizard_EnergyArmor_CastingEffect::Render()
{	
	CEffect::Render();
}

void CWizard_EnergyArmor_CastingEffect::Release()
{

}
