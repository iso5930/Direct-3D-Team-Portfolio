#pragma once
#include "effect.h"

class CMonk_CripplingWave_DecalGlowEffect : public CEffect
{
private:
	float m_fTime;
	int		m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_CripplingWave_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_CripplingWave_DecalGlowEffect(void);
};