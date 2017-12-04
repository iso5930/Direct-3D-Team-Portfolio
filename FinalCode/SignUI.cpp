#include "StdAfx.h"
#include "SignUI.h"

CSignUI::CSignUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CSignUI::~CSignUI()
{
	Release();
}

void CSignUI::Initialize()
{
	CUI::Initialize();
}

int CSignUI::Update()
{
	CUI::Update();

	return 0;
}

void CSignUI::Render()
{
	CUI::Render();
}

void CSignUI::Release()
{
}