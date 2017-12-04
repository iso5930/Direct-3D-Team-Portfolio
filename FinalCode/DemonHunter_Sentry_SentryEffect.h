#pragma once
#include "effect.h"

class CDemonHunter_Sentry_BaseEffect;
class CDemonHunter_Sentry_SentryEffect : public CEffect
{
private:
	vector<CObject*> m_vecMonster;
	CDynamicMesh* m_pMesh;
	float	m_fTime;
	float	m_fAccTime;
	int m_iMode;
	bool	m_bCheck;

private:
	CDemonHunter_Sentry_BaseEffect* m_pBaseEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1(); //����
	void Mode2(); //���
	void Mode3(); //����
	void Mode4(); //����2
	void Mode5(); //�Ҹ�

public:
	void SentryDestory();

public:
	explicit CDemonHunter_Sentry_SentryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Sentry_SentryEffect(void);
};