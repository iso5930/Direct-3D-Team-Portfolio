#pragma once
#include "effect.h"

class CDynamicMesh; 

class CWitchDoctorCorpseSpidersEffect : public CEffect
{
private:
	float m_fDetail;
	int		m_iMode;
	D3DXVECTOR3 m_vPos;	
	D3DXVECTOR3 m_vDestPos;
	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 m_vEndPos;
	CDynamicMesh* m_pDynamicMesh;

	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode0();
	void Mode1();
	void Mode2();


public:
	D3DXVECTOR3	GetBezier(D3DXVECTOR3 _v1, D3DXVECTOR3 _v2, D3DXVECTOR3 _v3, float _fDetail);

public:
	explicit CWitchDoctorCorpseSpidersEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDestPos);
	virtual ~CWitchDoctorCorpseSpidersEffect(void);
};