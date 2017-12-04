#pragma once

#include "TextFieldUI.h"

class CBasicButton;
class CWhiteCursor;

class CAmountTextField : public CTextFieldUI
{
private:
	// Type
	int m_iType;

	// Index
	int m_iIndex;

	// Page
	int m_iPage;

	// LeftButton
	CBasicButton* m_pLeftButton;

	// RightButton
	CBasicButton* m_pRightButton;

	// ConfirmButton
	CBasicButton* m_pConfirmButton;

	// CancelButton
	CBasicButton* m_pCancelButton;

	// WhiteCursor
	CWhiteCursor* m_pWhiteCursor;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CAmountTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iType, int _iIndex, int _iPage = -1);
	virtual ~CAmountTextField();
};
