#pragma once

#include "WindowUI.h"

class CSkillButton;

class CSkillWindow : public CWindowUI
{
private:
	// Text
	TCHAR m_tszText[6][MIN_STR];

	// Text
	RECT m_rcText[6];

	// SkillButton
	CSkillButton* m_pSkillButton[6];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	explicit CSkillWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CSkillWindow();
};
