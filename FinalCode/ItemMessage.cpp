#include "StdAfx.h"
#include "ItemMessage.h"

CItemMessage::CItemMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_ItemGrid"))
{
	// Item
	m_pItem = new Item(_pItem);

	// ItemNameMessage
	m_pItemNameMessage = NULL;

	// ItemValueMessage
	m_pItemValueMessage = NULL;

	// ItemInfoMessage
	m_pItemInfoMessage = NULL;
}

CItemMessage::~CItemMessage()
{
	Release();
}

void CItemMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF9;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000006;

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
	if(m_pItem->tAttackStat.fReducedCooldownTime > 0.0f || m_pItem->tAttackStat.fCriticalProbability > 0.0f || m_pItem->tAttackStat.fCriticalDamage > 0.0f)
		++iCnt;
	if(m_pItem->tDefenseStat.fReducedFarDamage > 0.0f || m_pItem->tDefenseStat.fReducedNearDamage > 0.0f || m_pItem->tDefenseStat.iColdResistance > 0 || m_pItem->tDefenseStat.iFlameResistance > 0 || m_pItem->tDefenseStat.iHolyResistance > 0 || m_pItem->tDefenseStat.iLightningResistance > 0 || m_pItem->tDefenseStat.iPhysicalResistance > 0 || m_pItem->tDefenseStat.iPoisonResistance > 0)
		++iCnt;
	if(m_pItem->tLifeStat.iLifeRecoveryOfHit > 0 || m_pItem->tLifeStat.iLifeRecoveryOfSecond > 0 || m_pItem->tLifeStat.fRestoresBonus > 0.0f)
		++iCnt;
	if(m_pItem->tAdventureStat.fDiscoveryOfGoldCoins > 0.0f || m_pItem->tAdventureStat.fExperience > 0.0f || m_pItem->tAdventureStat.fMagicItemsFound > 0.0f)
		++iCnt;
	if(m_pItem->tResourceStat.fReducedControlConsumption > 0.0f || m_pItem->tResourceStat.fReducedEffortConsumption > 0.0f || m_pItem->tResourceStat.fReducedHateConsumption > 0.0f || m_pItem->tResourceStat.fReducedManaConsumption > 0.0f || m_pItem->tResourceStat.fReducedRageConsumption > 0.0f || m_pItem->tResourceStat.fReducedVisionConsumption > 0.0f ||
		m_pItem->tResourceStat.iControlRecoveryOfSecond > 0 || m_pItem->tResourceStat.iEffortRecoveryOfSecond > 0 || m_pItem->tResourceStat.iHateRecoveryOfSecond > 0 || m_pItem->tResourceStat.iManaRecoveryOfSecond > 0 || m_pItem->tResourceStat.iRageRecoveryOfSecond > 0 || m_pItem->tResourceStat.iVisionRecoveryOfSecond > 0)
		++iCnt;

	// Add
	float fAdd = 0.0f;
	if(iCnt > 0)
		fAdd += (iCnt * 0.055f);

	// 0.08( ItemNameMessage )
	// 0.02( 여백 )
	// 0.25 + add( ItemInfoMessage )
	// 0.02( 여백 )
	// 0.06( ItemValueMessage )
	m_pTransformCom->m_vPos.x -= 0.2083f;
	m_pTransformCom->m_vSize.x = 0.4166f;
	m_pTransformCom->m_vSize.y = 0.08f + 0.02f + 0.06f + 0.02f + 0.3f + fAdd;

	// ItemNameMessage
	m_pItemNameMessage = new CItemNameMessage(NULL, OBJ_TYPE_STATIC, m_pItem);
	m_pLayer->AddObject(m_pItemNameMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformComA = (CTransformCom*)m_pItemNameMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformComA->m_vSize = D3DXVECTOR3(0.4166f, 0.08f, 0.0f);
	pTransformComA->m_vPos = D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f - pTransformComA->m_vSize.y / 2.0f, 0.0f);
	m_pItemNameMessage->Initialize();

	// ItemValueMessage
	m_pItemValueMessage = new CItemValueMessage(NULL, OBJ_TYPE_STATIC, m_pItem);
	m_pLayer->AddObject(m_pItemValueMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformComB = (CTransformCom*)m_pItemValueMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformComB->m_vSize = D3DXVECTOR3(0.4166f, 0.06f, 0.0f);
	pTransformComB->m_vPos = D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y - m_pTransformCom->m_vSize.y / 2.0f + pTransformComB->m_vSize.y / 2.0f, 0.0f);
	m_pItemValueMessage->Initialize();

	// ItemInfoMessage
	m_pItemInfoMessage = new CItemInfoMessage(NULL, OBJ_TYPE_STATIC, m_pItem);
	m_pLayer->AddObject(m_pItemInfoMessage, LAYER_TYPE_UI);

	CTransformCom* pTransformComC = (CTransformCom*)m_pItemInfoMessage->GetComponent(COM_TYPE_TRANSFORM);
	pTransformComC->m_vSize = D3DXVECTOR3(0.4166f, 0.3f + fAdd, 0.0f);
	pTransformComC->m_vPos = m_pTransformCom->m_vPos - D3DXVECTOR3(0.0f, pTransformComA->m_vSize.y / 2.0f - pTransformComB->m_vSize.y / 2.0f, 0.0f);
	m_pItemInfoMessage->Initialize();

	// 0.2, 0.2( 기본여백 )
	m_pTransformCom->m_vSize += D3DXVECTOR3(0.02f, 0.04f, 0.0f);
}

int CItemMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF9;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000006;

	return 0;
}

void CItemMessage::Render()
{
	CMessageUI::Render();
}

void CItemMessage::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	// ItemNameMessage
	if(m_pItemNameMessage != NULL)
	{
		m_pItemNameMessage->Destroy();
		m_pItemNameMessage = NULL;
	}

	// ItemValueMessage
	if(m_pItemValueMessage != NULL)
	{
		m_pItemValueMessage->Destroy();
		m_pItemValueMessage = NULL;
	}

	// ItemInfoMessage
	if(m_pItemInfoMessage != NULL)
	{
		m_pItemInfoMessage->Destroy();
		m_pItemInfoMessage = NULL;
	}
}