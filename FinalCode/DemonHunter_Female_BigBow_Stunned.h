#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_BigBow_Stunned : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_BigBow_Stunned();
	virtual ~CDemonHunter_Female_BigBow_Stunned();
};
