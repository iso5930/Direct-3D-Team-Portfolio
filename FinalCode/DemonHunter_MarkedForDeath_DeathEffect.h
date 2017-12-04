#pragma once
#include "effect.h"

class CDemonHunter_MarkedForDeath_DeathEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_MarkedForDeath_DeathEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CDemonHunter_MarkedForDeath_DeathEffect(void);
};