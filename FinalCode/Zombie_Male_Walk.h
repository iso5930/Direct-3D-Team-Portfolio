#pragma once
#include "monsterstate.h"

class CZombie_Male_Walk :
	public CMonsterState
{
private:
	// Mode
	int	m_iMode;

	// Time
	float m_fTime;	
	float m_fWaitTime;
	float m_fChaseTime;

	bool m_bHover;
	D3DXVECTOR3	m_vHoverPos;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0 (Slow Walk - Player Don't Exist)
	CMonsterState*	Mode0();

	// Mode1 (Fast Walk - Player Exist)
	CMonsterState*	Mode1();

	// Mode2 (Attack range exist player. but, zombie go away.)
	CMonsterState*	Mode2();

	CMonsterState*	Mode3();

public:
	explicit CZombie_Male_Walk(int _iMode);
	virtual ~CZombie_Male_Walk(void);
};
