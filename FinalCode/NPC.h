#pragma once

#include "Object.h"

class CRenderCom;
class CBufferCom;
class CDynamicMesh;
class CBasicMessage;
class CNPCState;

class CNPC : public CObject
{
protected:
	// RenderCom
	CRenderCom* m_pRenderCom;

	// BufferCom
	CBufferCom* m_pBufferCom;

	// DynamicMesh
	CDynamicMesh* m_pDynamicMesh;

	// NPCType
	NPC_TYPE m_eNPCType;

	// Name
	TCHAR m_tszName[MIN_STR];

	// NameMessage
	CBasicMessage* m_pNameMessage;

	// State
	CNPCState* m_pState;

	// Mode
	int m_iMode;

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

	// SetMode
	virtual void SetMode(int _iMode) = 0;

public:
	// GetNPCType
	NPC_TYPE GetNPCType() { return m_eNPCType; }

	// IsOver
	bool IsOver() { return m_bIsOver; }

	// DisOver
	void DisOver();

	// Intersect
	void Intersect(D3DXVECTOR3* _pSrc, D3DXVECTOR3* _pDst);

public:
	// SetState
	void SetState(CNPCState* _pState);

	// SetAnimation
	void SetAnimation(int _iIndex);

	// SetAnimationMode
	void SetAnimationMode(int _iMode);

public:
	explicit CNPC(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CNPC();
};
