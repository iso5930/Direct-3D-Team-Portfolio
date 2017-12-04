#include "StdAfx.h"
#include "SkeletonKing_WeaponTrail.h"

CSkeletonKing_WeaponTrail::CSkeletonKing_WeaponTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("SkeletonKing_WeaponTrail"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);
}

CSkeletonKing_WeaponTrail::~CSkeletonKing_WeaponTrail(void)
{
}

void CSkeletonKing_WeaponTrail::Initialize()
{
	CEffect::Initialize();
}

int CSkeletonKing_WeaponTrail::Update()
{
	CEffect::Update();

	//m_pTransformCom->m_vAngle.y += D3DXToRadian(45.f) * 10 * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha > 1.f)
		Destroy();

	return 0;
}

void CSkeletonKing_WeaponTrail::Render()
{
	CEffect::Render();
}

void CSkeletonKing_WeaponTrail::Release()
{

}
