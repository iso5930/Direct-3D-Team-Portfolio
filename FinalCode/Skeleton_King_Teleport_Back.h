#pragma once
#include "monsterstate.h"

class CSkeleton_King_Teleport_Back :
	public CMonsterState
{
private:
	D3DXVECTOR3 m_vMovePos;
	bool m_bEffect;
	
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Teleport_Back(void);
	virtual ~CSkeleton_King_Teleport_Back(void);
};
