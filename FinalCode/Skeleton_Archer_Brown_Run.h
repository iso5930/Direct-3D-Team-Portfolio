#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Brown_Run :
	public CMonsterState
{
private:
	int m_iMode;
	float m_fTime;
	float m_fEscapeTime;
	float m_fChaseTime;
	D3DXVECTOR3 m_vEscapePos;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CSkeleton_Archer_Brown_Run(int _iMode);
	virtual ~CSkeleton_Archer_Brown_Run(void);
};
