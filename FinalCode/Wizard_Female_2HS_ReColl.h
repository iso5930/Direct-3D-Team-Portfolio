#pragma once
#include "playerstate.h"

class CWizard_Female_2HS_ReColl :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_2HS_ReColl(void);
	virtual ~CWizard_Female_2HS_ReColl(void);
};
