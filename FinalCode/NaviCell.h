#pragma once

class CNaviLine;
class CNaviHeap;

class CNaviCell
{
public:
	// Type
	DWORD m_dwType;

	// Point
	D3DXVECTOR3 m_vPoint[3];

	// Center
	D3DXVECTOR3 m_vCenter;

	// Line
	CNaviLine* m_pLine[3];

	// Dist
	float m_fDist[3];

	// Plane
	D3DXPLANE m_Plane;

	// Link
	CNaviCell* m_pLink[3];

	// Cost
	float m_fCost;

	// Heuristic
	float m_fHeuristic;

	// Session
	int m_iSession;

	// IntersectSide
	int m_iIntersectSide;

	// Open
	bool m_bOpen;

	// Visited
	bool m_bVisited;

public:
	// Setup
	void Setup(D3DXVECTOR3* _pPointA, D3DXVECTOR3* _pPointB, D3DXVECTOR3* _pPointC, DWORD _dwType);

	// IsIn
	bool IsIn(D3DXVECTOR3* _pPoint);

	// Request
	bool Request(D3DXVECTOR3* _pV1, D3DXVECTOR3* _pV2, CNaviCell* _pCaller);

	// Query
	bool Query(CNaviHeap* _pHeap, CNaviCell* _pCaller, float _fCost);

	// Process
	bool Process(CNaviHeap* _pHeap);

	// Projection
	void Projection(D3DXVECTOR3* _pPoint);

	// Classify
	MOVE_CLASS Classify(CNaviLine* _pMove, CNaviCell** _ppNext, CELL_SIDE* _pCellSide, D3DXVECTOR3* _pIntersectPoint);

	// ProjectPathOnCellWall
	void ProjectPathOnCellWall(CELL_SIDE _eCellSide, CNaviLine* _pMove);

	// ForcePointToCellCollumn
	bool ForcePointToCellCollumn(D3DXVECTOR3* _pPoint);

	// ForcePointToWallInterior
	bool ForcePointToWallInterior(CELL_SIDE _eCellSide, D3DXVECTOR3* _pPoint);

public:
	explicit CNaviCell();
	~CNaviCell();
};