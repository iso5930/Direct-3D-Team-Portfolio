#pragma once

#include "MessageUI.h"

class CControlMessage : public CMessageUI
{
private:
	// Control
	int m_iControl;

	// MaxControl
	int m_iMaxControl;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CControlMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CControlMessage();
};
