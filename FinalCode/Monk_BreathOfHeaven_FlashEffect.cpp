#include "StdAfx.h"
#include "Monk_BreathOfHeaven_FlashEffect.h"

CMonk_BreathOfHeaven_FlashEffect::CMonk_BreathOfHeaven_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;
	m_iMode = 0;
	m_fAccTime = 0.f;

	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_BreathOfHeaven_Flash0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_BreathOfHeaven_Flash1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_BreathOfHeaven_Flash2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_BreathOfHeaven_Flash3")));

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
}

CMonk_BreathOfHeaven_FlashEffect::~CMonk_BreathOfHeaven_FlashEffect(void)
{
	Release();
}

void CMonk_BreathOfHeaven_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CMonk_BreathOfHeaven_FlashEffect::Update()
{
	CEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAccTime += fTime;
	m_fTime += fTime;
	m_Frame.fAccTime += fTime;

	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.f;
		if(++m_Frame.iCur >= m_Frame.iEnd)
		{
			m_Frame.iCur = m_Frame.iStart;
		}
	}

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	if(m_fAccTime >= 0.4f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_BreathOfHeaven_FlashEffect::Render()
{	
	CEffect::Render();
}

void CMonk_BreathOfHeaven_FlashEffect::Release()
{

}

void CMonk_BreathOfHeaven_FlashEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_BreathOfHeaven_FlashEffect::Mode2()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		--m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}