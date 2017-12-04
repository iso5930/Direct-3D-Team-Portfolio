#pragma once

#include "QuestMessage.h"

class CMainQuest5_Message : public CQuestMessage
{
private:
	// Mode
	int m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	// Mode0
	void Mode0();

	// Mode1
	void Mode1();

	// Mode2
	void Mode2();

public:
	explicit CMainQuest5_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMainQuest5_Message();
};
