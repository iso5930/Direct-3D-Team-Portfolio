#pragma once
#include "monsterstate.h"

class CSkeleton_AxeTrailEffect;
class CSkeleton_Axe_Blue_Attack1 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;
	// Time
	float m_fTime;

	// Effect
	CSkeleton_AxeTrailEffect* m_pAxeTrail;
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
	explicit CSkeleton_Axe_Blue_Attack1(void);
	virtual ~CSkeleton_Axe_Blue_Attack1(void);
};
