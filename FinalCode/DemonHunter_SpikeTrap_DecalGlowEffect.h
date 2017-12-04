#pragma once
#include "effect.h"

class CDemonHunter_SpikeTrap_DecalGlowEffect : public CEffect
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
	explicit CDemonHunter_SpikeTrap_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_SpikeTrap_DecalGlowEffect(void);
};
