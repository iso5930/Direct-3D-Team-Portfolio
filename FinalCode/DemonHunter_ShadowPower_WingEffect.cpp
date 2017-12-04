#include "StdAfx.h"
#include "DemonHunter_ShadowPower_WingEffect.h"

CDemonHunter_ShadowPower_WingEffect::CDemonHunter_ShadowPower_WingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_pWorld = _pWorld;
	m_fTime = 0.f;
	m_fAccTime = 0.f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_ShadowPower_Wing"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 9;
	AddComponent(pRenderCom);
}

CDemonHunter_ShadowPower_WingEffect::~CDemonHunter_ShadowPower_WingEffect(void)
{
	Release();
}

void CDemonHunter_ShadowPower_WingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vPos = D3DXVECTOR3(0.f, -10.f, -20.f);
}

int CDemonHunter_ShadowPower_WingEffect::Update()
{
	CEffect::Update();

	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 5.f)
	{
		Destroy();
	}

	Bone WingBone;
	ZeroMemory(&WingBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	WingBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spine3");
	WingBone.mWorld = WingBone.pFrame->mCombinedMatrix * (*m_pWorld);

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * WingBone.mWorld;

	return 0;
}

void CDemonHunter_ShadowPower_WingEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_ShadowPower_WingEffect::Release()
{

}