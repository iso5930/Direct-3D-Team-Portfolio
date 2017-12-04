#include "StdAfx.h"
#include "DataMgr.h"

IMPLEMENT_SINGLETON(CDataMgr)

CDataMgr::CDataMgr()
{
	// Select
	m_iSelect = 0;

	// CharacterNum
	m_iCharacterNum = 0;

	// Gold
	m_iGold = 0;

	// RenderMode
	m_dwRenderMode = 0;

	// GameMode
	m_dwGameMode = 0;

	// ID
	ZeroMemory(m_tszID, sizeof(m_tszID));

	// Account
	ZeroMemory(m_tszPW, sizeof(m_tszPW));

	// Account
	ZeroMemory(m_tszAccount, sizeof(m_tszAccount));

	// AccountArr
	ZeroMemory(m_pAccountArr, sizeof(m_pAccountArr));
}

CDataMgr::~CDataMgr()
{
	Release();
}

void CDataMgr::Initialize()
{
}

int CDataMgr::Update()
{
	return 0;
}

void CDataMgr::Render()
{
}

void CDataMgr::Release()
{
	// Save
	Save();

	// Reset
	Reset();

	// AccountArr
	for(int i = 0; i < 10; ++i)
	{
		if(m_pAccountArr[i] != NULL)
		{
			delete m_pAccountArr[i];
			m_pAccountArr[i] = NULL;
		}
	}
}

bool CDataMgr::IsGateWay(GATE_WAY_TYPE _eGateWayType)
{
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iGateWayNum; ++i)
	{
		if(m_pAccountArr[m_iSelect]->GateWayVec[i] == int(_eGateWayType))
			return true;
	}

	return false;
}

void CDataMgr::AddGateWay(GATE_WAY_TYPE _eGateWayType)
{
	m_pAccountArr[m_iSelect]->GateWayVec.push_back(int(_eGateWayType));
	m_pAccountArr[m_iSelect]->iGateWayNum += 1;
}

