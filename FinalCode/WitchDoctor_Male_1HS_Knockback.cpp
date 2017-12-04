#include "StdAfx.h"
#include "WitchDoctor_Male_1HS_Knockback.h"

CWitchDoctor_Male_1HS_Knockback::CWitchDoctor_Male_1HS_Knockback(D3DXVECTOR3& _vDir , float _fPower )
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_1HS_KNOCKBACK;

	m_vDir = _vDir;
}

CWitchDoctor_Male_1HS_Knockback::~CWitchDoctor_Male_1HS_Knockback(void)
{
}

void CWitchDoctor_Male_1HS_Knockback::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(44);

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

CPlayerState* CWitchDoctor_Male_1HS_Knockback::Action()
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
		return new CWitchDoctor_Male_1HS_Knockback_End;
	}

	return NULL;
}
