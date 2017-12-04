#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_Red_Walk1 : public CMonsterState
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

	CMonsterState*	Mode2();

public:
	explicit CZombie_Skinny_Male_Red_Walk1(int _iMode);
	virtual ~CZombie_Skinny_Male_Red_Walk1(void);
};
