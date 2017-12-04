#pragma once

#include "ButtonUI.h"

class CCategoryButton : public CButtonUI
{
private:
	// Open
	bool m_bOpen;

	// CloseTexture
	LPDIRECT3DBASETEXTURE9 m_pCloseTexture[3];

	// OpenTexture
	LPDIRECT3DBASETEXTURE9 m_pOpenTexture[3];

	// Category
	TCHAR m_tszCategory[MIN_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// IsOpen
	bool IsOpen() { return m_bOpen; }

	// Open
	void Open();

	// Close
	void Close();

public:
	explicit CCategoryButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszCategory);
	virtual ~CCategoryButton();
};
