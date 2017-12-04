#pragma once

#include "MessageUI.h"

class CNameEmptyMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CNameEmptyMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CNameEmptyMessage();
};
