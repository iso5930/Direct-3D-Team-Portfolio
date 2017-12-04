#pragma once

#include "QuestMessage.h"

class CMainQuest3_Message : public CQuestMessage
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

	// Mode3
	void Mode3();

	// Mode4
	void Mode4();

	// Mode5
	void Mode5();

public:
	explicit CMainQuest3_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMainQuest3_Message();
};
