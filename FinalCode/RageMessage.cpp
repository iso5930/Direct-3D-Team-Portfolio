#include "StdAfx.h"
#include "RageMessage.h"

CRageMessage::CRageMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("�߸���簡 �г� ���� ����� ����ϰų� ���ظ� ������ �г밡 �����˴ϴ�.\n�г븦 ����Ͽ� �� ������ ������ �� �� �ֽ��ϴ�."));

	// Rage
	m_iRage = 0;

	// MaxRage
	m_iMaxRage = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.442f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.793f, 0.202f, 0.0f);
}

CRageMessage::~CRageMessage()
{
	Release();
}

void CRageMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CRageMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iRage = ((CPlayer*)pPlayer)->GetStat()->iRage;
		m_iMaxRage = ((CPlayer*)pPlayer)->GetStat()->iMaxRage;
	}

	return 0;
}

void CRageMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("�г�: "), m_iRage, m_iMaxRage);

	RECT rcText;
	SetRect(&rcText, 686, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 686, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CRageMessage::Release()
{
}