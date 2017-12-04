#pragma once

#include "MonsterState.h"

class CZombie_Female_Attack : public CMonsterState
{
private:
	// Mode
	int	m_iMode;

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
	CMonsterState*	Mode0();

	// Mode1
	CMonsterState*	Mode1();

public:
	explicit CZombie_Female_Attack();
	virtual ~CZombie_Female_Attack();
};
