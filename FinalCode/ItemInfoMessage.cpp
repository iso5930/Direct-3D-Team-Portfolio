#include "StdAfx.h"
#include "ItemInfoMessage.h"

CItemInfoMessage::CItemInfoMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_ItemInfo"))
{
	// Item
	m_pItem = new Item(_pItem);

	// ItemPannelMessage
	m_pItemPannelMessage = NULL;

	// ItemGridMessage
	m_pItemGridMessage = NULL;

	// ItemIconMessage
	m_pItemIconMessage = NULL;

	// ItemSockSign
	ZeroMemory(m_pItemSockSign, sizeof(m_pItemSockSign));

	// Color
	m_dwColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	// Class
	ZeroMemory(m_tszClass, sizeof(m_tszClass));
	if(m_pItem->dwItemClass == 0)
	{
		if(m_pItem->dwItemType & ITEM_TYPE_GEM)
		{
			_tcscpy_s(m_tszClass, MIN_STR, _T("보석 아이템"));
			m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if(m_pItem->dwItemType & ITEM_TYPE_MATERIAL)
		{
			_tcscpy_s(m_tszClass, MIN_STR, _T("재료 아이템"));
			m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if(m_pItem->dwItemType & ITEM_TYPE_QUEST)
		{
			_tcscpy_s(m_tszClass, MIN_STR, _T("퀘스트 아이템"));
			m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_NORMAL)
	{
		_tcscpy_s(m_tszClass, MIN_STR, _T("일반 아이템"));
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		_tcscpy_s(m_tszClass, MIN_STR, _T("마법 아이템"));
		m_dwColor = D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f);
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		_tcscpy_s(m_tszClass, MIN_STR, _T("희귀 아이템"));
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		_tcscpy_s(m_tszClass, MIN_STR, _T("전설 아이템"));
		m_dwColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_SET)
	{
		_tcscpy_s(m_tszClass, MIN_STR, _T("세트 아이템"));
		m_dwColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}

	// Type
	ZeroMemory(m_tszType, sizeof(m_tszType));
	if(m_pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
		_tcscpy_s(m_tszType, MIN_STR, _T("장비"));
	else if(m_pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
		_tcscpy_s(m_tszType, MIN_STR, _T("보조장비"));
	else if(m_pItem->dwItemType & ITEM_TYPE_HELMS)
		_tcscpy_s(m_tszType, MIN_STR, _T("머리"));
	else if(m_pItem->dwItemType & ITEM_TYPE_SHOULDERS)
		_tcscpy_s(m_tszType, MIN_STR, _T("어깨"));
	else if(m_pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
		_tcscpy_s(m_tszType, MIN_STR, _T("몸통"));
	else if(m_pItem->dwItemType & ITEM_TYPE_BRACERS)
		_tcscpy_s(m_tszType, MIN_STR, _T("손목"));
	else if(m_pItem->dwItemType & ITEM_TYPE_GLOVES)
		_tcscpy_s(m_tszType, MIN_STR, _T("손"));
	else if(m_pItem->dwItemType & ITEM_TYPE_BELT)
		_tcscpy_s(m_tszType, MIN_STR, _T("허리"));
	else if(m_pItem->dwItemType & ITEM_TYPE_PANTS)
		_tcscpy_s(m_tszType, MIN_STR, _T("다리"));
	else if(m_pItem->dwItemType & ITEM_TYPE_BOOTS)
		_tcscpy_s(m_tszType, MIN_STR, _T("발"));
	else if(m_pItem->dwItemType & ITEM_TYPE_AMULET)
		_tcscpy_s(m_tszType, MIN_STR, _T("목"));
	else if(m_pItem->dwItemType & ITEM_TYPE_RING)
		_tcscpy_s(m_tszType, MIN_STR, _T("손가락"));
	else if(m_pItem->dwItemType & ITEM_TYPE_GEM)
		_tcscpy_s(m_tszType, MIN_STR, _T("보석"));
	else if(m_pItem->dwItemType & ITEM_TYPE_MATERIAL)
		_tcscpy_s(m_tszType, MIN_STR, _T("재료"));
	else if(m_pItem->dwItemType & ITEM_TYPE_QUEST)
		_tcscpy_s(m_tszType, MIN_STR, _T("퀘스트"));

	// Job
	ZeroMemory(m_tszJob, sizeof(m_tszJob));
	if(m_pItem->dwItemType & (ITEM_TYPE_BOOTS | ITEM_TYPE_GLOVES | ITEM_TYPE_HELMS | ITEM_TYPE_PANTS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_BELT | ITEM_TYPE_BRACERS | ITEM_TYPE_CHESTARMOR))
	{
		if(m_pItem->dwItemID & (BOOTS_ID_BARBARIAN | GLOVES_ID_BARBARIAN | HELMS_ID_BARBARIAN | PANTS_ID_BARBARIAN | SHOULDERS_ID_BARBARIAN | BELT_ID_BARBARIAN | BRACERS_ID_BARBARIAN | CHESTARMOR_ID_BARBARIAN))
			_tcscpy_s(m_tszJob, MIN_STR, _T("야만용사"));
		else if(m_pItem->dwItemID & (BOOTS_ID_DEMONHUNTER | GLOVES_ID_DEMONHUNTER | HELMS_ID_DEMONHUNTER | PANTS_ID_DEMONHUNTER | SHOULDERS_ID_DEMONHUNTER | BELT_ID_DEMONHUNTER | BRACERS_ID_DEMONHUNTER | CHESTARMOR_ID_DEMONHUNTER))
			_tcscpy_s(m_tszJob, MIN_STR, _T("악마사냥꾼"));
		else if(m_pItem->dwItemID & (BOOTS_ID_MONK | GLOVES_ID_MONK | HELMS_ID_MONK | PANTS_ID_MONK | SHOULDERS_ID_MONK | BELT_ID_MONK| BRACERS_ID_MONK | CHESTARMOR_ID_MONK))
			_tcscpy_s(m_tszJob, MIN_STR, _T("수도사"));
		else if(m_pItem->dwItemID & (BOOTS_ID_WITCHDOCTOR | GLOVES_ID_WITCHDOCTOR | HELMS_ID_WITCHDOCTOR | PANTS_ID_WITCHDOCTOR | SHOULDERS_ID_WITCHDOCTOR | BELT_ID_WITCHDOCTOR | BRACERS_ID_WITCHDOCTOR | CHESTARMOR_ID_WITCHDOCTOR))
			_tcscpy_s(m_tszJob, MIN_STR, _T("부두술사"));
		else if(m_pItem->dwItemID & (BOOTS_ID_WIZARD | GLOVES_ID_WIZARD | HELMS_ID_WIZARD | PANTS_ID_WIZARD | SHOULDERS_ID_WIZARD | BELT_ID_WIZARD | BRACERS_ID_WIZARD | CHESTARMOR_ID_WIZARD))
			_tcscpy_s(m_tszJob, MIN_STR, _T("마법사"));
	}

	// Gender
	ZeroMemory(m_tszGender, sizeof(m_tszGender));
	if(m_pItem->iGender == 0)
		_tcscpy_s(m_tszGender, MIN_STR, _T("남성"));
	else if(m_pItem->iGender == 1)
		_tcscpy_s(m_tszGender, MIN_STR, _T("여성"));
	else if(m_pItem->iGender == 2)
		_tcscpy_s(m_tszGender, MIN_STR, _T("공용"));

	// Level
	ZeroMemory(m_tszLevel, sizeof(m_tszLevel));
	StringCbPrintf(m_tszLevel, sizeof(m_tszLevel), _T("%s: %d"), _T("요구레벨"), m_pItem->iLevel);

	// Value
	ZeroMemory(m_tszValue, sizeof(m_tszValue));
	ZeroMemory(m_tszValueType, sizeof(m_tszValueType));
	if(m_pItem->iAtt > 0)
	{
		_itot_s(m_pItem->iAtt, m_tszValue, 10);
		_tcscpy_s(m_tszValueType, MIN_STR, _T("공격력"));
	}
	else if(m_pItem->iDef > 0)
	{
		_itot_s(m_pItem->iDef, m_tszValue, 10);
		_tcscpy_s(m_tszValueType, MIN_STR, _T("방어력"));
	}

	// AttackStat
	ZeroMemory(m_tszAttackStat, sizeof(m_tszAttackStat));
	ZeroMemory(m_tszAttackStatType, sizeof(m_tszAttackStatType));
	if(m_pItem->tAttackStat.fReducedCooldownTime > 0.0f)
	{
		StringCbPrintf(m_tszAttackStat, sizeof(m_tszAttackStat), _T("%g%%"), m_pItem->tAttackStat.fReducedCooldownTime * 100.0f);
		_tcscpy_s(m_tszAttackStatType, MIN_STR, _T("재사용대기시간 감소"));
	}
	else if(m_pItem->tAttackStat.fCriticalProbability > 0.0f)
	{
		StringCbPrintf(m_tszAttackStat, sizeof(m_tszAttackStat), _T("%g%%"), m_pItem->tAttackStat.fCriticalProbability * 100.0f);
		_tcscpy_s(m_tszAttackStatType, MIN_STR, _T("극대화 확률"));
	}
	else if(m_pItem->tAttackStat.fCriticalDamage > 0.0f)
	{
		StringCbPrintf(m_tszAttackStat, sizeof(m_tszAttackStat), _T("%g%%"), m_pItem->tAttackStat.fCriticalDamage * 100.0f);
		_tcscpy_s(m_tszAttackStatType, MIN_STR, _T("극대화 피해"));
	}

	// DefenseStat
	ZeroMemory(m_tszDefenseStat, sizeof(m_tszDefenseStat));
	ZeroMemory(m_tszDefenseStatType, sizeof(m_tszDefenseStatType));
	if(m_pItem->tDefenseStat.iPhysicalResistance > 0)
	{
		_itot_s(m_pItem->tDefenseStat.iPhysicalResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("물리저항"));
	}
	else if(m_pItem->tDefenseStat.iColdResistance > 0)	
	{
		_itot_s(m_pItem->tDefenseStat.iColdResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("냉기저항"));
	}
	else if(m_pItem->tDefenseStat.iFlameResistance > 0)
	{
		_itot_s(m_pItem->tDefenseStat.iFlameResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("화염저항"));
	}
	else if(m_pItem->tDefenseStat.iLightningResistance > 0)
	{
		_itot_s(m_pItem->tDefenseStat.iLightningResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("번개저항"));
	}
	else if(m_pItem->tDefenseStat.iPoisonResistance > 0)
	{
		_itot_s(m_pItem->tDefenseStat.iPoisonResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("독저항"));
	}
	else if(m_pItem->tDefenseStat.iHolyResistance > 0)
	{
		_itot_s(m_pItem->tDefenseStat.iHolyResistance, m_tszDefenseStat, 10);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("신성저항 감소"));
	}
	else if(m_pItem->tDefenseStat.fReducedNearDamage > 0.0f)
	{
		StringCbPrintf(m_tszDefenseStat, sizeof(m_tszDefenseStat), _T("%g%%"), m_pItem->tDefenseStat.fReducedNearDamage * 100.0f);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("근접피해 감소"));
	}
	else if(m_pItem->tDefenseStat.fReducedFarDamage > 0.0f)
	{
		StringCbPrintf(m_tszDefenseStat, sizeof(m_tszDefenseStat), _T("%g%%"), m_pItem->tDefenseStat.fReducedFarDamage * 100.0f);
		_tcscpy_s(m_tszDefenseStatType, MIN_STR, _T("투사체피해 감소"));
	}

	// LifeStat
	ZeroMemory(m_tszLifeStat, sizeof(m_tszLifeStat));
	ZeroMemory(m_tszLifeStatType, sizeof(m_tszLifeStatType));
	if(m_pItem->tLifeStat.fRestoresBonus > 0.0f)
	{
		StringCbPrintf(m_tszLifeStat, sizeof(m_tszLifeStat), _T("%g%%"), m_pItem->tLifeStat.fRestoresBonus * 100.0f);
		_tcscpy_s(m_tszLifeStatType, MIN_STR, _T("전체 생명력 보너스"));
	}
	else if(m_pItem->tLifeStat.iLifeRecoveryOfSecond > 0)
	{
		_itot_s(m_pItem->tLifeStat.iLifeRecoveryOfSecond, m_tszLifeStat, 10);
		_tcscpy_s(m_tszLifeStatType, MIN_STR, _T("초당 생명력 회복량"));
	}
	else if(m_pItem->tLifeStat.iLifeRecoveryOfHit > 0)
	{
		_itot_s(m_pItem->tLifeStat.iLifeRecoveryOfHit, m_tszLifeStat, 10);
		_tcscpy_s(m_tszLifeStatType, MIN_STR, _T("적중당 생명력 회복량"));
	}

	// ResourceStat
	ZeroMemory(m_tszResourceStat, sizeof(m_tszResourceStat));
	ZeroMemory(m_tszResourceStatType, sizeof(m_tszResourceStatType));
	if(m_pItem->tResourceStat.iControlRecoveryOfSecond > 0)
	{
		_itot_s(m_pItem->tResourceStat.iControlRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("절제 회복량/초"));
	}
	else if(m_pItem->tResourceStat.iEffortRecoveryOfSecond > 0)
	{
		_itot_s(m_pItem->tResourceStat.iEffortRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("공력 회복량/초"));
	}
	else if(m_pItem->tResourceStat.iHateRecoveryOfSecond > 0)	
	{
		_itot_s(m_pItem->tResourceStat.iHateRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("증오 회복량/초"));
	}
	else if(m_pItem->tResourceStat.iManaRecoveryOfSecond > 0)	
	{
		_itot_s(m_pItem->tResourceStat.iManaRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("마나 회복량/초"));
	}
	else if(m_pItem->tResourceStat.iRageRecoveryOfSecond > 0)	
	{
		_itot_s(m_pItem->tResourceStat.iRageRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("분노 회복량/초"));
	}
	else if(m_pItem->tResourceStat.iVisionRecoveryOfSecond > 0)
	{
		_itot_s(m_pItem->tResourceStat.iVisionRecoveryOfSecond, m_tszResourceStat, 10);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("비전력 회복량/초"));
	}
	else if(m_pItem->tResourceStat.fReducedControlConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedControlConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("절제 소모량 감소"));
	}
	else if(m_pItem->tResourceStat.fReducedEffortConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedEffortConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("공력 소모량 감소"));
	}
	else if(m_pItem->tResourceStat.fReducedHateConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedHateConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("증오 소모량 감소"));
	}
	else if(m_pItem->tResourceStat.fReducedManaConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedManaConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("마나 소모량 감소"));
	}
	else if(m_pItem->tResourceStat.fReducedRageConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedRageConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("분노 소모량 감소"));
	}
	else if(m_pItem->tResourceStat.fReducedVisionConsumption > 0.0f)
	{
		StringCbPrintf(m_tszResourceStat, sizeof(m_tszResourceStat), _T("%g%%"), m_pItem->tResourceStat.fReducedVisionConsumption * 100.0f);
		_tcscpy_s(m_tszResourceStatType, MIN_STR, _T("비전력 소모량 감소"));
	}

	// AdventureStat
	ZeroMemory(m_tszAdventureStat, sizeof(m_tszAdventureStat));
	ZeroMemory(m_tszAdventureStatType, sizeof(m_tszAdventureStatType));
	if(m_pItem->tAdventureStat.fExperience > 0.0f)
	{
		StringCbPrintf(m_tszAdventureStat, sizeof(m_tszAdventureStat), _T("%g%%"), m_pItem->tAdventureStat.fExperience * 100.0f);
		_tcscpy_s(m_tszAdventureStatType, MIN_STR, _T("추가경험치"));
	}
	else if(m_pItem->tAdventureStat.fMagicItemsFound > 0.0f)
	{
		StringCbPrintf(m_tszAdventureStat, sizeof(m_tszAdventureStat), _T("%g%%"), m_pItem->tAdventureStat.fMagicItemsFound * 100.0f);
		_tcscpy_s(m_tszAdventureStatType, MIN_STR, _T("마법아이템 발견"));
	}
	else if(m_pItem->tAdventureStat.fDiscoveryOfGoldCoins > 0.0f)
	{
		StringCbPrintf(m_tszAdventureStat, sizeof(m_tszAdventureStat), _T("%g%%"), m_pItem->tAdventureStat.fDiscoveryOfGoldCoins * 100.0f);
		_tcscpy_s(m_tszAdventureStatType, MIN_STR, _T("금화 발견"));
	}
}

