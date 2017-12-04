#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Run :
	public CMonsterState
{
private:
	int m_iMode;

	float m_fTime;
	float m_fChaseTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CTriune_Cultists_Run(int _iMode);
	virtual ~CTriune_Cultists_Run(void);
};
