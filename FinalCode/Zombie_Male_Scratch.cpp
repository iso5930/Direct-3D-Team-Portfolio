#include "StdAfx.h"
#include "Zombie_Male_Scratch.h"

CZombie_Male_Scratch::CZombie_Male_Scratch(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos = *_pPos;

	// Time
	m_fTime = 0.0f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Male_Scratch"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);
}

CZombie_Male_Scratch::~CZombie_Male_Scratch(void)
{
	Release();
}

void CZombie_Male_Scratch::Initialize()
{
	CEffect::Initialize();
}

int CZombie_Male_Scratch::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CZombie_Male_Scratch::Render()
{
	CEffect::Render();
}

void CZombie_Male_Scratch::Release()
{

}

