#pragma once

#include "UI.h"

class CButtonUI : public CUI
{
protected:
	// Enable
	bool m_bEnable;

	// OverTexture
	LPDIRECT3DBASETEXTURE9 m_pOverTexture;

	// DownTexture
	LPDIRECT3DBASETEXTURE9 m_pDownTexture;

	// DisableTexture
	LPDIRECT3DBASETEXTURE9 m_pDisableTexture;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	// Enable
	void Enable();

	// Disable
	void Disable();

	// IsEnable
	bool IsEnable();

public:
	explicit CButtonUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey, TCHAR* _tszDisableTexture);
	virtual ~CButtonUI();
};
