#pragma once
#include "monsterstate.h"

class CSkeleton_King_Summon :
	public CMonsterState
{
private:
	int m_iCount;
	
	int m_iEffect;
	
	float m_fEctoplasmTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Summon(int _iCount);
	virtual ~CSkeleton_King_Summon(void);
};
