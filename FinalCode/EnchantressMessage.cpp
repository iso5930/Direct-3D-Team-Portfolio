#include "StdAfx.h"
#include "EnchantressMessage.h"

CEnchantressMessage::CEnchantressMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("¿ä¼ú»ç"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("¾È³çÇì¼õ? ¿ä¼ú»ç °í¿ëÇÏ·Á±¸¼õ?"));

	// Mode
	m_iMode = 0;
}

CEnchantressMessage::~CEnchantressMessage()
{
	Release();
}

void CEnchantressMessage::Initialize()
{
	CQuestMessage::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Enchantress"));
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CEnchantressMessage::Update()
{
	CQuestMessage::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;
	}

	return 0;
}

void CEnchantressMessage::Render()
{
	CQuestMessage::Render();
}

void CEnchantressMessage::Release()
{
}

void CEnchantressMessage::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
		if(pFindObject == NULL)
			return;

		CPlayer* pPlayer = (CPlayer*)pFindObject;
		ZeroMemory(m_tszText, sizeof(m_tszText));
		StringCbPrintf(m_tszText, sizeof(m_tszText), _T("°í¿ëºñ´Â %d °ñµåÀÌ±¸¼õ! ÀÌÄí!"), pPlayer->GetStat()->iLevel * 10000);

		m_iMode = 1;
	}
}

void CEnchantressMessage::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
		if(pFindObject == NULL)
			return;

		CPlayer* pPlayer = (CPlayer*)pFindObject;
		int iGold = CItemMgr::GetInstance()->GetGold();
		if(iGold < pPlayer->GetStat()->iLevel * 10000)
		{
			_tcscpy_s(m_tszText, MAX_STR, _T("µ·ÀÌ ¾ø±¸¼õ! ²¨Áö¶ó±¸¼õ!"));
			m_iMode = 2;
		}
		else
		{
			// Gold
			CItemMgr::GetInstance()->SetGold(iGold - pPlayer->GetStat()->iLevel * 10000);

			// FindFollower
			CObject* pFindFollower = NULL;
			m_pLayer->FindObject(pFindFollower, _T("Follower"), LAYER_TYPE_FOLLOWER);
			if(pFindFollower != NULL)
				pFindFollower->Destroy();

			// FindFollowerEnergy
			CObject* pFindFollowerEnergy = NULL;
			m_pLayer->FindObject(pFindFollowerEnergy, _T("FollowerEnergy"), LAYER_TYPE_UI);
			if(pFindFollowerEnergy != NULL)
				pFindFollowerEnergy->Destroy();

			// DeleteWindow
			if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER) != NULL)
				CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_FOLLOWER);

			// FollowerInfo
			FollowerInfo tFollowerInfo;
			tFollowerInfo.eFollowerType = FOLLOWER_TYPE_ENCHANTRESS;
			tFollowerInfo.stat.iLevel = pPlayer->GetStat()->iLevel;
			tFollowerInfo.stat.iStrength = 1 * pPlayer->GetStat()->iLevel;
			tFollowerInfo.stat.iAgility = 1 * pPlayer->GetStat()->iLevel;
			tFollowerInfo.stat.iIntelligence = 3 * pPlayer->GetStat()->iLevel;
			tFollowerInfo.stat.iVitality = 2 * pPlayer->GetStat()->iLevel;
			tFollowerInfo.stat.iLife = 40 + tFollowerInfo.stat.iVitality * 10;
			tFollowerInfo.stat.iMaxLife = 40;
			tFollowerInfo.stat.iVision = 100;
			tFollowerInfo.stat.iMaxVision = 100;
			tFollowerInfo.stat.iExp = tFollowerInfo.stat.iLevel * tFollowerInfo.stat.iLevel * 100;

			// Follower
			CFollower* pFollower = new CEnchantress(_T("Follower"), OBJ_TYPE_STATIC, pPlayer, &tFollowerInfo);
			m_pLayer->AddObject(pFollower, LAYER_TYPE_FOLLOWER);
			pFollower->Initialize();

			CTransformCom* pTransformComA = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)pFollower->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComB->m_vPos = pTransformComA->m_vPos;

			// FollowerEnergy
			CFollowerEnergy* pFollowerEnergy = new CFollowerEnergy(_T("FollowerEnergy"), OBJ_TYPE_STATIC, pFollower);
			m_pLayer->AddObject(pFollowerEnergy, LAYER_TYPE_UI);
			pFollowerEnergy->Initialize();

			_tcscpy_s(m_tszText, MAX_STR, _T("°í¿ë‰ç±¸¼õ, Á×À¸¸é ´Ù½Ã »ç¾ßµÇ¼õ~"));
			m_iMode = 2;
		}
	}
}

void CEnchantressMessage::Mode2()
{
	if(m_pXButton->IsLUp())
		Destroy();
}