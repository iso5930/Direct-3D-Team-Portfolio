#pragma once

#include "EnergyUI.h"

class CRageMessage;

class CRageEnergy : public CEnergyUI
{
private:
	// RageMessage
	CRageMessage* m_pRageMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CRageEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CRageEnergy();
};
