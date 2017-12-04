#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_Companion : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_Companion();
	virtual ~CDemonHunter_Female_Companion();
};
