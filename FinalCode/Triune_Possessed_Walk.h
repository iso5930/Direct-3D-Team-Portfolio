#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Walk :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fAttack2Time;
	float m_fTime;
	float m_fChaseTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CTriune_Possessed_Walk(int _iMode);
	virtual ~CTriune_Possessed_Walk(void);
};
