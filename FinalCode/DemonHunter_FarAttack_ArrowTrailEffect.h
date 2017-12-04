#pragma once

#include "TrailEffect.h"

class CDemonHunter_FarAttack_ArrowTrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_FarAttack_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CDemonHunter_FarAttack_ArrowTrailEffect();
};
