#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_White_Attack3 : public CMonsterState
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
	CMonsterState*	Mode0();

	// Mode1
	CMonsterState*	Mode1();

public:
	explicit CZombie_Skinny_Male_White_Attack3(void);
	virtual ~CZombie_Skinny_Male_White_Attack3(void);
};
