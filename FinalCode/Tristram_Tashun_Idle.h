#pragma once

#include "NPCState.h"

class CTristram_Tashun_Idle : public CNPCState
{
public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Tashun_Idle();
	virtual ~CTristram_Tashun_Idle();
};
