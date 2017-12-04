#pragma once
#include "effect.h"

class CDemonHunter_Grenades_GrenadesEffect : public CEffect
{
private:
	float m_fDetail;
	int		m_iCount;
	D3DXVECTOR3 m_vPos;	
	D3DXVECTOR3 m_vDestPos;
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vEndPos;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();
	void Mode3();

public:
	D3DXVECTOR3	GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail);

public:
	explicit CDemonHunter_Grenades_GrenadesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos);
	virtual ~CDemonHunter_Grenades_GrenadesEffect(void);
};