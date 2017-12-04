#include "Stdafx.h"
#include "TransformCom.h"

CTransformCom::CTransformCom()
{
	// ComType
	m_eComType = COM_TYPE_TRANSFORM;

	// Pos, Angle, Size
	ZeroMemory(&m_vPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vAngle, sizeof(D3DXVECTOR3));
	m_vSize.x = 1.0f;	m_vSize.y = 1.0f;	m_vSize.z = 1.0f;

	// Axis
	m_vAxisX.x = 1.0f;	m_vAxisX.y = 0.0f;	m_vAxisX.z = 0.0f;
	m_vAxisY.x = 0.0f;	m_vAxisY.y = 1.0f;	m_vAxisY.z = 0.0f;
	m_vAxisZ.x = 0.0f;	m_vAxisZ.y = 0.0f;	m_vAxisZ.z = 1.0f;

	// Matrix
	D3DXMatrixIdentity(&m_mTrans);
	D3DXMatrixIdentity(&m_mRotate);
	D3DXMatrixIdentity(&m_mScale);
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mPreWorld);
}

CTransformCom::~CTransformCom()
{
	Release();
}

void CTransformCom::Initialize()
{
}

int CTransformCom::Update()
{
	// PreWorld
	m_mPreWorld = m_mWorld;

	// Trans, Rotate, Scale
	D3DXMatrixTranslation(&m_mTrans, m_vPos.x, m_vPos.y, m_vPos.z);
	MatrixRotation(&m_mRotate, m_vAngle.x, m_vAngle.y, m_vAngle.z);
	D3DXMatrixScaling(&m_mScale, m_vSize.x, m_vSize.y, m_vSize.z);

	// World
	m_mWorld = m_mScale * m_mRotate * m_mTrans;

	// Axis
	MatrixToAxisX(&m_vAxisX, &m_mRotate);
	MatrixToAxisY(&m_vAxisY, &m_mRotate);
	MatrixToAxisZ(&m_vAxisZ, &m_mRotate);

	return 0;
}

void CTransformCom::Render()
{
	// SetTransform
	CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
}

void CTransformCom::Release()
{
}