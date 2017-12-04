#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_BackFlip : public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_BackFlip();
	virtual ~CDemonHunter_Female_CB2_BackFlip();
};
