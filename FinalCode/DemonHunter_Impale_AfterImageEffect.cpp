#include "StdAfx.h"
#include "DemonHunter_Impale_AfterImageEffect.h"

CDemonHunter_Impale_AfterImageEffect::CDemonHunter_Impale_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vAxis, float _fAngle)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vAxis = _vAxis;
	m_fAngle = _fAngle;
	m_fTime = 0.f;
	
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Impale_Knife"));
	AddComponent(pMaterialCom);
}

CDemonHunter_Impale_AfterImageEffect::~CDemonHunter_Impale_AfterImageEffect(void)
{
	Release();
}

void CDemonHunter_Impale_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 50.f);
}

int CDemonHunter_Impale_AfterImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
		Destroy();

	D3DXMATRIX matScale, matRotate, matAxis, matTrans;
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	MatrixRotation(&matRotate, m_pTransformCom->m_vAngle.x, m_pTransformCom->m_vAngle.y, m_pTransformCom->m_vAngle.z);
	D3DXMatrixRotationAxis(&matAxis, &m_vAxis, m_fAngle);

	m_pTransformCom->m_mWorld = matScale * matRotate * matAxis * matTrans;

	return 0;
}

void CDemonHunter_Impale_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Impale_AfterImageEffect::Release()
{

}