#pragma once
#include "playerstate.h"

class CBarbarian_Male_2HT_HirlWind :	public CPlayerState
{
private:
	int m_iMode;

	int m_iPushSlot;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	CPlayerState* Mode0();

	CPlayerState* Mode1();

	CPlayerState* SlotAction(int _iIndex);

public:
	explicit CBarbarian_Male_2HT_HirlWind(int _iPushSlot);
	virtual ~CBarbarian_Male_2HT_HirlWind(void);
};
