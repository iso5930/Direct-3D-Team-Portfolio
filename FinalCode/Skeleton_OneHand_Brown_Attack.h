#pragma once
#include "monsterstate.h"

class CSkeleton_SwordTrailEffect;
class CSkeleton_OneHand_Brown_Attack :
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
	int m_iEffect; // 0 : 飘饭老 积己, 1 : 飘饭老 家戈

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CSkeleton_OneHand_Brown_Attack(void);
	virtual ~CSkeleton_OneHand_Brown_Attack(void);
};
