#pragma once

#include "EnergyUI.h"

class CManaMessage;

class CManaEnergy : public CEnergyUI
{
private:
	// ManaMessage
	CManaMessage* m_pManaMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CManaEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CManaEnergy();
};
