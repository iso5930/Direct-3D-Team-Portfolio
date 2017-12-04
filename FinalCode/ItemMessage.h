#pragma once

#include "MessageUI.h"

class CItemNameMessage;
class CItemValueMessage;
class CItemInfoMessage;

class CItemMessage : public CMessageUI
{
private:
	// Item
	Item* m_pItem;

	// ItemNameMessage
	CItemNameMessage* m_pItemNameMessage;

	// ItemValueMessage
	CItemValueMessage* m_pItemValueMessage;

	// ItemInfoMessage
	CItemInfoMessage* m_pItemInfoMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CItemMessage();
};
