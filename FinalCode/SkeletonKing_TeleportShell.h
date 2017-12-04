#pragma once
#include "effect.h"

class CSkeletonKing_TeleportShell :
	public CEffect
{
private:
	float m_fSize;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonKing_TeleportShell(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CSkeletonKing_TeleportShell(void);
};
