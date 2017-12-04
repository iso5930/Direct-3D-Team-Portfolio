#pragma once

class CSoundMgr
{
private:
	unsigned int m_iVersion;
	FMOD_SYSTEM* m_pSystem;
	FMOD_RESULT m_Result;

	unordered_map<TCHAR*, FMOD_SOUND*> m_SystemSoundMap;
	unordered_map<TCHAR*, FMOD_SOUND*> m_UISoundMap;
	unordered_map<TCHAR*, FMOD_SOUND*> m_PlayerSoundMap;
	unordered_map<TCHAR*, FMOD_SOUND*> m_MonsterSoundMap;

	FMOD_CHANNEL* m_pEffect;
	FMOD_CHANNEL* m_pSystemBGM;
	FMOD_CHANNEL* m_pUI[4];
	FMOD_CHANNEL* m_pPlayer[4];
	FMOD_CHANNEL* m_pPlayerBGM[4];
	FMOD_CHANNEL* m_pPlayerSkill[8];
	FMOD_CHANNEL* m_pMonster[4];
	FMOD_CHANNEL* m_pMonsterBGM[4];
	FMOD_CHANNEL* m_pMonsterSkill[8];
	
	int m_iUICnt;
	int m_iPlayerCnt;
	int m_iPlayerBGMCnt;
	int m_iPlayerSkillCnt;
	int m_iMonsterCnt;
	int m_iMonsterBGMCnt;
	int m_iMonsterSkillCnt;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

private:
	void ErrorCheck(FMOD_RESULT _result);

public: ////////////////////////////////////////////////////////////////////////// Load
	void LoadSystemSoundFile();
	void LoadUISoundFile();
	void LoadPlayerSoundFile();
	void LoadMonsterSoundFile();

public: ////////////////////////////////////////////////////////////////////////// System
	void PlaySoundForSystem(TCHAR* _tszSoundKey);
	void PlaySoundForSystemBGM(TCHAR* _tszSoundKey);
	void StopSoundForSystem();
	void StopSoundForSystemBGM();
	void StopSoundAll();

public: ////////////////////////////////////////////////////////////////////////// UI
	int PlaySoundForUI(TCHAR* _tszSoundKey);
	void StopSoundForUI(int _iIndex);
	
public: ////////////////////////////////////////////////////////////////////////// Player
	int PlaySoundForPlayer(TCHAR* _tszSoundKey);
	int PlaySoundForPlayerBGM(TCHAR* _tszSoundKey);
	int PlaySoundForPlayerSkill(TCHAR* _tszSoundKey);
	void StopSoundForPlayer(int _iIndex);
	void StopSoundForPlayerBGM(int _iIndex);
	void StopSoundForPlayerSkill(int _iIndex);

public: ////////////////////////////////////////////////////////////////////////// Monster
	int PlaySoundForMonster(TCHAR* _tszSoundKey);
	int PlaySoundForMonsterBGM(TCHAR* _tszSoundKey);
	int PlaySoundForMonsterSkill(TCHAR* _tszSoundKey);
	void StopSoundForMonster(int _iIndex);
	void StopSoundForMonsterBGM(int _iIndex);
	void StopSoundForMonsterSkill(int _iIndex);

private:
	DECLARE_SINGLETON(CSoundMgr)

private:
	explicit CSoundMgr();
	~CSoundMgr();
};
