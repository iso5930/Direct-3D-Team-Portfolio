#pragma once

#include "TextFieldUI.h"

class CNameTextField : public CTextFieldUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CNameTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CNameTextField();
};
