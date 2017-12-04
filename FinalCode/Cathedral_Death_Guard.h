#pragma once

#include "StaticProb.h"

class CCathedral_Death_Guard : public CStaticProb
{
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

public:
	explicit CCathedral_Death_Guard(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCathedral_Death_Guard();
};
