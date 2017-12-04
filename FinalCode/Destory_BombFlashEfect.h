#pragma once
#include "effect.h"

class CDestory_BombFlashEfect : public CEffect
{
private:
	vector<LPDIRECT3DTEXTURE9>	m_TextureVec;
	CMaterialCom*				m_pMaterialCom;
	Frame						m_Frame;
	bool						m_bCheck;
	TCHAR*						m_pName;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDestory_BombFlashEfect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, bool _bCheck, TCHAR* _tszName);
	virtual ~CDestory_BombFlashEfect(void);
};