#pragma once
#include "effect.h"

class CMonk_WayOfTheHundredFists_TrailEffect;
class CMonk_WayOfTheHundredFists_DummyEffect : public CEffect
{
private:
	CMonk_WayOfTheHundredFists_TrailEffect* m_pTrailEffect;
	D3DXVECTOR3 m_vDir;
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_WayOfTheHundredFists_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir);
	virtual ~CMonk_WayOfTheHundredFists_DummyEffect(void);
};