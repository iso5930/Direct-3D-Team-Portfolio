#include "StdAfx.h"
#include "SkeletonKing_SummonShell.h"

CSkeletonKing_SummonShell::CSkeletonKing_SummonShell(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fSize = 0.f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("SkeletonKing_TeleportShell"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);
}

CSkeletonKing_SummonShell::~CSkeletonKing_SummonShell(void)
{
	Release();
}

void CSkeletonKing_SummonShell::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 1.0f;
}

int CSkeletonKing_SummonShell::Update()
{
	CEffect::Update();

	m_fAlpha -= CTimeMgr::GetInstance()->GetDeltaTime() / 4.f;

	m_fSize += CTimeMgr::GetInstance()->GetDeltaTime() / 2.f;

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.f - m_fSize, 1.f, 1.f - m_fSize);

	if(m_fAlpha < 0.5f)
		Destroy();

	return 0;	
}

void CSkeletonKing_SummonShell::Render()
{
	CEffect::Render();
}

void CSkeletonKing_SummonShell::Release()
{

}