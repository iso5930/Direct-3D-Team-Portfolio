#pragma once

#include "Object.h"

class CRenderCom;
class CBufferCom;
class CDynamicMesh;
class CBasicMessage;

class CDynamicProb : public CObject
{
protected:
	// RenderCom
	CRenderCom* m_pRenderCom;

	// BufferCom
	CBufferCom* m_pBufferCom;

	// DynamicMesh
	CDynamicMesh* m_pDynamicMesh;

	// ProbType
	PROB_TYPE m_eProbType;

	// Name
	TCHAR m_tszName[MIN_STR];

	// NameMessage
	CBasicMessage* m_pNameMessage;

	// Width
	float m_fWidth;

	// Height
	float m_fHeight;

	// Depth
	float m_fDepth;

	// Ray
	Ray m_ray;

	// IsOver
	bool m_bIsOver;

	// Line
	LPD3DXLINE m_pLine;

	// Point
	D3DXVECTOR3 m_vPoint[8];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Event
	virtual void Event() = 0;

	// EventEnd
	virtual void EventEnd() = 0;

public:
	// GetProbType
	PROB_TYPE GetProbType() { return m_eProbType; }

	// IsOver
	bool IsOver() { return m_bIsOver; }

	// DisOver
	void DisOver();

	// Intersect
	void Intersect(D3DXVECTOR3* _pSrc, CNaviCell* _pSrcCell, D3DXVECTOR3* _pDst, CNaviCell** _ppDstCell);

	// Intersect
	void Intersect(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst);

public:
	explicit CDynamicProb(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CDynamicProb();
};
