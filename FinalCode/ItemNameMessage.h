#pragma once

#include "MessageUI.h"

class CItemNameMessage : public CMessageUI
{
private:
	// Item
	Item* m_pItem;

	// Color
	D3DXCOLOR m_dwColor;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemNameMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CItemNameMessage();
};
