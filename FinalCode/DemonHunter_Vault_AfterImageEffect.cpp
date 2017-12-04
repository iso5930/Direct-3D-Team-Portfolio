#include "StdAfx.h"
#include "DemonHunter_Vault_AfterImageEffect.h"

CDemonHunter_Vault_AfterImageEffect::CDemonHunter_Vault_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	m_pBufferCom = new CBufferCom;
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Boots"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hair"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Hands"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Pants"));
	m_pBufferCom->AddBuffer(_T("DemonHunter_Female_Base_Upper"));
	AddComponent(m_pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 10;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
}

CDemonHunter_Vault_AfterImageEffect::~CDemonHunter_Vault_AfterImageEffect(void)
{
	Release();
}

void CDemonHunter_Vault_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	CBufferCom* pBufferCom = ((CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER));
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_dTrackPos = pDynamicMesh->m_pAnimController->GetTrackPos();
	
	for(size_t i = 0; i < m_pBufferCom->m_BufferVec.size(); ++i)
	{
		((CDynamicMesh*)(m_pBufferCom->m_BufferVec[i]))->m_pAnimController->SetAnimation(34);
	}
}	

int CDemonHunter_Vault_AfterImageEffect::Update()
{
	CEffect::Update();

	for(size_t i = 0; i < m_pBufferCom->m_BufferVec.size(); ++i)
	{
		((CDynamicMesh*)(m_pBufferCom->m_BufferVec[i]))->m_pAnimController->SetTrackPos(m_dTrackPos);
	}

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_Vault_AfterImageEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_Vault_AfterImageEffect::Release()
{

}