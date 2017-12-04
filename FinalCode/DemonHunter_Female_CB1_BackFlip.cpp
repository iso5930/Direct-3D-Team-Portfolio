#include "StdAfx.h"
#include "DemonHunter_Female_CB1_BackFlip.h"

CDemonHunter_Female_CB1_BackFlip::CDemonHunter_Female_CB1_BackFlip()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BACKFLIP;
	
	
	m_vDir = D3DXVECTOR3(0.f, 0.f, 0.f);

	

}

CDemonHunter_Female_CB1_BackFlip::~CDemonHunter_Female_CB1_BackFlip()
{
}

void CDemonHunter_Female_CB1_BackFlip::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(34);

	m_pPathFindCom->Clear();

	m_vDir =  *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;

	m_vDir.y = 0.0f;
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

CPlayerState* CDemonHunter_Female_CB1_BackFlip::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}


	vector<CObject*> pFindObjects;
	CDynamicProb* pDynamicProb;
	CStaticProb* pStaticProb;
	CNaviCell* pNextCell;

	D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + ( m_vDir * CTimeMgr::GetInstance()->GetDeltaTime() * 1000.f);

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

	return NULL;
}

