#pragma once

#include "DynamicProb.h"

class CTristram_Gate_Town : public CDynamicProb
{
private:
	// Mode
	int m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Event
	virtual void Event();

	// EventEnd
	virtual void EventEnd();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

public:
	explicit CTristram_Gate_Town(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTristram_Gate_Town();
};
