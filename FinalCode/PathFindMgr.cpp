#include "Stdafx.h"
#include "PathFindMgr.h"

IMPLEMENT_SINGLETON(CPathFindMgr)

CPathFindMgr::CPathFindMgr()
{
	// Line
	D3DXCreateLine(CDeviceMgr::GetInstance()->GetDevice(), &m_pLine);
}

CPathFindMgr::~CPathFindMgr()
{
	Release();
}

void CPathFindMgr::Initialize()
{
}

int CPathFindMgr::Update()
{
	return 0;
}

void CPathFindMgr::Render()
{
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_NAVIGATION_MESH)
	{
		D3DXVECTOR3 vPoint[4];
		D3DXVECTOR3 vDelta = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		D3DXMATRIX mIdentity;
		D3DXMatrixIdentity(&mIdentity);

		for(size_t i = 0; i < m_CellVec.size(); ++i)
		{
			if(CCameraMgr::GetInstance()->IsIn(&m_CellVec[i]->m_vCenter, 0.0f) == false)
				continue;

			vPoint[0] = m_CellVec[i]->m_vPoint[0] + vDelta; D3DXVec3TransformCoord(&vPoint[0], &vPoint[0], CCameraMgr::GetInstance()->GetViewProj());
			vPoint[1] = m_CellVec[i]->m_vPoint[1] + vDelta; D3DXVec3TransformCoord(&vPoint[1], &vPoint[1], CCameraMgr::GetInstance()->GetViewProj());
			vPoint[2] = m_CellVec[i]->m_vPoint[2] + vDelta; D3DXVec3TransformCoord(&vPoint[2], &vPoint[2], CCameraMgr::GetInstance()->GetViewProj());
			vPoint[3] = m_CellVec[i]->m_vPoint[0] + vDelta; D3DXVec3TransformCoord(&vPoint[3], &vPoint[3], CCameraMgr::GetInstance()->GetViewProj());

			m_pLine->SetWidth(2.0f);
			m_pLine->Begin();
			m_pLine->DrawTransform(vPoint, 4, &mIdentity, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pLine->End();
		}
	}
}

void CPathFindMgr::Release()
{
	// CellVec
	for(size_t i = 0; i < m_CellVec.size(); ++i)
		delete m_CellVec[i];
	m_CellVec.clear();
}

