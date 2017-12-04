#pragma once
#include "monsterstate.h"

class CSkeleton_King_Teleport_Attack :
	public CMonsterState
{
private:
	int m_iMode;
	float m_fTime;
	bool m_bEffect;
	float m_fEctoplasmTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CSkeleton_King_Teleport_Attack(void);
	virtual ~CSkeleton_King_Teleport_Attack(void);
};
