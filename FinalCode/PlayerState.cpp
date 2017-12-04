#include "StdAfx.h"
#include "PlayerState.h"

CPlayerState::CPlayerState()
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

CPlayerState::~CPlayerState()
{
}

void CPlayerState::Initialize()
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

CPlayerState* CPlayerState::Action()
{
	return NULL;
}

int CPlayerState::UsingKeyMouse()
{
	DWORD dwPriorityMin = 0xFFFFFFFF;
	int iSlotNum = SLOT_PUSH_TYPE_NONE;

	if(CInputMgr::GetInstance()->KeyPriority(DIK_1) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->KeyPriority(DIK_1);
		iSlotNum = SLOT_PUSH_TYPE_KEY_1;
	}
	if(CInputMgr::GetInstance()->KeyPriority(DIK_2) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->KeyPriority(DIK_2);
		iSlotNum = SLOT_PUSH_TYPE_KEY_2;
	}
	if(CInputMgr::GetInstance()->KeyPriority(DIK_3) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->KeyPriority(DIK_3);
		iSlotNum = SLOT_PUSH_TYPE_KEY_3;
	}
	if(CInputMgr::GetInstance()->KeyPriority(DIK_4) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->KeyPriority(DIK_4);
		iSlotNum = SLOT_PUSH_TYPE_KEY_4;
	}
	if(CInputMgr::GetInstance()->MousePriority(DIM_LBUTTON) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->MousePriority(DIM_LBUTTON);
		iSlotNum = SLOT_PUSH_TYPE_MOUSE_LEFT;
	}
	if(CInputMgr::GetInstance()->MousePriority(DIM_RBUTTON) < dwPriorityMin)
	{
		dwPriorityMin = CInputMgr::GetInstance()->MousePriority(DIM_RBUTTON);
		iSlotNum = SLOT_PUSH_TYPE_MOUSE_RIGHT;
	}

	return iSlotNum;
}

bool CPlayerState::KeyMouseUP(int _KeyMouse)
{
	bool IsPress = false;
	switch(_KeyMouse)
	{
	case SLOT_PUSH_TYPE_KEY_1:
		if(CInputMgr::GetInstance()->KeyUp(DIK_1))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_2:
		if(CInputMgr::GetInstance()->KeyUp(DIK_2))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_3:
		if(CInputMgr::GetInstance()->KeyUp(DIK_3))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_4:
		if(CInputMgr::GetInstance()->KeyUp(DIK_4))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_MOUSE_LEFT:
		if(CInputMgr::GetInstance()->MouseUp(DIM_LBUTTON))
			IsPress = true;		
		break;
	case SLOT_PUSH_TYPE_MOUSE_RIGHT:
		if(CInputMgr::GetInstance()->MouseUp(DIM_RBUTTON))
			IsPress = true;
		break;
	}

	return IsPress;
}

bool CPlayerState::KeyMousePress(int _KeyMouse)
{
	bool IsPress = false;
	switch(_KeyMouse)
	{
	case SLOT_PUSH_TYPE_KEY_1:
		if(CInputMgr::GetInstance()->KeyPress(DIK_1))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_2:
		if(CInputMgr::GetInstance()->KeyPress(DIK_2))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_3:
		if(CInputMgr::GetInstance()->KeyPress(DIK_3))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_4:
		if(CInputMgr::GetInstance()->KeyPress(DIK_4))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_MOUSE_LEFT:
		if(CInputMgr::GetInstance()->MousePress(DIM_LBUTTON))
			IsPress = true;		
		break;
	case SLOT_PUSH_TYPE_MOUSE_RIGHT:
		if(CInputMgr::GetInstance()->MousePress(DIM_RBUTTON))
			IsPress = true;
		break;
	}

	return IsPress;
}

bool CPlayerState::KeyMouseDown(int _KeyMouse)
{
	bool IsPress = false;
	switch(_KeyMouse)
	{
	case SLOT_PUSH_TYPE_KEY_1:
		if(CInputMgr::GetInstance()->KeyDown(DIK_1))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_2:
		if(CInputMgr::GetInstance()->KeyDown(DIK_2))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_3:
		if(CInputMgr::GetInstance()->KeyDown(DIK_3))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_KEY_4:
		if(CInputMgr::GetInstance()->KeyDown(DIK_4))
			IsPress = true;
		break;
	case SLOT_PUSH_TYPE_MOUSE_LEFT:
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			IsPress = true;		
		break;
	case SLOT_PUSH_TYPE_MOUSE_RIGHT:
		if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
			IsPress = true;
		break;
	}

	return IsPress;
}

void CPlayerState::KeyMouseStop(int _KeyMouse)
{
	switch(_KeyMouse)
	{
	case SLOT_PUSH_TYPE_KEY_1:
		CInputMgr::GetInstance()->KeyStop(DIK_1);
		break;
	case SLOT_PUSH_TYPE_KEY_2:
		CInputMgr::GetInstance()->KeyStop(DIK_2);
		break;
	case SLOT_PUSH_TYPE_KEY_3:
		CInputMgr::GetInstance()->KeyStop(DIK_3);
		break;
	case SLOT_PUSH_TYPE_KEY_4:
		CInputMgr::GetInstance()->KeyStop(DIK_4);
		break;
	case SLOT_PUSH_TYPE_MOUSE_LEFT:
		CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
		break;
	case SLOT_PUSH_TYPE_MOUSE_RIGHT:
		CInputMgr::GetInstance()->MouseStop(DIM_RBUTTON);
		break;
	}
}