void CPathFindMgr::LoadNaviMesh(TCHAR* _tszFilePath)
{
	// Clear
	for(size_t i = 0; i < m_CellVec.size(); ++i)
		delete m_CellVec[i];
	m_CellVec.clear();

	// Handle
	HANDLE hFile = CreateFile(_tszFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;
	if(hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateFile() Error : %s\n"), _tszFilePath);
		return;
	}

	// Size
	int iSize;
	ReadFile(hFile, &iSize, sizeof(int), &dwByte, NULL);

	// Cell
	D3DXVECTOR3 vPoint[3];
	DWORD dwType;
	CNaviCell* pCell;
	for(int i = 0; i < iSize; ++i)
	{
		ReadFile(hFile, &(vPoint[0]), sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, &(vPoint[1]), sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, &(vPoint[2]), sizeof(D3DXVECTOR3), &dwByte, NULL);
		ReadFile(hFile, &dwType, sizeof(DWORD), &dwByte, NULL);

		if(vPoint[0].x * vPoint[1].z + vPoint[1].x * vPoint[2].z + vPoint[2].x * vPoint[0].z - vPoint[0].x * vPoint[2].z - vPoint[1].x * vPoint[0].z - vPoint[2].x * vPoint[1].z > 0.0f)
		{
			D3DXVECTOR3 vTemp = vPoint[1];
			vPoint[1] = vPoint[2];
			vPoint[2] = vTemp;
		}

		pCell = new CNaviCell;
		pCell->Setup(&(vPoint[0]), &(vPoint[1]), &(vPoint[2]), dwType);
		m_CellVec.push_back(pCell);
	}

	// Link
	for(size_t i = 0; i < m_CellVec.size(); ++i)
	{
		CNaviCell* pCellA = m_CellVec[i];

		for(size_t j = 0; j < m_CellVec.size(); ++j)
		{
			CNaviCell* pCellB = m_CellVec[j];

			if(pCellA == pCellB)
				continue;

			if (!pCellA->m_pLink[CELL_SIDE_AB] && pCellB->Request(&(pCellA->m_vPoint[0]), &(pCellA->m_vPoint[1]), pCellA))
				pCellA->m_pLink[CELL_SIDE_AB] = pCellB;
			else if (!pCellA->m_pLink[CELL_SIDE_BC] && pCellB->Request(&(pCellA->m_vPoint[1]), &(pCellA->m_vPoint[2]), pCellA))
				pCellA->m_pLink[CELL_SIDE_BC] = pCellB;
			else if (!pCellA->m_pLink[CELL_SIDE_CA] && pCellB->Request(&(pCellA->m_vPoint[2]), &(pCellA->m_vPoint[0]), pCellA))
				pCellA->m_pLink[CELL_SIDE_CA] = pCellB;
		}
	}

	CloseHandle(hFile);
}

CNaviCell* CPathFindMgr::FindCell(D3DXVECTOR3* _pPoint)
{
	for(size_t i = 0; i < m_CellVec.size(); ++i)
	{
		if(m_CellVec[i]->IsIn(_pPoint) == true)
			return m_CellVec[i];
	}

	return NULL;
}

CNaviCell* CPathFindMgr::FindCell(CNaviCell* _pCell, D3DXVECTOR3* _pPoint)
{
	if(_pCell == NULL)
		return NULL;

	vector<CNaviCell*> CellVec;
	DWORD dwFront = 0;

	// Start Push
	CellVec.push_back(_pCell);

	// Find Cell
	CNaviCell* pCurCell = NULL;
	while(dwFront < CellVec.size())
	{
		pCurCell = CellVec[dwFront++];
		pCurCell->m_bVisited = true;

		if(pCurCell->IsIn(_pPoint) == true)
		{
			for(size_t i = 0; i < CellVec.size(); ++i)
				CellVec[i]->m_bVisited = false;

			return pCurCell;
		}

		if(pCurCell->m_pLink[0] != NULL && pCurCell->m_pLink[0]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[0]);
		if(pCurCell->m_pLink[1] != NULL && pCurCell->m_pLink[1]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[1]);
		if(pCurCell->m_pLink[2] != NULL && pCurCell->m_pLink[2]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[2]);
	}

	for(size_t i = 0; i < CellVec.size(); ++i)
		CellVec[i]->m_bVisited = false;

	return NULL;
}

CNaviCell* CPathFindMgr::FindCell(CNaviCell* _pCell, D3DXVECTOR3* _pPoint, float _fRadius)
{
	if(_pCell == NULL)
		return NULL;

	vector<CNaviCell*> CellVec;
	DWORD dwFront = 0;
	D3DXVECTOR2 vPoint(_pPoint->x, _pPoint->z);

	// Start Push
	CellVec.push_back(_pCell);

	// Find Cell
	CNaviCell* pCurCell = NULL;
	while(dwFront < CellVec.size())
	{
		pCurCell = CellVec[dwFront++];
		pCurCell->m_bVisited = true;

		for(int i = 0; i < 3; ++i)
		{
			if(PointToCircle(&D3DXVECTOR2(pCurCell->m_vPoint[i].x, pCurCell->m_vPoint[i].z), &vPoint, _fRadius))
			{
				for(size_t i = 0; i < CellVec.size(); ++i)
					CellVec[i]->m_bVisited = false;

				return pCurCell;
			}
		}

		if(pCurCell->m_pLink[0] != NULL && pCurCell->m_pLink[0]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[0]);
		if(pCurCell->m_pLink[1] != NULL && pCurCell->m_pLink[1]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[1]);
		if(pCurCell->m_pLink[2] != NULL && pCurCell->m_pLink[2]->m_bVisited == false)
			CellVec.push_back(pCurCell->m_pLink[2]);
	}

	for(size_t i = 0; i < CellVec.size(); ++i)
		CellVec[i]->m_bVisited = false;

	return NULL;
}

bool CPathFindMgr::SightTest(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell)
{
	CNaviLine Move;
	Move.Setup(_pSrc, _pDst);

	CNaviCell* pNextCell = _pSrcCell;
	CELL_SIDE eCellSide;
	MOVE_CLASS eMoveClass;

	while((eMoveClass = pNextCell->Classify(&Move, &pNextCell, &eCellSide, NULL)) == MOVE_CLASS_OUT_CELL)
	{
		if(pNextCell == NULL)
			return false;
	}

	return (eMoveClass == MOVE_CLASS_IN_CELL);
}

void CPathFindMgr::Solution(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell** _ppDstCell)
{
	if(_pSrcCell == NULL)
	{
		*_pDst = *_pSrc;
		*_ppDstCell = NULL;
		return;
	}

	// Move
	CNaviLine Move;
	Move.Setup(_pSrc, _pDst);

	// Variable
	MOVE_CLASS eMoveClass = MOVE_CLASS_NO_PASS;
	CELL_SIDE eCellSide;
	D3DXVECTOR3 vIntersectPoint;
	CNaviCell* pNextCell;
	CNaviCell* pTestCell = _pSrcCell;

	int iCnt = 0;
	while(eMoveClass != MOVE_CLASS_IN_CELL && Move.m_vSrc != Move.m_vDst)
	{
		eMoveClass = pTestCell->Classify(&Move, &pNextCell, &eCellSide, &vIntersectPoint);

		if(eMoveClass == MOVE_CLASS_OUT_CELL)
		{
			if(pNextCell != NULL)
			{
				Move.m_vSrc = vIntersectPoint;
				pTestCell = pNextCell;
			}
			else
			{
				Move.m_vSrc = vIntersectPoint;
				pTestCell->ProjectPathOnCellWall(eCellSide, &Move);

				D3DXVECTOR3 vDir = (Move.m_vDst - Move.m_vSrc) * 0.9f;
				Move.m_vDst = Move.m_vSrc + vDir;
			}
		}
		else if(eMoveClass == MOVE_CLASS_NO_PASS)
		{
			D3DXVECTOR3 vNewSrc = Move.m_vSrc;
			pTestCell->ForcePointToCellCollumn(&vNewSrc);
			Move.m_vSrc = vNewSrc;
		}

		if(++iCnt > 1000)
			Move.m_vSrc = Move.m_vDst;
	}

	*_ppDstCell = pTestCell;
	*_pDst = Move.m_vDst;
	pTestCell->Projection(_pDst);
}

bool CPathFindMgr::BuildPath(CNaviPath* _pPath, CNaviHeap* _pHeap, D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell)
{
	// Find
	bool bFind = false;

	// Heap Setup
	_pHeap->Setup(_pSrc);

	// Query Start
	_pDstCell->Query(_pHeap, NULL, NULL);

	// Compute Heap
	while(_pHeap->Empty() == false && bFind == false)
	{
		CNaviNode ThisNode;

		// Get Top
		_pHeap->PopTop(&ThisNode);

		if(ThisNode.m_pCell == _pSrcCell)
			bFind = true;
		else
			ThisNode.m_pCell->Process(_pHeap);
	}

	if(bFind)
	{
		CNaviCell* pTestCell = _pSrcCell;
		D3DXVECTOR3 vNewWayPoint;

		// Setup
		_pPath->Setup(_pSrc, _pSrcCell, _pDst, _pDstCell);

		while(pTestCell && pTestCell != _pDstCell)
		{
			int iIntersectSide = pTestCell->m_iIntersectSide;

			// Way Point
			vNewWayPoint = pTestCell->m_pLine[iIntersectSide]->m_vMid;

			// Interpolation
			pTestCell->ForcePointToCellCollumn(&vNewWayPoint);
			pTestCell->Projection(&vNewWayPoint);

			// Add WayPoint
			_pPath->AddWayPoint(&vNewWayPoint, pTestCell);

			// Next Cell
			pTestCell = pTestCell->m_pLink[iIntersectSide];
		}

		_pPath->End();
		return true;
	}

	return false;
}

void CPathFindMgr::AddGroup(PATH_TYPE _ePathType, CObject* _pObject)
{
	m_ObjectVec[_ePathType].push_back(_pObject);
}

void CPathFindMgr::RemoveGroup(PATH_TYPE _ePathType, CObject* _pObject)
{
	for(size_t i = 0; i < m_ObjectVec[_ePathType].size(); ++i)
	{
		if(m_ObjectVec[_ePathType][i] == _pObject)
		{
			m_ObjectVec[_ePathType][i] = m_ObjectVec[_ePathType][m_ObjectVec[_ePathType].size() - 1];
			m_ObjectVec[_ePathType].pop_back();
			break;
		}
	}
}