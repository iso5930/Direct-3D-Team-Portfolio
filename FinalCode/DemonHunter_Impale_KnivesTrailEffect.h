#pragma once
#include "traileffect.h"

class CDemonHunter_Impale_KnivesTrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Impale_KnivesTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CDemonHunter_Impale_KnivesTrailEffect(void);
};