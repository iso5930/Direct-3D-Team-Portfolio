#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_BolaSlot : public CPlayerState
{
private:
	// PushSlot
	int m_iPushSlot;

	// Mode
	int	m_iMode;

	// Time
	float m_fTime;



public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	// ����
	CPlayerState* Mode0();

	// ����
	CPlayerState* Mode1();

	// SlotAtion
	CPlayerState* SlotAction(int _iIndex); 

	bool IsSlotRange(int _iIndex);

public:
	explicit CDemonHunter_Female_CB2_BolaSlot(int _iPushSlot);
	virtual ~CDemonHunter_Female_CB2_BolaSlot();
};
