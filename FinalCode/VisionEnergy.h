#pragma once

#include "EnergyUI.h"

class CVisionMessage;

class CVisionEnergy : public CEnergyUI
{
private:
	// VisionMessage
	CVisionMessage* m_pVisionMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CVisionEnergy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CVisionEnergy();
};
