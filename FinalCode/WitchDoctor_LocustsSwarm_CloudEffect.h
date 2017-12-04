#pragma once
#include "effect.h"

class CWitchDoctor_LocustsSwarm_CloudEffect : public CEffect
{
private:
	float	m_fTime;

	float	m_fSizeTime;

	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDoctor_LocustsSwarm_CloudEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner ,D3DXVECTOR3& _vDir);
	virtual ~CWitchDoctor_LocustsSwarm_CloudEffect(void);
};
