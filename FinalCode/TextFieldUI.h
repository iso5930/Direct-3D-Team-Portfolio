#pragma once

#include "UI.h"

class CTextFieldUI : public CUI
{
protected:
	// OverTexture
	LPDIRECT3DBASETEXTURE9 m_pOverTexture;

	// Enable
	bool m_bEnable;

	// Text
	TCHAR m_tszText[MIN_STR];

	// Cnt
	int m_iCnt;

	// Width
	int m_iWidth;
	
	// Height
	int m_iHeight;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetText
	TCHAR* GetText() { return m_tszText; }

	// GetCnt
	int GetCnt() { return m_iCnt; }

	// GetWidth
	int GetWidth() { return m_iWidth; }

	// GetHeight
	int GetHeight() { return m_iHeight; }

	// Enable
	void Enable() { m_bEnable = true; }

	// Disable
	void Disable() { m_bEnable = false; }

	// IsEnable
	bool IsEnable() { return m_bEnable; }

public:
	explicit CTextFieldUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey);
	virtual ~CTextFieldUI();
};
