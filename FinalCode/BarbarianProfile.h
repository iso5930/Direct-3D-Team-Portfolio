#pragma once

#include "ProfileUI.h"

class CBarbarianProfile : public CProfileUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CBarbarianProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CBarbarianProfile();
};
