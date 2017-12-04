#pragma once

#include "UI.h"

class CScrollUI : public CUI
{
protected:
	// OverTexture
	LPDIRECT3DBASETEXTURE9 m_pOverTexture;

	// DownTexture
	LPDIRECT3DBASETEXTURE9 m_pDownTexture;

	// Clicked
	bool m_bClicked;

	// Max
	float m_fMax;

	// Min
	float m_fMin;

	// Scroll
	int m_iScroll;

	// MaxScroll
	int m_iMaxScroll;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// Setup
	void Setup(int _iScroll, int _iMaxScroll, float _fMax, float _fMin);

	// GetScroll
	int GetScroll() { return m_iScroll; }

	// GetMaxScroll
	int GetMaxScroll() { return m_iMaxScroll; }

	// GetMax
	float GetMax() { return m_fMax; }

	// GetMin
	float GetMin() { return m_fMin; }

private:
	// Clicked
	void Clicked();

	// NoneClicked
	void NoneClicked();

public:
	explicit CScrollUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey);
	virtual ~CScrollUI();
};
