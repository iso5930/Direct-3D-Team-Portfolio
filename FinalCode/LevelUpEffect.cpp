#include "StdAfx.h"
#include "LevelUpEffect.h"

CLevelUpEffect::CLevelUpEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CEffect(_tszObjKey, _eObjType, NULL)
{
	// Texture
	m_pTextureArr[0] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_0"));
	m_pTextureArr[1] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_1"));
	m_pTextureArr[2] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_2"));
	m_pTextureArr[3] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_3"));
	m_pTextureArr[4] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_4"));
	m_pTextureArr[5] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_5"));
	m_pTextureArr[6] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_6"));
	m_pTextureArr[7] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_7"));
	m_pTextureArr[8] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_8"));
	m_pTextureArr[9] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_9"));
	m_pTextureArr[10] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_10"));
	m_pTextureArr[11] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_11"));
	m_pTextureArr[12] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_12"));
	m_pTextureArr[13] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_13"));
	m_pTextureArr[14] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_14"));
	m_pTextureArr[15] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_15"));
	m_pTextureArr[16] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_16"));
	m_pTextureArr[17] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_17"));
	m_pTextureArr[18] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_18"));
	m_pTextureArr[19] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_19"));
	m_pTextureArr[20] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_20"));
	m_pTextureArr[21] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_21"));
	m_pTextureArr[22] = CTextureMgr::GetInstance()->GetTexture(_T("Effect_LevelUp_22"));

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 5;
	AddComponent(pRenderCom);

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	m_pMaterialCom->m_pTexture = m_pTextureArr[0];
	AddComponent(m_pMaterialCom);

	// Frame
	m_Frame.iEnd = 22;
	m_Frame.fFrameTime = 0.05f;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(150.0f, 180.0f, 0.0f);
}

CLevelUpEffect::~CLevelUpEffect()
{
	Release();
}

void CLevelUpEffect::Initialize()
{
	CEffect::Initialize();
}

int CLevelUpEffect::Update()
{
	CEffect::Update();

	// Frame
	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_Frame.fAccTime > m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.0f;

		if(++m_Frame.iCur > m_Frame.iEnd)
			Destroy();

		m_pMaterialCom->m_pTexture = m_pTextureArr[m_Frame.iCur];
	}

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);
	//D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetViewProj());

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
		m_pTransformCom->m_vPos = pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	}

	return 0;
}

void CLevelUpEffect::Render()
{
	CEffect::Render();
}

void CLevelUpEffect::Release()
{
}