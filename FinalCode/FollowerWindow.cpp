#include "StdAfx.h"
#include "FollowerWindow.h"

CFollowerWindow::CFollowerWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, NULL)
{
	// ID
	m_dwBothSide = 0;
	m_dwLeftSide = 0;
	m_dwRightSide = 0;
	m_dwAmulet = 0;
	m_dwRing = 0;

	// Mouse
	m_pMouse = NULL;

	// Player
	m_pPlayer = NULL;

	// Follower
	m_pFollower = NULL;

	// EquipSign
	ZeroMemory(m_EquipSign, sizeof(m_EquipSign));

	// EquipMessage
	ZeroMemory(m_EquipMessage, sizeof(m_EquipMessage));

	// MainWeaponBorderSign
	ZeroMemory(m_pMainWeaponBorderSign, sizeof(m_pMainWeaponBorderSign));

	// SubWeaponBorderSign
	ZeroMemory(m_pSubWeaponBorderSign, sizeof(m_pSubWeaponBorderSign));

	// AmuletBorderSign
	ZeroMemory(m_pAmuletBorderSign, sizeof(m_pAmuletBorderSign));

	// LeftRingBorderSign
	ZeroMemory(m_pLeftRingBorderSign, sizeof(m_pLeftRingBorderSign));

	// RightRingBorderSign
	ZeroMemory(m_pRightRingBorderSign, sizeof(m_pRightRingBorderSign));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CFollowerWindow::~CFollowerWindow()
{
	Release();
}

void CFollowerWindow::Initialize()
{
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));

	CWindowUI::Initialize();

	// Disable PlayerEnergy
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("PlayerEnergy"), LAYER_TYPE_UI);
	if(pFindObject != NULL)
	{
		CPlayerEnergy* pFollowerEnergy = (CPlayerEnergy*)pFindObject;
		pFollowerEnergy->Disable();
	}

	// Disable FollowerEnergy
	pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("FollowerEnergy"), LAYER_TYPE_UI);
	if(pFindObject != NULL)
	{
		CFollowerEnergy* pFollowerEnergy = (CFollowerEnergy*)pFindObject;
		pFollowerEnergy->Disable();
	}

	// Find Follower
	pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Follower"), LAYER_TYPE_FOLLOWER);
	if(pFindObject == NULL)
		return;

	// Follower
	CFollower* pFollower = (CFollower*)pFindObject;

	if(pFollower->GetFollowerInfo()->eFollowerType == FOLLOWER_TYPE_ENCHANTRESS)
	{
		m_dwBothSide = 0;
		m_dwLeftSide = WEAPON_ID_STAFF | WEAPON_ID_SWORD | WEAPON_ID_SPEAR | WEAPON_ID_AXE | WEAPON_ID_MACE;
		m_dwRightSide = 0;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwRing = RING_ID_RING;

		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_EnchantressInven"));
	}

	// TransformCom
	CTransformCom* pTransformCom;

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.446f, 0.977f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);

	// TexKey
	TCHAR tszTexKey[3][MIN_STR];
	_tcscpy_s(tszTexKey[0], MIN_STR, _T("Sign_WhiteBorder"));
	_tcscpy_s(tszTexKey[1], MIN_STR, _T("Sign_YellowBorder"));
	_tcscpy_s(tszTexKey[2], MIN_STR, _T("Sign_RedBorder"));

	// TextKey
	TCHAR tszTextKey[5][MIN_STR];
	_tcscpy_s(tszTextKey[0], MIN_STR, _T("한손 무기"));
	_tcscpy_s(tszTextKey[1], MIN_STR, _T("보조 장비"));
	_tcscpy_s(tszTextKey[2], MIN_STR, _T("목"));
	_tcscpy_s(tszTextKey[3], MIN_STR, _T("손가락"));
	_tcscpy_s(tszTextKey[4], MIN_STR, _T("손가락"));

	// EquipMessage
	for(int i = 0; i < 5; ++i)
	{
		m_EquipMessage[i] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Equip"), tszTextKey[i]);
		m_pLayer->AddObject(m_EquipMessage[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_EquipMessage[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		m_EquipMessage[i]->Initialize();
	}

	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pMainWeaponBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pMainWeaponBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.693997f, 0.524006f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		m_pMainWeaponBorderSign[i]->Initialize();
	}

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pSubWeaponBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pSubWeaponBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.524999f, 0.524006f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		m_pSubWeaponBorderSign[i]->Initialize();
	}

	// AmuletBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pAmuletBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pAmuletBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pAmuletBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.607998f, 0.571005f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
		m_pAmuletBorderSign[i]->Initialize();
	}

	// LeftRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pLeftRingBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pLeftRingBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.632998f, 0.475006f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		m_pLeftRingBorderSign[i]->Initialize();
	}

	// RightRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pRightRingBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pRightRingBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pRightRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.585998f, 0.475006f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		m_pRightRingBorderSign[i]->Initialize();
	}

	// Renew
	Renew();
}

