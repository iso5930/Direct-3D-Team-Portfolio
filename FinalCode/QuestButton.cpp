#include "StdAfx.h"
#include "QuestButton.h"

CQuestButton::CQuestButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Quest* _pQuest)
: CButtonUI(_tszObjKey, _eObjType, _T("Button_Back_Button0"), _T("Button_Over_Button0"), _T("Button_Down_Button0"), NULL)
{
	// Quest
	m_pQuest = new Quest(_pQuest);
}

CQuestButton::~CQuestButton()
{
	Release();
}

void CQuestButton::Initialize()
{
	CButtonUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CQuestButton::Update()
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

void CQuestButton::Render()
{
	if(Equals(m_pTransformCom->m_vSize.x, 0.0f, MIN_EPSILON) || Equals(m_pTransformCom->m_vSize.y, 0.0f, MIN_EPSILON))
		return;

	CButtonUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	TCHAR tszText[MIN_STR];
	if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 1)
		_tcscpy_s(tszText, MIN_STR, _T("E1. 트리스트럼 마을로.."));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 2)
		_tcscpy_s(tszText, MIN_STR, _T("E2. 용병단원이 되자"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 3)
		_tcscpy_s(tszText, MIN_STR, _T("E3. 첫번째 임무..?"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 4)
		_tcscpy_s(tszText, MIN_STR, _T("E4. 좀비 처치!"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 5)
		_tcscpy_s(tszText, MIN_STR, _T("E5. 임무 완료!"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 6)
		_tcscpy_s(tszText, MIN_STR, _T("E6. 분해?"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 7)
		_tcscpy_s(tszText, MIN_STR, _T("E7. 제련?"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 8)
		_tcscpy_s(tszText, MIN_STR, _T("E8. 용병 탈주"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 9)
		_tcscpy_s(tszText, MIN_STR, _T("E9. 정찰"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 10)
		_tcscpy_s(tszText, MIN_STR, _T("E10. 암살"));
	else if(m_pQuest->eQuestType == QUEST_TYPE_MAIN && m_pQuest->iStep == 11)
		_tcscpy_s(tszText, MIN_STR, _T("E10. 엔딩"));

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 90.0f), long(vPos.y - 7.0f), long(vPos.x + 110.0f), long(vPos.y + 7.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(0.85098f, 0.6f, 0.247058f, 1.0f));
}

void CQuestButton::Release()
{
	// Quest
	if(m_pQuest != NULL)
	{
		delete m_pQuest;
		m_pQuest = NULL;
	}
}