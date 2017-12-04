#include "StdAfx.h"
#include "Vessel_TransformEffect.h"

CVessel_TransformEffect::CVessel_TransformEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, int _iTextureNumber)
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

	
	if(_iTextureNumber == 0)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Vessel_Transform0"));
		AddComponent(pMaterialCom);
	}

	if(_iTextureNumber == 1)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Vessel_Transform1"));
		AddComponent(pMaterialCom);		
	}

	if(_iTextureNumber == 2)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Vessel_Transform2"));
		AddComponent(pMaterialCom);		
	}

	if(_iTextureNumber == 3)
	{
		CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Vessel_Transform3"));
		AddComponent(pMaterialCom);		
	}
}

CVessel_TransformEffect::~CVessel_TransformEffect(void)
{
	Release();
}

void CVessel_TransformEffect::Initialize()
{
	CEffect::Initialize();
}

int CVessel_TransformEffect::Update()
{
	CEffect::Update();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos.y += CTimeMgr::GetInstance()->GetDeltaTime() * 10;

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

void CVessel_TransformEffect::Render()
{
	CEffect::Render();
}

void CVessel_TransformEffect::Release()
{

}
