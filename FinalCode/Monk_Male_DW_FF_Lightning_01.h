#pragma once
#include "playerstate.h"

class CMonk_Male_DW_FF_Lightning_01 :	public CPlayerState
{
private:
	int m_iMode;

	int	m_iSlotNum;
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	CPlayerState* Mode0();
	CPlayerState* Mode1();
	CPlayerState* Mode2();

public:
	explicit CMonk_Male_DW_FF_Lightning_01(void);
	virtual ~CMonk_Male_DW_FF_Lightning_01(void);
};
