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
		_tcscpy_s(m_tszText, MIN_STR, _T("디아블로3에 오신걸 환영합니다."));
		break;
	case 1:
		_tcscpy_s(m_tszText, MIN_STR, _T("사람보다 좀비가 더 많은 세상이야.."));
		break;
	case 2:
		_tcscpy_s(m_tszText, MIN_STR, _T("먹고 살기 힘들구만.."));
		break;
	case 3:
		_tcscpy_s(m_tszText, MIN_STR, _T("대악마보다 취직이 더 문제여!"));
		break;
	case 4:
		_tcscpy_s(m_tszText, MIN_STR, _T("지금은 새벽 5시 반입니다."));
		break;
	case 5:
		_tcscpy_s(m_tszText, MIN_STR, _T("3대 악마는 메피스토, 바알, 디아블로입니다."));
		break;
	case 6:
		_tcscpy_s(m_tszText, MIN_STR, _T("1 + 1은 귀요미~"));
		break;
	case 7:
		_tcscpy_s(m_tszText, MIN_STR, _T("좋은 하루 되세요."));
		break;
	case 8:
		_tcscpy_s(m_tszText, MIN_STR, _T("진형아..."));
		break;
	case 9:
		_tcscpy_s(m_tszText, MIN_STR, _T("한푼만 줍쇼.."));
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