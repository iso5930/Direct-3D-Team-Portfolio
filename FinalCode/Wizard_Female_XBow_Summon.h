#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_Summon :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_Summon(void);
	virtual ~CWizard_Female_XBow_Summon(void);
};
