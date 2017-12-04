#pragma once
#include "effect.h"

class CDemonHunter_RapidFire_ArrowTrailEffect;
class CDemonHunter_RapidFire_ArrowEffect : public CEffect
{
private:
	CDemonHunter_RapidFire_ArrowTrailEffect* m_pTrailEffect;
	D3DXVECTOR3 m_vDir;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_RapidFire_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_RapidFire_ArrowEffect(void);
};