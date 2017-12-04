#include "StdAfx.h"
#include "EffortMessage.h"

CEffortMessage::CEffortMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("�����簡 ���� ������ �ϰų� Ư�� ����� ����� �� ������ �����˴ϴ�.\n������ ����Ͽ� �� ������ ���� ����� ��� ����� �� �� �ֽ��ϴ�."));

	// Effort
	m_iEffort = 0;

	// MaxEffort
	m_iMaxEffort = 0;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.437f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.756f, 0.202f, 0.0f);
}

CEffortMessage::~CEffortMessage()
{
	Release();
}

void CEffortMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CEffortMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->MouseInvalidate();

	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer != NULL)
	{
		m_iEffort = ((CPlayer*)pPlayer)->GetStat()->iEffort;
		m_iMaxEffort = ((CPlayer*)pPlayer)->GetStat()->iMaxEffort;
	}

	return 0;
}

void CEffortMessage::Render()
{
	CMessageUI::Render();

	TCHAR tszLife[MIN_STR];
	wsprintf(tszLife, _T("%s%d/%d"), _T("����: "), m_iEffort, m_iMaxEffort);

	RECT rcText;
	SetRect(&rcText, 694, 545, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, tszLife, -1, &rcText, DT_LEFT, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));

	SetRect(&rcText, 694, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(17, 7)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CEffortMessage::Release()
{
}