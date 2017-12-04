#pragma once

#include "EnergyUI.h"

class CLifeMessage;

class CLifeEnergy : public CEnergyUI
{
private:
	// LifeMessage
	CLifeMessage* m_pLifeMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CLifeEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CLifeEnergy();
};
