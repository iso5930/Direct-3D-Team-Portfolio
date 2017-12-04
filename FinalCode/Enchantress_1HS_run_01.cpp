#include "StdAfx.h"
#include "Enchantress_1HS_run_01.h"

CEnchantress_1HS_run_01::CEnchantress_1HS_run_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_RUN_01;
}

CEnchantress_1HS_run_01::~CEnchantress_1HS_run_01()
{
}

void CEnchantress_1HS_run_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(49);

	// PathFinCom
	m_pPathFindCom->Enable();
}

CFollowerState* CEnchantress_1HS_run_01::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();
	}

	return NULL;
}

// Mode0 - ToWait
CFollowerState* CEnchantress_1HS_run_01::Mode0()
{
	// Dst
	D3DXVECTOR3 vDst = m_pPlayerTransformCom->m_vPos + m_pPlayerTransformCom->m_vAxisZ * 200.0f;

	// Dir
	D3DXVECTOR3 vDir = vDst - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;

	if(Equals(vDir.x, 0.0f, MIN_EPSILON) && Equals(vDir.z, 0.0f, MIN_EPSILON) || fabs(D3DXVec3Length(&vDir)) < 10.0f)
		return new CEnchantress_1HS_Idle_01(0);

	// Normalize
	D3DXVec3Normalize(&vDir, &vDir);

	// Move
	m_pPathFindCom->Move(&vDst);

	// DotX
	float fDotX = RevisionDot(D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir));

	// DotZ
	float fDotZ = RevisionDot(D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir));

	// Rotate
	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

	return NULL;
}