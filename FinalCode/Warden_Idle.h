#pragma once
#include "monsterstate.h"

class CWarden_Idle :
	public CMonsterState
{
private:
	// Mode
	// 0 : �⺻ ���, 1 : ���ݰ� ���� ���� �� ����, 2 : �ӹ�
	int m_iMode;

	// Worry
	float m_fWorryTime;

	// Fetter
	float m_fFetterTime;
	
	// Hover
	float m_fHoverTime;
	int m_iHover;

	// Effect
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CWarden_Idle(int _iMode);
	virtual ~CWarden_Idle(void);
};
