#pragma once
#include "monsterstate.h"

class CTriune_Vessel_Activating :
	public CMonsterState
{
private:
	float m_fActivationTime;
	int m_iActivationCount;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Vessel_Activating(void);
	virtual ~CTriune_Vessel_Activating(void);
};
