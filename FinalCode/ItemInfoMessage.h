#pragma once

#include "MessageUI.h"

class CItemPannelMessage;
class CItemGridMessage;
class CItemIconMessage;
class CSockSign;
class CStatMarkSign;

class CItemInfoMessage : public CMessageUI
{
private:
	// Item
	Item* m_pItem;

	// ItemPannelMessage
	CItemPannelMessage* m_pItemPannelMessage;

	// ItemGridMessage
	CItemGridMessage* m_pItemGridMessage;

	// ItemIconMessage
	CItemIconMessage* m_pItemIconMessage;

	// ItemSockSign
	CSockSign* m_pItemSockSign[3];

	// StatMarkSign
	vector<CStatMarkSign*> m_StatMarkVec;

	// Color
	D3DXCOLOR m_dwColor;

	// Class
	TCHAR m_tszClass[MIN_STR];

	// Type
	TCHAR m_tszType[MIN_STR];

	// Gender
	TCHAR m_tszGender[MIN_STR];

	// Job
	TCHAR m_tszJob[MIN_STR];

	// Level
	TCHAR m_tszLevel[MIN_STR];

	// Value
	TCHAR m_tszValue[MIN_STR];
	TCHAR m_tszValueType[MIN_STR];

	// AttackStat
	TCHAR m_tszAttackStat[MIN_STR];
	TCHAR m_tszAttackStatType[MIN_STR];

	// DefenseStat
	TCHAR m_tszDefenseStat[MIN_STR];
	TCHAR m_tszDefenseStatType[MIN_STR];

	// LifeStat
	TCHAR m_tszLifeStat[MIN_STR];
	TCHAR m_tszLifeStatType[MIN_STR];

	// ResourceStat
	TCHAR m_tszResourceStat[MIN_STR];
	TCHAR m_tszResourceStatType[MIN_STR];

	// AdventureStat
	TCHAR m_tszAdventureStat[MIN_STR];
	TCHAR m_tszAdventureStatType[MIN_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CItemInfoMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem);
	virtual ~CItemInfoMessage();
};
