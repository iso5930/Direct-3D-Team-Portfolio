#include "StdAfx.h"
#include "Barbarian_Male_1HS_Knockback_Loop.h"

CBarbarian_Male_1HS_Knockback_Loop::CBarbarian_Male_1HS_Knockback_Loop(D3DXVECTOR3& _vDir , float _fPower )
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_LOOP;

	m_vDir = _vDir;

	m_fTime = 0.0f; 

	m_fPower = _fPower;
}

CBarbarian_Male_1HS_Knockback_Loop::~CBarbarian_Male_1HS_Knockback_Loop(void)
{
}

void CBarbarian_Male_1HS_Knockback_Loop::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &(-m_vDir));
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &(-m_vDir));
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
}

CPlayerState* CBarbarian_Male_1HS_Knockback_Loop::Action()
{
	vector<CObject*> pFindObjects;
	CDynamicProb* pDynamicProb;
	CStaticProb* pStaticProb;
	CNaviCell* pNextCell;

	D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + ( m_vDir * CTimeMgr::GetInstance()->GetDeltaTime() * m_fPower);

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



	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if (m_fTime > 0.1f )
	{
		return new CBarbarian_Male_1HS_Knockback_End;
	}
	return NULL;
}
