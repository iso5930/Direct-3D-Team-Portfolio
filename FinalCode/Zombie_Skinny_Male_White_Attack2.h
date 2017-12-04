#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_White_Attack2 : public CMonsterState
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
	explicit CZombie_Skinny_Male_White_Attack2(void);
	virtual ~CZombie_Skinny_Male_White_Attack2(void);
};
