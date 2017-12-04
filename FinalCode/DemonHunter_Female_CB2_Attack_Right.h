#pragma once

#include "PlayerState.h"



class CDemonHunter_Female_CB2_Attack_Right : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_Attack_Right();
	virtual ~CDemonHunter_Female_CB2_Attack_Right();
};
