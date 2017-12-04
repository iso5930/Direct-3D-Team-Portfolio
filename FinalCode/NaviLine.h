#pragma once

class CNaviLine
{
public:
	// Src
	D3DXVECTOR3 m_vSrc;

	// Dst
	D3DXVECTOR3 m_vDst;

	// Mid
	D3DXVECTOR3 m_vMid;

	// Dir
	D3DXVECTOR3 m_vDir;

	// Normal
	D3DXVECTOR3 m_vNormal;

	// Size
	float m_fSize;

public:
	// Setup
	void Setup(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst);

	// Classify Point
	POINT_CLASS Classify(D3DXVECTOR3* _pPoint);

	// Classify Line
	LINE_CLASS Classify(CNaviLine* _pLine, D3DXVECTOR3* _pIntersectPoint = NULL);

public:
	explicit CNaviLine();
	~CNaviLine();
};