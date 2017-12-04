#include "StdAfx.h"
#include "CollisionCom.h"

#include "CollisionMgr.h"
#include "Object.h"

CCollisionCom::CCollisionCom(COLL_TYPE _eCollType, Sphere* _pCheckSphere, Sphere* _pCollisionSphere)
{
	// ComType
	m_eComType = COM_TYPE_COLLISION;

	// CollType
	m_eCollType = _eCollType;

	// CheckSphere
	m_pCheckSphere = _pCheckSphere;

	// CollsionSphere
	m_pCollisionSphere = _pCollisionSphere;

	// CollisionBox
	m_pCollisionBox = NULL;

	// Pushed
	ZeroMemory(&m_vPushed, sizeof(D3DXVECTOR3));
}

CCollisionCom::CCollisionCom(COLL_TYPE _eCollType, Sphere* _pCheckSphere,	Collision* _pCollisionBox)
{
	// ComType
	m_eComType = COM_TYPE_COLLISION;

	// CollType
	m_eCollType = _eCollType;

	// CheckSphere
	m_pCheckSphere = _pCheckSphere;

	// CollsionSphere
	m_pCollisionSphere = NULL;

	// CollisionBox
	m_pCollisionBox = _pCollisionBox;

	// Pushed
	ZeroMemory(&m_vPushed, sizeof(D3DXVECTOR3));
}

CCollisionCom::~CCollisionCom()
{
	Release();
}

void CCollisionCom::Initialize()
{
}

int CCollisionCom::Update()
{
	// Pushed
	ZeroMemory(&m_vPushed, sizeof(D3DXVECTOR3));

	if(m_pCollisionBox != NULL)
	{
		D3DXVec3TransformNormal(&m_pCollisionBox->vAxisX, &AXIS_X, m_pCollisionBox->pMatrix);
		D3DXVec3TransformNormal(&m_pCollisionBox->vAxisY, &AXIS_Y, m_pCollisionBox->pMatrix);
		D3DXVec3TransformNormal(&m_pCollisionBox->vAxisZ, &AXIS_Z, m_pCollisionBox->pMatrix);
	}

	for(size_t i = 0; i < m_CollisionVec.size(); ++i)
	{
		D3DXVec3TransformNormal(&m_CollisionVec[i]->vAxisX, &AXIS_X, m_CollisionVec[i]->pMatrix);
		D3DXVec3TransformNormal(&m_CollisionVec[i]->vAxisY, &AXIS_Y, m_CollisionVec[i]->pMatrix);
		D3DXVec3TransformNormal(&m_CollisionVec[i]->vAxisZ, &AXIS_Z, m_CollisionVec[i]->pMatrix);
	}

	CCollisionMgr::GetInstance()->AddObject(m_eCollType, m_pOwner);

	return 0;
}

void CCollisionCom::Render()
{
}

void CCollisionCom::Release()
{
	CCollisionMgr::GetInstance()->RemoveObject(m_eCollType, m_pOwner);

	if(m_pCheckSphere != NULL)
	{
		delete m_pCheckSphere;
		m_pCheckSphere = NULL;
	}

	if(m_pCollisionSphere != NULL)
	{
		delete m_pCollisionSphere;
		m_pCollisionSphere = NULL;
	}

	if(m_pCollisionBox != NULL)
	{
		delete m_pCollisionBox;
		m_pCollisionBox = NULL;
	}

	for(size_t i = 0; i < m_CollisionVec.size(); ++i)
	{
		delete m_CollisionVec[i];
		m_CollisionVec[i] = NULL;
	}
	m_CollisionVec.clear();
}