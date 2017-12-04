#pragma once

#include "QuestMessage.h"

class CBasicSign;

class CMainQuest1_Message : public CQuestMessage
{
private:
	// Mode
	int m_iMode;

	// AnuAndTathametSign
	CBasicSign* m_pAnuAndTathametSign;

	// TyraelSign
	CBasicSign* m_pTyraelSign;

	// AurielSign
	CBasicSign* m_pAurielSign;

	// MalthaelSign
	CBasicSign* m_pMalthaelSign;

	// ImperiusSign
	CBasicSign* m_pImperiusSign;

	// ItheraelSign
	CBasicSign* m_pItheraelSign;

	// MephistoSign
	CBasicSign* m_pMephistoSign;

	// BaalSign
	CBasicSign* m_pBaalSign;

	// DiabloSign
	CBasicSign* m_pDiabloSign;

	// AzmodanSign
	CBasicSign* m_pAzmodanSign;

	// BelialSign
	CBasicSign* m_pBelialSign;

	// DuriekSign
	CBasicSign* m_pDuriekSign;

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

	// Mode6
	void Mode6();

	// Mode7
	void Mode7();

	// Mode8
	void Mode8();

	// Mode9
	void Mode9();

	// Mode10
	void Mode10();

	// Mode11
	void Mode11();

	// Mode12
	void Mode12();

	// Mode13
	void Mode13();

	// Mode14
	void Mode14();

	// Mode15
	void Mode15();

	// Mode16
	void Mode16();

	// Mode17
	void Mode17();

	// Mode18
	void Mode18();

	// Mode19
	void Mode19();

	// Mode20
	void Mode20();

	// Mode21
	void Mode21();

	// Mode22
	void Mode22();

	// Mode23
	void Mode23();

	// Mode24
	void Mode24();

	// Mode25
	void Mode25();

	// Mode26
	void Mode26();

	// Mode27
	void Mode27();

	// Mode28
	void Mode28();

public:
	explicit CMainQuest1_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CMainQuest1_Message();
};
