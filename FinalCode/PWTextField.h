#pragma once

#include "TextFieldUI.h"

class CPWTextField : public CTextFieldUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CPWTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CPWTextField();
};
