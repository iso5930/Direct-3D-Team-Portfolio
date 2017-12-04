#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB1_Hit : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB1_Hit();
	virtual ~CDemonHunter_Female_CB1_Hit();
};
