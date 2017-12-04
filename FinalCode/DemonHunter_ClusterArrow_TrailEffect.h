#pragma once
#include "TrailEffect_3.h"

class CDemonHunter_ClusterArrow_TrailEffect : public CTrailEffect_3
{
private:
	D3DXMATRIX* m_pWorld;
	int			m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_ClusterArrow_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld, D3DXVECTOR3 _vDir);
	virtual ~CDemonHunter_ClusterArrow_TrailEffect(void);
};