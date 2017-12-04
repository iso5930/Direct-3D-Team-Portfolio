#pragma once

#include "Effect.h"

class CMaterialCom;

class CMousePickEffect : public CEffect
{
private:
	// Frame
	Frame m_Frame;

	// Texture
	LPDIRECT3DBASETEXTURE9 m_pTextureArr[20];

	// MaterialCom
	CMaterialCom* m_pMaterialCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMousePickEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMousePickEffect();
};
