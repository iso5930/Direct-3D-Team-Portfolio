#include "StdAfx.h"
#include "SkeletonSummoner_ArcaneBall.h"

CSkeletonSummoner_ArcaneBall::CSkeletonSummoner_ArcaneBall(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("SkeletonSummoner_ArcaneBall"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);
	
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	AddComponent(pCollisionCom);
}

CSkeletonSummoner_ArcaneBall::~CSkeletonSummoner_ArcaneBall(void)
{
	Release();
}

void CSkeletonSummoner_ArcaneBall::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
	m_vFirstPos = m_pTransformCom->m_vPos;
}

int CSkeletonSummoner_ArcaneBall::Update()
{
	CEffect::Update();

	
	if(D3DXVec3Length(&(m_vFirstPos - m_pTransformCom->m_vPos)) > 1000.f)
		Destroy();

	m_pTransformCom->m_vAngle.z += D3DXToRadian(45.f) * 10 * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CSkeletonSummoner_ArcaneBall::Render()
{	
	CEffect::Render();
}

void CSkeletonSummoner_ArcaneBall::Release()
{

}
