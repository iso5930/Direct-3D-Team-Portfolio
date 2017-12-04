#include "StdAfx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr()
{
	m_iVersion = 0;

	m_pSystem = NULL;
	m_pEffect = NULL;
	m_pSystemBGM = NULL;

	ZeroMemory(m_pUI, sizeof(m_pUI));
	ZeroMemory(m_pPlayer, sizeof(m_pPlayer));
	ZeroMemory(m_pPlayerBGM, sizeof(m_pPlayerBGM));
	ZeroMemory(m_pPlayerSkill, sizeof(m_pPlayerSkill));
	ZeroMemory(m_pMonster, sizeof(m_pMonster));
	ZeroMemory(m_pMonsterBGM, sizeof(m_pMonsterBGM));
	ZeroMemory(m_pMonsterSkill, sizeof(m_pMonsterSkill));

	m_iUICnt = 0;
	m_iPlayerCnt = 0;
	m_iPlayerBGMCnt = 0;
	m_iPlayerSkillCnt = 0;
	m_iMonsterCnt = 0;
	m_iMonsterBGMCnt = 0;
	m_iMonsterSkillCnt = 0;
}

CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 64, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);
}

int  CSoundMgr::Update()
{
	return 0;
}

void CSoundMgr::Render()
{
}

void CSoundMgr::Release()
{
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator Iter1 = m_SystemSoundMap.begin();
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator IterEnd1 = m_SystemSoundMap.end();
	for(; Iter1 != IterEnd1; ++Iter1)
		delete[] Iter1->first;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator Iter2 = m_UISoundMap.begin();
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator IterEnd2 = m_UISoundMap.end();
	for(; Iter2 != IterEnd2; ++Iter2)
		delete[] Iter2->first;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator Iter3 = m_PlayerSoundMap.begin();
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator IterEnd3 = m_PlayerSoundMap.end();
	for(; Iter3 != IterEnd3; ++Iter3)
		delete[] Iter3->first;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator Iter4 = m_MonsterSoundMap.begin();
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator IterEnd4 = m_MonsterSoundMap.end();
	for(; Iter4 != IterEnd4; ++Iter4)
		delete[] Iter4->first;
}

void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
		return;
}

