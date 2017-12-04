#pragma once

#include "UI.h"

class CSignUI : public CUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSignUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CSignUI();
};
