#pragma once
#include "effect.h"

class CMonk_BreathOfHeaven_FlashEffect : public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	float m_fTime;
	int m_iMode;
	float m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CMonk_BreathOfHeaven_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_BreathOfHeaven_FlashEffect(void);
};