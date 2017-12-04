#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_Attack :	public CPlayerState
{
private:
	int		m_iMode;
	float	m_fTime;
	
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	CPlayerState* Mode0();
	CPlayerState* Mode1();

public:
	explicit CBarbarian_Male_1HS_Attack(void);
	virtual ~CBarbarian_Male_1HS_Attack(void);
};