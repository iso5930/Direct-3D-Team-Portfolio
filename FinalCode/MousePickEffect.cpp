#include "StdAfx.h"
#include "MousePickEffect.h"

CMousePickEffect::CMousePickEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CEffect(_tszObjKey, _eObjType, NULL)
{
	// Texture
	m_pTextureArr[0] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_0"));
	m_pTextureArr[1] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_1"));
	m_pTextureArr[2] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_2"));
	m_pTextureArr[3] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_3"));
	m_pTextureArr[4] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_4"));
	m_pTextureArr[5] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_5"));
	m_pTextureArr[6] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_6"));
	m_pTextureArr[7] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_7"));
	m_pTextureArr[8] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_8"));
	m_pTextureArr[9] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_9"));
	m_pTextureArr[10] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_10"));
	m_pTextureArr[11] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_11"));
	m_pTextureArr[12] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_12"));
	m_pTextureArr[13] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_13"));
	m_pTextureArr[14] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_14"));
	m_pTextureArr[15] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_15"));
	m_pTextureArr[16] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_16"));
	m_pTextureArr[17] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_17"));
	m_pTextureArr[18] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_18"));
	m_pTextureArr[19] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_MousePick_19"));

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4;
	AddComponent(pRenderCom);

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	m_pMaterialCom->m_pTexture = m_pTextureArr[0];
	AddComponent(m_pMaterialCom);

	// Frame
	m_Frame.iEnd = 19;
	m_Frame.fFrameTime = 0.01f;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(50.0f, 100.0f, 50.0f);
}

CMousePickEffect::~CMousePickEffect()
{
	Release();
}

void CMousePickEffect::Initialize()
{
	CEffect::Initialize();
}

int CMousePickEffect::Update()
{
	CEffect::Update();

	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_Frame.fAccTime > m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.0f;
		
		if(++m_Frame.iCur > m_Frame.iEnd)
			Destroy();

		m_pMaterialCom->m_pTexture = m_pTextureArr[m_Frame.iCur];
	}

	return 0;
}

void CMousePickEffect::Render()
{
	CEffect::Render();
}

void CMousePickEffect::Release()
{
}