int CPlayerState::OverObjectPick()
{
	CObject* pFind = NULL;
	CMouse*	pMouse = NULL;
	m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
	pMouse = (CMouse*)pFind;

	D3DXVECTOR3 vDist ,vDir;
	

	switch( pMouse->GetMouseOverType() )
	{
	case MOUSE_OVER_TYPE_NONE :
		if (CInputMgr::GetInstance()->GetPickPos() == NULL)
			break;
		
		m_pOwner->SetPickObject(NULL);
		m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE);
		m_pPathFindCom->Move(CInputMgr::GetInstance()->GetPickPos());
		break;
	case MOUSE_OVER_TYPE_NPC :
		m_pOwner->SetPickObject(pMouse->GetOverObject());
		m_pOwner->SetPickType(pMouse->GetMouseOverType());
		vDir = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
		{
			PickObjectEvent();		
			KeyMouseStop(SLOT_PUSH_TYPE_MOUSE_LEFT);
			return MOUSE_OVER_TYPE_END;
		}
		
		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);	
		break;

	case MOUSE_OVER_TYPE_DROP_ITEM:
		m_pOwner->SetPickObject(pMouse->GetOverObject());
		m_pOwner->SetPickType(pMouse->GetMouseOverType());
		m_pPathFindCom->Move(&((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos);
		CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
		break;

	case MOUSE_OVER_TYPE_STATIC_PROB:
		m_pOwner->SetPickObject(pMouse->GetOverObject());
		m_pOwner->SetPickType(pMouse->GetMouseOverType());
		vDir = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
		{
			PickObjectEvent();
			KeyMouseStop(SLOT_PUSH_TYPE_MOUSE_LEFT);
			return MOUSE_OVER_TYPE_END;
		}
		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
		break;

	case MOUSE_OVER_TYPE_DYNAMIC_PROB:
		m_pOwner->SetPickObject(pMouse->GetOverObject());
		m_pOwner->SetPickType(pMouse->GetMouseOverType());
		vDir = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
		{
			PickObjectEvent();
			KeyMouseStop(SLOT_PUSH_TYPE_MOUSE_LEFT);
			return MOUSE_OVER_TYPE_END;
		}
		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
		break;

	case MOUSE_OVER_TYPE_MONSTER:
		break;
	}

	return pMouse->GetMouseOverType();
}

void CPlayerState::PickObjectEvent()
{
	if (m_pOwner->GetPickObject() == NULL)
	{
		return ;
	}

	switch(m_pOwner->GetPickType())
	{
	case	MOUSE_OVER_TYPE_NONE:
		break;

	case	MOUSE_OVER_TYPE_NPC:
		{
			CNPC* pNPC = (CNPC*)m_pOwner->GetPickObject();
			if (!pNPC->IsDestroy())
				pNPC->Event();
			
			m_pOwner->SetPickObject(NULL);
			m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE); 
			break;
		}
	case	MOUSE_OVER_TYPE_DROP_ITEM:
		{
			CDropItem* pDropItem = (CDropItem*)m_pOwner->GetPickObject();
			if (!pDropItem->IsDestroy())
				pDropItem->Get();

			m_pOwner->SetPickObject(NULL);
			m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE); 
			break;
		}
	case	MOUSE_OVER_TYPE_STATIC_PROB:
		{
			CStaticProb* pStaticProb = (CStaticProb*)m_pOwner->GetPickObject();
			if (!pStaticProb->IsDestroy())
				pStaticProb->Event();

			m_pOwner->SetPickObject(NULL);
			m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE); 
			break;
		}

	case	MOUSE_OVER_TYPE_DYNAMIC_PROB:
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)m_pOwner->GetPickObject();
			if (!pDynamicProb->IsDestroy())
				pDynamicProb->Event();

			m_pOwner->SetPickObject(NULL);
			m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE); 
			break;
		}

	case	MOUSE_OVER_TYPE_MONSTER:		
		break;
		
	}	
}

int CPlayerState::AttackMode()
{
	CObject* pFind = NULL;
	CMouse*	pMouse = NULL;
	m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
	pMouse = (CMouse*)pFind;

	D3DXVECTOR3 vDist ,vDir;

	m_pOwner->SetPickObject(NULL);
	m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE);

	switch( pMouse->GetMouseOverType() )
	{
	case MOUSE_OVER_TYPE_NONE :
		if (CInputMgr::GetInstance()->GetPickPos() == NULL)
			break;
		
		m_pPathFindCom->Move(CInputMgr::GetInstance()->GetPickPos());
		break;
	case MOUSE_OVER_TYPE_NPC :
		vDir = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
			break;

		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		break;

	case MOUSE_OVER_TYPE_DROP_ITEM:
		m_pPathFindCom->Move(&((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos);
		break;

	case MOUSE_OVER_TYPE_STATIC_PROB:
		vDir = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
			break;

		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		break;

	case MOUSE_OVER_TYPE_DYNAMIC_PROB:
		vDir = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos ;
		if (D3DXVec3Length(&vDir) < 100.f)
			break;

		D3DXVec3Normalize(&vDir , &vDir);
		vDist = ((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos - (vDir * 100);
		m_pPathFindCom->Move(&vDist);
		break;
	case MOUSE_OVER_TYPE_MONSTER:
		m_pPathFindCom->Move(&((CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM))->m_vPos);
		break;

	}

	return pMouse->GetMouseOverType();
}

