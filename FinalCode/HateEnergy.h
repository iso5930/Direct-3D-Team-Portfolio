#pragma once

#include "EnergyUI.h"

class CHateMessage;

class CHateEnergy : public CEnergyUI
{
private:
	// HateMessage
	CHateMessage* m_pHateMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CHateEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CHateEnergy();
};
