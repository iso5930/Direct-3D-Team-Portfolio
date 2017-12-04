#pragma once

#include "WindowUI.h"

class CAchieveButton;

class CAchieveWindow : public CWindowUI
{
private:
	// Texture
	LPDIRECT3DBASETEXTURE9 m_pTexture[2];

	// Page
	int m_iPage;

	// Scroll
	int m_iScroll;

	// MaxScroll
	int m_iMaxScroll;

	// VScroll
	CVScroll* m_pVScroll;

	// AchieveButtonVec
	vector<CAchieveButton*> m_AchieveButtonVec;

	// Title
	TCHAR m_tszTitle[MIN_STR];

	// Content
	TCHAR m_tszContent[512];

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Renew
	virtual void Renew();

public:
	// UpdateScroll
	void UpdateScroll();

	// UpdateContent
	void UpdateContent(Achieve* _pAchieve);

public:
	explicit CAchieveWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType);
	virtual ~CAchieveWindow();
};
