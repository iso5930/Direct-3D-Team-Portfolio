#pragma once

#include "WindowUI.h"

class CBasicSign;

class CBarbarianPrimaryWindow : public CWindowUI
{
private:
	// Select
	int m_iSelect;

	// Index
	int m_iIndex;

	// SlotID
	SLOT_ID m_eSlotID;

	// Name
	RECT m_rcName[4];
	TCHAR m_tszName[4][MIN_STR];

	// Level
	RECT m_rcLevel[4];
	TCHAR m_tszLevel[4][MIN_STR];

	// DownArrowSign
	CBasicSign* m_pDownArrowSign;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	explicit CBarbarianPrimaryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID);
	virtual ~CBarbarianPrimaryWindow();
};
