#include "StdAfx.h"
#include "LevelUpAlarmMessage.h"

CLevelUpAlarmMessage::CLevelUpAlarmMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_LevelUpAlarm"))
{
	// Text
	StringCbPrintf(m_tszText, sizeof(m_tszText), _T("%d 레벨을 달성하셨습니다"), _iLevel);

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// RenderCom
	m_pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	m_pRenderCom->m_vColor.w = 0.0f;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.538502f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.3f, 0.0f);
}

CLevelUpAlarmMessage::~CLevelUpAlarmMessage()
{
	Release();
}

void CLevelUpAlarmMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;
}

int CLevelUpAlarmMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;

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
	}

	return 0;
}

void CLevelUpAlarmMessage::Render()
{
	CMessageUI::Render();

	// Text
	RECT rcText;
	SetRect(&rcText, 0, 172, WINCX, 188);
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_pRenderCom->m_vColor.w));
}

void CLevelUpAlarmMessage::Release()
{
}

void CLevelUpAlarmMessage::Mode0()
{
	// Alpha
	m_pRenderCom->m_vColor.w = m_fTime / 2.0f;

	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 2.0f)
	{
		// Alpha
		m_pRenderCom->m_vColor.w = 1.0f;

		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CLevelUpAlarmMessage::Mode1()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 3.0f)
	{
		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CLevelUpAlarmMessage::Mode2()
{
	// Alpha
	m_pRenderCom->m_vColor.w = (5.0f - m_fTime) / 5.0f;

	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 5.0f)
	{
		// Alpha
		m_pRenderCom->m_vColor.w = 0.0f;

		// Destroy
		Destroy();

		m_fTime = 0.0f;
		++m_iMode;
	}
}