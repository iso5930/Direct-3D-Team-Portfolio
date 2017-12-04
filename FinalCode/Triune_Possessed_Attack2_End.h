#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Attack2_End :
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
	explicit CTriune_Possessed_Attack2_End(void);
	virtual ~CTriune_Possessed_Attack2_End(void);
};
