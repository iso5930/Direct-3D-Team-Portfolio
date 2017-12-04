#pragma once
#include "monsterstate.h"

class CSkeleton_Summoner_Brown_Idle :
	public CMonsterState
{
private:
	// ���
	int		m_iMode;

	// ���ݴ�� �ð�
	float	m_fWorryTime;

	// ��ȸ
	float	m_fHoverTime;
	int		m_iHover;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CSkeleton_Summoner_Brown_Idle(int _iMode);
	virtual ~CSkeleton_Summoner_Brown_Idle(void);
};