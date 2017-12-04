#pragma once

#include "NPCState.h"

class CTristram_Mystic_Talk : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Mystic_Talk();
	virtual ~CTristram_Mystic_Talk();
};
