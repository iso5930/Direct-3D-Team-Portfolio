#pragma once

#include "MessageUI.h"

class CPWEmptyMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CPWEmptyMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CPWEmptyMessage();
};
