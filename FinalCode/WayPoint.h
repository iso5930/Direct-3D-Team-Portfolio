#pragma once

class CNaviCell;

class CWayPoint
{
public:
	// Cell
	CNaviCell* m_pCell;

	// Point
	D3DXVECTOR3 m_vPoint;

public:
	explicit CWayPoint();
	~CWayPoint();
};