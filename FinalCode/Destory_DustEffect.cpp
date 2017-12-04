#include "StdAfx.h"
#include "Destory_DustEffect.h"

CDestory_DustEffect::CDestory_DustEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust5")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust6")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust7")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust8")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust9")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Destory_Dust10")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 10;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.05f;

	//BufferCom
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

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);
}

CDestory_DustEffect::~CDestory_DustEffect(void)
{
	Release();
}

void CDestory_DustEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
}

int CDestory_DustEffect::Update()
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

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);

	/*
	D3DXMATRIX matBill = *CCameraMgr::GetInstance()->GetBillBoard();

	D3DXMATRIX matTrans, matScale, matRotate;
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);
	MatrixRotation(&matRotate, m_pTransformCom->m_vAngle.x, m_pTransformCom->m_vAngle.y, m_pTransformCom->m_vAngle.z);

	m_pTransformCom->m_mWorld = matScale * matRotate * matBill * matTrans;
	*/

	return 0;
}	

void CDestory_DustEffect::Render()
{	
	CEffect::Render();
}

void CDestory_DustEffect::Release()
{
	
}