CItemInfoMessage::~CItemInfoMessage()
{
	Release();
}

void CItemInfoMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;

	// TransformCom
	CTransformCom* pTransformCom;

	// ItemPannel
	m_pItemPannelMessage = new CItemPannelMessage(NULL, OBJ_TYPE_STATIC, _T("Message_ItemPannel"));
	m_pLayer->AddObject(m_pItemPannelMessage, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pItemPannelMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize.x = m_pItem->iWidth * 0.0525f + 0.02f;
	pTransformCom->m_vSize.y = m_pItem->iHeight * 0.09216667f + 0.02f;
	pTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f + 0.02f + 1.0f * 0.0525f / 2.0f;
	pTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f - 0.02f - 2.0f * 0.09216667f / 2.0f;
	m_pItemPannelMessage->Initialize();

	// ItemGridMessage
	if(m_pItem->dwItemClass & ITEM_CLASS_MAGIC)
		m_pItemGridMessage = new CItemGridMessage(NULL, OBJ_TYPE_STATIC, _T("Sign_MagicGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
		m_pItemGridMessage = new CItemGridMessage(NULL, OBJ_TYPE_STATIC, _T("Sign_UniqueGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_LEGEND)
		m_pItemGridMessage = new CItemGridMessage(NULL, OBJ_TYPE_STATIC, _T("Sign_LegendGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_SET)
		m_pItemGridMessage = new CItemGridMessage(NULL, OBJ_TYPE_STATIC, _T("Sign_SetGrid"));

	if(m_pItemGridMessage != NULL)
	{
		m_pLayer->AddObject(m_pItemGridMessage, LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pItemGridMessage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = m_pItem->iWidth * 0.0525f + 0.02f;
		pTransformCom->m_vSize.y = m_pItem->iHeight * 0.09216667f + 0.02f;
		pTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f + 0.02f + 1.0f * 0.0525f / 2.0f;
		pTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f - 0.02f - 2.0f * 0.09216667f / 2.0f;
		m_pItemGridMessage->Initialize();
	}

	// ItemIconMessage
	m_pItemIconMessage = new CItemIconMessage(NULL, OBJ_TYPE_STATIC, m_pItem->tszTexKey);
	m_pLayer->AddObject(m_pItemIconMessage, LAYER_TYPE_UI);

	CTransformCom* pIconTransformCom = (CTransformCom*)m_pItemIconMessage->GetComponent(COM_TYPE_TRANSFORM);
	pIconTransformCom->m_vSize.x = m_pItem->iWidth * 0.0525f;
	pIconTransformCom->m_vSize.y = m_pItem->iHeight * 0.09216667f;
	pIconTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f + 0.02f + 1.0f * 0.0525f / 2.0f;
	pIconTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f - 0.02f - 2.0f * 0.09216667f / 2.0f;
	m_pItemIconMessage->Initialize();

	// ItemSockSign
	for(int i = 0; i < m_pItem->iSockNum; ++i)
	{
		if(m_pItemSockSign[i] != NULL)
			continue;

		m_pItemSockSign[i] = new CSockSign(NULL, OBJ_TYPE_STATIC, m_pItem->SockArr[i]);
		m_pLayer->AddObject(m_pItemSockSign[i], LAYER_TYPE_UI);

		// Pos
		CTransformCom* pTransformCom = (CTransformCom*)m_pItemSockSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = pIconTransformCom->m_vPos.x;
		pTransformCom->m_vPos.y = pIconTransformCom->m_vPos.y + pIconTransformCom->m_vSize.y / 6.0f * (m_pItem->iSockNum - 1) - pIconTransformCom->m_vSize.y / 6.0f * i * 2.0f;

		// Size
		pTransformCom->m_vSize = D3DXVECTOR3(0.04f, 0.06f, 0.0f);

		// UpdateCom
		pUpdateCom = (CUpdateCom*)m_pItemSockSign[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFE;

		// RenderCom
		pRenderCom = (CRenderCom*)m_pItemSockSign[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000001;

		m_pItemSockSign[i]->Initialize();
	}

	// Cnt
	int iCnt = 0;
	if(m_pItem->GetStrength() > 0)
		++iCnt;
	if(m_pItem->GetAgility() > 0)
		++iCnt;
	if(m_pItem->GetIntelligence() > 0)
		++iCnt;
	if(m_pItem->GetVitality() > 0)
		++iCnt;

	// StatMark
	if(m_pItem->dwItemClass == 0)
	{
		for(int i = 0; i < iCnt; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + iCnt * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
	else if(m_pItem->dwItemClass & ITEM_CLASS_NORMAL)
	{
		for(int i = 0; i < iCnt; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + iCnt * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
	if(m_pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		for(int i = 0; i < iCnt + 1; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + (iCnt + 1) * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
	if(m_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		for(int i = 0; i < iCnt + 2; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + (iCnt + 2) * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
	if(m_pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		for(int i = 0; i < iCnt + 3; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + (iCnt + 3) * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
	if(m_pItem->dwItemClass & ITEM_CLASS_SET)
	{
		for(int i = 0; i < iCnt + 5; ++i)
		{
			CStatMarkSign* pStatMarkSign = new CStatMarkSign(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pStatMarkSign, LAYER_TYPE_UI);

			pTransformCom = (CTransformCom*)pStatMarkSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.178656f, -0.1655948f + (iCnt + 5) * 0.0267958f - i * 0.056f, 0.0f);

			pStatMarkSign->Initialize();
			m_StatMarkVec.push_back(pStatMarkSign);
		}
	}
}

int CItemInfoMessage::Update()
{
	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;

	CMessageUI::Update();

	return 0;
}

void CItemInfoMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f, 0.0f));

	// Class
	RECT rcText;
	SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 6.0f), long(vPos.x + 120.0f), long(vPos.y + 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, m_tszClass, -1, &rcText, DT_LEFT, m_dwColor);

	// Type
	SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 6.0f), long(vPos.x + 120.0f), long(vPos.y + 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, m_tszType, -1, &rcText, DT_RIGHT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// Value
	SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 22.0f), long(vPos.x + 120.0f), long(vPos.y + 62.0f));
	CFontMgr::GetInstance()->GetBauhaus(40, 20)->DrawText(NULL, m_tszValue, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ValueType
	SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 64.0f), long(vPos.x + 120.0f), long(vPos.y + 78.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, m_tszValueType, -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// Cnt
	int iCnt = 0;
	TCHAR tszTemp[MIN_STR];

	// Strength
	if(m_pItem->GetStrength() > 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %d"), _T("힘"), m_pItem->GetStrength());
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}
	// Agility
	if(m_pItem->GetAgility() > 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %d"), _T("민첩"), m_pItem->GetAgility());
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}
	// Intelligence
	if(m_pItem->GetIntelligence() > 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %d"), _T("지능"), m_pItem->GetIntelligence());
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}
	//Vitality
	if(m_pItem->GetVitality() > 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %d"), _T("활력"), m_pItem->GetVitality());
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}

	// AttackStat
	if(_tcscmp(m_tszAttackStat, _T("")) != 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %s"), m_tszAttackStatType, m_tszAttackStat);
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}

	// DefenseStat
	if(_tcscmp(m_tszDefenseStat, _T("")) != 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %s"), m_tszDefenseStatType, m_tszDefenseStat);
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}

	// LifeStat
	if(_tcscmp(m_tszLifeStat, _T("")) != 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %s"), m_tszLifeStatType, m_tszLifeStat);
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}

	// ResourceStat
	if(_tcscmp(m_tszResourceStat, _T("")) != 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %s"), m_tszResourceStatType, m_tszResourceStat);
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}

	// AdventureStat
	if(_tcscmp(m_tszAdventureStat, _T("")) != 0)
	{
		++iCnt;
		StringCbPrintf(tszTemp, sizeof(tszTemp), _T("%s %s"), m_tszAdventureStatType, m_tszAdventureStat);
		SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszTemp, -1, &rcText, DT_LEFT, m_dwColor);
	}
	
	// Job
	SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 50.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 70.0f + iCnt * 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszJob, -1, &rcText, DT_RIGHT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// Gender
	SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 70.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 90.0f + iCnt * 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszGender, -1, &rcText, DT_RIGHT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// Level
	SetRect(&rcText, long(vPos.x - 100.0f), long(vPos.y + 90.0f + iCnt * 20.0f), long(vPos.x + 120.0f), long(vPos.y + 110.0f + iCnt * 20.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszLevel, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Gem
	if(m_pItem->dwItemType & ITEM_TYPE_GEM)
	{
		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 26.0f), long(vPos.x + 120.0f), long(vPos.y + 38.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("아이템 강화에 사용됩니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("종류"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		SetRect(&rcText, long(vPos.x - 46.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("와 "), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		SetRect(&rcText, long(vPos.x - 30.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("등급"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		SetRect(&rcText, long(vPos.x - 6.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("이 각각 5가지씩"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 62.0f), long(vPos.x + 120.0f), long(vPos.y + 74.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("존재합니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// Material
	else if(m_pItem->dwItemType & ITEM_TYPE_MATERIAL)
	{
		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 26.0f), long(vPos.x + 120.0f), long(vPos.y + 38.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("아이템 제작에 사용됩니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
		if(m_pItem->dwItemID & MATERIAL_ID_IRON)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("일반 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_CRYSTAL)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("마법 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_PATTERNS)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("마법 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_DIAMOND)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("희귀 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_MANA_SOURCE)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("희귀 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_ADAMANTIUM)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("전설 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & MATERIAL_ID_METAL_STAIN)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("전설 아이템 이상"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		SetRect(&rcText, long(vPos.x + 22.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("을 분해하"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 62.0f), long(vPos.x + 120.0f), long(vPos.y + 74.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("여 얻을 수 있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// Quest
	else if(m_pItem->dwItemType & ITEM_TYPE_QUEST)
	{
		SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 26.0f), long(vPos.x + 120.0f), long(vPos.y + 38.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("퀘스트 완료에 사용됩니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if(m_pItem->dwItemID & QUEST_ID_1)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_2)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_3)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("경비대원"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 22.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("이나 "), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetRect(&rcText, long(vPos.x + 6.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("촌장"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			SetRect(&rcText, long(vPos.x + 30.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("에게서"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 62.0f), long(vPos.x + 120.0f), long(vPos.y + 74.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("구할 수 있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & QUEST_ID_4)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_5)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_6)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_7)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("좀비"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 46.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("를 사냥하여 얻을 수"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 62.0f), long(vPos.x + 120.0f), long(vPos.y + 74.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & QUEST_ID_8)
		{
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("좀비"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 46.0f), long(vPos.y + 44.0f), long(vPos.x + 120.0f), long(vPos.y + 56.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("를 사냥하여 얻을 수 있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetRect(&rcText, long(vPos.x - 70.0f), long(vPos.y + 62.0f), long(vPos.x + 120.0f), long(vPos.y + 74.0f));
			CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if(m_pItem->dwItemID & QUEST_ID_9)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_10)
		{
		}
		else if(m_pItem->dwItemID & QUEST_ID_11)
		{
		}
	}

	// 추가 능력치
	SetRect(&rcText, long(vPos.x - 120.0f), long(vPos.y + 90.0f), long(vPos.x + 120.0f), long(vPos.y + 102.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("추가 능력치"), -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CItemInfoMessage::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	// ItemPannelMessage
	if(m_pItemPannelMessage != NULL)
	{
		m_pItemPannelMessage->Destroy();
		m_pItemPannelMessage = NULL;
	}

	// ItemGridMessage
	if(m_pItemGridMessage != NULL)
	{
		m_pItemGridMessage->Destroy();
		m_pItemGridMessage = NULL;
	}

	// ItemIconMessage
	if(m_pItemIconMessage != NULL)
	{
		m_pItemIconMessage->Destroy();
		m_pItemIconMessage = NULL;
	}

	// ItemSockSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pItemSockSign[i] != NULL)
		{
			m_pItemSockSign[i]->Destroy();
			m_pItemSockSign[i] = NULL;
		}
	}

	// StatMarkVec
	for(size_t i = 0; i < m_StatMarkVec.size(); ++i)
	{
		m_StatMarkVec[i]->Destroy();
		m_StatMarkVec[i] = NULL;
	}
	m_StatMarkVec.clear();
}