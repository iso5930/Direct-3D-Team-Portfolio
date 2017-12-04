#pragma once

#include "MessageUI.h"

class CPortraitSign;

class CQuestMessage : public CMessageUI
{
protected:
	// Name
	TCHAR m_tszName[MIN_STR];

	// XButton
	CBasicButton* m_pXButton;

	//PortraitSign
	CPortraitSign* m_pPortraitSign;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CQuestMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CQuestMessage();
};
