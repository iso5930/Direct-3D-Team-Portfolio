#pragma once

#include "MessageUI.h"

class CHateMessage : public CMessageUI
{
private:
	// Hate
	int m_iHate;

	// MaxHate
	int m_iMaxHate;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CHateMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CHateMessage();
};
