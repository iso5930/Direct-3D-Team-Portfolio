#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_Impale : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_Impale();
	virtual ~CDemonHunter_Female_CB2_Impale();
};
