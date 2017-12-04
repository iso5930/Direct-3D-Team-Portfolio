#pragma once
#include "effect.h"

class CMonk_CripplingWave_Attack2DecalEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_CripplingWave_Attack2DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_CripplingWave_Attack2DecalEffect(void);
};