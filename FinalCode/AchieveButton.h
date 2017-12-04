#pragma once

#include "ButtonUI.h"

class CAchieveButton : public CButtonUI
{
private:
	// Achieve
	Achieve* m_pAchieve;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetAchieve
	Achieve* GetAchieve() { return m_pAchieve; }

public:
	explicit CAchieveButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Achieve* _pAchieve);
	virtual ~CAchieveButton();
};
