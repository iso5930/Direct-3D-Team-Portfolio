#include "StdAfx.h"
#include "BasicButton.h"

CBasicButton::CBasicButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey)
: CButtonUI(_tszObjKey, _eObjType, _tszBackTexKey, _tszOverTexKey, _tszDownTexKey, NULL)
{
}

CBasicButton::~CBasicButton()
{
	Release();
}

void CBasicButton::Initialize()
{
	CButtonUI::Initialize();
}

int CBasicButton::Update()
{
	CButtonUI::Update();

	return 0;
}

void CBasicButton::Render()
{
	CButtonUI::Render();
}

void CBasicButton::Release()
{
}