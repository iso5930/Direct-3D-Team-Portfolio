#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Red_Attack :
	public CMonsterState
{
private:
	int m_iMode;

	// Effect
	CSkeleton_ArrowEffect* m_pArrowEffect;
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CSkeleton_Archer_Red_Attack(int _iMode);
	virtual ~CSkeleton_Archer_Red_Attack(void);
};
