#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_Directed :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_Directed(void);
	virtual ~CWizard_Female_XBow_Directed(void);
};
