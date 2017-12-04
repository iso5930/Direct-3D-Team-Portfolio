#pragma once
#include "monsterstate.h"

class CSkeleton_Shield_Mint_Walk :
	public CMonsterState
{
private:
	int	m_iMode;

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
	CSkeleton_Shield_Mint_Walk(int _iMode);
	~CSkeleton_Shield_Mint_Walk(void);
};
