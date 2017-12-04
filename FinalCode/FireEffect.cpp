#include "StdAfx.h"
#include "FireEffect.h"

CFireEffect::CFireEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _tszDiff, TCHAR* _tszAlpha, TCHAR* _tszNoise)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_tszDiff));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_tszNoise));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_tszAlpha));

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 23; //합성패스
	AddComponent(pRenderCom);
}

CFireEffect::~CFireEffect(void)
{
	Release();
}

void CFireEffect::Initialize()
{
	CEffect::Initialize();
}

int CFireEffect::Update()
{
	CEffect::Update();

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);

	return 0;
}

void CFireEffect::Render()
{
	CEffect::Render();
}

void CFireEffect::Release()
{
}