int CFollowerWindow::Update()
{
	// Mouse
	CObject* pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Mouse"), LAYER_TYPE_MOUSE);
	m_pMouse = (CMouse*)pFind;

	// Player
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Player"), LAYER_TYPE_PLAYER);
	m_pPlayer = (CPlayer*)pFind;

	// Follower
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Follower"), LAYER_TYPE_FOLLOWER);
	m_pFollower = (CFollower*)pFind;

	// TransformCom
	CTransformCom* pTransformCom;

	// EquipSign
	for(int i = 0; i < 5; ++ i)
	{
		if(m_EquipSign[i] != NULL)
		{
			if(m_EquipSign[i]->IsOver())
				m_EquipSign[i]->EnableItemMessage();
			else
				m_EquipSign[i]->DisableItemMessage();
		}
	}

	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// AmuletBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pAmuletBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// LeftRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// RightRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pRightRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-1.0f, -1.0f), &D3DXVECTOR2(-0.365f, 1.0f)))
	{
		UpdateIn();

		switch(m_pMouse->GetPickType())
		{
		case -1:
			UpdateNonePick();
			UpdateNonePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, 0.3655065f), &D3DXVECTOR2(-0.4689975f, 0.7105055f)))
			{
				UpdateInEquip();
				UpdateNonePickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.35148845f), &D3DXVECTOR2(-0.4689975f, 0.33934155f)))
			{
				UpdateInSkill();
				UpdateNonePickInSkill();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.617488f), &D3DXVECTOR2(-0.4689975f, -0.354488f)))
			{
				UpdateInStat();
				UpdateNonePickInStat();
			}
			break;

		case 0:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickIn();
			UpdateInventoryPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, 0.3655065f), &D3DXVECTOR2(-0.4689975f, 0.7105055f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateInventoryPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.35148845f), &D3DXVECTOR2(-0.4689975f, 0.33934155f)))
			{
				UpdateInSkill();
				UpdatePickInSkill();
				UpdateInventoryPickInSkill();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.617488f), &D3DXVECTOR2(-0.4689975f, -0.354488f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateInventoryPickInStat();
			}
			break;

		case 1:
			UpdatePick();
			UpdateEquipmentPick();
			UpdatePickIn();
			UpdateEquipmentPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, 0.3655065f), &D3DXVECTOR2(-0.4689975f, 0.7105055f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateEquipmentPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.35148845f), &D3DXVECTOR2(-0.4689975f, 0.33934155f)))
			{
				UpdateInSkill();
				UpdatePickInSkill();
				UpdateEquipmentPickInSkill();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.617488f), &D3DXVECTOR2(-0.4689975f, -0.354488f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateEquipmentPickInStat();
			}
			break;

		case 5:
			UpdatePick();
			UpdateFollowerEquipmentPick();
			UpdatePickIn();
			UpdateFollowerEquipmentPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, 0.3655065f), &D3DXVECTOR2(-0.4689975f, 0.7105055f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateFollowerEquipmentPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.35148845f), &D3DXVECTOR2(-0.4689975f, 0.33934155f)))
			{
				UpdateInSkill();
				UpdatePickInSkill();
				UpdateFollowerEquipmentPickInSkill();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.9849945f, -0.617488f), &D3DXVECTOR2(-0.4689975f, -0.354488f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateFollowerEquipmentPickInStat();
			}
			break;
		}
	}
	else
	{
		UpdateOut();

		switch(m_pMouse->GetPickType())
		{
		case -1:
			UpdateNonePick();
			UpdateNonePickOut();
			break;

		case 0:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickOut();
			UpdateInventoryPickOut();
			break;

		case 1:
			UpdatePick();
			UpdateEquipmentPick();
			UpdatePickOut();
			UpdateEquipmentPickOut();
			break;

		case 5:
			UpdatePick();
			UpdateFollowerEquipmentPick();
			UpdatePickOut();
			UpdateFollowerEquipmentPickOut();
			break;
		}
	}

	CWindowUI::Update();

	return 0;
}

