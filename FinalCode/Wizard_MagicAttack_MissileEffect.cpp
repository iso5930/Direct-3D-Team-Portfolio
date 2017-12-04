#include "StdAfx.h"
#include "Wizard_MagicAttack_MissileEffect.h"

CWizard_MagicAttack_MissileEffect::CWizard_MagicAttack_MissileEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = (*_pDir);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_StormArmor_Flash"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_fTime = 0.f;
	m_fModeTime = 0.f;
	m_iMode = 0;
}		

CWizard_MagicAttack_MissileEffect::~CWizard_MagicAttack_MissileEffect(void)
{
	Release();
}

void CWizard_MagicAttack_MissileEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(20.f, 20.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CWizard_MagicAttack_MissileEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fModeTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 3.f)
	{
		Destroy();
	}

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

void CWizard_MagicAttack_MissileEffect::Render()
{
	CEffect::Render();
}

void CWizard_MagicAttack_MissileEffect::Release()
{

}

void CWizard_MagicAttack_MissileEffect::Destroy()
{
	CEffect::Destroy();
}

void CWizard_MagicAttack_MissileEffect::Mode1()
{
	if(m_fModeTime >= 0.1f)
	{
		m_fModeTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_MagicAttack_MissileEffect::Mode2()
{
	if(m_fModeTime >= 0.1f)
	{
		m_fModeTime = 0.f;
		--m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}
