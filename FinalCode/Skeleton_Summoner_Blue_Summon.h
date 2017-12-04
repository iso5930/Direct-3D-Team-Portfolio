#pragma once
#include "monsterstate.h"

class CSkeletonSummoner_SummonEffect;
class CSkeleton_Summoner_Blue_Summon :
	public CMonsterState
{
private:
	CSkeletonSummoner_SummonEffect* m_pSummonEffect;
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Summoner_Blue_Summon(void);
	virtual	~CSkeleton_Summoner_Blue_Summon(void);
};
