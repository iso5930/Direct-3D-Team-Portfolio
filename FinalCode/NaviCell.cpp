#include "Stdafx.h"
#include "NaviCell.h"

CNaviCell::CNaviCell()
{
	// Type
	m_dwType = 0;

	// Point
	ZeroMemory(m_vPoint, sizeof(m_vPoint));

	// Center
	ZeroMemory(&m_vCenter, sizeof(D3DXVECTOR3));

	// Line
	m_pLine[0] = new CNaviLine;
	m_pLine[1] = new CNaviLine;
	m_pLine[2] = new CNaviLine;

	// Dist
	ZeroMemory(m_fDist, sizeof(m_fDist));

	// Plane
	ZeroMemory(&m_Plane, sizeof(D3DXPLANE));

	// Link
	ZeroMemory(m_pLink, sizeof(m_pLink));

	// Cost
	m_fCost = 0.0f;

	// Heuristic
	m_fHeuristic = 0.0f;

	// Session
	m_iSession = 0;

	// IntersectSide
	m_iIntersectSide = 0;

	// Open
	m_bOpen = false;

	// Visited
	m_bVisited = false;
}

CNaviCell::~CNaviCell()
{
	delete m_pLine[0];
	delete m_pLine[1];
	delete m_pLine[2];
}

void CNaviCell::Setup(D3DXVECTOR3* _pPointA, D3DXVECTOR3* _pPointB, D3DXVECTOR3* _pPointC, DWORD _dwType)
{
	// Type
	m_dwType = _dwType;

	// Point
	m_vPoint[0] = (*_pPointA);
	m_vPoint[1] = (*_pPointB);
	m_vPoint[2] = (*_pPointC);

	// Center
	m_vCenter = (m_vPoint[0] + m_vPoint[1] + m_vPoint[2]) / 3.0f;

	// Line
	m_pLine[0]->Setup(&(m_vPoint[0]), &(m_vPoint[1]));
	m_pLine[1]->Setup(&(m_vPoint[1]), &(m_vPoint[2]));
	m_pLine[2]->Setup(&(m_vPoint[2]), &(m_vPoint[0]));

	// Dist
	m_fDist[0] = D3DXVec3Length(&(m_pLine[0]->m_vMid - m_vCenter));
	m_fDist[1] = D3DXVec3Length(&(m_pLine[1]->m_vMid - m_vCenter));
	m_fDist[2] = D3DXVec3Length(&(m_pLine[2]->m_vMid - m_vCenter));

	// Plane
	D3DXPlaneFromPoints(&m_Plane, _pPointA, _pPointB, _pPointC);
}

bool CNaviCell::IsIn(D3DXVECTOR3* _pPoint)
{
	int iCnt = 0;

	for(int i = 0; i < 3; ++i)
	{
		if(m_pLine[i]->Classify(_pPoint) != POINT_CLASS_LEFT_SIDE)
			++iCnt;
	}

	return (iCnt == 3);
}

bool CNaviCell::Request(D3DXVECTOR3* _pV1, D3DXVECTOR3* _pV2, CNaviCell* _pCaller)
{
	if(m_vPoint[POINT_TYPE_A] == *_pV1)
	{
		if(m_vPoint[POINT_TYPE_B] == *_pV2)
		{
			m_pLink[CELL_SIDE_AB] = _pCaller;
			return true;
		}
		else if(m_vPoint[POINT_TYPE_C] == *_pV2)
		{
			m_pLink[CELL_SIDE_CA] = _pCaller;
			return true;
		}
	}
	else if(m_vPoint[POINT_TYPE_B] == *_pV1)
	{
		if(m_vPoint[POINT_TYPE_A] == *_pV2)
		{
			m_pLink[CELL_SIDE_AB] = _pCaller;
			return true;
		}
		else if(m_vPoint[POINT_TYPE_C] == *_pV2)
		{
			m_pLink[CELL_SIDE_BC] = _pCaller;
			return true;
		}
	}
	else if(m_vPoint[POINT_TYPE_C] == *_pV1)
	{
		if(m_vPoint[POINT_TYPE_A] == *_pV2)
		{
			m_pLink[CELL_SIDE_CA] = _pCaller;
			return true;
		}
		else if(m_vPoint[POINT_TYPE_B] == *_pV2)
		{
			m_pLink[CELL_SIDE_BC] = _pCaller;
			return true;
		}
	}

	return false;
}

bool CNaviCell::Query(CNaviHeap* _pHeap, CNaviCell* _pCaller, float _fCost)
{
	if(m_iSession != _pHeap->m_iSession)
	{
		m_iSession = _pHeap->m_iSession;

		if(_pCaller)
		{
			// Open
			m_bOpen = true;

			// Heuristic
			float XDelta = fabs(_pHeap->m_vGoal.x - m_vCenter.x);
			float ZDelta = fabs(_pHeap->m_vGoal.z - m_vCenter.z);
			m_fHeuristic = __max(XDelta,ZDelta);

			// Cost
			m_fCost = _fCost;

			// IntersectSide
			if(_pCaller == m_pLink[0])
				m_iIntersectSide = 0;
			else if(_pCaller == m_pLink[1])
				m_iIntersectSide = 1;
			else if(_pCaller == m_pLink[2])
				m_iIntersectSide = 2;
		}
		else
		{
			// Init
			m_bOpen = false;
			m_fCost = 0.0f;
			m_fHeuristic = 0.0f;
			m_iIntersectSide = 0;
		}

		_pHeap->AddCell(this);
		return true;
	}

	if(m_bOpen)
	{
		if(m_fCost > _fCost)
		{
			// Cost
			m_fCost = _fCost;

			// IntersectSide
			if(_pCaller == m_pLink[0])
				m_iIntersectSide = 0;
			else if(_pCaller == m_pLink[1])
				m_iIntersectSide = 1;
			else if(_pCaller == m_pLink[2])
				m_iIntersectSide = 2;

			// Adjust
			_pHeap->AdjustCell(this);

			return true;
		}
	}

	return false;
}

