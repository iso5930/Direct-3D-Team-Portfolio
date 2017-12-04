#pragma once

#include "WindowUI.h"

class CEnergyUI;
class CSlotButton;
class CCooldownEnergy;
class CBasicMessage;

class CSlotWindow : public CWindowUI
{
private:
	// EnergyVec
	vector<CEnergyUI*> m_EnergyVec;

	// SlotButton
	CSlotButton* m_pSlotButton[7];

	// CooldownEnergy
	CCooldownEnergy* m_pCooldownEnergy[7];

	// InterfaceMessage
	CBasicMessage* m_pInterfaceMessage[5];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	explicit CSlotWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CSlotWindow();
};
