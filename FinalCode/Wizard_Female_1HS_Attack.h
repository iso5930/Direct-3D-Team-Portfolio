#pragma once
#include "playerstate.h"

class CWizard_Female_1HS_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_1HS_Attack(void);
	virtual ~CWizard_Female_1HS_Attack(void);
};
