#pragma once

#include "StaticProb.h"

class CTristram_BlackSmith_Store : public CStaticProb
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
	explicit CTristram_BlackSmith_Store(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTristram_BlackSmith_Store();
};
