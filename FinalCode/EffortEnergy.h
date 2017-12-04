#pragma once

#include "EnergyUI.h"

class CEffortMessage;

class CEffortEnergy : public CEnergyUI
{
private:
	// EffortMessage
	CEffortMessage* m_pEffortMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CEffortEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CEffortEnergy();
};
