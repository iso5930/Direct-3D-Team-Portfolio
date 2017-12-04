#include "StdAfx.h"
#include "ZombieFemale_PukeBase.h"

CZombieFemale_PukeBase::CZombieFemale_PukeBase(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = *_pDir;

	// BufferCom 
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);

	//
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("ZombieFemale_PukeBase"));
	AddComponent(pMaterialCom);
}

CZombieFemale_PukeBase::~CZombieFemale_PukeBase(void)
{
	Release();
}

void CZombieFemale_PukeBase::Initialize()
{
	CEffect::Initialize();
}

int CZombieFemale_PukeBase::Update()
{
	CEffect::Update();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() / 5;

	m_pTransformCom->m_vPos -= m_vDir * 2;

	m_pTransformCom->m_vPos.y -= CTimeMgr::GetInstance()->GetDeltaTime() * 80;

	if(m_fAlpha > 1.f)
		Destroy();

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);

	/*
	D3DXMATRIX matBill = *CCameraMgr::GetInstance()->GetBillBoard();

	D3DXMATRIX matTrans, matScale;
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);

	m_pTransformCom->m_mWorld = matScale * matBill * matTrans;
	*/

	return 0;
}

void CZombieFemale_PukeBase::Render()
{
	CEffect::Render();
}

void CZombieFemale_PukeBase::Release()
{

}
