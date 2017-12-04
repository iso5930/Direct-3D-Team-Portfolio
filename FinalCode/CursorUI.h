#pragma once

#include "UI.h"

class CCursorUI : public CUI
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Visible
	void Visible();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

public:
	explicit CCursorUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CCursorUI();
};
