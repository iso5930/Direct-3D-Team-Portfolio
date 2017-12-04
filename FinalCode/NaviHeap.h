#pragma once

#include "NaviNode.h"

class CNaviCell;

class CNaviHeap
{
public:
	// Session
	int m_iSession;

	// Goal
	D3DXVECTOR3 m_vGoal;

	// Node Vector
	vector<CNaviNode> m_NodeVec;

	// Compare
	std::greater<CNaviNode> m_Compare;

public:
	// Setup
	void Setup(D3DXVECTOR3* _pGoal);

	// Add Cell
	void AddCell(CNaviCell* _pCell);

	// Adjust Cell
	void AdjustCell(CNaviCell* _pCell);

	// Empty
	bool Empty();

	// Pop Top
	void PopTop(CNaviNode* _pNode);

public:
	explicit CNaviHeap();
	~CNaviHeap();
};