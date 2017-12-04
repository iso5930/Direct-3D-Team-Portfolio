#include "StdAfx.h"
#include "LoginSceneBack.h"

CLoginSceneBack::CLoginSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_LoginScene"))
{
}

CLoginSceneBack::~CLoginSceneBack()
{
	Release();
}

void CLoginSceneBack::Initialize()
{
	CBack::Initialize();
}

int CLoginSceneBack::Update()
{
	CBack::Update();

	return 0;
}

void CLoginSceneBack::Render()
{
	CBack::Render();
}

void CLoginSceneBack::Release()
{
}