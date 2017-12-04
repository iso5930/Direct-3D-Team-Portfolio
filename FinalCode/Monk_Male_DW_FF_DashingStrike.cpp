#include "StdAfx.h"
#include "Monk_Male_DW_FF_DashingStrike.h"

CMonk_Male_DW_FF_DashingStrike::CMonk_Male_DW_FF_DashingStrike()
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_FF_DASHINGSTRIKE;
}

CMonk_Male_DW_FF_DashingStrike::~CMonk_Male_DW_FF_DashingStrike(void)
{
}

void CMonk_Male_DW_FF_DashingStrike::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(47);

	// Clear
	m_pPathFindCom->Clear();

	// Dist
	if (CInputMgr::GetInstance()->GetPickPos() != NULL)
		m_vDest = *CInputMgr::GetInstance()->GetPickPos();
	else
		m_vDest = m_pTransformCom->m_vPos;

	m_vDist = m_vDest - m_pTransformCom->m_vPos;

	float fLeagth = 0.0f;	
	fLeagth = D3DXVec3Length(&m_vDist);

	if (fLeagth >= 450.f )
		fLeagth = 450.f;

	m_fLeagth = fLeagth / float( m_pAnimController->m_dFrameTime - 0.15 ) ;	
	D3DXVec3Normalize(&m_vDir , &m_vDist);

	m_pOwner->CreateAttack();

}

CPlayerState* CMonk_Male_DW_FF_DashingStrike::Action()
{
	if(!(Equals(m_pTransformCom->m_vPos.x, m_vDest.x, MAX_EPSILON) && Equals(m_pTransformCom->m_vPos.z, m_vDest.z, MAX_EPSILON)))
	{
		vector<CObject*> pFindObjects;
		CDynamicProb* pDynamicProb;
		CNaviCell* pNextCell;
		float fMoveLeagth;

		fMoveLeagth = m_fLeagth	* CTimeMgr::GetInstance()->GetDeltaTime();	 

		D3DXVECTOR3 vDir = m_vDest - m_pTransformCom->m_vPos;
		D3DXVec3Normalize(&vDir , &vDir);

		D3DXVECTOR3 vNextPos  =	  m_pTransformCom->m_vPos + ( m_vDir * fMoveLeagth);

		m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);
		for(size_t i = 0; i < pFindObjects.size(); ++i)
		{
			pDynamicProb = (CDynamicProb*)pFindObjects[i];

			pDynamicProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
			m_pTransformCom->m_vPos = vNextPos;
			m_pPathFindCom->m_pCell = pNextCell;

		}
	}

	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		m_pOwner->RemoveAttack();
		return new CMonk_Male_DW_FF_Idle;	
	}



	return NULL;
}
