#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Mint_Walk :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Archer_Mint_Walk(void);
	virtual ~CSkeleton_Archer_Mint_Walk(void);
};
