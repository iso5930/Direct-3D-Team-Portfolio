#include "StdAfx.h"
#include "Trigger.h"

CTrigger::CTrigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CObject(_tszObjKey, _eObjType)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_TRIGGER);
	AddComponent(pUpdateCom);
}

CTrigger::~CTrigger()
{
	Release();
}

void CTrigger::Initialize()
{
	CObject::Initialize();
}

int CTrigger::Update()
{
	CObject::Update();

	return 0;
}

void CTrigger::Render()
{
	CObject::Render();
}

void CTrigger::Release()
{
}