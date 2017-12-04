#include "StdAfx.h"
#include "WhiteCursor.h"

CWhiteCursor::CWhiteCursor(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CCursorUI(_tszObjKey, _eObjType, _T("Cursor_White"))
{
}

CWhiteCursor::~CWhiteCursor()
{
	Release();
}

void CWhiteCursor::Initialize()
{
	CCursorUI::Initialize();
}

int CWhiteCursor::Update()
{
	CCursorUI::Update();

	return 0;
}

void CWhiteCursor::Render()
{
	CCursorUI::Render();
}

void CWhiteCursor::Release()
{
}