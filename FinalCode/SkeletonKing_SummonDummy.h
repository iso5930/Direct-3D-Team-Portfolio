#pragma once
#include "effect.h"

class CSkeletonKing_EctoplasmBase;
class CSkeletonKing_SummonDummy :
	public CEffect
{
private:
	float m_fDetail;
	float m_fTime;
	D3DXVECTOR3 m_vBezierPos;
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vEndPos;

	CSkeletonKing_EctoplasmBase* m_pTrailEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	D3DXVECTOR3	GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail);

public:
	explicit CSkeletonKing_SummonDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vEndPos);
	virtual ~CSkeletonKing_SummonDummy(void);
};
