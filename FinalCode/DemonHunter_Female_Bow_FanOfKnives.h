#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_Bow_FanOfKnives : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_Bow_FanOfKnives();
	virtual ~CDemonHunter_Female_Bow_FanOfKnives();
};
