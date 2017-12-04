#include "StdAfx.h"
#include "Zombie_Skinny_Male_Scratch_A.h"

CZombie_Skinny_Male_Scratch_A::CZombie_Skinny_Male_Scratch_A(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos = *_pPos;

	// Time
	m_fTime = 0.0f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Skinny_Male_Scratch_A"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);
}

CZombie_Skinny_Male_Scratch_A::~CZombie_Skinny_Male_Scratch_A(void)
{
	Release();
}

void CZombie_Skinny_Male_Scratch_A::Initialize()
{
	CEffect::Initialize();
}

int CZombie_Skinny_Male_Scratch_A::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();
	
	return 0;
}

void CZombie_Skinny_Male_Scratch_A::Render()
{
	CEffect::Render();
}

void CZombie_Skinny_Male_Scratch_A::Release()
{

}