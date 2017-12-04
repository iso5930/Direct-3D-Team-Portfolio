#include "StdAfx.h"
#include "Monk_WaveOfLight_StaffEffect.h"

CMonk_WaveOfLight_StaffEffect::CMonk_WaveOfLight_StaffEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_TempestRush_Staff"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
}	

CMonk_WaveOfLight_StaffEffect::~CMonk_WaveOfLight_StaffEffect(void)
{
	Release();
}

void CMonk_WaveOfLight_StaffEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_WaveOfLight_StaffEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 1.f)
	{
		Destroy();
	}

	Bone tBone;
	ZeroMemory(&tBone, sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	tBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	tBone.mWorld = tBone.pFrame->mCombinedMatrix * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	m_pTransformCom->m_mWorld *= tBone.mWorld;

	return 0;
}

void CMonk_WaveOfLight_StaffEffect::Render()
{		
	CEffect::Render();
}

void CMonk_WaveOfLight_StaffEffect::Release()
{

}
