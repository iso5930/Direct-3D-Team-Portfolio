#pragma once

#include "EnergyUI.h"

class CSlot;

class CCooldownEnergy : public CEnergyUI
{
private:
	// Slot
	CSlot* m_pSlot;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CCooldownEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CSlot* _pSlot);
	virtual ~CCooldownEnergy();
};
