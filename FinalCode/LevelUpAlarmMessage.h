#pragma once

#include "MessageUI.h"

class CLevelUpAlarmMessage : public CMessageUI
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
	explicit CLevelUpAlarmMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel);
	virtual ~CLevelUpAlarmMessage();
};
