#pragma once
#include "monsterstate.h"

class CButcher_Charge_In :
	public CMonsterState
{
private:
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Charge_In(void);
	virtual ~CButcher_Charge_In(void);
};
