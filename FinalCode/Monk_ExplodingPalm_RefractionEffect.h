#pragma once
#include "effect.h"

class CMonk_ExplodingPalm_RefractionEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_ExplodingPalm_RefractionEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_ExplodingPalm_RefractionEffect(void);
};
