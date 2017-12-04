#pragma once
#include "effect.h"

class CDemonHunter_ShadowPower_WingEffect : public CEffect
{
private:
	D3DXMATRIX* m_pWorld;
	float		m_fTime;
	float		m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_ShadowPower_WingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld);
	virtual ~CDemonHunter_ShadowPower_WingEffect(void);
};