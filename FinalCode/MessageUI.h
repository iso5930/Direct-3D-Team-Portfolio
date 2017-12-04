#pragma once

#include "UI.h"

class CBasicButton;

class CMessageUI : public CUI
{
protected:
	// Text
	TCHAR m_tszText[MAX_STR];

	// CloseButton
	CBasicButton* m_pCloseButton;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetText
	TCHAR* GetText() { return m_tszText; }

public:
	explicit CMessageUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CMessageUI();
};
