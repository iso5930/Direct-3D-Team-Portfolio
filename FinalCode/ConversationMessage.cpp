#include "StdAfx.h"
#include "ConversationMessage.h"

CConversationMessage::CConversationMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszName, TCHAR* _tszPortraitTexKey)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Name
	_tcscpy_s(m_tszName, MIN_STR, _tszName);

	// PortraitTexKey
	_tcscpy_s(m_tszPortraitTexKey, MIN_STR, _tszPortraitTexKey);

	// Text
	int iRand = rand() % 10;
	switch(iRand)
	{
	case 0:
		_tcscpy_s(m_tszText, MIN_STR, _T("��ƺ��3�� ���Ű� ȯ���մϴ�."));
		break;
	case 1:
		_tcscpy_s(m_tszText, MIN_STR, _T("������� ���� �� ���� �����̾�.."));
		break;
	case 2:
		_tcscpy_s(m_tszText, MIN_STR, _T("�԰� ��� ���鱸��.."));
		break;
	case 3:
		_tcscpy_s(m_tszText, MIN_STR, _T("��Ǹ����� ������ �� ������!"));
		break;
	case 4:
		_tcscpy_s(m_tszText, MIN_STR, _T("������ ���� 5�� ���Դϴ�."));
		break;
	case 5:
		_tcscpy_s(m_tszText, MIN_STR, _T("3�� �Ǹ��� ���ǽ���, �پ�, ��ƺ���Դϴ�."));
		break;
	case 6:
		_tcscpy_s(m_tszText, MIN_STR, _T("1 + 1�� �Ϳ��~"));
		break;
	case 7:
		_tcscpy_s(m_tszText, MIN_STR, _T("���� �Ϸ� �Ǽ���."));
		break;
	case 8:
		_tcscpy_s(m_tszText, MIN_STR, _T("������..."));
		break;
	case 9:
		_tcscpy_s(m_tszText, MIN_STR, _T("��Ǭ�� �ݼ�.."));
		break;
	}
}

CConversationMessage::~CConversationMessage()
{
}

void CConversationMessage::Initialize()
{
	CQuestMessage::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, m_tszPortraitTexKey);
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CConversationMessage::Update()
{
	CQuestMessage::Update();

	// Destroy
	if(m_pXButton->IsLUp())
		Destroy();

	return 0;
}

void CConversationMessage::Render()
{
	CQuestMessage::Render();
}

void CConversationMessage::Release()
{
}