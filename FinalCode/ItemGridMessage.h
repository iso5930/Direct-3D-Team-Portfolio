#pragma once

#include "MessageUI.h"

class CItemGridMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemGridMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CItemGridMessage();
};
