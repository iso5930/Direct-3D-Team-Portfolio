#pragma once
#include "traileffect.h"

class CDemonHunter_RapidFire_ArrowTrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_RapidFire_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CDemonHunter_RapidFire_ArrowTrailEffect(void);
};