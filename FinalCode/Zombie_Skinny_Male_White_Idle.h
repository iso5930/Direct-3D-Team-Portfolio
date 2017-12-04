#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_White_Idle : public CMonsterState
{
private:
	// 배회 시간
	float	m_fHoverTime;

	// 정지 상태 걸렸을 때 정지 시간
	float	m_fWaitTime;

	// 고민
	float	m_fWorryTime;
	bool	m_bWorry;
	int		m_iWorryRand;
	float	m_fWorryMaxTime;

	int		m_iHover;

	int		m_iMode;


public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// 대기
	CMonsterState*	Mode0();

	// 정지 후 재탐색
	CMonsterState*	Mode1();

	// 고민
	CMonsterState*	Mode2();

public:
	explicit CZombie_Skinny_Male_White_Idle(int _iMode);
	virtual ~CZombie_Skinny_Male_White_Idle(void);
};
