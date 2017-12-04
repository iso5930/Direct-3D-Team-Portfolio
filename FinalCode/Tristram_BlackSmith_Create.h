#pragma once

#include "NPCState.h"

class CTristram_BlackSmith_Create : public CNPCState
{
private:
	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CNPCState* Action();

public:
	explicit CTristram_BlackSmith_Create();
	virtual ~CTristram_BlackSmith_Create();
};
