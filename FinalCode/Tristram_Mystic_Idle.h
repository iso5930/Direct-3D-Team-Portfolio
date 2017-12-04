#pragma once

#include "NPCState.h"

class CTristram_Mystic_Idle : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Mystic_Idle();
	virtual ~CTristram_Mystic_Idle();
};
