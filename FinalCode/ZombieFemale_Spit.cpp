#include "StdAfx.h"
#include "ZombieFemale_Spit.h"

CZombieFemale_Spit::CZombieFemale_Spit(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
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

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("ZombieFemale_Spit"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	AddComponent(pCollisionCom);
	
}

CZombieFemale_Spit::~CZombieFemale_Spit(void)
{
	Release();
}

void CZombieFemale_Spit::Initialize()
{
	CEffect::Initialize();
	
	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 50.f);

	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.0f);

	m_vFirstPos = m_pTransformCom->m_vPos;

}

int CZombieFemale_Spit::Update()
{
	CEffect::Update();

	if(D3DXVec3Length(&(m_vFirstPos - m_pTransformCom->m_vPos)) > 1500.0f)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CZombieFemale_Spit::Render()
{
	CEffect::Render();
}

void CZombieFemale_Spit::Release()
{

}