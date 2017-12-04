#pragma once

#include "MessageUI.h"

class CManaMessage : public CMessageUI
{
private:
	// Mana
	int m_iMana;

	// MaxMana
	int m_iMaxMana;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CManaMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CManaMessage();
};
