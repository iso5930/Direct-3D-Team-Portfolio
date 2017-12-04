#pragma once
#include "effect.h"

class CBufferCom;
class CDemonHunter_Vault_AfterImageEffect : public CEffect
{
private:
	double			m_dTrackPos;
	CBufferCom*		m_pBufferCom;
	float			m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Vault_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Vault_AfterImageEffect(void);
};