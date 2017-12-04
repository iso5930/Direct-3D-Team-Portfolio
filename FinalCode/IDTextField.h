#pragma once

#include "TextFieldUI.h"

class CIDTextField : public CTextFieldUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CIDTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CIDTextField();
};
