#include "StdAfx.h"
#include "NPCState.h"

CNPCState::CNPCState()
{
	// StateType
	m_eStateType = STATE_TYPE_END;

	// Owner
	m_pOwner = NULL;

	// AnimController
	m_pAnimController = NULL;
}

CNPCState::~CNPCState()
{
}

void CNPCState::Initialize()
{
	// BufferCom
	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);

	// DynamicMesh
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];

	// AnimController
	m_pAnimController = pDynamicMesh->m_pAnimController;
}

CNPCState* CNPCState::Action()
{
	return NULL;
}