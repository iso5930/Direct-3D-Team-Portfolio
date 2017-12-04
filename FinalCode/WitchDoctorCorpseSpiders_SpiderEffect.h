#pragma once
#include "effect.h"

class CDynamicMesh;
class CWitchDoctorCorpseSpiders_SpiderEffect : public CEffect
{
private:
	vector<CObject*> m_vecMonster;
	CDynamicMesh* m_pMesh;
	float	m_fTime;
	float	m_fAccTime;
	int m_iMode;
	bool	m_bCheck;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode0(); //idle
	void Mode1(); //Run
	void Mode2(); //attack


public:
	explicit CWitchDoctorCorpseSpiders_SpiderEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWitchDoctorCorpseSpiders_SpiderEffect(void);
};
