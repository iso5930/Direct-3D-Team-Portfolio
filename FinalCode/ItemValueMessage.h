#pragma once

#include "MessageUI.h"

class CItemValueMessage : public CMessageUI
{
private:
	// Item
	Item* m_pItem;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemValueMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CItemValueMessage();
};
