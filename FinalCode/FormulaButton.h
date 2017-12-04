#pragma once

#include "ButtonUI.h"

class CFormulaButton : public CButtonUI
{
private:
	// Formula
	Formula* m_pFormula;

	// Color
	D3DXCOLOR m_dwColor;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	// GetFormula
	Formula* GetFormula() { return m_pFormula; }

public:
	explicit CFormulaButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Formula* _pFormula);
	virtual ~CFormulaButton();
};
