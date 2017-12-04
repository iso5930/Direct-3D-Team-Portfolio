#include "StdAfx.h"
#include "AchieveButton.h"

CAchieveButton::CAchieveButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Achieve* _pAchieve)
: CButtonUI(_tszObjKey, _eObjType, _T("Button_Back_Button0"), _T("Button_Over_Button0"), _T("Button_Down_Button0"), NULL)
{
	// Achieve
	m_pAchieve = new Achieve(_pAchieve);
}

CAchieveButton::~CAchieveButton()
{
	Release();
}

void CAchieveButton::Initialize()
{
	CButtonUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CAchieveButton::Update()
{
	CButtonUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	return 0;
}

void CAchieveButton::Render()
{
	if(Equals(m_pTransformCom->m_vSize.x, 0.0f, MIN_EPSILON) || Equals(m_pTransformCom->m_vSize.y, 0.0f, MIN_EPSILON))
		return;

	CButtonUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	TCHAR tszText[MIN_STR];
	if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST1)
		_tcscpy_s(tszText, MIN_STR, _T("E1: ȥ���� �ô�"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST2)
		_tcscpy_s(tszText, MIN_STR, _T("E2: Ʈ����Ʈ�� �Լ�"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST3)
		_tcscpy_s(tszText, MIN_STR, _T("E3: �뺴��� �Ϸ�"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST4)
		_tcscpy_s(tszText, MIN_STR, _T("E4: ù ��° �ӹ�"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST5)
		_tcscpy_s(tszText, MIN_STR, _T("E5: ������ ��ȭ"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST6)
		_tcscpy_s(tszText, MIN_STR, _T("E6: ������ ����"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST7)
		_tcscpy_s(tszText, MIN_STR, _T("E7: ������ ����"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST8)
		_tcscpy_s(tszText, MIN_STR, _T("E8: �ʹ� �ʾ���.."));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST9)
		_tcscpy_s(tszText, MIN_STR, _T("E9: ������ ���"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST10)
		_tcscpy_s(tszText, MIN_STR, _T("E10: ħ����"));
	else if(m_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST11)
		_tcscpy_s(tszText, MIN_STR, _T("E11: ����"));

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 90.0f), long(vPos.y - 7.0f), long(vPos.x + 110.0f), long(vPos.y + 7.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(0.85098f, 0.6f, 0.247058f, 1.0f));
}

void CAchieveButton::Release()
{
	// Achieve
	if(m_pAchieve != NULL)
	{
		delete m_pAchieve;
		m_pAchieve = NULL;
	}
}