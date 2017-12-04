#pragma once

#include "StaticProb.h"

class CFireEffect;
class CGateWay : public CStaticProb
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
	// Event
	virtual void Event();

	// EventEnd
	virtual void EventEnd();

public:
	// GetGateWayType
	GATE_WAY_TYPE GetGateWayType() { return m_eGateWayType; }

public:
	explicit CGateWay(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, GATE_WAY_TYPE _eGateWayType);
	virtual ~CGateWay();
};
