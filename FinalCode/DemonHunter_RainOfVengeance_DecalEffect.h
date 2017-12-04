#pragma once
#include "effect.h"

class CDemonHunter_RainOfVengeance_DecalEffect : public CEffect
{
private:
	int		m_iMode;
	float	m_fTime;
	float	m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CDemonHunter_RainOfVengeance_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_RainOfVengeance_DecalEffect(void);
};