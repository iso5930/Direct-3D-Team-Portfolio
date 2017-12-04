#pragma once

#include "Object.h"

class CMonsterState;
class CDynamicMesh;
class CAnimController;
class CCollisionCom;
class CRenderCom;
class CMonsterEnergy;

class CMonster : public CObject
{
protected:
	// Info
	Info m_info;

	// Stat
	Stat m_stat;

	// State
	CMonsterState* m_pState;

	// DynamicMesh
	CDynamicMesh* m_pDynamicMesh;

	// AnimController
	CAnimController* m_pAnimController;

	// CollisionCom
	CCollisionCom* m_pCollisionCom;

	// RenderCom
	CRenderCom* m_pRenderCom;

	// Width
	float m_fWidth;

	// Height
	float m_fHeight;

	// Depth
	float m_fDepth;

	// Ray
	Ray m_ray;

	// IsOver
	bool m_bIsOver;

	// Line
	LPD3DXLINE m_pLine;

	// Point
	D3DXVECTOR3 m_vPoint[8];

	// Energy
	CMonsterEnergy* m_pEnergy;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Damage
	virtual void Damage(CPlayer* _pPlayer) = 0;

	// Damage
	virtual void Damage(CEffect* _pEffect) = 0;

	// CreateAttack
	virtual void CreateAttack() = 0;

	// Attack
	int Attack();

	// Death
	void Death();

public:
	// GetInfo
	Info* GetInfo() { return &m_info; }

	// GetStat
	Stat* GetStat() { return &m_stat; }

	// IsOver
	bool IsOver() { return m_bIsOver; }

	// DisOver
	void DisOver();

public:
	// SetState
	void SetState(CMonsterState* _pState);

	// SetAnimation
	void SetAnimation(int _iIndex);

	// SetAnimationMode
	void SetAnimationMode(int _iIndex);

	// RemoveAttack
	void RemoveAttack();

	// Intersect
	void Intersect(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst);

private:
	// DropItem
	void DropItem();

	// DropGold
	void DropGold();

public:
	explicit CMonster(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CMonster();
};
