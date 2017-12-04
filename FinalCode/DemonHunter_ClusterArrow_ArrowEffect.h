#pragma once
#include "effect.h"

class CDemonHunter_ClusterArrow_TrailEffect;
class CDemonHunter_ClusterArrow_ArrowEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	CDemonHunter_ClusterArrow_TrailEffect* m_pTrailEffect;
	D3DXVECTOR3 m_vDest;
	float	m_fTime;
	int		m_iTest;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_ClusterArrow_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDest);
	virtual ~CDemonHunter_ClusterArrow_ArrowEffect(void);
};
