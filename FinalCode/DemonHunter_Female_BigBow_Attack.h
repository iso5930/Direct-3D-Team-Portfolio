#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_BigBow_Attack : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_BigBow_Attack();
	virtual ~CDemonHunter_Female_BigBow_Attack();
};
