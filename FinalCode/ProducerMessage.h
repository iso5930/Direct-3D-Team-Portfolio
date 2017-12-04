#pragma once

#include "MessageUI.h"

class CProducerMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CProducerMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CProducerMessage();
};
