#pragma once
#include "playerstate.h"

class CWizard_Female_STF_KnockbackEnd :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_STF_KnockbackEnd(void);
	virtual ~CWizard_Female_STF_KnockbackEnd(void);
};
