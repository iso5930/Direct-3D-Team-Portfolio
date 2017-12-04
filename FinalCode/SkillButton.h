#pragma once

#include "ButtonUI.h"

class CSlotMessage;

class CSkillButton : public CButtonUI
{
private:
	// SlotType
	SLOT_TYPE m_eSlotType;

	// SlotID
	SLOT_ID m_eSlotID;

	// SlotMessage
	CSlotMessage* m_pSlotMessage;

	// KeySign


public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetSlotType
	SLOT_TYPE GetSlotType() { return m_eSlotType; }

	// GetSlotID
	SLOT_ID GetSlotID() { return m_eSlotID; }

public:
	explicit CSkillButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, SLOT_TYPE _eSlotType, SLOT_ID _eSlotID);
	virtual ~CSkillButton();
};
