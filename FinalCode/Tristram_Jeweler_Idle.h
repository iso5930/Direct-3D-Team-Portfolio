#pragma once

#include "NPCState.h"

class CTristram_Jeweler_Idle : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Jeweler_Idle();
	virtual ~CTristram_Jeweler_Idle();
};
