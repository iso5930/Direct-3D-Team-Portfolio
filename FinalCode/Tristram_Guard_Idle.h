#pragma once

#include "NPCState.h"

class CTristram_Guard_Idle : public CNPCState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CNPCState* Action();

private:
	// Mode0
	CNPCState* Mode0();

	// Mode1
	CNPCState* Mode1();

public:
	explicit CTristram_Guard_Idle();
	virtual ~CTristram_Guard_Idle();
};
