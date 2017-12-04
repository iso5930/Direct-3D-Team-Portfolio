#pragma once
#include "monsterstate.h"

class CZombie_Male_Attack :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// Effect
	float m_fEffectCreateTime;
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CZombie_Male_Attack(void);
	virtual ~CZombie_Male_Attack(void);
};
