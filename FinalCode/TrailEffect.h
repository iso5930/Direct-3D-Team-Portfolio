#pragma once

#include "Object.h"

class CTrail;
class CBufferCom;

class CTrailEffect : public CObject
{
private:
	// Vertex
	Vertex* m_pVertex;

	// Trail
	CTrail* m_pTrail;

	// Cnt
	DWORD m_dwCnt;

	// MaxCnt
	DWORD m_dwMaxCnt;

	// Matrix
	D3DXMATRIX* m_pMatrix;

	// Up
	D3DXVECTOR3 m_vUp;

	// Down
	D3DXVECTOR3 m_vDown;

	// Period
	float m_fPeriod;

	// Time
	float m_fTime;

	// BufferCom
	CBufferCom* m_pBufferCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Add(D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown);

public:
	explicit CTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwMaxCnt, D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown, float _fPeriod, TCHAR* _tszTexKey);
	virtual ~CTrailEffect();
};
