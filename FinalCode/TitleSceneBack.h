#pragma once

#include "Back.h"

class CRenderCom;

class CTitleSceneBack : public CBack
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

	// Mode3
	void Mode3();

public:
	explicit CTitleSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CTitleSceneBack();
};
