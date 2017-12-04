#pragma once
#include "effect.h"

class CZombieFemale_PukeGroundDecal :
	public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CZombieFemale_PukeGroundDecal(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CZombieFemale_PukeGroundDecal(void);
};