void CFollowerWindow::Render()
{
	CWindowUI::Render();

	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Follower"), LAYER_TYPE_FOLLOWER);
	if(pFindObject == NULL)
		return;

	// Follower
	CFollower* pFollower = (CFollower*)pFindObject;

	// Variable
	TCHAR tszText[MIN_STR];
	RECT rcText;

	// 힘
	SetRect(&rcText, 0, 503, 165, 515);
	_itot_s(pFollower->GetStrength(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 민첩
	SetRect(&rcText, 0, 521, 165, 533);
	_itot_s(pFollower->GetAgility(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 지능
	SetRect(&rcText, 0, 539, 165, 551);
	_itot_s(pFollower->GetIntelligence(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	// 활력
	SetRect(&rcText, 0, 557, 165, 569);
	_itot_s(pFollower->GetVitality(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 공격력
	SetRect(&rcText, 160, 503, 325, 515);
	_itot_s(pFollower->TotalStat1(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 강인함
	SetRect(&rcText, 160, 521, 325, 533);
	_itot_s(pFollower->TotalStat2(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 회복력
	SetRect(&rcText, 160, 539, 325, 551);
	_itot_s(pFollower->TotalStat3(), tszText, 10);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CFollowerWindow::Release()
{
	// Enable PlayerEnergy
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("PlayerEnergy"), LAYER_TYPE_UI);
	if(pFindObject != NULL)
	{
		CPlayerEnergy* pFollowerEnergy = (CPlayerEnergy*)pFindObject;
		pFollowerEnergy->Enable();
	}

	// Enable FollowerEnergy
	pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("FollowerEnergy"), LAYER_TYPE_UI);
	if(pFindObject != NULL)
	{
		CFollowerEnergy* pFollowerEnergy = (CFollowerEnergy*)pFindObject;
		pFollowerEnergy->Enable();
	}

	// EquipSign
	for(int i = 0; i < 5; ++i)
	{
		if(m_EquipSign[i] != NULL)
		{
			m_EquipSign[i]->Destroy();
			m_EquipSign[i] = NULL;
		}
	}

	// EquipMessage
	for(int i = 0; i < 5; ++i)
	{
		if(m_EquipMessage[i] != NULL)
		{
			m_EquipMessage[i]->Destroy();
			m_EquipMessage[i] = NULL;
		}
	}

	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pMainWeaponBorderSign[i] != NULL)
		{
			m_pMainWeaponBorderSign[i]->Destroy();
			m_pMainWeaponBorderSign[i] = NULL;
		}
	}

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pSubWeaponBorderSign[i] != NULL)
		{
			m_pSubWeaponBorderSign[i]->Destroy();
			m_pSubWeaponBorderSign[i] = NULL;
		}
	}

	// AmuletBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pAmuletBorderSign[i] != NULL)
		{
			m_pAmuletBorderSign[i]->Destroy();
			m_pAmuletBorderSign[i] = NULL;
		}
	}

	// LeftRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pLeftRingBorderSign[i] != NULL)
		{
			m_pLeftRingBorderSign[i]->Destroy();
			m_pLeftRingBorderSign[i] = NULL;
		}
	}

	// RightRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pRightRingBorderSign[i] != NULL)
		{
			m_pRightRingBorderSign[i]->Destroy();
			m_pRightRingBorderSign[i] = NULL;
		}
	}
}

void CFollowerWindow::Renew()
{
	// EquipSign Clear
	for(size_t i = 0; i < 5; ++i)
	{
		if(m_EquipSign[i] != NULL)
		{
			m_EquipSign[i]->Destroy();
			m_EquipSign[i] = NULL;
		}
	}

	// EquipSign
	for(int i = 0; i < 5; ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(i);
		if(pItem == NULL)
			continue;

		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pItem);
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		CTransformCom* pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);

		switch(i)
		{
		case 0:
			pTransformCom->m_vPos = D3DXVECTOR3(-0.693997f, 0.524006f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			break;
		case 1:
			pTransformCom->m_vPos = D3DXVECTOR3(-0.524999f, 0.524006f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			break;
		case 2:
			pTransformCom->m_vPos = D3DXVECTOR3(-0.607998f, 0.571005f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			break;
		case 3:
			pTransformCom->m_vPos = D3DXVECTOR3(-0.632998f, 0.475006f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			break;
		case 4:
			pTransformCom->m_vPos = D3DXVECTOR3(-0.585998f, 0.475006f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			break;
		}

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableSockSign();
		if(pItemSign->IsOver()) { pItemSign->EnableItemMessage(); }

		m_EquipSign[i] = pItemSign;
	}
}

////////////////////////////////////////////////////////////////////////// Pick
void CFollowerWindow::UpdateNonePick()
{
}
void CFollowerWindow::UpdatePick()
{
	// Item
	Item* pItem = m_pMouse->GetItem();

	// MainWeapon & SubWeapon
	if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		if((pItem->dwItemID & m_dwBothSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
	}
	// MainWeapon
	else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
	{
		if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
	}
	// SubWeapon
	else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
	{
		if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
	}
	// Amulet
	else if(pItem->dwItemType & ITEM_TYPE_AMULET)
	{
		if((pItem->dwItemID & m_dwAmulet) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
		}
	}
	// Ring
	else if(pItem->dwItemType & ITEM_TYPE_RING)
	{
		if((pItem->dwItemID & m_dwRing) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
	}
}
void CFollowerWindow::UpdateInventoryPick()
{
}
void CFollowerWindow::UpdateEquipmentPick()
{
}
void CFollowerWindow::UpdateFollowerEquipmentPick()
{
}

////////////////////////////////////////////////////////////////////////// In
void CFollowerWindow::UpdateIn()
{
}
void CFollowerWindow::UpdateNonePickIn()
{
	if(m_ButtonVec[0]->IsLUp())
		Destroy();
}
void CFollowerWindow::UpdatePickIn()
{
}
void CFollowerWindow::UpdateInventoryPickIn()
{
}
void CFollowerWindow::UpdateEquipmentPickIn()
{
}
void CFollowerWindow::UpdateFollowerEquipmentPickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CFollowerWindow::UpdateOut()
{
}
void CFollowerWindow::UpdateNonePickOut()
{
	// Find InvenWindow
	CObject* pFindObject = CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);
	if(pFindObject == NULL)
		return;

	// InvenWindow
	CInvenWindow* pInvenWindow = (CInvenWindow*)pFindObject;

	// OverItemInInven
	if(pInvenWindow->GetOverItemInInven() != NULL)
	{
		// Item
		Item* pItem = pInvenWindow->GetOverItemInInven();

		// MainWeapon & SubWeapon
		if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
		{
			if((pItem->dwItemID & m_dwBothSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// MainWeapon
		else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
		{
			if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// SubWeapon
		else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
		{
			if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// Amulet
		else if(pItem->dwItemType & ITEM_TYPE_AMULET)
		{
			if((pItem->dwItemID & m_dwAmulet) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			}
		}
		// Ring
		else if(pItem->dwItemType & ITEM_TYPE_RING)
		{
			if((pItem->dwItemID & m_dwRing) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
				pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
				pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}
		}
	}
	else if(pInvenWindow->GetOverItemInEquip() != NULL)
	{
		// Item
		Item* pItem = pInvenWindow->GetOverItemInEquip();

		// MainWeapon & SubWeapon
		if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
		{
			if((pItem->dwItemID & m_dwBothSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
				pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// MainWeapon
		else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
		{
			if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// SubWeapon
		else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
		{
			if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
		}
		// Amulet
		else if(pItem->dwItemType & ITEM_TYPE_AMULET)
		{
			if((pItem->dwItemID & m_dwAmulet) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			}
		}
		// Ring
		else if(pItem->dwItemType & ITEM_TYPE_RING)
		{
			if((pItem->dwItemID & m_dwRing) && pItem->iLevel <= m_pFollower->GetFollowerInfo()->stat.iLevel)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
				pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}
			else
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
				pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}
		}
	}
}
void CFollowerWindow::UpdatePickOut()
{
}
void CFollowerWindow::UpdateInventoryPickOut()
{
}
void CFollowerWindow::UpdateEquipmentPickOut()
{
}
void CFollowerWindow::UpdateFollowerEquipmentPickOut()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		D3DXVECTOR3 vPos;
		ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

		if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.4389982f, -1.0f), &D3DXVECTOR2(0.4529938f, 1.0f)))
		{
			CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, CItemMgr::GetInstance()->GetItemInFollowerEquip(m_pMouse->GetSelect()));
			m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

			CTransformCom* pTransformComA = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pPlayer->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComA->m_vPos = pTransformComB->m_vPos;

			pDropItem->Initialize();

			CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
			CItemMgr::GetInstance()->RemoveItemInFollowerEquip(m_pMouse->GetSelect());
			CItemMgr::GetInstance()->CommitFollowerEquip();
			m_pMouse->Drop();
			m_pFollower->Renew();
			Renew();
		}
	}
}

////////////////////////////////////////////////////////////////////////// InEquip
void CFollowerWindow::UpdateInEquip()
{
}
void CFollowerWindow::UpdateNonePickInEquip()
{
	for(int i = 0; i < 5; ++i)
	{
		if(m_EquipSign[i] == NULL)
			continue;

		if(m_EquipSign[i]->IsOver())
		{
			if(i == 0)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if(i == 1)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
			}
			else if(i == 2)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
			}
			else if(i == 3)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}
			else if(i == 4)
			{
				CTransformCom* pTransformCom = (CTransformCom*)m_pRightRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
			}

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
			{
				if(CItemMgr::GetInstance()->MoveFollowerEquipToInven(i, -1, -1))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitFollowerEquip();
					m_pMouse->Drop();
					CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackFollowerEquip();
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(5, i, m_EquipSign[i]->GetItem());

			break;
		}

		if(m_EquipSign[i] != NULL && m_EquipSign[i]->IsOver() && CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			m_pMouse->Pick(5, i, m_EquipSign[i]->GetItem());
			break;
		}
	}
}
void CFollowerWindow::UpdatePickInEquip()
{
	// Item
	Item* pItem = m_pMouse->GetItem();
	if(pItem == NULL)
		return;

	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.724997f, 0.413006f), &D3DXVECTOR2(-0.662997f, 0.635006f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false || (pItem->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false || pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInFollowerEquip(0) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.555999f, 0.413006f), &D3DXVECTOR2(-0.493999f, 0.635006f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Item* pItem = m_pMouse->GetItem();
		if((pItem->dwItemType & ITEM_TYPE_SUB_WEAPON) == false || (pItem->dwItemID & (m_dwBothSide | m_dwRightSide)) == false || pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInFollowerEquip(1) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.062f, 0.222f, 0.0f);
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.634998f, 0.525505f), &D3DXVECTOR2(-0.580998f, 0.616505f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_AMULET) == false || (pItem->dwItemID & m_dwAmulet) == false || pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInFollowerEquip(2) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pAmuletBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.054f, 0.091f, 0.0f);
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.651998f, 0.442006f), &D3DXVECTOR2(-0.613998f, 0.508006f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_RING) == false || (pItem->dwItemID & m_dwRing) == false || pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInFollowerEquip(3) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.604998f, 0.442006f), &D3DXVECTOR2(-0.566998f, 0.508006f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_RING) == false || (pItem->dwItemID & m_dwRing) == false || pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInFollowerEquip(4) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.038f, 0.066f, 0.0f);
		}
	}
}
void CFollowerWindow::UpdateInventoryPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.724997f, 0.413006f), &D3DXVECTOR2(-0.662997f, 0.635006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 0))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(0) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToFollowerEquip(m_pMouse->GetSelect(), 0);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToFollowerEquip(m_pMouse->GetSelect(), 0);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.555999f, 0.413006f), &D3DXVECTOR2(-0.493999f, 0.635006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 1))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_SUB_WEAPON) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & (m_dwBothSide | m_dwRightSide)) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(1) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToFollowerEquip(m_pMouse->GetSelect(), 1);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToFollowerEquip(m_pMouse->GetSelect(), 1);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.634998f, 0.525505f), &D3DXVECTOR2(-0.580998f, 0.616505f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 2))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_AMULET) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwAmulet) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(2) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToFollowerEquip(m_pMouse->GetSelect(), 2);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToFollowerEquip(m_pMouse->GetSelect(), 2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.651998f, 0.442006f), &D3DXVECTOR2(-0.613998f, 0.508006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 3))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(3) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToFollowerEquip(m_pMouse->GetSelect(), 3);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToFollowerEquip(m_pMouse->GetSelect(), 3);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.604998f, 0.442006f), &D3DXVECTOR2(-0.566998f, 0.508006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 4))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(4) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToFollowerEquip(m_pMouse->GetSelect(), 4);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToFollowerEquip(m_pMouse->GetSelect(), 4);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitInven();
		CItemMgr::GetInstance()->CommitFollowerEquip();
		m_pMouse->Drop();
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
		m_pFollower->Renew();
		Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackFollowerEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
	}
	else if(iSuccess == 2)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackFollowerEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
	}
}
void CFollowerWindow::UpdateEquipmentPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.724997f, 0.413006f), &D3DXVECTOR2(-0.662997f, 0.635006f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(0) != NULL)
				{
					// FollowerItem
					Item* pFollowerItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(0);

					// InvenWindow
					CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

					// ID
					DWORD dwID = pInvenWindow->GetID(0) | pInvenWindow->GetID(1);

					if((pFollowerItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
					else if(pFollowerItem->iLevel > m_pPlayer->GetStat()->iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else if(pFollowerItem->iGender != 2 && pFollowerItem->iGender != m_pPlayer->GetInfo()->iGender)
						CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapEquipToFollowerEquip(m_pMouse->GetSelect(), 0);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveEquipToFollowerEquip(m_pMouse->GetSelect(), 0);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.555999f, 0.413006f), &D3DXVECTOR2(-0.493999f, 0.635006f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_SUB_WEAPON) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & (m_dwBothSide | m_dwRightSide)) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(1) != NULL)
				{
					// FollowerItem
					Item* pFollowerItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(1);

					// InvenWindow
					CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

					// ID
					DWORD dwID = pInvenWindow->GetID(0) | pInvenWindow->GetID(2);

					if((pFollowerItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
					else if(pFollowerItem->iLevel > m_pPlayer->GetStat()->iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else if(pFollowerItem->iGender != 2 && pFollowerItem->iGender != m_pPlayer->GetInfo()->iGender)
						CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapEquipToFollowerEquip(m_pMouse->GetSelect(), 1);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveEquipToFollowerEquip(m_pMouse->GetSelect(), 1);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.634998f, 0.525505f), &D3DXVECTOR2(-0.580998f, 0.616505f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_AMULET) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwAmulet) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(2) != NULL)
				{
					// FollowerItem
					Item* pFollowerItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(2);

					// InvenWindow
					CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

					// ID
					DWORD dwID = pInvenWindow->GetID(5);

					if((pFollowerItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
					else if(pFollowerItem->iLevel > m_pPlayer->GetStat()->iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else if(pFollowerItem->iGender != 2 && pFollowerItem->iGender != m_pPlayer->GetInfo()->iGender)
						CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapEquipToFollowerEquip(m_pMouse->GetSelect(), 2);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveEquipToFollowerEquip(m_pMouse->GetSelect(), 2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.651998f, 0.442006f), &D3DXVECTOR2(-0.613998f, 0.508006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 3))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(3) != NULL)
				{
					// FollowerItem
					Item* pFollowerItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(3);

					// InvenWindow
					CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

					// ID
					DWORD dwID = pInvenWindow->GetID(9);

					if((pFollowerItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
					else if(pFollowerItem->iLevel > m_pPlayer->GetStat()->iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else if(pFollowerItem->iGender != 2 && pFollowerItem->iGender != m_pPlayer->GetInfo()->iGender)
						CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapEquipToFollowerEquip(m_pMouse->GetSelect(), 3);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveEquipToFollowerEquip(m_pMouse->GetSelect(), 3);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.604998f, 0.442006f), &D3DXVECTOR2(-0.566998f, 0.508006f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToFollowerEquip(m_pMouse->GetSelect(), 4))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInFollowerEquip(4) != NULL)
				{
					// FollowerItem
					Item* pFollowerItem = CItemMgr::GetInstance()->GetItemInFollowerEquip(4);

					// InvenWindow
					CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

					// ID
					DWORD dwID = pInvenWindow->GetID(9);

					if((pFollowerItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
					else if(pFollowerItem->iLevel > m_pPlayer->GetStat()->iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else if(pFollowerItem->iGender != 2 && pFollowerItem->iGender != m_pPlayer->GetInfo()->iGender)
						CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapEquipToFollowerEquip(m_pMouse->GetSelect(), 4);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveEquipToFollowerEquip(m_pMouse->GetSelect(), 4);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitInven();
		CItemMgr::GetInstance()->CommitFollowerEquip();
		m_pMouse->Drop();
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
		Renew();
		m_pPlayer->Renew();
		m_pFollower->Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackFollowerEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
	}
}
void CFollowerWindow::UpdateFollowerEquipmentPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.724997f, 0.413006f), &D3DXVECTOR2(-0.662997f, 0.635006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetSelect() == 0)
				m_pMouse->Drop();
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.555999f, 0.413006f), &D3DXVECTOR2(-0.493999f, 0.635006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetSelect() == 1)
				m_pMouse->Drop();
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.634998f, 0.525505f), &D3DXVECTOR2(-0.580998f, 0.616505f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetSelect() == 2)
				m_pMouse->Drop();
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.651998f, 0.442006f), &D3DXVECTOR2(-0.613998f, 0.508006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetSelect() == 4)
			{
				CItemMgr::GetInstance()->SwapInFollowerEquip(3, 4);
				CItemMgr::GetInstance()->CommitFollowerEquip();
				m_pMouse->Drop();
				Renew();
			}
			else if(m_pMouse->GetSelect() == 3)
				m_pMouse->Drop();
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.604998f, 0.442006f), &D3DXVECTOR2(-0.566998f, 0.508006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetSelect() == 3)
			{
				CItemMgr::GetInstance()->SwapInFollowerEquip(3, 4);
				CItemMgr::GetInstance()->CommitFollowerEquip();
				m_pMouse->Drop();
				Renew();
			}	
			else if(m_pMouse->GetSelect() == 4)
				m_pMouse->Drop();
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
	}
}

////////////////////////////////////////////////////////////////////////// InSkill
void CFollowerWindow::UpdateInSkill()
{
}
void CFollowerWindow::UpdateNonePickInSkill()
{
}
void CFollowerWindow::UpdatePickInSkill()
{
}
void CFollowerWindow::UpdateInventoryPickInSkill()
{
}
void CFollowerWindow::UpdateEquipmentPickInSkill()
{
}
void CFollowerWindow::UpdateFollowerEquipmentPickInSkill()
{
}

////////////////////////////////////////////////////////////////////////// InStat
void CFollowerWindow::UpdateInStat()
{
}
void CFollowerWindow::UpdateNonePickInStat()
{
}
void CFollowerWindow::UpdatePickInStat()
{
}
void CFollowerWindow::UpdateInventoryPickInStat()
{
}
void CFollowerWindow::UpdateEquipmentPickInStat()
{
}
void CFollowerWindow::UpdateFollowerEquipmentPickInStat()
{
}

////////////////////////////////////////////////////////////////////////// Share
Item* CFollowerWindow::GetOverItemInFollowerEquip()
{
	for(int i = 0; i < 5; ++i)
	{
		if(m_EquipSign[i] != NULL && m_EquipSign[i]->IsOver())
			return m_EquipSign[i]->GetItem();
	}

	return NULL;
}

DWORD CFollowerWindow::GetID(int _iIndex)
{
	// ID
	if(_iIndex == 0)
		return m_dwBothSide;
	else if(_iIndex == 1)
		return m_dwLeftSide;
	else if(_iIndex == 2)
		return m_dwRightSide;
	else if(_iIndex == 3)
		return m_dwAmulet;
	else if(_iIndex == 4)
		return m_dwRing;

	return 0;
}