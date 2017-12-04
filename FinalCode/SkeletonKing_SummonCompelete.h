#pragma once
#include "effect.h"

class CSkeletonKing_SummonCompelete :
	public CEffect
{
private:
	float m_fSize;
	D3DXVECTOR3 m_vOriginPos;
	bool m_bCreate;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonKing_SummonCompelete(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos, bool _bCreate = false);
	virtual ~CSkeletonKing_SummonCompelete(void);
};
