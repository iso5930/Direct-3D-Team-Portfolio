#include "StdAfx.h"
#include "MonsterState.h"

CMonsterState::CMonsterState()
{
	// StateType
	m_eStateType = STATE_TYPE_END;

	// Owner
	m_pOwner = NULL;

	// TransformCom
	m_pTransformCom = NULL;

	// PathFindCom
	m_pPathFindCom = NULL;

	// AnimController
	m_pAnimController = NULL;
}

CMonsterState::~CMonsterState()
{
}

void CMonsterState::Initialize()
{
	// TransformCom
	m_pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	// PathFindCom
	m_pPathFindCom = (CPathFindCom*)m_pOwner->GetComponent(COM_TYPE_PATH_FIND);

	// BufferCom
	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);

	// DynamicMesh
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];

	// AnimController
	m_pAnimController = pDynamicMesh->m_pAnimController;

	// RemoveAttack
	m_pOwner->RemoveAttack();

	// Disable
	m_pPathFindCom->Disable();
}

CMonsterState* CMonsterState::Action()
{
	return NULL;
}