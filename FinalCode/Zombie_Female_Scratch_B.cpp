#include "StdAfx.h"
#include "Zombie_Female_Scratch_B.h"

CZombie_Female_Scratch_B::CZombie_Female_Scratch_B(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos = *_pPos;

	// Time
	m_fTime = 0.0f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Female_Scratch_B"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);
}

CZombie_Female_Scratch_B::~CZombie_Female_Scratch_B(void)
{
	Release();
}

void CZombie_Female_Scratch_B::Initialize()
{
	CEffect::Initialize();
}

int CZombie_Female_Scratch_B::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CZombie_Female_Scratch_B::Render()
{
	CEffect::Render();
}

void CZombie_Female_Scratch_B::Release()
{

}
