#include "Stdafx.h"
#include "NaviHeap.h"

CNaviHeap::CNaviHeap()
{
	// Session
	m_iSession = 0;

	// Goal
	ZeroMemory(&m_vGoal, sizeof(D3DXVECTOR3));
}

CNaviHeap::~CNaviHeap()
{
	// Node Clear
	m_NodeVec.clear();
}

void CNaviHeap::Setup(D3DXVECTOR3* _pGoal)
{
	// Session Áõ°¡
	++m_iSession;

	// Goal
	m_vGoal = (*_pGoal);

	// Node Clear
	m_NodeVec.clear();
}

void CNaviHeap::AddCell(CNaviCell* _pCell)
{
	CNaviNode NewNode;

	NewNode.m_pCell = _pCell;
	NewNode.m_fCost = (_pCell->m_fCost + _pCell->m_fHeuristic);

	m_NodeVec.push_back(NewNode);
	push_heap(m_NodeVec.begin(), m_NodeVec.end(), m_Compare);
}

void CNaviHeap::AdjustCell(CNaviCell* _pCell)
{
	vector<CNaviNode>::iterator Iter = m_NodeVec.begin();
	vector<CNaviNode>::iterator IterEnd = m_NodeVec.end();

	for(; Iter != IterEnd; ++Iter)
	{
		if((*Iter).m_pCell == _pCell)
			break;
	}

	if(Iter == IterEnd)
		return;

	(*Iter).m_pCell = _pCell;
	(*Iter).m_fCost = _pCell->m_fCost + _pCell->m_fHeuristic;

	push_heap(m_NodeVec.begin(), Iter + 1, m_Compare);
}

bool CNaviHeap::Empty()
{
	return (m_NodeVec.size() == 0);
}

void CNaviHeap::PopTop(CNaviNode* _pNode)
{
	*_pNode = m_NodeVec.front();

	pop_heap(m_NodeVec.begin(), m_NodeVec.end(), m_Compare);
	m_NodeVec.pop_back();
}