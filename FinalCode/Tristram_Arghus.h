#pragma once

#include "NPC.h"

// ªÛ¡°
class CTristram_Arghus : public CNPC
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

	// SetMode
	virtual void SetMode(int _iMode);

public:
	explicit CTristram_Arghus(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTristram_Arghus();
};
