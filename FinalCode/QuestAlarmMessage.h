#pragma once

#include "MessageUI.h"

class CRenderCom;

class CQuestAlarmMessage : public CMessageUI
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// RenderCom
	CRenderCom* m_pRenderCom;

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
	explicit CQuestAlarmMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText);
	virtual ~CQuestAlarmMessage();
};
