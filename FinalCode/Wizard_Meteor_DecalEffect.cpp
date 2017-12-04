#include "StdAfx.h"
#include "Wizard_Meteor_DecalEffect.h"

CWizard_Meteor_DecalEffect::CWizard_Meteor_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Meteor_Decal"));
	AddComponent(pMaterialCom);

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f));
	AddComponent(m_pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;
	m_fDemageTime = 0.f;

	// Coef
	m_fCoef = 1.175f;
}

CWizard_Meteor_DecalEffect::~CWizard_Meteor_DecalEffect(void)
{
	Release();
}

void CWizard_Meteor_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);

	m_fAlpha = 0.3f;
}

int CWizard_Meteor_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fDemageTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 3.f)
	{
		Destroy(); 
	}

	if(m_fDemageTime >= 0.5f)
	{
		m_fDemageTime = 0.f;
		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}

	return 0;
}

void CWizard_Meteor_DecalEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_DecalEffect::Release()
{

}
