#include "StdAfx.h"
#include "QuestMgr.h"

IMPLEMENT_SINGLETON(CQuestMgr)

CQuestMgr::CQuestMgr()
{
}

CQuestMgr::~CQuestMgr()
{
	Release();
}

void CQuestMgr::Initialize()
{
}

int CQuestMgr::Update()
{
	return 0;
}

void CQuestMgr::Render()
{
}

void CQuestMgr::Release()
{
	// QuestList
	list<Quest*>::iterator QuestList_Iter = m_QuestList.begin();
	list<Quest*>::iterator QuestList_IterEnd = m_QuestList.end();
	for(; QuestList_Iter != QuestList_IterEnd; ++QuestList_Iter)
	{
		delete (*QuestList_Iter);
		*QuestList_Iter = NULL;
	}

	m_QuestList.clear();

	// AchieveList
	list<Achieve*>::iterator AchieveList_Iter = m_AchieveList.begin();
	list<Achieve*>::iterator AchieveList_IterEnd = m_AchieveList.end();
	for(; AchieveList_Iter != AchieveList_IterEnd; ++AchieveList_Iter)
	{
		delete (*AchieveList_Iter);
		*AchieveList_Iter = NULL;
	}
	m_AchieveList.clear();
}

void CQuestMgr::Begin()
{
	// Account
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

	for(int i = 0; i < pAccount->iQuestNum; ++i)
		m_QuestList.push_back(new Quest(pAccount->QuestVec[i]));

	for(int i = 0; i < pAccount->iAchieveNum; ++i)
		m_AchieveList.push_back(new Achieve(pAccount->AchieveVec[i]));
}

void CQuestMgr::End()
{
	// QuestList
	list<Quest*>::iterator QuestList_Iter = m_QuestList.begin();
	list<Quest*>::iterator QuestList_IterEnd = m_QuestList.end();
	for(; QuestList_Iter != QuestList_IterEnd; ++QuestList_Iter)
	{
		delete (*QuestList_Iter);
		*QuestList_Iter = NULL;
	}

	m_QuestList.clear();

	// AchieveList
	list<Achieve*>::iterator AchieveList_Iter = m_AchieveList.begin();
	list<Achieve*>::iterator AchieveList_IterEnd = m_AchieveList.end();
	for(; AchieveList_Iter != AchieveList_IterEnd; ++AchieveList_Iter)
	{
		delete (*AchieveList_Iter);
		*AchieveList_Iter = NULL;
	}
	m_AchieveList.clear();
}

////////////////////////////////////////////////////////////////////////// Quest
void CQuestMgr::AddQuest(Quest* _pQuest)
{
	m_QuestList.push_back(_pQuest);
}

Quest* CQuestMgr::GetQuest(QUEST_TYPE _eQuestType)
{
	list<Quest*>::iterator Iter = m_QuestList.begin();
	list<Quest*>::iterator IterEnd = m_QuestList.end();
	for(; Iter != IterEnd; ++Iter)
	{
		Quest* pQuest = *Iter;
		if(pQuest->eQuestType == _eQuestType)
			return pQuest;
	}

	return NULL;
}

Quest* CQuestMgr::GetQuest(int _iIndex)
{
	list<Quest*>::iterator Iter = m_QuestList.begin();
	list<Quest*>::iterator IterEnd = m_QuestList.end();
	for(int i = 0; i < _iIndex; ++i, ++Iter)
	{
		if(Iter == IterEnd)
			return NULL;
	}

	return *Iter;
}

void CQuestMgr::RemoveQuest(QUEST_TYPE _eQuestType)
{
	list<Quest*>::iterator Iter = m_QuestList.begin();
	list<Quest*>::iterator IterEnd = m_QuestList.end();
	for(; Iter != IterEnd; ++Iter)
	{
		Quest* pQuest = *Iter;
		if(pQuest->eQuestType == _eQuestType)
		{
			delete pQuest;
			m_QuestList.erase(Iter);
			break;
		}
	}
}

int CQuestMgr::GetSizeOfQuest()
{
	return m_QuestList.size();
}

////////////////////////////////////////////////////////////////////////// Achieve
void CQuestMgr::AddAchieve(Achieve* _pAchieve)
{
	m_AchieveList.push_back(_pAchieve);
}

Achieve* CQuestMgr::GetAchieve(ACHIEVE_TYPE _eAchieveType)
{
	list<Achieve*>::iterator Iter = m_AchieveList.begin();
	list<Achieve*>::iterator IterEnd = m_AchieveList.end();
	for(; Iter != IterEnd; ++Iter)
	{
		Achieve* pAchieve = *Iter;
		if(pAchieve->eAchieveType == _eAchieveType)
			return pAchieve;
	}

	return NULL;
}

Achieve* CQuestMgr::GetAchieve(int _iIndex)
{
	list<Achieve*>::iterator Iter = m_AchieveList.begin();
	list<Achieve*>::iterator IterEnd = m_AchieveList.end();
	for(int i = 0; i < _iIndex; ++i, ++Iter)
	{
		if(Iter == IterEnd)
			return NULL;
	}

	return *Iter;
}

void CQuestMgr::RemoveAchieve(ACHIEVE_TYPE _eAchieveType)
{
	list<Achieve*>::iterator Iter = m_AchieveList.begin();
	list<Achieve*>::iterator IterEnd = m_AchieveList.end();
	for(; Iter != IterEnd; ++Iter)
	{
		Achieve* pAchieve = *Iter;
		if(pAchieve->eAchieveType == _eAchieveType)
		{
			delete pAchieve;
			m_AchieveList.erase(Iter);
			break;
		}
	}
}

int CQuestMgr::GetSizeOfAchieve()
{
	return m_AchieveList.size();
}