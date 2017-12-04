#pragma once
#include "monsterstate.h"

class CZombie_Male_Idle :
	public CMonsterState
{
private:
	// ��ȸ �ð�
	float	m_fHoverTime;

	// ���� ���� �ɷ��� �� ���� �ð�
	float	m_fWaitTime;

	// ���
	float	m_fWorryTime;
	bool	m_bWorry;
	int		m_iWorryRand;
	float	m_fWorryMaxTime;

	int		m_iHover;

	int		m_iMode;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// ���
	CMonsterState*	Mode0();

	// ���� �� ��Ž��
	CMonsterState*	Mode1();

	// ���
	CMonsterState*	Mode2();

public:
	explicit CZombie_Male_Idle(int _iMode);
	virtual ~CZombie_Male_Idle(void);
};
