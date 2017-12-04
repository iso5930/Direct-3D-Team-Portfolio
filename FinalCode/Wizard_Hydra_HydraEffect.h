#pragma once
#include "effect.h"

class CDynamicMesh;
class CWizard_Hydra_HydraEffect : public CEffect
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
	void Mode1(); //생성
	void Mode2(); //대기
	void Mode3(); //공격
	void Mode4(); //공격2
	void Mode5(); //소멸

public:
	void HydraDestory();

public:
	explicit CWizard_Hydra_HydraEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Hydra_HydraEffect(void);
};
