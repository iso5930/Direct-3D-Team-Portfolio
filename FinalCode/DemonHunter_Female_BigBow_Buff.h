#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_BigBow_Buff : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_BigBow_Buff();
	virtual ~CDemonHunter_Female_BigBow_Buff();
};
