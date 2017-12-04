#pragma once

#include "MessageUI.h"

class CIDEmptyMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CIDEmptyMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CIDEmptyMessage();
};
