#include "Stdafx.h"
#include "Camera.h"

CCamera::CCamera(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwIndex)
: CObject(_tszObjKey, _eObjType)
{
	// Index
	m_dwIndex = _dwIndex;

	// Far
	m_fFar = 0.0f;

	// Near
	m_fNear = 0.0f;

	// View
	D3DXMatrixIdentity(&m_mView);

	// Proj
	D3DXMatrixIdentity(&m_mProj);

	// UpdateCom
	AddComponent(new CUpdateCom(UPDATE_TYPE_CAMERA));
}

CCamera::~CCamera()
{
	Release();
}

void CCamera::Initialize()
{
	CCameraMgr::GetInstance()->AddCamera(m_dwIndex, this);

	CObject::Initialize();
}

int CCamera::Update()
{
	if(CCameraMgr::GetInstance()->GetCamera() == this)
	{
		// Update
		CObject::Update();

		// View
		MatrixLookAtLH(&m_mView, &(m_pTransformCom->m_vPos), &(m_pTransformCom->m_vAxisX), &(m_pTransformCom->m_vAxisY), &(m_pTransformCom->m_vAxisZ));
	}

	return 0;
}

void CCamera::Render()
{
	CObject::Render();
}

void CCamera::Release()
{
	CCameraMgr::GetInstance()->RemoveCamera(m_dwIndex, this);
}

void CCamera::SetView(D3DXVECTOR3* _pPos, D3DXVECTOR3* _pAngle, D3DXVECTOR3* _pSize)
{
	m_pTransformCom->m_vPos = *_pPos;
	m_pTransformCom->m_vAngle = *_pAngle;
	m_pTransformCom->m_vSize = *_pSize;
}

void CCamera::SetProj(float _fFovy, float _fAspect, float _fNear, float _fFar)
{
	// Near
	m_fNear = _fNear;

	// Far
	m_fFar = _fFar;

	// Proj
	D3DXMatrixPerspectiveFovLH(&m_mProj, _fFovy, _fAspect, _fNear, _fFar);
}