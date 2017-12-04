#pragma once

#include "DynamicProb.h"

class CCath4FToRoyalChamber_Entrance : public CDynamicProb
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
	explicit CCath4FToRoyalChamber_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCath4FToRoyalChamber_Entrance();
};
