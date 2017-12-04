#pragma once

#include "MessageUI.h"

class CCharacterFullMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CCharacterFullMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCharacterFullMessage();
};