int CDataMgr::Load(TCHAR* _tszID, TCHAR* _tszPW)
{
	if(_tcscmp(_tszID, _T("")) == 0)
	{
		// ID Empty
		return 1;
	}

	if(_tcscmp(_tszPW, _T("")) == 0)
	{
		// PW Empty
		return 2;
	}

	// Account
	TCHAR tszAccount[MAX_STR];
	_tcscpy_s(tszAccount, MAX_STR, _T("../Data/Account/"));
	_tcscat_s(tszAccount, MAX_STR, _tszID);
	_tcscat_s(tszAccount, MAX_STR, _T(".dat"));

	// Handle
	HANDLE hFile = CreateFile(tszAccount, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;

	if(hFile == INVALID_HANDLE_VALUE)
	{
		// Success
		hFile = CreateFile(tszAccount, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, _tszPW, sizeof(TCHAR) * MIN_STR, &dwByte, NULL);
		WriteFile(hFile, &m_iSelect, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &m_iCharacterNum, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &m_iGold, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &m_dwRenderMode, sizeof(DWORD), &dwByte, NULL);
		WriteFile(hFile, &m_dwGameMode, sizeof(DWORD), &dwByte, NULL);

		CloseHandle(hFile);

		// Load
		_tcscpy_s(m_tszID, MIN_STR, _tszID);
		_tcscpy_s(m_tszPW, MIN_STR, _tszPW);
		_tcscpy_s(m_tszAccount, MAX_STR, tszAccount);
		Load();
		return 0;
	}
	else
	{
		TCHAR tszPW[MIN_STR];
		ReadFile(hFile, tszPW, sizeof(TCHAR) * MIN_STR, &dwByte, NULL);

		if(_tcscmp(tszPW, _tszPW) == 0)
		{
			// Success
			CloseHandle(hFile);

			// Load
			_tcscpy_s(m_tszID, MIN_STR, _tszID);
			_tcscpy_s(m_tszPW, MIN_STR, _tszPW);
			_tcscpy_s(m_tszAccount, MAX_STR, tszAccount);
			Load();
			return 0;
		}
		else
		{
			// PW Error
			CloseHandle(hFile);
			return 3;
		}
	}
}

int CDataMgr::Create(TCHAR* _tszName, int _iGender, int _iJob)
{
	if(_tcscmp(_tszName, _T("")) == 0)
	{
		// NameEmpty
		return 1;
	}

	for(int i = 0; i < 10; ++i)
	{
		if(m_pAccountArr[i] == NULL)
		{
			m_pAccountArr[i] = new Account;

			// Pos
			m_pAccountArr[i]->vPos = D3DXVECTOR3(7200.0f, 777.0f, 2423.0f);

			// Angle
			m_pAccountArr[i]->vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// Size
			m_pAccountArr[i]->vSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// SlotType
			if(_iJob == 0)
			{
				m_pAccountArr[i]->eSlotType[0] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[0] = SLOT_ID_BARBARIAN_CLOSE;
				m_pAccountArr[i]->eSlotType[1] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[1] = SLOT_ID_BARBARIAN_CLOSE;
				m_pAccountArr[i]->eSlotType[2] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[2] = SLOT_ID_BARBARIAN_CLOSE;
				m_pAccountArr[i]->eSlotType[3] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[3] = SLOT_ID_BARBARIAN_CLOSE;
				m_pAccountArr[i]->eSlotType[4] = SLOT_TYPE_BARBARIAN_PRIMARY;
				m_pAccountArr[i]->eSlotID[4] = SLOT_ID_BARBARIAN_BASH;
				m_pAccountArr[i]->eSlotType[5] = SLOT_TYPE_BARBARIAN_SECONDARY;
				m_pAccountArr[i]->eSlotID[5] = SLOT_ID_BARBARIAN_PUNCH;
				m_pAccountArr[i]->eSlotType[6] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[6] = SLOT_ID_BARBARIAN_POTION;
			}
			else if(_iJob == 1)
			{
				m_pAccountArr[i]->eSlotType[0] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[0] = SLOT_ID_DEMONHUNTER_CLOSE;
				m_pAccountArr[i]->eSlotType[1] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[1] = SLOT_ID_DEMONHUNTER_CLOSE;
				m_pAccountArr[i]->eSlotType[2] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[2] = SLOT_ID_DEMONHUNTER_CLOSE;
				m_pAccountArr[i]->eSlotType[3] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[3] = SLOT_ID_DEMONHUNTER_CLOSE;
				m_pAccountArr[i]->eSlotType[4] = SLOT_TYPE_DEMONHUNTER_PRIMARY;
				m_pAccountArr[i]->eSlotID[4] = SLOT_ID_DEMONHUNTER_HUNGERING_ARROW;
				m_pAccountArr[i]->eSlotType[5] = SLOT_TYPE_DEMONHUNTER_SECONDARY;
				m_pAccountArr[i]->eSlotID[5] = SLOT_ID_DEMONHUNTER_PUNCH;
				m_pAccountArr[i]->eSlotType[6] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[6] = SLOT_ID_DEMONHUNTER_POTION;
			}
			else if(_iJob == 2)
			{
				m_pAccountArr[i]->eSlotType[0] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[0] = SLOT_ID_MONK_CLOSE;
				m_pAccountArr[i]->eSlotType[1] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[1] = SLOT_ID_MONK_CLOSE;
				m_pAccountArr[i]->eSlotType[2] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[2] = SLOT_ID_MONK_CLOSE;
				m_pAccountArr[i]->eSlotType[3] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[3] = SLOT_ID_MONK_CLOSE;
				m_pAccountArr[i]->eSlotType[4] = SLOT_TYPE_MONK_PRIMARY;
				m_pAccountArr[i]->eSlotID[4] = SLOT_ID_MONK_FISTS_OF_THUNDER;
				m_pAccountArr[i]->eSlotType[5] = SLOT_TYPE_MONK_SECONDARY;
				m_pAccountArr[i]->eSlotID[5] = SLOT_ID_MONK_PUNCH;
				m_pAccountArr[i]->eSlotType[6] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[6] = SLOT_ID_MONK_POTION;
			}
			else if(_iJob == 3)
			{
				m_pAccountArr[i]->eSlotType[0] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[0] = SLOT_ID_WITCHDOCTOR_CLOSE;
				m_pAccountArr[i]->eSlotType[1] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[1] = SLOT_ID_WITCHDOCTOR_CLOSE;
				m_pAccountArr[i]->eSlotType[2] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[2] = SLOT_ID_WITCHDOCTOR_CLOSE;
				m_pAccountArr[i]->eSlotType[3] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[3] = SLOT_ID_WITCHDOCTOR_CLOSE;
				m_pAccountArr[i]->eSlotType[4] = SLOT_TYPE_WITCHDOCTOR_PRIMARY;
				m_pAccountArr[i]->eSlotID[4] = SLOT_ID_WITCHDOCTOR_POISON_DART;
				m_pAccountArr[i]->eSlotType[5] = SLOT_TYPE_WITCHDOCTOR_SECONDARY;
				m_pAccountArr[i]->eSlotID[5] = SLOT_ID_WITCHDOCTOR_PUNCH;
				m_pAccountArr[i]->eSlotType[6] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[6] = SLOT_ID_WITCHDOCTOR_POTION;
			}
			else if(_iJob == 4)
			{
				m_pAccountArr[i]->eSlotType[0] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[0] = SLOT_ID_WIZARD_CLOSE;
				m_pAccountArr[i]->eSlotType[1] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[1] = SLOT_ID_WIZARD_CLOSE;
				m_pAccountArr[i]->eSlotType[2] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[2] = SLOT_ID_WIZARD_CLOSE;
				m_pAccountArr[i]->eSlotType[3] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[3] = SLOT_ID_WIZARD_CLOSE;
				m_pAccountArr[i]->eSlotType[4] = SLOT_TYPE_WIZARD_PRIMARY;
				m_pAccountArr[i]->eSlotID[4] = SLOT_ID_WIZARD_MAGIC_MISSILE;
				m_pAccountArr[i]->eSlotType[5] = SLOT_TYPE_WIZARD_SECONDARY;
				m_pAccountArr[i]->eSlotID[5] = SLOT_ID_WIZARD_PUNCH;
				m_pAccountArr[i]->eSlotType[6] = SLOT_TYPE_END;
				m_pAccountArr[i]->eSlotID[6] = SLOT_ID_WIZARD_POTION;
			}

			// Info
			_tcscpy_s(m_pAccountArr[i]->info.tszMapKey, MIN_STR, _T("Tristram"));
			_tcscpy_s(m_pAccountArr[i]->info.tszName, MIN_STR, _tszName);
			m_pAccountArr[i]->info.iGender = _iGender;
			m_pAccountArr[i]->info.iJob = _iJob;

			// Stat
			m_pAccountArr[i]->stat.iLevel = 1;

			if(_iJob == 0)
			{
				m_pAccountArr[i]->stat.iStrength = 10;
				m_pAccountArr[i]->stat.iAgility = 8;
				m_pAccountArr[i]->stat.iIntelligence = 8;
				m_pAccountArr[i]->stat.iVitality = 9;
				m_pAccountArr[i]->stat.iLife = 130;		m_pAccountArr[i]->stat.iMaxLife = 40;
				m_pAccountArr[i]->stat.iRage = 0;		m_pAccountArr[i]->stat.iMaxRage = 100;
				m_pAccountArr[i]->stat.iExp = 0;		m_pAccountArr[i]->stat.iMaxExp = 280;
			}
			else if(_iJob == 1)
			{
				m_pAccountArr[i]->stat.iStrength = 8;
				m_pAccountArr[i]->stat.iAgility = 10;
				m_pAccountArr[i]->stat.iIntelligence = 8;
				m_pAccountArr[i]->stat.iVitality = 9;
				m_pAccountArr[i]->stat.iLife = 130;		m_pAccountArr[i]->stat.iMaxLife = 40;
				m_pAccountArr[i]->stat.iHate = 125;		m_pAccountArr[i]->stat.iMaxHate = 125;		
				m_pAccountArr[i]->stat.iControl = 30;	m_pAccountArr[i]->stat.iMaxControl = 30;
				m_pAccountArr[i]->stat.iExp = 0;		m_pAccountArr[i]->stat.iMaxExp = 280;
			}
			else if(_iJob == 2)
			{
				m_pAccountArr[i]->stat.iStrength = 8;
				m_pAccountArr[i]->stat.iAgility = 10;
				m_pAccountArr[i]->stat.iIntelligence = 8;
				m_pAccountArr[i]->stat.iVitality = 9;
				m_pAccountArr[i]->stat.iLife = 130;		m_pAccountArr[i]->stat.iMaxLife = 40;
				m_pAccountArr[i]->stat.iEffort = 250;	m_pAccountArr[i]->stat.iMaxEffort = 250;
				m_pAccountArr[i]->stat.iExp = 0;		m_pAccountArr[i]->stat.iMaxExp = 280;
			}
			else if(_iJob == 3)
			{
				m_pAccountArr[i]->stat.iStrength = 8;
				m_pAccountArr[i]->stat.iAgility = 8;
				m_pAccountArr[i]->stat.iIntelligence = 10;
				m_pAccountArr[i]->stat.iVitality = 9;
				m_pAccountArr[i]->stat.iLife = 130;		m_pAccountArr[i]->stat.iMaxLife = 40;
				m_pAccountArr[i]->stat.iMana = 750;		m_pAccountArr[i]->stat.iMaxMana = 750;
				m_pAccountArr[i]->stat.iExp = 0;		m_pAccountArr[i]->stat.iMaxExp = 280;
			}
			else if(_iJob == 4)
			{
				m_pAccountArr[i]->stat.iStrength = 8;
				m_pAccountArr[i]->stat.iAgility = 8;
				m_pAccountArr[i]->stat.iIntelligence = 10;
				m_pAccountArr[i]->stat.iVitality = 9;
				m_pAccountArr[i]->stat.iLife = 130;		m_pAccountArr[i]->stat.iMaxLife = 40;
				m_pAccountArr[i]->stat.iVision = 100;	m_pAccountArr[i]->stat.iMaxVision = 100;
				m_pAccountArr[i]->stat.iExp = 0;		m_pAccountArr[i]->stat.iMaxExp = 280;
			}

			// Success
			++m_iCharacterNum;
			return 0;
		}
	}

	// Full
	return 2;
}

int CDataMgr::Delete(int _iIndex)
{
	Account* pAccount = m_pAccountArr[_iIndex];

	for(int i = _iIndex + 1; i < m_iCharacterNum; ++i)
		m_pAccountArr[i - 1] = m_pAccountArr[i];
	m_pAccountArr[--m_iCharacterNum] = NULL;

	if(m_iCharacterNum <= m_iSelect)
	{
		if(--m_iSelect < 0)
			m_iSelect = 0;
	}

	delete pAccount;
	return 0;
}

void CDataMgr::Renew()
{
	// FindObject
	CObject* pFindObject = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_PLAYER)->FindObject(pFindObject, _T("Player"));
	if(pFindObject == NULL)
		return;

	// Player
	CPlayer* pPlayer = (CPlayer*)pFindObject;

	// Clear ItemVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iItemNum; ++i)
	{
		delete m_pAccountArr[m_iSelect]->ItemVec[i];
		m_pAccountArr[m_iSelect]->ItemVec[i] = NULL;
	}
	m_pAccountArr[m_iSelect]->ItemVec.clear();

	// Clear EquipIndexVec
	m_pAccountArr[m_iSelect]->EquipIndexVec.clear();

	// Clear EquipVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iEquipNum; ++i)
	{
		delete m_pAccountArr[m_iSelect]->EquipVec[i];
		m_pAccountArr[m_iSelect]->EquipVec[i] = NULL;
	}
	m_pAccountArr[m_iSelect]->EquipVec.clear();

	// Clear StorageVec
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < m_pAccountArr[m_iSelect]->iStorageNum[i]; ++j)
		{
			delete m_pAccountArr[m_iSelect]->StorageVec[i][j];
			m_pAccountArr[m_iSelect]->StorageVec[i][j] = NULL;
		}
		m_pAccountArr[m_iSelect]->StorageVec[i].clear();
	}

	// Clear QuestVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iQuestNum; ++i)
	{
		delete m_pAccountArr[m_iSelect]->QuestVec[i];
		m_pAccountArr[m_iSelect]->QuestVec[i] = NULL;
	}
	m_pAccountArr[m_iSelect]->QuestVec.clear();

	// Clear AchieveVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iAchieveNum; ++i)
	{
		delete m_pAccountArr[m_iSelect]->AchieveVec[i];
		m_pAccountArr[m_iSelect]->AchieveVec[i] = NULL;
	}
	m_pAccountArr[m_iSelect]->AchieveVec.clear();

	// Clear FollowerEquipIndexVec
	m_pAccountArr[m_iSelect]->FollowerEquipIndexVec.clear();

	// Clear FollowerEquipVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iFollowerEquipNum; ++i)
	{
		delete m_pAccountArr[m_iSelect]->FollowerEquipVec[i];
		m_pAccountArr[m_iSelect]->FollowerEquipVec[i] = NULL;
	}
	m_pAccountArr[m_iSelect]->FollowerEquipVec.clear();

	// Gold
	m_iGold = CItemMgr::GetInstance()->GetGold();

	// RenderMode
	m_dwRenderMode = CSettingMgr::GetInstance()->GetRenderMode();

	// GameMode
	m_dwGameMode = CSettingMgr::GetInstance()->GetGameMode();

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Info
	Info* pInfo = ((CPlayer*)pPlayer)->GetInfo();

	// Stat
	Stat* pStat = ((CPlayer*)pPlayer)->GetStat();

	// Pos
	m_pAccountArr[m_iSelect]->vPos = pTransformCom->m_vPos;

	// Angle
	m_pAccountArr[m_iSelect]->vAngle = pTransformCom->m_vAngle;

	// Size
	m_pAccountArr[m_iSelect]->vSize = pTransformCom->m_vSize;

	// SlotType & SlotID
	for(int i = 0; i < 7; ++i)
	{
		// Slot
		CSlot* pSlot = ((CPlayer*)pPlayer)->GetSlot(i);
		m_pAccountArr[m_iSelect]->eSlotType[i] = pSlot->GetSlotType();
		m_pAccountArr[m_iSelect]->eSlotID[i] = pSlot->GetSlotID();
	}

	// Info
	_tcscpy_s(m_pAccountArr[m_iSelect]->info.tszMapKey, MIN_STR, pInfo->tszMapKey);
	_tcscpy_s(m_pAccountArr[m_iSelect]->info.tszName, MIN_STR, pInfo->tszName);
	m_pAccountArr[m_iSelect]->info.iJob = pInfo->iJob;
	m_pAccountArr[m_iSelect]->info.iGender = pInfo->iGender;

	// Stat
	memcpy_s(&m_pAccountArr[m_iSelect]->stat, sizeof(Stat), pStat, sizeof(Stat));

	// ItemNum
	m_pAccountArr[m_iSelect]->iItemNum = CItemMgr::GetInstance()->GetSizeOfInven();

	// ItemVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iItemNum; ++i)
	{
		Item* pItem = new Item(CItemMgr::GetInstance()->GetItemInInven(i));
		m_pAccountArr[m_iSelect]->ItemVec.push_back(pItem);
	}

	// EquipNum
	m_pAccountArr[m_iSelect]->iEquipNum = CItemMgr::GetInstance()->GetSizeOfEquip();

	// EquipIndex & EquipVec
	for(int i = 0; i < 13; ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInEquip(i);
		if(pItem == NULL)
			continue;

		m_pAccountArr[m_iSelect]->EquipIndexVec.push_back(i);
		m_pAccountArr[m_iSelect]->EquipVec.push_back(new Item(pItem));
	}

	// StorageNum
	for(int i = 0; i < 5; ++i)
	{
		m_pAccountArr[m_iSelect]->iStorageNum[i] = CItemMgr::GetInstance()->GetSizeOfStorage(i);

		// Storage
		for(int j = 0; j < m_pAccountArr[m_iSelect]->iStorageNum[i]; ++j)
		{
			Item* pItem = CItemMgr::GetInstance()->GetItemInStorage(i, j);
			if(pItem == NULL)
				continue;

			m_pAccountArr[m_iSelect]->StorageVec[i].push_back(new Item(pItem));
		}
	}

	// QuestNum
	m_pAccountArr[m_iSelect]->iQuestNum = CQuestMgr::GetInstance()->GetSizeOfQuest();

	// QuestVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iQuestNum; ++i)
	{
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(i);
		if(pQuest == NULL)
			continue;

		m_pAccountArr[m_iSelect]->QuestVec.push_back(new Quest(pQuest));
	}

	// AchieveNum
	m_pAccountArr[m_iSelect]->iAchieveNum = CQuestMgr::GetInstance()->GetSizeOfAchieve();

	// AchieveVec
	for(int i = 0; i < m_pAccountArr[m_iSelect]->iAchieveNum; ++i)
	{
		Achieve* pAchieve = CQuestMgr::GetInstance()->GetAchieve(i);
		if(pAchieve == NULL)
			continue;

		m_pAccountArr[m_iSelect]->AchieveVec.push_back(new Achieve(pAchieve));
	}

	// FindObject
	pFindObject = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_FOLLOWER)->FindObject(pFindObject, _T("Follower"));
	if(pFindObject == NULL)
	{
		// HaveFollower
		m_pAccountArr[m_iSelect]->bHaveFollower = false;

		// FollowerInfo
		ZeroMemory(&m_pAccountArr[m_iSelect]->followerInfo, sizeof(FollowerInfo));

		// FollowerPos
		ZeroMemory(&m_pAccountArr[m_iSelect]->vFollowerPos, sizeof(D3DXVECTOR3));

		// FollowerAngle
		ZeroMemory(&m_pAccountArr[m_iSelect]->vFollowerAngle, sizeof(D3DXVECTOR3));

		// FollowerSize
		m_pAccountArr[m_iSelect]->vFollowerSize.x = 1.0f; m_pAccountArr[m_iSelect]->vFollowerSize.y = 1.0f; m_pAccountArr[m_iSelect]->vFollowerSize.z = 1.0f;
	}
	else
	{
		// Follower
		CFollower* pFollower = (CFollower*)pFindObject;
		CTransformCom* pTransformCom = (CTransformCom*)pFollower->GetComponent(COM_TYPE_TRANSFORM);

		// HaveFollower
		m_pAccountArr[m_iSelect]->bHaveFollower = true;

		// FollowerInfo
		memcpy_s(&m_pAccountArr[m_iSelect]->followerInfo, sizeof(FollowerInfo), pFollower->GetFollowerInfo(), sizeof(FollowerInfo));

		// FollowerPos
		memcpy_s(&m_pAccountArr[m_iSelect]->vFollowerPos, sizeof(D3DXVECTOR3), &pTransformCom->m_vPos, sizeof(D3DXVECTOR3));

		// FollowerAngle
		memcpy_s(&m_pAccountArr[m_iSelect]->vFollowerAngle, sizeof(D3DXVECTOR3), &pTransformCom->m_vAngle, sizeof(D3DXVECTOR3));

		// FollowerSize
		memcpy_s(&m_pAccountArr[m_iSelect]->vFollowerSize, sizeof(D3DXVECTOR3), &pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// FollowerEquipNum
	m_pAccountArr[m_iSelect]->iFollowerEquipNum = CItemMgr::GetInstance()->GetSizeOfFollowerEquip();

	// EquipIndex & EquipVec
	for(int i = 0; i < 5; ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(i);
		if(pItem == NULL)
			continue;

		m_pAccountArr[m_iSelect]->FollowerEquipIndexVec.push_back(i);
		m_pAccountArr[m_iSelect]->FollowerEquipVec.push_back(new Item(pItem));
	}
}

void CDataMgr::Reset()
{
	// Select
	m_iSelect = 0;

	// CharacterNum
	m_iCharacterNum = 0;

	// Gold
	m_iGold = 0;

	// RenderMode
	m_dwRenderMode = 0;

	// GameMode
	m_dwGameMode = 0;

	// ID
	ZeroMemory(m_tszID, sizeof(m_tszID));

	// Account
	ZeroMemory(m_tszPW, sizeof(m_tszPW));

	// Account
	ZeroMemory(m_tszAccount, sizeof(m_tszAccount));

	// AccountArr
	for(int i = 0; i < 10; ++i)
	{
		if(m_pAccountArr[i] != NULL)
		{
			delete m_pAccountArr[i];
			m_pAccountArr[i] = NULL;
		}
	}
}

void CDataMgr::Save()
{
	if(_tcscmp(m_tszAccount, _T("")) == 0)
		return;

	// Handle
	HANDLE hFile = CreateFile(m_tszAccount, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;

	// PW
	WriteFile(hFile, m_tszPW, sizeof(TCHAR) * MIN_STR, &dwByte, NULL);

	// Select
	WriteFile(hFile, &m_iSelect, sizeof(int), &dwByte, NULL);

	// CharacterNum
	WriteFile(hFile, &m_iCharacterNum, sizeof(int), &dwByte, NULL);

	// Gold
	WriteFile(hFile, &m_iGold, sizeof(int), &dwByte, NULL);

	// RenderMode
	WriteFile(hFile, &m_dwRenderMode, sizeof(DWORD), &dwByte, NULL);

	// GameMode
	WriteFile(hFile, &m_dwGameMode, sizeof(DWORD), &dwByte, NULL);

	for(int i = 0; i < m_iCharacterNum; ++i)
	{
		// Pos
		WriteFile(hFile, &m_pAccountArr[i]->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// Angle
		WriteFile(hFile, &m_pAccountArr[i]->vAngle, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// Size
		WriteFile(hFile, &m_pAccountArr[i]->vSize, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// SlotType
		WriteFile(hFile, &m_pAccountArr[i]->eSlotType, sizeof(SLOT_TYPE) * 7, &dwByte, NULL);

		// SlotID
		WriteFile(hFile, &m_pAccountArr[i]->eSlotID, sizeof(SLOT_ID) * 7, &dwByte, NULL);

		// Info
		WriteFile(hFile, &m_pAccountArr[i]->info, sizeof(Info), &dwByte, NULL);

		// Stat
		WriteFile(hFile, &m_pAccountArr[i]->stat, sizeof(Stat), &dwByte, NULL);

		// ItemNum
		WriteFile(hFile, &m_pAccountArr[i]->iItemNum, sizeof(int), &dwByte, NULL);

		// ItemVec
		for(int j = 0; j < m_pAccountArr[i]->iItemNum; ++j)
		{
			// Item
			WriteFile(hFile, m_pAccountArr[i]->ItemVec[j], 568, &dwByte, NULL);

			// SockNum
			WriteFile(hFile, &m_pAccountArr[i]->ItemVec[j]->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			WriteFile(hFile, &m_pAccountArr[i]->ItemVec[j]->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < m_pAccountArr[i]->ItemVec[j]->iSockCnt; ++k)
				WriteFile(hFile, m_pAccountArr[i]->ItemVec[j]->SockArr[k], sizeof(Item), &dwByte, NULL);
		}

		// EquipNum
		WriteFile(hFile, &m_pAccountArr[i]->iEquipNum, sizeof(int), &dwByte, NULL);

		// EquipVec
		for(int j = 0; j < m_pAccountArr[i]->iEquipNum; ++j)
		{
			// EquipIndex
			WriteFile(hFile, &m_pAccountArr[i]->EquipIndexVec[j], sizeof(int), &dwByte, NULL);

			// Item
			WriteFile(hFile, m_pAccountArr[i]->EquipVec[j], 568, &dwByte, NULL);

			// SockNum
			WriteFile(hFile, &m_pAccountArr[i]->EquipVec[j]->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			WriteFile(hFile, &m_pAccountArr[i]->EquipVec[j]->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < m_pAccountArr[i]->EquipVec[j]->iSockCnt; ++k)
				WriteFile(hFile, m_pAccountArr[i]->EquipVec[j]->SockArr[k], sizeof(Item), &dwByte, NULL);
		}

		// StorageNum
		for(int j = 0; j < 5; ++j)
		{
			WriteFile(hFile, &m_pAccountArr[i]->iStorageNum[j], sizeof(int), &dwByte, NULL);

			// Storage
			for(int k = 0; k < m_pAccountArr[i]->iStorageNum[j]; ++k)
			{
				// Item
				WriteFile(hFile, m_pAccountArr[i]->StorageVec[j][k], 568, &dwByte, NULL);

				// SockNum
				WriteFile(hFile, &m_pAccountArr[i]->StorageVec[j][k]->iSockNum, sizeof(int), &dwByte, NULL);

				// SockCnt
				WriteFile(hFile, &m_pAccountArr[i]->StorageVec[j][k]->iSockCnt, sizeof(int), &dwByte, NULL);

				// SockArr
				for(int z = 0; z < m_pAccountArr[i]->StorageVec[j][k]->iSockNum; ++z)
					WriteFile(hFile, m_pAccountArr[i]->StorageVec[j][k]->SockArr[z], sizeof(Item), &dwByte, NULL);
			}
		}

		// QuestNum
		WriteFile(hFile, &m_pAccountArr[i]->iQuestNum, sizeof(int), &dwByte, NULL);

		// QuestVec
		for(int j = 0; j < m_pAccountArr[i]->iQuestNum; ++j)
		{
			// Quest
			WriteFile(hFile, m_pAccountArr[i]->QuestVec[j], sizeof(Quest), &dwByte, NULL);
		}

		// AchieveNum
		WriteFile(hFile, &m_pAccountArr[i]->iAchieveNum, sizeof(int), &dwByte, NULL);

		// AchieveVec
		for(int j = 0; j < m_pAccountArr[i]->iAchieveNum; ++j)
		{
			// Achieve
			WriteFile(hFile, m_pAccountArr[i]->AchieveVec[j], sizeof(Achieve), &dwByte, NULL);
		}

		// HaveFollower
		WriteFile(hFile, &m_pAccountArr[i]->bHaveFollower, sizeof(bool), &dwByte, NULL);

		// FollowerInfo
		WriteFile(hFile, &m_pAccountArr[i]->followerInfo, sizeof(FollowerInfo), &dwByte, NULL);

		// FollowerPos
		WriteFile(hFile, &m_pAccountArr[i]->vFollowerPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerAngle
		WriteFile(hFile, &m_pAccountArr[i]->vFollowerAngle, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerSize
		WriteFile(hFile, &m_pAccountArr[i]->vFollowerSize, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerEquipNum
		WriteFile(hFile, &m_pAccountArr[i]->iFollowerEquipNum, sizeof(int), &dwByte, NULL);

		// FollowerEquipVec
		for(int j = 0; j < m_pAccountArr[i]->iFollowerEquipNum; ++j)
		{
			// FollowerEquipIndex
			WriteFile(hFile, &m_pAccountArr[i]->FollowerEquipIndexVec[j], sizeof(int), &dwByte, NULL);

			// Item
			WriteFile(hFile, m_pAccountArr[i]->FollowerEquipVec[j], 568, &dwByte, NULL);

			// SockNum
			WriteFile(hFile, &m_pAccountArr[i]->FollowerEquipVec[j]->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			WriteFile(hFile, &m_pAccountArr[i]->FollowerEquipVec[j]->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < m_pAccountArr[i]->FollowerEquipVec[j]->iSockCnt; ++k)
				WriteFile(hFile, m_pAccountArr[i]->FollowerEquipVec[j]->SockArr[k], sizeof(Item), &dwByte, NULL);
		}

		// GateWayNum
		WriteFile(hFile, &m_pAccountArr[i]->iGateWayNum, sizeof(int), &dwByte, NULL);

		// GateWayVec
		for(int j = 0; j < m_pAccountArr[i]->iGateWayNum; ++j)
			WriteFile(hFile, &m_pAccountArr[i]->GateWayVec[j], sizeof(int), &dwByte, NULL);
	}

	// Close
	CloseHandle(hFile);
}

void CDataMgr::Load()
{
	if(_tcscmp(m_tszAccount, _T("")) == 0)
		return;

	// Handle
	HANDLE hFile = CreateFile(m_tszAccount, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByte;

	// PW
	TCHAR tszPW[MIN_STR];
	ReadFile(hFile, tszPW, sizeof(TCHAR) * MIN_STR, &dwByte, NULL);

	// Select
	ReadFile(hFile, &m_iSelect, sizeof(int), &dwByte, NULL);

	// CharacterNum
	ReadFile(hFile, &m_iCharacterNum, sizeof(int), &dwByte, NULL);

	// Gold
	ReadFile(hFile, &m_iGold, sizeof(int), &dwByte, NULL);

	// RenderMode
	ReadFile(hFile, &m_dwRenderMode, sizeof(DWORD), &dwByte, NULL);

	// GameMode
	ReadFile(hFile, &m_dwGameMode, sizeof(DWORD), &dwByte, NULL);

	for(int i = 0; i < m_iCharacterNum; ++i)
	{
		m_pAccountArr[i] = new Account;

		// Pos
		ReadFile(hFile, &m_pAccountArr[i]->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// Angle
		ReadFile(hFile, &m_pAccountArr[i]->vAngle, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// Size
		ReadFile(hFile, &m_pAccountArr[i]->vSize, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// SlotType
		ReadFile(hFile, &m_pAccountArr[i]->eSlotType, sizeof(SLOT_TYPE) * 7, &dwByte, NULL);

		// SlotID
		ReadFile(hFile, &m_pAccountArr[i]->eSlotID, sizeof(SLOT_ID) * 7, &dwByte, NULL);

		// Info
		ReadFile(hFile, &m_pAccountArr[i]->info, sizeof(Info), &dwByte, NULL);

		// Stat
		ReadFile(hFile, &m_pAccountArr[i]->stat, sizeof(Stat), &dwByte, NULL);

		// ItemNum
		ReadFile(hFile, &m_pAccountArr[i]->iItemNum, sizeof(int), &dwByte, NULL);

		// ItemVec
		for(int j = 0; j < m_pAccountArr[i]->iItemNum; ++j)
		{
			// Item
			Item* pItem = new Item;
			ReadFile(hFile, pItem, 568, &dwByte, NULL);

			// SockNum
			ReadFile(hFile, &pItem->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			ReadFile(hFile, &pItem->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < pItem->iSockCnt; ++k)
			{
				Item* pSock = new Item;
				ReadFile(hFile, pSock, sizeof(Item), &dwByte, NULL);
				pItem->SockArr[k] = pSock;
			}

			m_pAccountArr[i]->ItemVec.push_back(pItem);
		}

		// EquipNum
		ReadFile(hFile, &m_pAccountArr[i]->iEquipNum, sizeof(int), &dwByte, NULL);
		
		// EquipVec
		for(int j = 0; j < m_pAccountArr[i]->iEquipNum; ++j)
		{
			// EquipIndex
			int iEquipIndex;
			ReadFile(hFile, &iEquipIndex, sizeof(int), &dwByte, NULL);
			m_pAccountArr[i]->EquipIndexVec.push_back(iEquipIndex);

			// Item
			Item* pItem = new Item;
			ReadFile(hFile, pItem, 568, &dwByte, NULL);

			// SockNum
			ReadFile(hFile, &pItem->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			ReadFile(hFile, &pItem->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < pItem->iSockCnt; ++k)
			{
				Item* pSock = new Item;
				ReadFile(hFile, pSock, sizeof(Item), &dwByte, NULL);
				pItem->SockArr[k] = pSock;
			}

			m_pAccountArr[i]->EquipVec.push_back(pItem);
		}

		// StorageNum
		for(int j = 0; j < 5; ++j)
		{
			ReadFile(hFile, &m_pAccountArr[i]->iStorageNum[j], sizeof(int), &dwByte, NULL);

			// StorageVec
			for(int k = 0; k < m_pAccountArr[i]->iStorageNum[j]; ++k)
			{
				// Item
				Item* pItem = new Item;
				ReadFile(hFile, pItem, 568, &dwByte, NULL);

				// SockNum
				ReadFile(hFile, &pItem->iSockNum, sizeof(int), &dwByte, NULL);

				// SockCnt
				ReadFile(hFile, &pItem->iSockCnt, sizeof(int), &dwByte, NULL);

				// SockArr
				for(int z = 0; z < pItem->iSockCnt; ++z)
				{
					Item* pSock = new Item;
					ReadFile(hFile, pSock, sizeof(Item), &dwByte, NULL);
					pItem->SockArr[z] = pSock;
				}

				m_pAccountArr[i]->StorageVec[j].push_back(pItem);
			}
		}

		// QuestNum
		ReadFile(hFile, &m_pAccountArr[i]->iQuestNum, sizeof(int), &dwByte, NULL);

		// QuestVec
		for(int j = 0; j < m_pAccountArr[i]->iQuestNum; ++j)
		{
			// Quest
			Quest* pQuest = new Quest;
			ReadFile(hFile, pQuest, sizeof(Quest), &dwByte, NULL);

			m_pAccountArr[i]->QuestVec.push_back(pQuest);
		}

		// AchieveNum
		ReadFile(hFile, &m_pAccountArr[i]->iAchieveNum, sizeof(int), &dwByte, NULL);

		// AchieveVec
		for(int j = 0; j < m_pAccountArr[i]->iAchieveNum; ++j)
		{
			// Achieve
			Achieve* pAchieve = new Achieve;
			ReadFile(hFile, pAchieve, sizeof(Achieve), &dwByte, NULL);

			m_pAccountArr[i]->AchieveVec.push_back(pAchieve);
		}

		// HaveFollower
		ReadFile(hFile, &m_pAccountArr[i]->bHaveFollower, sizeof(bool), &dwByte, NULL);

		// FollowerInfo
		ReadFile(hFile, &m_pAccountArr[i]->followerInfo, sizeof(FollowerInfo), &dwByte, NULL);

		// FollowerPos
		ReadFile(hFile, &m_pAccountArr[i]->vFollowerPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerAngle
		ReadFile(hFile, &m_pAccountArr[i]->vFollowerAngle, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerSize
		ReadFile(hFile, &m_pAccountArr[i]->vFollowerSize, sizeof(D3DXVECTOR3), &dwByte, NULL);

		// FollowerEquipNum
		ReadFile(hFile, &m_pAccountArr[i]->iFollowerEquipNum, sizeof(int), &dwByte, NULL);

		// FollowerEquipVec
		for(int j = 0; j < m_pAccountArr[i]->iFollowerEquipNum; ++j)
		{
			// FollowerEquipIndex
			int iFollowerEquipIndex;
			ReadFile(hFile, &iFollowerEquipIndex, sizeof(int), &dwByte, NULL);
			m_pAccountArr[i]->FollowerEquipIndexVec.push_back(iFollowerEquipIndex);

			// Item
			Item* pItem = new Item;
			ReadFile(hFile, pItem, 568, &dwByte, NULL);

			// SockNum
			ReadFile(hFile, &pItem->iSockNum, sizeof(int), &dwByte, NULL);

			// SockCnt
			ReadFile(hFile, &pItem->iSockCnt, sizeof(int), &dwByte, NULL);

			// SockArr
			for(int k = 0; k < pItem->iSockCnt; ++k)
			{
				Item* pSock = new Item;
				ReadFile(hFile, pSock, sizeof(Item), &dwByte, NULL);
				pItem->SockArr[k] = pSock;
			}

			m_pAccountArr[i]->FollowerEquipVec.push_back(pItem);
		}

		// GeteWayNum
		ReadFile(hFile, &m_pAccountArr[i]->iGateWayNum, sizeof(int), &dwByte, NULL);

		// GateWayVec
		for(int j = 0; j < m_pAccountArr[i]->iGateWayNum; ++j)
		{
			int iGateWay;
			ReadFile(hFile, &iGateWay, sizeof(int), &dwByte, NULL);

			m_pAccountArr[i]->GateWayVec.push_back(iGateWay);
		}
	}

	// Close
	CloseHandle(hFile);
}