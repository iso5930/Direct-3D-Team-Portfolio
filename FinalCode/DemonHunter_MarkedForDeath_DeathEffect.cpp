#include "StdAfx.h"
#include "DemonHunter_MarkedForDeath_DeathEffect.h"

CDemonHunter_MarkedForDeath_DeathEffect::CDemonHunter_MarkedForDeath_DeathEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{	
	m_fTime = 0.f;
	m_pWorld = _pWorld;

	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_MarkedForDeath"));
	AddComponent(pMaterialCom);
}

CDemonHunter_MarkedForDeath_DeathEffect::~CDemonHunter_MarkedForDeath_DeathEffect(void)
{
	Release();
}

void CDemonHunter_MarkedForDeath_DeathEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 1.f);
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.f, 120.f, 0.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(45.f);
}

int CDemonHunter_MarkedForDeath_DeathEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 30.f)
		Destroy();

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	matTrans._41 = m_pWorld->_41;
	matTrans._42 = m_pWorld->_42;
	matTrans._43 = m_pWorld->_43;

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * matTrans;

	return 0;
}

void CDemonHunter_MarkedForDeath_DeathEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_MarkedForDeath_DeathEffect::Release()
{

}
