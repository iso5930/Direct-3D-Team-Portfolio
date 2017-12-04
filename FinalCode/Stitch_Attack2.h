#pragma once
#include "monsterstate.h"

class CStitch_Spike;
class CStitch_Attack2 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;
	
	// Spike
	CStitch_Spike* m_pSpike;

	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CStitch_Attack2(void);
	virtual ~CStitch_Attack2(void);
};
