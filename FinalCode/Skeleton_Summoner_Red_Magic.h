#pragma once
#include "monsterstate.h"

class CSkeletonSummoner_ArcaneBall;
class CSkeleton_Summoner_Red_Magic :
	public CMonsterState
{
private:
	CSkeletonSummoner_ArcaneBall* m_pArcaneBall;
	bool m_bEffect;

private:
	int m_iMode;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CSkeleton_Summoner_Red_Magic(int _iMode);
	virtual ~CSkeleton_Summoner_Red_Magic(void);
};
