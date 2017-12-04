#pragma once

class CObject;
class CPathFindCom;
class CNaviCell;
class CNaviHeap;
class CNaviPath;

class CPathFindMgr
{
private:
	// Line
	LPD3DXLINE m_pLine;

	// CellVec
	vector<CNaviCell*> m_CellVec;

	// Object Vector
	vector<CObject*> m_ObjectVec[PATH_TYPE_END];

public:
	////////////////////////////////////////////////////////////////////////// Function
	// LoadNaviMesh
	void LoadNaviMesh(TCHAR* _tszFilePath);

	// Find Cell
	CNaviCell* FindCell(D3DXVECTOR3* _pPoint);

	// FindCell
	CNaviCell* FindCell(CNaviCell* _pCell, D3DXVECTOR3* _pPoint);

	// FindCell
	CNaviCell* FindCell(CNaviCell* _pCell, D3DXVECTOR3* _pPoint, float _fRadius);

	// Sight Test
	bool SightTest(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell);

	// Solution
	void Solution(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell** _ppDstCell);

	// BuildPath
	bool BuildPath(CNaviPath* _pPath, CNaviHeap* _pHeap, D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell* _pDstCell);

	// Add Group
	void AddGroup(PATH_TYPE _ePathType, CObject* _pObject);

	// Remove Group
	void RemoveGroup(PATH_TYPE _ePathType, CObject* _pObject);

public:
	// GetSizeOfCell
	int GetSizeOfCell() { return m_CellVec.size(); }

	// GetCell
	CNaviCell* GetCell(int _iIndex) { return m_CellVec[_iIndex]; }

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	DECLARE_SINGLETON(CPathFindMgr)

private:
	explicit CPathFindMgr();
	~CPathFindMgr();
};