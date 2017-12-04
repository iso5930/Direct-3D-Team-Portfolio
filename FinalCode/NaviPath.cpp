#include "Stdafx.h"
#include "NaviPath.h"

CNaviPath::CNaviPath()
{
	// PathFindMgr
	m_pPathFindMgr = CPathFindMgr::GetInstance();

	// WayPoint ID
	m_iWayPointID = 0;

	// Source WayPoint
	m_pSrcWayPoint = new CWayPoint;

	// Destination WayPoint
	m_pDstWayPoint = new CWayPoint;
}

CNaviPath::~CNaviPath()
{
	// WayPoint Vector
	for(size_t i = 0; i < m_WayPointVec.size(); ++i)
		delete m_WayPointVec[i];
	m_WayPointVec.clear();

	// Source WayPoint
	delete m_pSrcWayPoint;

	// Destination WayPoint
	delete m_pDstWayPoint;
}

void CNaviPath::Setup(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell)
{
	// WayPoint Vector
	for(size_t i = 0; i < m_WayPointVec.size(); ++i)
		delete m_WayPointVec[i];
	m_WayPointVec.clear();

	// Source WayPoint
	m_pSrcWayPoint->m_vPoint = (*_pSrc);
	m_pSrcWayPoint->m_pCell = _pSrcCell;

	// Destination
	m_pDstWayPoint->m_vPoint = (*_pDst);
	m_pDstWayPoint->m_pCell = _pDstCell;

	// Push Source
	CWayPoint* pSrcWayPoint = new CWayPoint;
	memcpy_s(pSrcWayPoint, sizeof(CWayPoint), m_pSrcWayPoint, sizeof(CWayPoint));

	m_WayPointVec.push_back(pSrcWayPoint);
}

void CNaviPath::End()
{
	// Push Destination
	CWayPoint* pDstWayPoint = new CWayPoint;
	memcpy_s(pDstWayPoint, sizeof(CWayPoint), m_pDstWayPoint, sizeof(CWayPoint));

	m_WayPointVec.push_back(pDstWayPoint);
}

void CNaviPath::AddWayPoint(D3DXVECTOR3* _pPoint, CNaviCell* _pCell)
{
	CWayPoint* pNewWayPoint = new CWayPoint;

	pNewWayPoint->m_vPoint = (*_pPoint);
	pNewWayPoint->m_pCell = _pCell;

	m_WayPointVec.push_back(pNewWayPoint);
}

int CNaviPath::FindNext(int _iIndex)
{
	int iTestIndex = _iIndex;
	if(iTestIndex >= m_WayPointVec.size())
		return iTestIndex;

	int iVisibleIndex = iTestIndex++;
	while(iTestIndex != m_WayPointVec.size())
	{
		if(m_pPathFindMgr->SightTest(&(m_WayPointVec[_iIndex]->m_vPoint), m_WayPointVec[_iIndex]->m_pCell, &(m_WayPointVec[iTestIndex]->m_vPoint), m_WayPointVec[iTestIndex]->m_pCell) == false)
			return iVisibleIndex;

		iVisibleIndex = iTestIndex++;
	}

	return iVisibleIndex;
}