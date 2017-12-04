#pragma once

#include "SignUI.h"

class CBasicSign;
class CStoreGridSign;
class CItemMessage;

class CStoreSign : public CSignUI
{
private:
	// Item
	Item* m_pItem;

	// Sign
	CBasicSign* m_pSign;

	// StoreGridSign
	CStoreGridSign* m_pGridSign;

	// ItemMessage
	CItemMessage* m_pItemMessage;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetItem
	Item* GetItem() { return m_pItem; }

	// EnableItemMessage
	void EnableItemMessage();

	// DisableItemMessage
	void DisableItemMessage();

public:
	explicit CStoreSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CStoreSign();
};
