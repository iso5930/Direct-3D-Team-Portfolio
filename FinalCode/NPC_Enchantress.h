#pragma once

#include "NPC.h"

class CNPC_Enchantress : public CNPC
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
	explicit CNPC_Enchantress(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CNPC_Enchantress();
};
