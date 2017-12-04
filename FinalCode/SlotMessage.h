#pragma once

#include "MessageUI.h"

class CSlotMessage : public CMessageUI
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSlotMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, SLOT_ID _eSlotID);
	virtual ~CSlotMessage();
};
