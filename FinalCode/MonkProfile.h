#pragma once

#include "ProfileUI.h"

class CMonkProfile : public CProfileUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonkProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMonkProfile();
};
