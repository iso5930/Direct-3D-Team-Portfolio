#include "StdAfx.h"
#include "NPC.h"

CNPC::CNPC(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_NPC);
	AddComponent(pUpdateCom);

	// RenderCom
	m_pRenderCom = new CRenderCom(RENDER_TYPE_NPC);
	AddComponent(m_pRenderCom);

	// NPCType
	m_eNPCType = NPC_TYPE_END;

	// Name
	ZeroMemory(m_tszName, sizeof(m_tszName));

	// NameMessage
	m_pNameMessage = NULL;

	// State
	m_pState = NULL;

	// BufferCom
	m_pBufferCom = new CBufferCom;
	AddComponent(m_pBufferCom);

	// DynamicMesh
	m_pDynamicMesh = NULL;

	// Mode
	m_iMode = -1;

	// Width
	m_fWidth = 0.0f;

	// Height
	m_fHeight = 0.0f;

	// Depth
	m_fDepth = 0.0f;

	// Ray
	ZeroMemory(&m_ray, sizeof(Ray));

	// IsOver
	m_bIsOver = false;

	// Line
	D3DXCreateLine(CDeviceMgr::GetInstance()->GetDevice(), &m_pLine);

	// Point
	ZeroMemory(m_vPoint, sizeof(m_vPoint));
}

CNPC::~CNPC()
{
	Release();
}

void CNPC::Initialize()
{
	CObject::Initialize();

	// DynamicMesh
	m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[0];
}

int CNPC::Update()
{
	// Action
	CNPCState* pState = NULL;

	if(m_pState != NULL)
		pState = m_pState->Action();

	if(pState != NULL)
	{
		delete m_pState;
		m_pState = pState;
		m_pState->SetOwner(this);
		m_pState->Initialize();
	}

	// Is In?
	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 400.0f) == false)
	{
		// IsOver
		m_bIsOver = false;

		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		// NameMessage
		if(m_pNameMessage != NULL)
		{
			m_pNameMessage->Destroy();
			m_pNameMessage = NULL;
		}

		return 0;
	}

	// IsOver
	m_bIsOver = false;

	// Find Mouse
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Mouse"), LAYER_TYPE_MOUSE);
	if(pFindObject != NULL)
	{
		// Mouse
		CMouse* pMouse = (CMouse*)pFindObject;

		// Check
		bool bCheck = false;
		if(pMouse->GetMouseOverType() != MOUSE_OVER_TYPE_NONE)
		{
			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);

			if(D3DXVec3Length(&(pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())) > D3DXVec3Length(&(m_pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())))
				bCheck = true;
		}

		if(pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_NONE || bCheck)
		{
			// Intersect
			m_vPoint[0] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
			m_vPoint[1] = D3DXVECTOR3(-m_fWidth / 2.0f, m_fHeight, -m_fDepth / 2.0f);
			m_vPoint[2] = D3DXVECTOR3(m_fWidth / 2.0f, m_fHeight, -m_fDepth / 2.0f);
			m_vPoint[3] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
			m_vPoint[4] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
			m_vPoint[5] = D3DXVECTOR3(-m_fWidth / 2.0f, m_fHeight, m_fDepth / 2.0f);
			m_vPoint[6] = D3DXVECTOR3(m_fWidth / 2.0f, m_fHeight, m_fDepth / 2.0f);
			m_vPoint[7] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);

			// TransformCoord
			for(int i = 0; i < 8; ++i)
				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_pTransformCom->m_mWorld);

			// ScreenToWorld
			ScreenToWorld(&m_ray, CInputMgr::GetInstance()->GetMousePos(), CCameraMgr::GetInstance()->GetProj(), CCameraMgr::GetInstance()->GetInvView());

			// Intersect
			float u, v, dist;
			if(D3DXIntersectTri(&m_vPoint[0], &m_vPoint[1], &m_vPoint[2], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[0], &m_vPoint[2], &m_vPoint[3], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[5], &m_vPoint[1], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[1], &m_vPoint[0], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[7], &m_vPoint[6], &m_vPoint[5], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[7], &m_vPoint[5], &m_vPoint[4], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[3], &m_vPoint[2], &m_vPoint[6], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[3], &m_vPoint[6], &m_vPoint[7], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[1], &m_vPoint[5], &m_vPoint[6], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[1], &m_vPoint[6], &m_vPoint[2], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[6], &m_vPoint[3], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
			else if(D3DXIntersectTri(&m_vPoint[4], &m_vPoint[3], &m_vPoint[7], &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
		}
	}

	if(m_bIsOver)
	{
		// Over
		CMouse* pMouse = (CMouse*)pFindObject;
		pMouse->Over(MOUSE_OVER_TYPE_NPC, this);

		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

		// NameMessage
		if(m_pNameMessage == NULL)
		{
			m_pNameMessage = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Name"), m_tszName);
			m_pLayer->AddObject(m_pNameMessage, LAYER_TYPE_UI);

			RECT rcCalc;
			CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszName, -1, &rcCalc, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			CTransformCom* pTransformCom = (CTransformCom*)m_pNameMessage->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize.x = (rcCalc.right - rcCalc.left) / float(WINCX) * 2.0f + 0.04f;
			pTransformCom->m_vSize.y = (rcCalc.bottom - rcCalc.top) / float(WINCY) * 2.0f + 0.04f;
			pTransformCom->m_vSize.z = 0.0f;

			m_pNameMessage->Initialize();
		}

		CTransformCom* pTransformCom = (CTransformCom*)m_pNameMessage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 150.0f, 0.0f);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, CCameraMgr::GetInstance()->GetViewProj());
	}
	else
	{
		// RimColor
		m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		// NameMessage
		if(m_pNameMessage != NULL)
		{
			m_pNameMessage->Destroy();
			m_pNameMessage = NULL;
		}
	}

	CObject::Update();

	return 0;
}

