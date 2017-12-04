#pragma once
#include "monster.h"

class CStitch :
	public CMonster
{
public:
	// RightHandBone
	Bone m_RightHandBone;

	// RightElbowBone
	Bone m_RightElbowBone;

	// Spike
	Bone m_SpikeABone;
	Bone m_SpikeBBone;
	Bone m_SpikeCBone;
	Bone m_SpikeDBone;
	Bone m_SpikeEBone;
	Bone m_SpikeFBone;
	Bone m_SpikeGBone;
	Bone m_SpikeHBone;
	Bone m_SpikeIBone;
	Bone m_SpikeJBone;
	Bone m_SpikeKBone;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	virtual void CreateAttack();
	virtual void Damage(CPlayer* _pPlayer);
	virtual void Damage(CEffect* _pEffect);

public:
	explicit CStitch(TCHAR*	_tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CStitch(void);
};
