#include "StdAfx.h"
#include "SkeletonKing_CenterTrail.h"

CSkeletonKing_CenterTrail::CSkeletonKing_CenterTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("SkeletonKing_CenterTrail"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);
}

CSkeletonKing_CenterTrail::~CSkeletonKing_CenterTrail(void)
{
	Release();
}

void CSkeletonKing_CenterTrail::Initialize()
{
	CEffect::Initialize();
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
	m_fAlpha = 0.0f;
}

int CSkeletonKing_CenterTrail::Update()
{
	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() / 4.f;
	
	//D3DXVec3TransformCoord(&m_pTransformCom->m_vPos, &m_pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterBone.mWorld);

	m_pTransformCom->m_vAngle.y += D3DXToRadian(45.f) * 4 * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha > 0.5)
		Destroy();

	CEffect::Update();

	return 0;
}

void CSkeletonKing_CenterTrail::Render()
{
	CEffect::Render();
}

void CSkeletonKing_CenterTrail::Release()
{

}
