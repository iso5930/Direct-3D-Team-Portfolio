#pragma once

#include "Object.h"

class CTrail;
class CBufferCom;

class CTrailEffect_3 : public CObject
{
private:
	// Vertex
	Vertex* m_pVertex;

	// Trail
	CTrail* m_pTrail;

	// Cnt
	DWORD m_dwCnt;
	DWORD m_dwStartCnt;

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

	//Dir
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Add(D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown);

public:
	explicit CTrailEffect_3(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwMaxCnt, D3DXMATRIX* _pMatrix, D3DXVECTOR3* _pUp, D3DXVECTOR3* _pDown, float _fPeriod, TCHAR* _tszTexKey, DWORD _dwStartCnt, D3DXVECTOR3 _vDir);
	virtual ~CTrailEffect_3();
};
