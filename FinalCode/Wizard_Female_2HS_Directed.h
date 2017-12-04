#pragma once
#include "playerstate.h"

class CWizard_Female_2HS_Directed :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_2HS_Directed(void);
	virtual ~CWizard_Female_2HS_Directed(void);
};
