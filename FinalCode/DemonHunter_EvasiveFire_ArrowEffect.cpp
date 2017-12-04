#include "StdAfx.h"
#include "DemonHunter_EvasiveFire_ArrowEffect.h"

CDemonHunter_EvasiveFire_ArrowEffect::CDemonHunter_EvasiveFire_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_EvasiveFire"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
	m_fTime = 0.f;
}

CDemonHunter_EvasiveFire_ArrowEffect::~CDemonHunter_EvasiveFire_ArrowEffect(void)
{
	Release();
}

void CDemonHunter_EvasiveFire_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(120.f, 240.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CDemonHunter_EvasiveFire_ArrowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}
 
 	D3DXMATRIX matTrans, matScale, matRotate, matTest;
 	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
 	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);
 	MatrixRotation(&matRotate, m_pTransformCom->m_vAngle.x, m_pTransformCom->m_vAngle.y, m_pTransformCom->m_vAngle.z);
	D3DXMatrixTranslation(&matTest, 0.f, -150.f, 0.f);
 
 	m_pTransformCom->m_mWorld = matScale * matTest * matRotate * matTrans;

	return 0;
}

void CDemonHunter_EvasiveFire_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_EvasiveFire_ArrowEffect::Release()
{

}

void CDemonHunter_EvasiveFire_ArrowEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 0.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CDemonHunter_EvasiveFire_ArrowEffect::Mode2()
{
	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 0.f, 0.f) * 500.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.x <= 0.f)
	{
		Destroy();
	}
}