#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_BigBow_MultiShot : public CPlayerState
{
private:


public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_BigBow_MultiShot();
	virtual ~CDemonHunter_Female_BigBow_MultiShot();
};
