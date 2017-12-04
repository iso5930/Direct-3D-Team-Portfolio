#pragma once

#include "ButtonUI.h"

class CQuestButton : public CButtonUI
{
private:
	// Quest
	Quest* m_pQuest;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetQuest
	Quest* GetQuest() { return m_pQuest; }

public:
	explicit CQuestButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Quest* _pQuest);
	virtual ~CQuestButton();
};
