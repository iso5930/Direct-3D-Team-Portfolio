#pragma once
#include "monsterstate.h"

class CWarden_Run :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// FarAttack
	float m_fFarAttackTime;
	float m_fFarAttackMaxTime;
	int	m_iFarAttackRand;
	
	// Time
	float m_fTime;
	float m_fChaseTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CWarden_Run(int _iMode);
	virtual ~CWarden_Run(void);
};
