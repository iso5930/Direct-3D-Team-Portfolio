#pragma once
#include "traileffect.h"

class CDemonHunter_FanOfKnives_TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();
	
public:
	explicit CDemonHunter_FanOfKnives_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CDemonHunter_FanOfKnives_TrailEffect(void);
};