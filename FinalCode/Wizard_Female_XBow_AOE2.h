#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_AOE2 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_AOE2(void);
	virtual ~CWizard_Female_XBow_AOE2(void);
};