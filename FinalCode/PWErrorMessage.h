#pragma once

#include "MessageUI.h"

class CPWErrorMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CPWErrorMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CPWErrorMessage();
};
