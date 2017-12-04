#include "Stdafx.h"
#include "CameraMgr.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
{
	ZeroMemory(m_pCameraArr, sizeof(m_pCameraArr));
	m_pCamera = NULL;

	ZeroMemory(&m_vViewPoint4D, sizeof(m_vViewPoint4D));
	ZeroMemory(&m_vWorldPoint4D, sizeof(m_vWorldPoint4D));
	ZeroMemory(&m_vViewPoint3D, sizeof(m_vViewPoint3D));
	ZeroMemory(&m_vWorldPoint3D, sizeof(m_vWorldPoint3D));
	ZeroMemory(&m_Plane, sizeof(m_Plane));

	ZeroMemory(&m_vPos3D, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPos4D, sizeof(D3DXVECTOR4));

	m_fNear = 0.0f;
	m_fFar = 0.0f;

	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mProj);
	D3DXMatrixIdentity(&m_mViewProj);

	D3DXMatrixIdentity(&m_mInvView);
	D3DXMatrixIdentity(&m_mInvProj);
	D3DXMatrixIdentity(&m_mInvViewProj);

	D3DXMatrixIdentity(&m_mPreView);
	D3DXMatrixIdentity(&m_mPreProj);
	D3DXMatrixIdentity(&m_mPreViewProj);

	D3DXMatrixIdentity(&m_mBillBoard);

	m_fBeginTime = 0.0f;
	m_fEndTime = 0.0f;
	m_fPeriod = 0.0f;
	m_fAmplit = 0.0f;
	m_fAmount = 0.0f;
	m_fSign = 0.0f;
}

CCameraMgr::~CCameraMgr()
{
	Release();
}

void CCameraMgr::Initialize()
{
}

