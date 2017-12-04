#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_Buff : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_Buff();
	virtual ~CDemonHunter_Female_CB2_Buff();
};
