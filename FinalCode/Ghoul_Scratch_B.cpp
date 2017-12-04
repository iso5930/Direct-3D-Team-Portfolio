#include "StdAfx.h"
#include "Ghoul_Scratch_B.h"

CGhoul_Scratch_B::CGhoul_Scratch_B(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Pos
	m_pTransformCom->m_vPos = *_pPos;

	// Time
	m_fTime = 0.0f;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.8f, 0.8f, 0.8f);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Ghoul_Scratch_B"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

}

CGhoul_Scratch_B::~CGhoul_Scratch_B(void)
{
	Release();
}

void CGhoul_Scratch_B::Initialize()
{
	CEffect::Initialize();
}

int CGhoul_Scratch_B::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CGhoul_Scratch_B::Render()
{
	CEffect::Render();
}

void CGhoul_Scratch_B::Release()
{

}