#pragma once

#include "Object.h"

class CTrigger : public CObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CTrigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTrigger();
};
