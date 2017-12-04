#include "StdAfx.h"
#include "SkeletonKing_TeleportShell.h"

CSkeletonKing_TeleportShell::CSkeletonKing_TeleportShell(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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

CSkeletonKing_TeleportShell::~CSkeletonKing_TeleportShell(void)
{
	Release();
}

void CSkeletonKing_TeleportShell::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

	m_fAlpha = 0.2f;
}

int CSkeletonKing_TeleportShell::Update()
{
	CEffect::Update();

	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime();// / 2.f;
	
	m_fSize += CTimeMgr::GetInstance()->GetDeltaTime() * 2;

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.5f - m_fSize, 1.5f, 1.5f - m_fSize);

	if(m_fAlpha > 1.f)
		Destroy();

	return 0;
}

void CSkeletonKing_TeleportShell::Render()
{
	CEffect::Render();
}

void CSkeletonKing_TeleportShell::Release()
{

}

