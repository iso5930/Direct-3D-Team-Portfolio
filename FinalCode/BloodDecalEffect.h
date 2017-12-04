#pragma once

#include "Effect.h"

class CBloodDecalEffect : public CEffect
{
private:
	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CBloodDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CBloodDecalEffect();
};
