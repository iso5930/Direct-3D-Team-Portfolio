#pragma once
#include "monsterstate.h"

class CButcher_Run :
	public CMonsterState
{
private:
	D3DXVECTOR3 m_vDir;
	float m_fTime;
	int m_iMode;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CButcher_Run(D3DXVECTOR3* _pDir);
	virtual ~CButcher_Run(void);
};
