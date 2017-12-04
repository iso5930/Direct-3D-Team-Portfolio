#pragma once
#include "TrailEffect.h"

class CMonk_TempsetRush_TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_TempsetRush_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pWorld);
	virtual ~CMonk_TempsetRush_TrailEffect(void);
};