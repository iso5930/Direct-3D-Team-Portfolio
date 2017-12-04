#include "StdAfx.h"
#include "Enchantress_1HS_Idle_01.h"

CEnchantress_1HS_Idle_01::CEnchantress_1HS_Idle_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_IDLE_01;
}

CEnchantress_1HS_Idle_01::~CEnchantress_1HS_Idle_01()
{
}

void CEnchantress_1HS_Idle_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(59);
}

CFollowerState* CEnchantress_1HS_Idle_01::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();
	}

	return NULL;
}

// Mode0 - Wait
CFollowerState* CEnchantress_1HS_Idle_01::Mode0()
{
	// Dst
	D3DXVECTOR3 vDst = m_pPlayerTransformCom->m_vPos + m_pPlayerTransformCom->m_vAxisZ * 200.0f;

	// Dir
	D3DXVECTOR3 vDir = vDst - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;

	if(Equals(vDir.x, 0.0f, MIN_EPSILON) == false && Equals(vDir.z, 0.0f, MIN_EPSILON) == false && fabs(D3DXVec3Length(&vDir)) > 10.0f)
	{
		// Normalize
		D3DXVec3Normalize(&vDir, &vDir);

		// DotX
		float fDotX = RevisionDot(D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir));

		// DotZ
		float fDotZ = RevisionDot(D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir));

		// Rotate
		if(fDotX > 0.0f)
			m_pTransformCom->m_vAngle.y += acosf(fDotZ);
		else
			m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

		return new CEnchantress_1HS_run_01(0);
	}

	return NULL;
}