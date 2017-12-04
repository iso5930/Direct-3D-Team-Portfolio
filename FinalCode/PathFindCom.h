#pragma once

#include "Component.h"

class CTransformCom;
class CNaviCell;
class CNaviPath;

class CPathFindCom : public CComponent
{
private:
	// TransformCom
	CTransformCom* m_pTransformCom;

public:
	// PathType
	PATH_TYPE m_ePathType;

	// Enable
	bool m_bEnable;

	// Speed
	float m_fSpeed;

	// Dir
	D3DXVECTOR3 m_vDir;

	// Dst
	D3DXVECTOR3 m_vDst;

	// Cell
	CNaviCell* m_pCell;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	// UpdatePlayer
	void UpdatePlayer();

	// UpdateMonster
	void UpdateMonster();

	// UpdateFollower
	void UpdateFollower();

public:
	// Enable
	void Enable() { m_bEnable = true; }

	// Disable
	void Disable() { m_bEnable = false; }

	// IsEnable
	bool IsEnable() { return m_bEnable; }

	// Move
	bool Move(D3DXVECTOR3* _pDst);

	// Clear
	bool Clear();

	// IsMove
	bool IsMove(D3DXVECTOR3* _pNextPos);

	// Revision
	void Revision();

public:
	explicit CPathFindCom(PATH_TYPE _ePathType, float _fSpeed);
	virtual ~CPathFindCom();
};