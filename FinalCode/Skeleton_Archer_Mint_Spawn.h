#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Mint_Spawn :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Archer_Mint_Spawn(void);
	virtual ~CSkeleton_Archer_Mint_Spawn(void);
};