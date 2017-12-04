#pragma once

#include "QuestMessage.h"

class CConversationMessage : public CQuestMessage
{
private:
	// PortraitTexKey
	TCHAR m_tszPortraitTexKey[MIN_STR];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CConversationMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszName, TCHAR* _tszPortraitTexKey);
	virtual ~CConversationMessage();
};
