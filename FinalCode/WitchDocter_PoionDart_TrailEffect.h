#pragma once
#include "traileffect.h"

class CWitchDocter_PoionDart_TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();
	
public:
	explicit CWitchDocter_PoionDart_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType , int _iTrailNum , D3DXMATRIX* _pMatrix , D3DXVECTOR3& vUp ,  D3DXVECTOR3& vDown , float _fTrailInv , TCHAR* _tszTrailName, int _iPass );
	virtual ~CWitchDocter_PoionDart_TrailEffect(void);
};