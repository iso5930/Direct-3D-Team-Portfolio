#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_Red_Idle : public CMonsterState
{
private:
	// ��ȸ �ð�
	float	m_fHoverTime;

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
	explicit CZombie_Skinny_Male_Red_Idle(int _iMode);
	virtual ~CZombie_Skinny_Male_Red_Idle(void);
};
