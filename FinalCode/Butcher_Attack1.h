#pragma once
#include "monsterstate.h"

class CButcher_AxeTrail;
class CButcher_Attack1 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// Effect
	CButcher_AxeTrail* m_pAxeTrail;
	int m_iEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CButcher_Attack1(void);
	virtual ~CButcher_Attack1(void);
};
