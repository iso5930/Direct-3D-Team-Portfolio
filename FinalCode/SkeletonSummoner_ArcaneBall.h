#pragma once
#include "effect.h"

class CSkeletonSummoner_ArcaneBall :
	public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	D3DXVECTOR3 m_vFirstPos;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonSummoner_ArcaneBall(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual	~CSkeletonSummoner_ArcaneBall(void);
};
