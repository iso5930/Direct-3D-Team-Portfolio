#pragma once

#include "WindowUI.h"

class CGateWayWindow : public CWindowUI
{
private:
	// GateWayType
	GATE_WAY_TYPE m_eGateWayType;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CGateWayWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, GATE_WAY_TYPE _eGateWayType);
	virtual ~CGateWayWindow();
};
