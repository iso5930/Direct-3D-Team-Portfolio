#pragma once

#include "WindowUI.h"

class CBasicSign;

class CBarbarianMightWindow : public CWindowUI
{
private:
	// Select
	int m_iSelect;

	// Index
	int m_iIndex;

	// SlotID
	SLOT_ID m_eSlotID;

	// Name
	RECT m_rcName[3];
	TCHAR m_tszName[3][MIN_STR];

	// Level
	RECT m_rcLevel[3];
	TCHAR m_tszLevel[3][MIN_STR];

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
	explicit CBarbarianMightWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iIndex, SLOT_ID _eSlotID);
	virtual ~CBarbarianMightWindow();
};
