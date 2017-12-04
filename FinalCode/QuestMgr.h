#pragma once

class CQuestMgr
{
private:
	// QuestList
	list<Quest*> m_QuestList;

	// AchieveList
	list<Achieve*> m_AchieveList;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// Begin
	void Begin();

	// End
	void End();

public: ////////////////////////////////////////////////////////////////////////// Quest
	// AddQuest
	void AddQuest(Quest* _pQuest);

	// GetQuest
	Quest* GetQuest(QUEST_TYPE _eQuestType);

	// GetQuest
	Quest* GetQuest(int _iIndex);

	// RemoveQuest
	void RemoveQuest(QUEST_TYPE _eQuestType);

	// SizeOfQuest
	int GetSizeOfQuest();

public: ////////////////////////////////////////////////////////////////////////// Achieve
	// AddAchieve
	void AddAchieve(Achieve* _pAchieve);

	// GetAchieve
	Achieve* GetAchieve(ACHIEVE_TYPE _eAchieveType);

	// GetAchieve
	Achieve* GetAchieve(int _iIndex);

	// RemoveAchieve
	void RemoveAchieve(ACHIEVE_TYPE _eAchieveType);

	// SizeOfAchieve
	int GetSizeOfAchieve();

private:
	DECLARE_SINGLETON(CQuestMgr)

public:
	explicit CQuestMgr();
	virtual ~CQuestMgr();
};
