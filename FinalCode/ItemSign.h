#pragma once

#include "SignUI.h"

class CGridSign;
class CItemMessage;
class CItemPannelSign;
class CSockSign;

class CItemSign : public CSignUI
{
private:
	// Item
	Item* m_pItem;

	// GridSign
	CGridSign* m_pGridSign;

	// ItemMessage
	CItemMessage* m_pItemMessage;

	// ItemPannelSign
	CItemPannelSign* m_pItemPannelSign;

	// SockSign
	CSockSign* m_pSockSign[3];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetItem
	Item* GetItem() { return m_pItem; }

	// EnableGridSign
	void EnableGridSign();

	// DisableGridSign
	void DisableGridSign();

	// EnableItemMessage
	void EnableItemMessage();

	// DisableItemMessage
	void DisableItemMessage();

	// EnableItemPannelSign
	void EnableItemPannelSign();

	// DisableItemPannelSign
	void DisableItemPannelSign();

	// EnableSockSign
	void EnableSockSign();

	// DisableSockSign
	void DisableSockSign();

public:
	explicit CItemSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CItemSign();
};
