#pragma once

#include "UI.h"

class CProfileUI : public CUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CProfileUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CProfileUI();
};
