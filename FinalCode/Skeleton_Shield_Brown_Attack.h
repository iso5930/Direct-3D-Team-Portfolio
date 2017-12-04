#pragma once
#include "monsterstate.h"

class CSkeleton_Shield_Brown_Attack :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// Effect
	CSkeleton_SwordTrailEffect* m_pSwordTrail;
	float m_fEffectTime;
	int m_iEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0 
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	CSkeleton_Shield_Brown_Attack(void);
	~CSkeleton_Shield_Brown_Attack(void);
};
