#pragma once

#include "QuestMessage.h"

class CMainQuest7_1_Message : public CQuestMessage
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMainQuest7_1_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMainQuest7_1_Message();
};
