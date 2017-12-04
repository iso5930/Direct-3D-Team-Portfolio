#pragma once

#include "ButtonUI.h"

class CStorageButton : public CButtonUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CStorageButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey);
	virtual ~CStorageButton();
};
