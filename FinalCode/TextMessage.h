#pragma once

#include "MessageUI.h"

class CTextMessage : public CMessageUI
{
private:
	// Time
	float m_fTime;

	// Alpha
	float m_fAlpha;

	// Mode
	int m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

	// Mode2
	void Mode2();

public:
	explicit CTextMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText);
	virtual ~CTextMessage();
};
