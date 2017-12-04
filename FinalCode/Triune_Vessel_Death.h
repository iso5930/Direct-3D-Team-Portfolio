#pragma once
#include "monsterstate.h"

class CTriune_Vessel_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Vessel_Death(void);
	virtual ~CTriune_Vessel_Death(void);
};
