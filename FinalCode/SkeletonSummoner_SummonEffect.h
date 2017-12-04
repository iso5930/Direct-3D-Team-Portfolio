#pragma once
#include "effect.h"

class CSkeletonSummoner_SummonTrailEffect;
class CSkeletonSummoner_SummonSkeleton;
class CSkeletonSummoner_SummonEffect :
	public CEffect
{
private:
	float		m_fDetail;
	D3DXVECTOR3 m_vBezierPos;	
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vEndPos;

	CSkeletonSummoner_SummonTrailEffect* m_pTrailEffect;
	CSkeletonSummoner_SummonSkeleton* m_pSummonSkeletonEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	D3DXVECTOR3	GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail);

public:
	explicit CSkeletonSummoner_SummonEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _vDestPos);
	virtual ~CSkeletonSummoner_SummonEffect(void);
};
