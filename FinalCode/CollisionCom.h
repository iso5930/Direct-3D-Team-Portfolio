#pragma once

#include "Component.h"

class COptimizationCom;

class CCollisionCom : public CComponent
{
private:
	// CollType
	COLL_TYPE m_eCollType;

public:
	// CheckSphere
	Sphere* m_pCheckSphere;

	// CollsionSphere
	Sphere* m_pCollisionSphere;

	// CollisionBox
	Collision* m_pCollisionBox;

	// CollsionVec
	vector<Collision*> m_CollisionVec;

	// Pushed
	D3DXVECTOR3 m_vPushed;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CCollisionCom(COLL_TYPE _eCollType, Sphere* _pCheckSphere,	Sphere* _pCollisionSphere);
	explicit CCollisionCom(COLL_TYPE _eCollType, Sphere* _pCheckSphere,	Collision* _pCollisionBox);
	virtual ~CCollisionCom();
};
