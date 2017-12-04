#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_WayPoint : public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_WayPoint();
	virtual ~CDemonHunter_Female_WayPoint();
};
