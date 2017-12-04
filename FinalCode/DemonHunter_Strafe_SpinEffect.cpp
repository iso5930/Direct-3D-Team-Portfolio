#include "StdAfx.h"
#include "DemonHunter_Strafe_SpinEffect.h"

CDemonHunter_Strafe_SpinEffect::CDemonHunter_Strafe_SpinEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_pWorld = _pWorld;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Strafe_Spin"));
	AddComponent(pMaterialCom);
}

CDemonHunter_Strafe_SpinEffect::~CDemonHunter_Strafe_SpinEffect(void)
{
	Release();
}

void CDemonHunter_Strafe_SpinEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vPos = D3DXVECTOR3(0.f, 100.f, 0.f);
	m_pTransformCom->m_vSize = D3DXVECTOR3(250.f, 250.f, 250.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CDemonHunter_Strafe_SpinEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vAngle.y += D3DXToRadian(360.f) * 20.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * (*m_pWorld);

	return 0;
}

void CDemonHunter_Strafe_SpinEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Strafe_SpinEffect::Release()
{

}