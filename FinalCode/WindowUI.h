#pragma once

#include "UI.h"

class CBasicButton;

class CWindowUI : public CUI
{
protected:
	// ButtonVec
	vector<CButtonUI*> m_ButtonVec;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	// AddButton
	void AddButton(CButtonUI* _pButtonUI);

public:
	explicit CWindowUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey);
	virtual ~CWindowUI();
};
