#pragma once
#include "effect.h"

class CMaterialCom;
class CWitchDoctor_LocustsSwarm_DummyEffect : public CEffect
{
private:
	int m_iMode;

	float m_fTime;

	float m_fCreateTime2;
	float m_fCreateTime;

	int m_iCreateCnt;
	int m_iCreateCnt2;

	D3DXVECTOR3 m_vDir;
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	void	Mode0();



public:
	explicit CWitchDoctor_LocustsSwarm_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3& _vDir);
	virtual ~CWitchDoctor_LocustsSwarm_DummyEffect(void);
};