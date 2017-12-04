#include "StdAfx.h"
#include "LoginSceneBack.h"

CLobbySceneBack::CLobbySceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_LobbyScene"))
{
}

CLobbySceneBack::~CLobbySceneBack()
{
	Release();
}

void CLobbySceneBack::Initialize()
{
	CBack::Initialize();
}

int CLobbySceneBack::Update()
{
	CBack::Update();

	return 0;
}

void CLobbySceneBack::Render()
{
	CBack::Render();
}

void CLobbySceneBack::Release()
{
}