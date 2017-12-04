#pragma once
#include "effect.h"

class CDemonHunter_Sentry_BaseEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Sentry_BaseEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CDemonHunter_Sentry_BaseEffect(void);
};