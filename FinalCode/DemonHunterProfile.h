#pragma once

#include "ProfileUI.h"

class CDemonHunterProfile : public CProfileUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunterProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CDemonHunterProfile();
};
