#pragma once

#include "NPCState.h"

class CTristram_Mystic_Walk : public CNPCState
{
private:
	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_Mystic_Walk();
	virtual ~CTristram_Mystic_Walk();
};
