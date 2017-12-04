#pragma once
#include "effect.h"

class CMonk_CripplingWave_Attack1TrailEffect;
class CMonk_CripplingWave_Attack1DummyEffect : public CEffect
{
private:
	CMonk_CripplingWave_Attack1TrailEffect* m_pTrailEffect;
	float	m_fTime;
	Bone	m_Bone;
	int		m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();
	void Mode3();

public:
	explicit CMonk_CripplingWave_Attack1DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_CripplingWave_Attack1DummyEffect(void);
};