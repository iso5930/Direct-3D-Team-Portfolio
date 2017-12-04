#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_Cleave01 :	public CPlayerState
{
private:
	float m_fTime;
	int	m_iMode;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	CPlayerState* Mode0();
	CPlayerState* Mode1();

public:
	explicit CBarbarian_Male_1HS_Cleave01(void);
	virtual ~CBarbarian_Male_1HS_Cleave01(void);
};
