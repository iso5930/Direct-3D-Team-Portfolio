#include "StdAfx.h"
#include "Zombie_Female_Attack3.h"

CZombie_Female_Attack3::CZombie_Female_Attack3()
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_FEMALE_ATTACK3;

	// Effect
	m_bEffect = false;
}

CZombie_Female_Attack3::~CZombie_Female_Attack3()
{
}

void CZombie_Female_Attack3::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Female_Attack3.ogg"));
}

CMonsterState* CZombie_Female_Attack3::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.528f)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0;
		D3DXVec3Normalize(&vLook, &vLook);

		CZombieFemale_PukeDummy* pDummy = new CZombieFemale_PukeDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vLook);
		m_pOwner->GetLayer()->AddObject(pDummy, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDummy->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	
		pDummy->Initialize();
		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Female_Walk(1);

	return NULL;
}