#pragma once

#include "TrailEffect_2.h"

class CDemonHunter_EntanglingShot_ArrowTrailEffect : public CTrailEffect_2
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit  CDemonHunter_EntanglingShot_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CDemonHunter_EntanglingShot_ArrowTrailEffect(void);
};