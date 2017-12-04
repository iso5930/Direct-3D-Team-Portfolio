#pragma once

#include "MessageUI.h"

class CCharacterEmptyMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CCharacterEmptyMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CCharacterEmptyMessage();
};
