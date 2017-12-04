#pragma once

#include "WindowUI.h"

class CDetailMessage;

class CDetailWindow : public CWindowUI
{
private:
	// TextMessage
	CDetailMessage* m_pTextMessage[29];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	explicit CDetailWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CDetailWindow();
};
