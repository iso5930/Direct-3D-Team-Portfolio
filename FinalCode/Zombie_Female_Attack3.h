#pragma once

#include "MonsterState.h"

class CZombie_Female_Attack3 : public CMonsterState
{
private:
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Female_Attack3();
	virtual ~CZombie_Female_Attack3();
};
