#include "StdAfx.h"
#include "Skeleton_ArrowEffect.h"

CSkeleton_ArrowEffect::CSkeleton_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Skeleton_Arrow"));
	AddComponent(pBufferCom);
	
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	AddComponent(pCollisionCom);
}

CSkeleton_ArrowEffect::~CSkeleton_ArrowEffect(void)
{
	Release();
}

void CSkeleton_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_vFirstPos = m_pTransformCom->m_vPos;
}

int CSkeleton_ArrowEffect::Update()
{
	CEffect::Update();

	if(D3DXVec3Length(&(m_vFirstPos - m_pTransformCom->m_vPos)) > 1000.0f)
		Destroy();
	
	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CSkeleton_ArrowEffect::Render()
{
	CEffect::Render();
}

void CSkeleton_ArrowEffect::Release()
{

}
