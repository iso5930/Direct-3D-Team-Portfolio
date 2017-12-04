#pragma once
#include "effect.h"

class CDemonHunter_ClusterArrow_GrenadesEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vBezierPos;
	D3DXVECTOR3 m_vEndPos;
	float		m_fDetail;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	D3DXVECTOR3	GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail);

public:
	explicit CDemonHunter_ClusterArrow_GrenadesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos);
	virtual ~CDemonHunter_ClusterArrow_GrenadesEffect(void);
};