void CSoundMgr::LoadSystemSoundFile()
{
	_finddata_t fd;
	int iResult = 1;
	long handle = _findfirst("../SoundFile/System/*.*", &fd);

	if (handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];
		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		_tcscpy_s(pName, MAX_STR, szName);

		char szFullName[256];

		strcpy_s(szFullName, "../SoundFile/System/");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
			m_SystemSoundMap.insert( make_pair(pName, pSound) );
		else
			delete [] pName;

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::LoadUISoundFile()
{
	_finddata_t fd;
	int iResult = 1;
	long handle = _findfirst("../SoundFile/UI/*.*", &fd);

	if (handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];
		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		_tcscpy_s(pName, MAX_STR, szName);

		char szFullName[256];

		strcpy_s(szFullName, "../SoundFile/UI/");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
			m_UISoundMap.insert( make_pair(pName, pSound) );
		else
			delete [] pName;

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::LoadPlayerSoundFile()
{
	_finddata_t fd;
	int iResult = 1;
	long handle = _findfirst("../SoundFile/Player/*.*", &fd);

	if (handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];
		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		_tcscpy_s(pName, MAX_STR, szName);

		char szFullName[256];

		strcpy_s(szFullName, "../SoundFile/Player/");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
			m_PlayerSoundMap.insert( make_pair(pName, pSound) );
		else
			delete [] pName;

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::LoadMonsterSoundFile()
{
	_finddata_t fd;
	int iResult = 1;
	long handle = _findfirst("../SoundFile/Monster/*.*", &fd);

	if (handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];
		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		_tcscpy_s(pName, MAX_STR, szName);

		char szFullName[256];

		strcpy_s(szFullName, "../SoundFile/Monster/");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
			m_MonsterSoundMap.insert( make_pair(pName, pSound) );
		else
			delete [] pName;

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);
	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}

////////////////////////////////////////////////////////////////////////// System
void CSoundMgr::PlaySoundForSystem(TCHAR* _tszSoundKey)
{
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_SystemSoundMap.begin(), m_SystemSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_SystemSoundMap.end())
	{
		_tprintf(_T("PlaySoundForSystem() Error : %s\n"), _tszSoundKey);
		return;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pEffect);
	ErrorCheck(m_Result);
}
void CSoundMgr::PlaySoundForSystemBGM(TCHAR* _tszSoundKey)
{
	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_SystemSoundMap.begin(), m_SystemSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_SystemSoundMap.end())
	{
		_tprintf(_T("PlaySoundForBGM() Error : %s\n"), _tszSoundKey);
		return;
	}

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pSystemBGM);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForSystem()
{
	m_Result  = FMOD_Channel_Stop(m_pEffect);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForSystemBGM()
{
	m_Result  = FMOD_Channel_Stop(m_pSystemBGM);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundAll()
{
	StopSoundForSystem();
	StopSoundForSystemBGM();
	for(int i = 0; i < 4; ++i) { StopSoundForUI(i); }
	for(int i = 0; i < 4; ++i) { StopSoundForPlayer(i); }
	for(int i = 0; i < 4; ++i) { StopSoundForPlayerBGM(i); }
	for(int i = 0; i < 8; ++i) { StopSoundForPlayerSkill(i); }
	for(int i = 0; i < 4; ++i) { StopSoundForMonster(i); }
	for(int i = 0; i < 4; ++i) { StopSoundForMonsterBGM(i); }
	for(int i = 0; i < 8; ++i) { StopSoundForMonsterSkill(i); }
}

////////////////////////////////////////////////////////////////////////// UI
int CSoundMgr::PlaySoundForUI(TCHAR* _tszSoundKey)
{
	if(m_iUICnt >= 4)
		m_iUICnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_UISoundMap.begin(), m_UISoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_UISoundMap.end())
	{
		_tprintf(_T("PlaySoundForUI() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pUI[m_iUICnt]);
	ErrorCheck(m_Result);

	return m_iUICnt++;
}

void CSoundMgr::StopSoundForUI(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pUI[_iIndex]);
	ErrorCheck(m_Result);
}

////////////////////////////////////////////////////////////////////////// Player
int CSoundMgr::PlaySoundForPlayer(TCHAR* _tszSoundKey)
{
	if(m_iPlayerCnt >= 4)
		m_iPlayerCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_PlayerSoundMap.begin(), m_PlayerSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_PlayerSoundMap.end())
	{
		_tprintf(_T("PlaySoundForPlayer() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pPlayer[m_iPlayerCnt]);
	ErrorCheck(m_Result);

	return m_iPlayerCnt++;
}
int CSoundMgr::PlaySoundForPlayerBGM(TCHAR* _tszSoundKey)
{
	if(m_iPlayerBGMCnt >= 4)
		m_iPlayerBGMCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_PlayerSoundMap.begin(), m_PlayerSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_PlayerSoundMap.end())
	{
		_tprintf(_T("PlaySoundForPlayerBGM() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pPlayerBGM[m_iPlayerBGMCnt]);
	ErrorCheck(m_Result);

	return m_iPlayerBGMCnt++;
}
int CSoundMgr::PlaySoundForPlayerSkill(TCHAR* _tszSoundKey)
{
	if(m_iPlayerCnt >= 8)
		m_iPlayerCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_PlayerSoundMap.begin(), m_PlayerSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_PlayerSoundMap.end())
	{
		_tprintf(_T("PlaySoundForPlayerSkill() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pPlayerSkill[m_iPlayerSkillCnt]);
	ErrorCheck(m_Result);

	return m_iPlayerSkillCnt++;
}
void CSoundMgr::StopSoundForPlayer(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pPlayer[_iIndex]);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForPlayerBGM(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pPlayerBGM[_iIndex]);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForPlayerSkill(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pPlayerSkill[_iIndex]);
	ErrorCheck(m_Result);
}

////////////////////////////////////////////////////////////////////////// Monster
int CSoundMgr::PlaySoundForMonster(TCHAR* _tszSoundKey)
{
	if(m_iMonsterCnt >= 4)
		m_iMonsterCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_MonsterSoundMap.begin(), m_MonsterSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_MonsterSoundMap.end())
	{
		_tprintf(_T("PlaySoundForMonster() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pMonster[m_iMonsterCnt]);
	ErrorCheck(m_Result);

	return m_iMonsterCnt++;
}
int CSoundMgr::PlaySoundForMonsterBGM(TCHAR* _tszSoundKey)
{
	if(m_iMonsterBGMCnt >= 4)
		m_iMonsterBGMCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_MonsterSoundMap.begin(), m_MonsterSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_MonsterSoundMap.end())
	{
		_tprintf(_T("PlaySoundForMonsterBGM() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pMonsterBGM[m_iMonsterBGMCnt]);
	ErrorCheck(m_Result);

	return m_iMonsterBGMCnt++;
}
int CSoundMgr::PlaySoundForMonsterSkill(TCHAR* _tszSoundKey)
{
	if(m_iMonsterCnt >= 8)
		m_iMonsterCnt = 0;

	unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_MonsterSoundMap.begin(), m_MonsterSoundMap.end(), TStrCompare(_tszSoundKey));
	if(iter == m_MonsterSoundMap.end())
	{
		_tprintf(_T("PlaySoundForMonsterSkill() Error : %s\n"), _tszSoundKey);
		return 0;
	}

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pMonsterSkill[m_iMonsterSkillCnt]);
	ErrorCheck(m_Result);

	return m_iMonsterSkillCnt++;
}
void CSoundMgr::StopSoundForMonster(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pMonster[_iIndex]);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForMonsterBGM(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pMonsterBGM[_iIndex]);
	ErrorCheck(m_Result);
}
void CSoundMgr::StopSoundForMonsterSkill(int _iIndex)
{
	m_Result  = FMOD_Channel_Stop(m_pMonsterSkill[_iIndex]);
	ErrorCheck(m_Result);
}