bool CNaviCell::Process(CNaviHeap* _pHeap)
{
	if(m_iSession == _pHeap->m_iSession)
	{
		// Open
		m_bOpen = false;

		for(int i = 0; i < 3; ++i)
		{
			if(m_pLink[i])
				m_pLink[i]->Query(_pHeap, this, m_fCost + m_fDist[abs(i - m_iIntersectSide)]);
		}

		return true;
	}

	return false;
}

void CNaviCell::Projection(D3DXVECTOR3* _pPoint)
{
	if(m_Plane.b != 0.0f)
		_pPoint->y = -(m_Plane.a * _pPoint->x + m_Plane.c * _pPoint->z + m_Plane.d) / m_Plane.b;
	else
		_pPoint->y = 0.0f;
}

MOVE_CLASS CNaviCell::Classify(CNaviLine* _pMove, CNaviCell** _ppNext, CELL_SIDE* _pCellSide, D3DXVECTOR3* _pIntersectPoint)
{
	// Cnt
	int iCnt = 0;

	for(int i = 0; i < 3; ++i)
	{
		// 만약, Dst가 안에 없고 Src가 밖에 없다면 Move는 밖으로 나가려는 것이다.
		if(m_pLine[i]->Classify(&(_pMove->m_vDst)) != POINT_CLASS_RIGHT_SIDE && m_pLine[i]->Classify(&(_pMove->m_vSrc)) != POINT_CLASS_LEFT_SIDE)
		{
			// 선분교차를 통해 평행이 아님을 판단한다.
			LINE_CLASS eLineClass = _pMove->Classify(m_pLine[i], _pIntersectPoint);

			if(eLineClass == LINE_CLASS_SEGMENT || eLineClass == LINE_CLASS_A_BISECT_B)
			{
				// Next Cell
				*_ppNext = m_pLink[i];

				// Collision Side
				*_pCellSide = CELL_SIDE(i);

				return MOVE_CLASS_OUT_CELL;
			}
		}
		else
			++iCnt;
	}

	if(iCnt == 3)
		return MOVE_CLASS_IN_CELL;

	return MOVE_CLASS_NO_PASS;
}

void CNaviCell::ProjectPathOnCellWall(CELL_SIDE _eCellSide, CNaviLine* _pMove)
{
	// Direction
	D3DXVECTOR3 vDir = _pMove->m_vDst - _pMove->m_vSrc;

	// Direction * Line Direction
	float fDot = D3DXVec3Dot(&vDir, &m_pLine[_eCellSide]->m_vDir);

	// Set Direction
	vDir = fDot * m_pLine[_eCellSide]->m_vDir;

	// Set Destination
	_pMove->m_vDst = _pMove->m_vSrc + vDir;

	D3DXVECTOR3 vNewPoint = _pMove->m_vSrc;
	ForcePointToCellCollumn(&vNewPoint);
	_pMove->m_vSrc = vNewPoint;

	vNewPoint = _pMove->m_vDst;
	ForcePointToWallInterior(_eCellSide, &vNewPoint);
	_pMove->m_vDst = vNewPoint;
}

bool CNaviCell::ForcePointToCellCollumn(D3DXVECTOR3* _pPoint)
{
	bool PointAltered = false;

	// create a motion path from the center of the cell to our point
	CNaviLine Move;
	Move.m_vSrc = m_vCenter;
	Move.m_vDst = *_pPoint;

	D3DXVECTOR3 vIntersectPoint;
	CELL_SIDE eCellSide;
	CNaviCell* pNextCell;

	MOVE_CLASS eMoveClass = Classify(&Move, &pNextCell, &eCellSide, &vIntersectPoint);
	// compare this path to the cell.

	if (eMoveClass == MOVE_CLASS_OUT_CELL)
	{
		D3DXVECTOR3 vPathDir = vIntersectPoint - m_vCenter;
		vPathDir.y = 0.0f;
		vPathDir *= 0.9f;

		_pPoint->x = m_vCenter.x + vPathDir.x;
		_pPoint->z = m_vCenter.z + vPathDir.z;

		return true;
	}
	else if (eMoveClass == MOVE_CLASS_NO_PASS)
	{
		_pPoint->x = m_vCenter.x;
		_pPoint->z = m_vCenter.z;

		return true;
	}

	return false;
}

bool CNaviCell::ForcePointToWallInterior(CELL_SIDE _eCellSide, D3DXVECTOR3* _pPoint)
{
	D3DXVECTOR3 v = (*_pPoint) - m_pLine[_eCellSide]->m_vSrc;
	float Distance = D3DXVec3Dot(&v, &m_pLine[_eCellSide]->m_vNormal);

	if (Distance <= MIN_EPSILON)
	{
		if (Distance <= 0.0f)
			Distance -= MIN_EPSILON;

		Distance = fabs(Distance);
		Distance = (MIN_EPSILON > Distance ? MIN_EPSILON : Distance);

		// this point needs adjustment
		*_pPoint += (m_pLine[_eCellSide]->m_vNormal * Distance);

		return true;
	}

	return false;
}