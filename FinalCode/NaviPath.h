#pragma once

class CPathFindMgr;
class CNaviCell;
class CWayPoint;

class CNaviPath
{
private:
	// PathFindMgr
	CPathFindMgr* m_pPathFindMgr;

public:
	// WayPoint Vector
	vector<CWayPoint*> m_WayPointVec;

	// WayPoint ID
	int m_iWayPointID;

	// Source WayPoint
	CWayPoint* m_pSrcWayPoint;

	// Destination WayPoint
	CWayPoint* m_pDstWayPoint;

public:
	// Setup
	void Setup(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell);

	// End
	void End();

	// AddWayPoint
	void AddWayPoint(D3DXVECTOR3* _pPoint, CNaviCell* _pCell);

	// Find Next
	int FindNext(int _iIndex);

public:
	explicit CNaviPath();
	~CNaviPath();
};