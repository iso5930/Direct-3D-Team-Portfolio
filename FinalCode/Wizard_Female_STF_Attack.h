#pragma once
#include "playerstate.h"

class CWizard_Female_STF_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_STF_Attack(void);
	virtual ~CWizard_Female_STF_Attack(void);
};
