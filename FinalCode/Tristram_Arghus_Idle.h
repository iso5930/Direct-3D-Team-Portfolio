#pragma once

#include "NPCState.h"

class CTristram_Arghus_Idle : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Arghus_Idle();
	virtual ~CTristram_Arghus_Idle();
};
