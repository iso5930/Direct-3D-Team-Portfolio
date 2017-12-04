#pragma once
#include "monsterstate.h"

class CSkeleton_OneHand_Mint_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_OneHand_Mint_Hit(void);
	virtual ~CSkeleton_OneHand_Mint_Hit(void);
};
