#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_Teleport.h"

CWizard_Female_1HS_Orb_Teleport::CWizard_Female_1HS_Orb_Teleport(void)
{
	m_eStateType = 	STATE_TYPE_WIZARD_FEMALE_1HS_ORB_TELEPORT;

	// Time
	m_fTiem = 0.f ;

	// Mode
	m_iMode = 0 ;

}

CWizard_Female_1HS_Orb_Teleport::~CWizard_Female_1HS_Orb_Teleport(void)
{
	m_pOwner->SetAnimationMode(0);
}


void CWizard_Female_1HS_Orb_Teleport::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(49);

	// Clear
	m_pPathFindCom->Clear();

	// ModeDir
	ZeroMemory(m_vModeDir , sizeof(D3DXVECTOR3));

	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			m_vModeDist =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			m_vModeDist = D3DXVECTOR3(0.f, 1.f , 0.f );
		}	
		else
			m_vModeDist = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
		m_vModeDist = pTransformCom->m_vPos;
	}

	m_vModeDist = m_vModeDist - m_pTransformCom->m_vPos;

	D3DXVec3Normalize(&m_vModeDir, &m_vModeDist);
}

CPlayerState* CWizard_Female_1HS_Orb_Teleport::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();

	case 2:
		return Mode2();
	}

	return NULL;
}


CPlayerState* CWizard_Female_1HS_Orb_Teleport::Mode0()
{
	if (m_pAnimController->m_dFrameTime - 0.033 < m_pAnimController->GetTrackPos())
	{
		m_pOwner->SetAnimationMode(2);
		++m_iMode;
	}

	return NULL;
}

CPlayerState* CWizard_Female_1HS_Orb_Teleport::Mode1()
{
	++m_iMode;

	float fLeagth = D3DXVec3Length(&m_vModeDist);

	if(fLeagth > 500.f)
	{
		fLeagth = 500.f; 
	}

	vector<CObject*> pFindObjects;
	CDynamicProb* pDynamicProb;
	CStaticProb* pStaticProb;
	CNaviCell* pNextCell;

	D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + (m_vModeDir * fLeagth);

	m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);
	for(size_t i = 0; i < pFindObjects.size(); ++i)
	{
		pDynamicProb = (CDynamicProb*)pFindObjects[i];

		pDynamicProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
		m_pTransformCom->m_vPos = vNextPos;
		m_pPathFindCom->m_pCell = pNextCell;

	}
	pFindObjects.clear();

	m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);
	for(size_t i = 0; i < pFindObjects.size(); ++i)
	{
		pStaticProb = (CStaticProb*)pFindObjects[i];

		pStaticProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
		m_pTransformCom->m_vPos = vNextPos;
		m_pPathFindCom->m_pCell = pNextCell;

	}
	pFindObjects.clear();

	return NULL;
}

CPlayerState* CWizard_Female_1HS_Orb_Teleport::Mode2()
{
	m_pOwner->SetAnimationMode(0);
	return new CWizard_Female_1HS_Orb_Idle;
}	
