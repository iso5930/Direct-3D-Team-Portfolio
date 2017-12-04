#include "StdAfx.h"
#include "TitleSceneBack.h"

CTitleSceneBack::CTitleSceneBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_TitleScene"))
{
	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// RenderCom
	m_pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	m_pRenderCom->m_vColor.x = 0.0f;
	m_pRenderCom->m_vColor.y = 0.0f;
	m_pRenderCom->m_vColor.z = 0.0f;
}

CTitleSceneBack::~CTitleSceneBack()
{
	Release();
}

void CTitleSceneBack::Initialize()
{
	CBack::Initialize();
}

int CTitleSceneBack::Update()
{
	CBack::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;

	case 3:
		Mode3();
		break;
	}

	return 0;
}

void CTitleSceneBack::Render()
{
	CBack::Render();
}

void CTitleSceneBack::Release()
{
}

void CTitleSceneBack::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		++m_iMode;
		m_fTime = 0.0f;
	}
}

void CTitleSceneBack::Mode1()
{
	m_pRenderCom->m_vColor.x += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pRenderCom->m_vColor.y += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pRenderCom->m_vColor.z += CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime >= 1.0f)
	{
		m_pRenderCom->m_vColor.x = 1.0f;
		m_pRenderCom->m_vColor.y = 1.0f;
		m_pRenderCom->m_vColor.z = 1.0f;

		++m_iMode;
		m_fTime = 0.0f;
	}
}

void CTitleSceneBack::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime >= 2.0f)
	{
		++m_iMode;
		m_fTime = 0.0f;
	}
}

void CTitleSceneBack::Mode3()
{
	m_pRenderCom->m_vColor.x -= CTimeMgr::GetInstance()->GetDeltaTime();
	m_pRenderCom->m_vColor.y -= CTimeMgr::GetInstance()->GetDeltaTime();
	m_pRenderCom->m_vColor.z -= CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime >= 1.0f)
	{
		m_pRenderCom->m_vColor.x = 0.0f;
		m_pRenderCom->m_vColor.y = 0.0f;
		m_pRenderCom->m_vColor.z = 0.0f;

		++m_iMode;
		m_fTime = 0.0f;
	}
}