#pragma once
#include "playerstate.h"

class CWizard_Female_1HS_Orb_AOE :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_1HS_Orb_AOE(void);
	virtual ~CWizard_Female_1HS_Orb_AOE(void);
};
