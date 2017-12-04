#pragma once

#include "MessageUI.h"

class CAdviceMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CAdviceMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CAdviceMessage();
};
