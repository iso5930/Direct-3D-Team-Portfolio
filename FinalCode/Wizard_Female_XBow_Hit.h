#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_Hit :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_Hit(void);
	virtual ~CWizard_Female_XBow_Hit(void);
};
