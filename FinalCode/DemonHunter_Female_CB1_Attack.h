#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB1_Attack : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB1_Attack();
	virtual ~CDemonHunter_Female_CB1_Attack();
};
