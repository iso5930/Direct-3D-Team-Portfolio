#include "StdAfx.h"
#include "FollowerState.h"

CFollowerState::CFollowerState(int _iMode)
{
	// Mode
	m_iMode = _iMode;

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

CFollowerState::~CFollowerState()
{
}

void CFollowerState::Initialize()
{
	// PlayerTransformCom
	m_pPlayerTransformCom = (CTransformCom*)m_pOwner->GetOwner()->GetComponent(COM_TYPE_TRANSFORM);

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

	// Disable
	m_pPathFindCom->Disable();
}

CFollowerState* CFollowerState::Action()
{
	return NULL;
}