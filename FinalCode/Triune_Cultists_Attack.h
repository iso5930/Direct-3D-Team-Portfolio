#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Attack :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();
	
	// Mode1
	CMonsterState* Mode1();

public:
	explicit CTriune_Cultists_Attack(void);
	virtual ~CTriune_Cultists_Attack(void);
};
