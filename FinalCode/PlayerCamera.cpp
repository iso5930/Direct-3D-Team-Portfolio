#include "StdAfx.h"
#include "PlayerCamera.h"

CPlayerCamera::CPlayerCamera(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwIndex)
: CCamera(_tszObjKey, _eObjType, _dwIndex)
{
	// Angle
	m_pTransformCom->m_vAngle = D3DXVECTOR3(D3DX_PI / 4.0f, -D3DX_PI / 4.0f, 0.0f);

	// Dist
	m_fDist = 800.0f;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 1.0f;
}

CPlayerCamera::~CPlayerCamera()
{
	Release();
}

void CPlayerCamera::Initialize()
{
	CCamera::Initialize();
}

int CPlayerCamera::Update()
{
	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return 0;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
	if(pPlayerTransformCom == NULL)
		return 0;

	// Dir
	D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	// Pos
	m_pTransformCom->m_vPos = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vAxisZ * (200.0f + m_fTime * 600.0f) + D3DXVECTOR3(0.0f, 50.0f, 0.0f) * (1.0f - m_fTime);

	// Angle
	m_pTransformCom->m_vAngle.x = D3DX_PI / 8.0f + D3DX_PI / 8.0f * m_fTime;

	if(m_iMode == 1)
	{
		m_fTime += (2.0f * CTimeMgr::GetInstance()->GetDeltaTime());
		if(m_fTime > 1.0f)
		{
			m_iMode = 0;
			m_fTime = 1.0f;
		}
	}
	else if(m_iMode == 2)
	{
		m_fTime -= (2.0f * CTimeMgr::GetInstance()->GetDeltaTime());
		if(m_fTime < 0.0f)
		{
			m_iMode = 0;
			m_fTime = 0.0f;
		}
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Z))
	{
		if(Equals(m_fTime, 0.0f, MIN_EPSILON))
			m_iMode = 1;
		else if(Equals(m_fTime, 1.0f, MIN_EPSILON))
			m_iMode = 2;
	}

	/*
	// Far To Near
	if(m_iMode == 1)
	{
		// Near
		D3DXVECTOR3 vNear = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vAxisZ * 100.0f + D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// Far
		D3DXVECTOR3 vFar = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vAxisZ * 800.0f + D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// Mid
		D3DXVECTOR3 vMid = vFar - D3DXVECTOR3(0.0f, 100.0f, 0.0f);

		// Pos
		GetBezier(&m_pTransformCom->m_vPos, &vFar, &vMid, &vNear, m_fTime);

		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_fTime > 1.0f)
		{
			m_iMode = 0;
			m_fTime = 0.0f;
			m_fDist = 100.0f;
		}
	}
	// Near To Far
	else if(m_iMode == 2)
	{
		// Near
		D3DXVECTOR3 vNear = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vAxisZ * 100.0f + D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// Far
		D3DXVECTOR3 vFar = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vAxisZ * 800.0f + D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// Mid
		D3DXVECTOR3 vMid = vFar - D3DXVECTOR3(0.0f, 100.0f, 0.0f);

		// Pos
		GetBezier(&m_pTransformCom->m_vPos, &vNear, &vMid, &vFar, m_fTime);

		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_fTime > 1.0f)
		{
			m_iMode = 0;
			m_fTime = 0.0f;
			m_fDist = 800.0f;
		}
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Z))
	{
		if(m_fDist > 400.0f)
			m_iMode = 1;
		else
			m_iMode = 2;
	}
	*/

	return CCamera::Update();
}

void CPlayerCamera::Render()
{
}

void CPlayerCamera::Release()
{
}