#pragma once

class CNaviCell;

class CNaviNode
{
public:
	// Cell
	CNaviCell* m_pCell;

	// Cost
	float m_fCost;

public:
	inline bool operator < (const CNaviNode& b)
	{
		return (m_fCost < (b.m_fCost));
	}

	inline bool operator > (const CNaviNode& b)
	{
		return (m_fCost > (b.m_fCost));
	}

	inline bool operator == (const CNaviNode& b)
	{
		return ((m_pCell == b.m_pCell) && (m_fCost == b.m_fCost));
	}

public:
	explicit CNaviNode();
	~CNaviNode();
};

inline bool operator < (const CNaviNode& a, const CNaviNode& b)
{
	return (a.m_fCost < b.m_fCost);
}

inline bool operator > (const CNaviNode& a, const CNaviNode& b)
{
	return (a.m_fCost > b.m_fCost);
}

inline bool operator == (const CNaviNode& a, const CNaviNode& b)
{
	return ((a.m_pCell == b.m_pCell) && (a.m_fCost == b.m_fCost));
}