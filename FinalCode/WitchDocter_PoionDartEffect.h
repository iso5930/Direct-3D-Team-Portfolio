#pragma once
#include "Effect.h"

class CWitchDocter_PoionDart_TrailEffect;

class CWitchDocter_PoionDartEffect :
	public CEffect
{
public:
	D3DXVECTOR3 m_vDir;
	CWitchDocter_PoionDart_TrailEffect* m_pTrailEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWitchDocter_PoionDartEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner ,  D3DXVECTOR3* _pDir);
	virtual ~CWitchDocter_PoionDartEffect(void);

};
