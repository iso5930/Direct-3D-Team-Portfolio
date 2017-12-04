#pragma once

#include "NPCState.h"

class CTristram_Jeweler_Talk : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Jeweler_Talk();
	virtual ~CTristram_Jeweler_Talk();
};
