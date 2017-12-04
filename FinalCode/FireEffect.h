#pragma once

#include "Effect.h"

class CFireEffect : public CEffect
{
public:
	// TextureVec
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CFireEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _tszDiff, TCHAR* _tszAlpha, TCHAR* _tszNoise);
	virtual ~CFireEffect();
};