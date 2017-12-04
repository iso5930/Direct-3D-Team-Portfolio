#pragma once

#include "DynamicProb.h"

class CCath2FToCath1F_Entrance : public CDynamicProb
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
	explicit CCath2FToCath1F_Entrance(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCath2FToCath1F_Entrance();
};
