#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_Attack1 : public CPlayerState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	// Mode0
	CPlayerState* Mode0();

	// Mode1
	CPlayerState* Mode1();

public:
	explicit CDemonHunter_Female_Attack1();
	virtual ~CDemonHunter_Female_Attack1();
};
