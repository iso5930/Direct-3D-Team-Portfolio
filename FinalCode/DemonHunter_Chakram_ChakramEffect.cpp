#include "StdAfx.h"
#include "DemonHunter_Chakram_ChakramEffect.h"

CDemonHunter_Chakram_ChakramEffect::CDemonHunter_Chakram_ChakramEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{	
	m_pWorld = _pWorld;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Chakram"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 3.8f;
}

CDemonHunter_Chakram_ChakramEffect::~CDemonHunter_Chakram_ChakramEffect(void)
{
	Release();
}

void CDemonHunter_Chakram_ChakramEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	m_pTransformCom->m_vPos.x = 50.f;
	m_pTransformCom->m_vPos.z = 50.f;
}

int CDemonHunter_Chakram_ChakramEffect::Update()
{
	m_pTransformCom->m_vAngle.y += D3DXToRadian(360.f) * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos += D3DXVECTOR3(1.f, 0.f, 1.f) * 50.f * CTimeMgr::GetInstance()->GetDeltaTime();

	CEffect::Update();

	m_pTransformCom->m_mWorld *= (*m_pWorld);

	return 0;
}

void CDemonHunter_Chakram_ChakramEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Chakram_ChakramEffect::Release()
{	

}