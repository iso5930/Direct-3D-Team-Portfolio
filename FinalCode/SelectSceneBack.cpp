#include "StdAfx.h"
#include "SelectSceneBack.h"

CSelectSceneBack::CSelectSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_SelectScene"))
{
}

CSelectSceneBack::~CSelectSceneBack()
{
	Release();
}

void CSelectSceneBack::Initialize()
{
	CBack::Initialize();
}

int CSelectSceneBack::Update()
{
	CBack::Update();

	return 0;
}

void CSelectSceneBack::Render()
{
	CBack::Render();
}

void CSelectSceneBack::Release()
{
}