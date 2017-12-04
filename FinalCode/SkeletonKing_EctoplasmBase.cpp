#include "StdAfx.h"
#include "SkeletonKing_EctoplasmBase.h"

CSkeletonKing_EctoplasmBase::CSkeletonKing_EctoplasmBase(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("SkeletonKing_EctoplasmBase"));
	AddComponent(pMaterialCom);

}

CSkeletonKing_EctoplasmBase::~CSkeletonKing_EctoplasmBase(void)
{
	Release();
}

void CSkeletonKing_EctoplasmBase::Initialize()
{
	CEffect::Initialize();
}

int CSkeletonKing_EctoplasmBase::Update()
{
	CEffect::Update();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() * 2;
	
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

void CSkeletonKing_EctoplasmBase::Render()
{
	CEffect::Render();
}

void CSkeletonKing_EctoplasmBase::Release()
{

}
