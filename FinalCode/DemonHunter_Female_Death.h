#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_Death : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_Death();
	virtual ~CDemonHunter_Female_Death();
};
