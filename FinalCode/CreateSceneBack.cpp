#include "StdAfx.h"
#include "CreateSceneBack.h"

CCreateSceneBack::CCreateSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_CreateScene"))
{
}

CCreateSceneBack::~CCreateSceneBack()
{
	Release();
}

void CCreateSceneBack::Initialize()
{
	CBack::Initialize();
}

int CCreateSceneBack::Update()
{
	CBack::Update();

	return 0;
}

void CCreateSceneBack::Render()
{
	CBack::Render();
}

void CCreateSceneBack::Release()
{
}