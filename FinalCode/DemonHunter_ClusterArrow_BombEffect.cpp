#include "StdAfx.h"
#include "DemonHunter_ClusterArrow_BombEffect.h"

CDemonHunter_ClusterArrow_BombEffect::CDemonHunter_ClusterArrow_BombEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Cluster_Decal"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_ClusterArrow_BombEffect::~CDemonHunter_ClusterArrow_BombEffect(void)
{
	Release();
}

void CDemonHunter_ClusterArrow_BombEffect::Initialize()
{
	CEffect::Initialize();

	//m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 1.f);
	//m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CDemonHunter_ClusterArrow_BombEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAlpha += CTimeMgr::GetInstance()->GetDeltaTime() * 6.f;
	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_ClusterArrow_BombEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_ClusterArrow_BombEffect::Release()
{

}