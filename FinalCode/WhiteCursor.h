#pragma once

#include "CursorUI.h"

class CWhiteCursor : public CCursorUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWhiteCursor(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CWhiteCursor();
};
