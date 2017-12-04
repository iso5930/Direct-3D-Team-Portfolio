#pragma once
#include "effect.h"

class CWizard_FrostNova_ArrowEffect : public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float		m_fTime;
	float		m_fDelayTime;
	int			m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void	Mode1();
	void	Mode2();

public:
	explicit CWizard_FrostNova_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fDelayTime);
	virtual ~CWizard_FrostNova_ArrowEffect(void);
};