int CCameraMgr::Update()
{
	// Shake : http://blog.naver.com/mssixx/150016902268
	if(m_fSign > 0.0f)
	{
		if(m_fBeginTime < m_fEndTime)
		{
			m_fBeginTime += CTimeMgr::GetInstance()->GetDeltaTime() * m_fSign;
			if(m_fBeginTime < m_fEndTime)
				m_fAmount = sin(m_fBeginTime * m_fPeriod) * powf(0.5f, m_fBeginTime) * m_fAmplit;
			else
				m_fAmount = 0.0f;
		}
	}
	else
	{
		if(m_fBeginTime > m_fEndTime)
		{
			m_fBeginTime += CTimeMgr::GetInstance()->GetDeltaTime() * m_fSign;
			if(m_fBeginTime > m_fEndTime)
				m_fAmount = sin(m_fBeginTime * m_fPeriod) * powf(0.5f, m_fBeginTime) * m_fAmplit;
			else
				m_fAmount = 0.0f;
		}
	}

	// PreView
	m_mPreView = m_mView;

	// PreProj
	m_mPreProj = m_mProj;

	// PreViewProj
	m_mPreViewProj = m_mViewProj;

	if(m_pCamera != NULL)
	{
		// View
		memcpy_s(&m_mView, sizeof(D3DXMATRIX), m_pCamera->GetView(), sizeof(D3DXMATRIX));
		m_mView._42 += m_fAmount;

		// Proj
		memcpy_s(&m_mProj, sizeof(D3DXMATRIX), m_pCamera->GetProj(), sizeof(D3DXMATRIX));

		// InvView
		D3DXMatrixInverse(&m_mInvView, NULL, &m_mView);

		// InvProj
		D3DXMatrixInverse(&m_mInvProj, NULL, &m_mProj);

		// Pos3D
		MatrixToPos(&m_vPos3D, &m_mInvView);

		// Pos4D
		memcpy_s(&m_vPos4D, sizeof(D3DXVECTOR3), &m_vPos3D, sizeof(D3DXVECTOR3));
		m_vPos4D.w = 1.0f;

		// Near
		m_fNear = m_pCamera->GetNear();

		// Far
		m_fFar = m_pCamera->GetFar();
	}
	else
	{
		// View
		D3DXMatrixIdentity(&m_mView);
		m_mView._42 += m_fAmount;

		// Proj
		D3DXMatrixIdentity(&m_mProj);

		// BillBoard
		D3DXMatrixIdentity(&m_mBillBoard);

		// InvView
		D3DXMatrixInverse(&m_mInvView, NULL, &m_mView);

		// InvProj
		D3DXMatrixInverse(&m_mInvProj, NULL, &m_mProj);

		// Pos3D
		MatrixToPos(&m_vPos3D, &m_mInvView);

		// Pos4D
		memcpy_s(&m_vPos4D, sizeof(D3DXVECTOR3), &m_vPos3D, sizeof(D3DXVECTOR3));
		m_vPos4D.w = 1.0f;

		// Near
		m_fNear = 0.0f;

		// Far
		m_fFar = 0.0f;
	}

	// ViewProj
	D3DXMatrixMultiply(&m_mViewProj, &m_mView, &m_mProj);

	// InvViewProj
	D3DXMatrixInverse(&m_mInvViewProj, NULL, &m_mViewProj);

	// BillBoard
	memcpy_s(&m_mBillBoard, sizeof(D3DXMATRIX), &m_mInvView, sizeof(D3DXMATRIX));
	ZeroMemory(&m_mBillBoard._41, sizeof(D3DXVECTOR3));

	for(int i = 0; i < 8; ++i)
	{
		// To View
		D3DXVec3TransformCoord(&m_vViewPoint3D[i], &PROJ_POINTS[i], &m_mInvProj);
		memcpy_s(&m_vViewPoint4D[i], sizeof(D3DXVECTOR3), &m_vViewPoint3D[i], sizeof(D3DXVECTOR3));
		m_vViewPoint4D[i].w = 1.0f;

		// To World
		D3DXVec3TransformCoord(&m_vWorldPoint3D[i], &PROJ_POINTS[i], &m_mInvViewProj);
		memcpy_s(&m_vWorldPoint4D[i], sizeof(D3DXVECTOR3), &m_vWorldPoint3D[i], sizeof(D3DXVECTOR3));
		m_vWorldPoint4D[i].w = 1.0f;
	}

	// Plane
	D3DXPlaneFromPoints(&m_Plane[0], &(m_vWorldPoint3D[4]), &(m_vWorldPoint3D[7]), &(m_vWorldPoint3D[6])); // 상 평면(top)
	D3DXPlaneFromPoints(&m_Plane[1], &(m_vWorldPoint3D[0]), &(m_vWorldPoint3D[1]), &(m_vWorldPoint3D[2])); // 하 평면(bottom)
	D3DXPlaneFromPoints(&m_Plane[2], &(m_vWorldPoint3D[0]), &(m_vWorldPoint3D[4]), &(m_vWorldPoint3D[5])); // 근 평면(near)
	D3DXPlaneFromPoints(&m_Plane[3], &(m_vWorldPoint3D[2]), &(m_vWorldPoint3D[6]), &(m_vWorldPoint3D[7])); // 원 평면(far)
	D3DXPlaneFromPoints(&m_Plane[4], &(m_vWorldPoint3D[0]), &(m_vWorldPoint3D[3]), &(m_vWorldPoint3D[7])); // 좌 평면(left)
	D3DXPlaneFromPoints(&m_Plane[5], &(m_vWorldPoint3D[1]), &(m_vWorldPoint3D[5]), &(m_vWorldPoint3D[6])); // 우 평면(right)

	return 0;
}

void CCameraMgr::Render()
{
}

void CCameraMgr::Release()
{
}

void CCameraMgr::AddCamera(DWORD _dwIndex, CCamera* _pCamera)
{
	if(m_pCameraArr[_dwIndex] != NULL)
		RemoveCamera(_dwIndex, m_pCameraArr[_dwIndex]);

	m_pCameraArr[_dwIndex] = _pCamera;
}

void CCameraMgr::RemoveCamera(DWORD _dwIndex, CCamera* _pCamera)
{
	if(m_pCameraArr[_dwIndex] == _pCamera)
	{
		m_pCameraArr[_dwIndex]->Destroy();
		m_pCameraArr[_dwIndex] = NULL;
	}

	if(m_pCamera == _pCamera)
		m_pCamera = NULL;
}

void CCameraMgr::Enable(DWORD _dwIndex)
{
	m_pCamera = m_pCameraArr[_dwIndex];
}

void CCameraMgr::Shake(float _fBeginTime, float _fEndTime, float _fPeriod, float _fAmplit)
{
	m_fBeginTime = _fBeginTime;
	m_fEndTime = _fEndTime;
	m_fPeriod = _fPeriod;
	m_fAmplit = _fAmplit;

	if(m_fBeginTime > m_fEndTime)
		m_fSign = -1.0f;
	else
		m_fSign = 1.0f;
}

bool CCameraMgr::IsIn(D3DXVECTOR3* _pPos, float _fRadius)
{
	for(int i = 0; i < 6; ++i)
	{
		if(D3DXPlaneDotCoord(&m_Plane[i], _pPos) > _fRadius)
			return false;
	}

	return true;
}