void CNPC::Render()
{
	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 0.0f) == false)
		return;

	CObject::Render();

	m_pLine->SetWidth(2.0f);
	m_pLine->Begin();
	m_pLine->DrawTransform(m_vPoint, 8, CCameraMgr::GetInstance()->GetViewProj(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pLine->End();
}

void CNPC::Release()
{
	// NameMessage
	if(m_pNameMessage != NULL)
	{
		m_pNameMessage->Destroy();
		m_pNameMessage = NULL;
	}

	// State
	if(m_pState != NULL)
	{
		delete m_pState;
		m_pState = NULL;
	}

	// Line
	if(m_pLine != NULL)
	{
		m_pLine->Release();
		m_pLine = NULL;
	}
}

void CNPC::Event()
{
}

void CNPC::EventEnd()
{
}

void CNPC::SetMode(int _iMode)
{
	m_iMode = _iMode;

	if(m_iMode == -1)
	{
		// Width & Height & Depth
		m_fWidth = 0.0f; m_fHeight = 0.0f; m_fDepth = 0.0f;
	}
}

void CNPC::DisOver()
{
	// IsOver
	m_bIsOver = false;

	// RimColor
	m_pRenderCom->m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	// NameMessage
	if(m_pNameMessage != NULL)
	{
		m_pNameMessage->Destroy();
		m_pNameMessage = NULL;
	}
}

void CNPC::Intersect(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst)
{
	// v
	D3DXVECTOR3 v[4];
	v[0] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);
	v[1] = D3DXVECTOR3(-m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
	v[2] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, m_fDepth / 2.0f);
	v[3] = D3DXVECTOR3(m_fWidth / 2.0f, 0.0f, -m_fDepth / 2.0f);

	// TransformCoord
	for(int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&v[i], &v[i], &m_pTransformCom->m_mWorld);

	// line
	CNaviLine line[4];
	line[0].Setup(&v[0], &v[1]);
	line[1].Setup(&v[1], &v[2]);
	line[2].Setup(&v[2], &v[3]);
	line[3].Setup(&v[3], &v[0]);

	// Move
	CNaviLine MoveLine;
	MoveLine.Setup(_pSrc, _pDst);

	// IntersectPoint
	D3DXVECTOR3 vIntersectPoint;

	for(int i = 0; i < 4; ++i)
	{
		if(line[i].Classify(&MoveLine, &vIntersectPoint) == LINE_CLASS_SEGMENT)
		{
			POINT_CLASS ePointClass = line[i].Classify(_pSrc);
			if(ePointClass == POINT_CLASS_ON_LINE || ePointClass == POINT_CLASS_LEFT_SIDE)
			{
				_pDst->x = vIntersectPoint.x;
				_pDst->z = vIntersectPoint.z;
				break;
			}
		}
	}
}

void CNPC::SetState(CNPCState* _pState)
{
	if(m_pState != NULL)
		delete m_pState;

	m_pState = _pState;
	m_pState->SetOwner(this);
	m_pState->Initialize();
}

void CNPC::SetAnimation(int _iIndex)
{
	if(m_pDynamicMesh != NULL)
		m_pDynamicMesh->m_pAnimController->SetAnimation(_iIndex);
}

void CNPC::SetAnimationMode(int _iMode)
{
	if(m_pDynamicMesh != NULL)
		m_pDynamicMesh->m_iMode = _iMode;
}