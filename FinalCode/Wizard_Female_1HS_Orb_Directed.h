#pragma once
#include "playerstate.h"

class CWizard_Female_1HS_Orb_Directed :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_1HS_Orb_Directed(void);
	virtual ~CWizard_Female_1HS_Orb_Directed(void);
};