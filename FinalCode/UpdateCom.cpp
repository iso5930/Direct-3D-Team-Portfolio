#include "Stdafx.h"
#include "UpdateCom.h"

CUpdateCom::CUpdateCom(UPDATE_TYPE _eUpdateType)
{
	// ComType
	m_eComType = COM_TYPE_UPDATE;

	// UpdateType
	m_eUpdateType = _eUpdateType;

	// Priority
	m_dwPriority = 0xFFFFFFF0;
}

CUpdateCom::~CUpdateCom()
{
	Release();
}

void CUpdateCom::Initialize()
{
	CUpdateMgr::GetInstance()->AddObject(m_eUpdateType, m_pOwner);
}

int CUpdateCom::Update()
{
	/*
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		--m_dwPriority;
		*/

	return 0;
}

void CUpdateCom::Render()
{
}

void CUpdateCom::Release()
{
	CUpdateMgr::GetInstance()->RemoveObject(m_eUpdateType, m_pOwner);
}