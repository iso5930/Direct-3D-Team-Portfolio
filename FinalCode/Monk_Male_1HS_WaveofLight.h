#pragma once
#include "playerstate.h"

class CMonk_Male_1HS_WaveofLight :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HS_WaveofLight(void);
	virtual ~CMonk_Male_1HS_WaveofLight(void);
};
