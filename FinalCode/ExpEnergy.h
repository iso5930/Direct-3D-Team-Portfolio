#pragma once

#include "EnergyUI.h"

class CExpMessage;

class CExpEnergy : public CEnergyUI
{
private:
	// ExpMessage
	CExpMessage* m_pExpMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CExpEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CExpEnergy();
};
