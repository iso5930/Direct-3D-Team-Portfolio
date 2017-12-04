#pragma once

#include "ButtonUI.h"

class CCharacterButton : public CButtonUI
{
private:
	// Name
	TCHAR m_tszName[MIN_STR];

	// Info
	TCHAR m_tszInfo[MIN_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Setup
	void Setup(TCHAR* _tszName, int _iLevel, int _iJob);

public:
	explicit CCharacterButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey);
	virtual ~CCharacterButton();
};
