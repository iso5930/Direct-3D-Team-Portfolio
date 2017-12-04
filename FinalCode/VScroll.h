#pragma once

#include "ScrollUI.h"

class CVScroll : public CScrollUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CVScroll(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CVScroll();
};
