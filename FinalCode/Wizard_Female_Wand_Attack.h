#pragma once
#include "playerstate.h"

class CWizard_Female_Wand_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_Wand_Attack(void);
	virtual ~CWizard_Female_Wand_Attack(void);
};
