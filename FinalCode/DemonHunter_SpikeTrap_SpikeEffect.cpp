#include "StdAfx.h"
#include "DemonHunter_SpikeTrap_SpikeEffect.h"

CDemonHunter_SpikeTrap_SpikeEffect::CDemonHunter_SpikeTrap_SpikeEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Grenade"));
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

CDemonHunter_SpikeTrap_SpikeEffect::~CDemonHunter_SpikeTrap_SpikeEffect(void)
{
	Release();
}

void CDemonHunter_SpikeTrap_SpikeEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
}

int CDemonHunter_SpikeTrap_SpikeEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 10.f)
		Destroy();
	
	return 0;
}

void CDemonHunter_SpikeTrap_SpikeEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_SpikeTrap_SpikeEffect::Release()
{

}