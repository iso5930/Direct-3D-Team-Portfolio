#pragma once

#include "EnergyUI.h"

class CControlMessage;

class CControlEnergy : public CEnergyUI
{
private:
	// ControlMessage
	CControlMessage* m_pControlMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CControlEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CControlEnergy();
};
