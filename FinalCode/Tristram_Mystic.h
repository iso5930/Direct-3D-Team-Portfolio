#pragma once

#include "NPC.h"

// 메인퀘스트
class CTristram_Mystic : public CNPC
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
	explicit CTristram_Mystic(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTristram_Mystic();
};
