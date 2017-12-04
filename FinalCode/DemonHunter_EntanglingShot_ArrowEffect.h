#pragma once
#include "Effect.h"

class CDemonHunter_EntanglingShot_ArrowTrailEffect;

class CDemonHunter_EntanglingShot_ArrowEffect : public CEffect
{
private:
	// Dir
	D3DXVECTOR3 m_vDir;

	// TrailEffect
	CDemonHunter_EntanglingShot_ArrowTrailEffect* m_pTrailEffect;
	float	m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_EntanglingShot_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_EntanglingShot_ArrowEffect(void);
};