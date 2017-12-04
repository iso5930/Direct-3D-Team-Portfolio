#include "Stdafx.h"
#include "NaviNode.h"

CNaviNode::CNaviNode()
{
	// Cell
	m_pCell = NULL;

	// Cost
	m_fCost = 0.0f;
}

CNaviNode::~CNaviNode()
{
}