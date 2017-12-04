#pragma once
#include "effect.h"

class CDemonHunter_Preparation_DecalEffect : public CEffect
{
private:
	float	m_fTime;
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
	explicit CDemonHunter_Preparation_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Preparation_DecalEffect(void);
};