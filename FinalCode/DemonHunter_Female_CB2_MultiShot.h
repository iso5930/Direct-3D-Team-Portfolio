#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_MultiShot : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_MultiShot();
	virtual ~CDemonHunter_Female_CB2_MultiShot();
};
