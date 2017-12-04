#include "StdAfx.h"
#include "Wizard_Disintegrate_FlashEffect.h"

CWizard_Disintegrate_FlashEffect::CWizard_Disintegrate_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Disintegrate_Flash"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

	m_iMode = 0;
	m_fTime = 0.f;
	m_fResetTime = 0.f;

	m_pCollisionCom = NULL;

	// Coef
	m_fCoef = 1.95f;
}

CWizard_Disintegrate_FlashEffect::~CWizard_Disintegrate_FlashEffect(void)
{
	Release();
}

void CWizard_Disintegrate_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
}

int CWizard_Disintegrate_FlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vAngle.z += D3DXToRadian(90.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	return 0;
}

void CWizard_Disintegrate_FlashEffect::Render()
{
	CEffect::Render();
}

void CWizard_Disintegrate_FlashEffect::Release()
{

}

void CWizard_Disintegrate_FlashEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(0.1f, 0.1f, 0.1f) * 200.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_Disintegrate_FlashEffect::Mode2()
{
	if(m_fTime >= 0.2f)
	{
		m_fTime = 0.f;
		--m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(0.1f, 0.1f, 0.1f) * 100.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_Disintegrate_FlashEffect::AddCollisionComponent()
{
	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(m_pCollisionCom);

	m_iMaxCnt = 10000;
}

void CWizard_Disintegrate_FlashEffect::ResetCollision()
{
	m_fResetTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fResetTime >= 0.5f)
	{
		m_fResetTime = 0.f;
		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}
}