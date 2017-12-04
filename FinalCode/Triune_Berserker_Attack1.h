#pragma once
#include "monsterstate.h"

class CSkeleton_AxeTrailEffect;
class CTriune_Berserker_Attack1 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;
	// Time
	float m_fTime;

	// Effect
	CSkeleton_AxeTrailEffect* m_pMaceTrail;
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
	explicit CTriune_Berserker_Attack1(void);
	virtual ~CTriune_Berserker_Attack1(void);
};
