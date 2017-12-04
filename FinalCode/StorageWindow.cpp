#include "StdAfx.h"
#include "StorageWindow.h"

CStorageWindow::CStorageWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Storage"))
{
	Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());
	if(pAccount->info.iJob == 0)
	{
		// ID
		m_dwBothSide = WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_MIGHTY1H;
		m_dwLeftSide = WEAPON_ID_POLEARM | WEAPON_ID_MIGHTY2H | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
		m_dwRightSide = WEAPON_ID_SHIELD;
		m_dwShoulders = SHOULDERS_ID_BARBARIAN;
		m_dwHelms = HELMS_ID_BARBARIAN;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwGloves = GLOVES_ID_BARBARIAN;
		m_dwChestArmor = CHESTARMOR_ID_BARBARIAN;
		m_dwBracers = BRACERS_ID_BARBARIAN;
		m_dwRing = RING_ID_RING;
		m_dwBelt = BELT_ID_BARBARIAN;
		m_dwPants = PANTS_ID_BARBARIAN;
		m_dwBoots = BOOTS_ID_BARBARIAN;
	}
	else if(pAccount->info.iJob == 1)
	{
		// ID
		m_dwBothSide = WEAPON_ID_HANDXBOW;
		m_dwLeftSide = WEAPON_ID_BOW | WEAPON_ID_AXE | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_CROSSBOW;
		m_dwRightSide = WEAPON_ID_QUIVER | WEAPON_ID_SHIELD;
		m_dwShoulders = SHOULDERS_ID_DEMONHUNTER;
		m_dwHelms = HELMS_ID_DEMONHUNTER;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwGloves = GLOVES_ID_DEMONHUNTER;
		m_dwChestArmor = CHESTARMOR_ID_DEMONHUNTER;
		m_dwBracers = BRACERS_ID_DEMONHUNTER;
		m_dwRing = RING_ID_RING;
		m_dwBelt = BELT_ID_DEMONHUNTER;
		m_dwPants = PANTS_ID_DEMONHUNTER;
		m_dwBoots = BOOTS_ID_DEMONHUNTER;
	}
	else if(pAccount->info.iJob == 2)
	{
		// ID
		m_dwBothSide = WEAPON_ID_AXE | WEAPON_ID_FIST | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD;
		m_dwLeftSide = WEAPON_ID_POLEARM | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD;
		m_dwRightSide = WEAPON_ID_SHIELD;
		m_dwShoulders = SHOULDERS_ID_MONK;
		m_dwHelms = HELMS_ID_MONK;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwGloves = GLOVES_ID_MONK;
		m_dwChestArmor = CHESTARMOR_ID_MONK;
		m_dwBracers = BRACERS_ID_MONK;
		m_dwRing = RING_ID_RING;
		m_dwBelt = BELT_ID_MONK;
		m_dwPants = PANTS_ID_MONK;
		m_dwBoots = BOOTS_ID_MONK;
	}
	else if(pAccount->info.iJob == 3)
	{
		// ID
		m_dwBothSide = 0;
		m_dwLeftSide = WEAPON_ID_AXE | WEAPON_ID_CEREMONIAL_DAGGER | WEAPON_ID_MACE | WEAPON_ID_SPEAR | WEAPON_ID_SWORD | WEAPON_ID_BOW | WEAPON_ID_POLEARM | WEAPON_ID_STAFF | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_CROSSBOW;
		m_dwRightSide = WEAPON_ID_SHIELD | WEAPON_ID_MOJO;
		m_dwShoulders = SHOULDERS_ID_WITCHDOCTOR;
		m_dwHelms = HELMS_ID_WITCHDOCTOR;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwGloves = GLOVES_ID_WITCHDOCTOR;
		m_dwChestArmor = CHESTARMOR_ID_WITCHDOCTOR;
		m_dwBracers = BRACERS_ID_WITCHDOCTOR;
		m_dwRing = RING_ID_RING;
		m_dwBelt = BELT_ID_WITCHDOCTOR;
		m_dwPants = PANTS_ID_WITCHDOCTOR;
		m_dwBoots = BOOTS_ID_WITCHDOCTOR;
	}
	else if(pAccount->info.iJob == 4)
	{
		// ID
		m_dwBothSide = 0;
		m_dwLeftSide = WEAPON_ID_AXE | WEAPON_ID_BOW | WEAPON_ID_MACE | WEAPON_ID_POLEARM | WEAPON_ID_SPEAR | WEAPON_ID_STAFF | WEAPON_ID_SWORD | WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD | WEAPON_ID_WAND | WEAPON_ID_CROSSBOW;
		m_dwRightSide = WEAPON_ID_SHIELD | WEAPON_ID_ORB;
		m_dwShoulders = SHOULDERS_ID_WIZARD;
		m_dwHelms = HELMS_ID_WIZARD;
		m_dwAmulet = AMULET_ID_AMULET;
		m_dwGloves = GLOVES_ID_WIZARD;
		m_dwChestArmor = CHESTARMOR_ID_WIZARD;
		m_dwBracers = BRACERS_ID_WIZARD;
		m_dwRing = RING_ID_RING;
		m_dwBelt = BELT_ID_WIZARD;
		m_dwPants = PANTS_ID_WIZARD;
		m_dwBoots = BOOTS_ID_WIZARD;
	}

	// Page
	m_iPage = 0;

	// Mouse
	m_pMouse = NULL;

	// Player
	m_pPlayer = NULL;

	// StorageButton
	ZeroMemory(m_pStorageButton, sizeof(m_pStorageButton));

	// BorderSign
	ZeroMemory(m_pBorderSign, sizeof(m_pBorderSign));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CStorageWindow::~CStorageWindow()
{
	Release();
}

void CStorageWindow::Initialize()
{
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

	// Storage0Button
	m_pStorageButton[0] = new CStorageButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Storage0"), _T("Button_Over_Storage0"), _T("Button_Down_Storage0"));
	m_pLayer->AddObject(m_pStorageButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStorageButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.532f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStorageButton[0]->SetState(UI_L_DOWN);
	m_pStorageButton[0]->Initialize();

	// Storage1Button
	m_pStorageButton[1] = new CStorageButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Storage1"), _T("Button_Over_Storage1"), _T("Button_Down_Storage1"));
	m_pLayer->AddObject(m_pStorageButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStorageButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.332f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStorageButton[1]->Initialize();

	// Storage2Button
	m_pStorageButton[2] = new CStorageButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Storage2"), _T("Button_Over_Storage2"), _T("Button_Down_Storage2"));
	m_pLayer->AddObject(m_pStorageButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStorageButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.132f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStorageButton[2]->Initialize();

	// Storage3Button
	m_pStorageButton[3] = new CStorageButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Storage3"), _T("Button_Over_Storage3"), _T("Button_Down_Storage3"));
	m_pLayer->AddObject(m_pStorageButton[3], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStorageButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, -0.068f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStorageButton[3]->Initialize();

	// Storage4Button
	m_pStorageButton[4] = new CStorageButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Storage4"), _T("Button_Over_Storage4"), _T("Button_Down_Storage4"));
	m_pLayer->AddObject(m_pStorageButton[4], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStorageButton[4]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, -0.268f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStorageButton[4]->Initialize();

	// TexKey
	TCHAR tszTexKey[3][MIN_STR];
	_tcscpy_s(tszTexKey[0], MIN_STR, _T("Sign_WhiteBorder"));
	_tcscpy_s(tszTexKey[1], MIN_STR, _T("Sign_YellowBorder"));
	_tcscpy_s(tszTexKey[2], MIN_STR, _T("Sign_RedBorder"));

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pBorderSign[i]->Initialize();
	}

	/*
	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pMainWeaponBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pMainWeaponBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.711747f, 0.122333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		m_pMainWeaponBorderSign[i]->Initialize();
	}

	// HelmsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pHelmsBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pHelmsBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pHelmsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812747f, 0.635329f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
		m_pHelmsBorderSign[i]->Initialize();
	}

	// SholdersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pSholdersBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pSholdersBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pSholdersBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.735747f, 0.580329f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
		m_pSholdersBorderSign[i]->Initialize();
	}

	// ChestArmorBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pChestArmorBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pChestArmorBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.481331f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
		m_pChestArmorBorderSign[i]->Initialize();
	}

	// BracersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pBracersBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pBracersBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pBracersBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.913744f, 0.416332f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		m_pBracersBorderSign[i]->Initialize();
	}

	// GlovesBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pGlovesBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pGlovesBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pGlovesBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.711747f, 0.416332f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		m_pGlovesBorderSign[i]->Initialize();
	}

	// BeltBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pBeltBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pBeltBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pBeltBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.349332f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
		m_pBeltBorderSign[i]->Initialize();
	}

	// PantsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pPantsBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pPantsBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pPantsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.241334f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		m_pPantsBorderSign[i]->Initialize();
	}

	// BootsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pBootsBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pBootsBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pBootsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812747f, 0.089333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		m_pBootsBorderSign[i]->Initialize();
	}

	// AmuletBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pAmuletBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pAmuletBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pAmuletBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.886745f, 0.57333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
		m_pAmuletBorderSign[i]->Initialize();
	}

	// LeftRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pLeftRingBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pLeftRingBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.710747f, 0.286333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		m_pLeftRingBorderSign[i]->Initialize();
	}

	// RightRingBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pRightRingBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pRightRingBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pRightRingBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.286333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		m_pRightRingBorderSign[i]->Initialize();
	}

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pSubWeaponBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pSubWeaponBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.122333f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		m_pSubWeaponBorderSign[i]->Initialize();
	}
	*/

	Renew();
}

int CStorageWindow::Update()
{
	// Mouse
	CObject* pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Mouse"), LAYER_TYPE_MOUSE);
	m_pMouse = (CMouse*)pFind;

	// Player
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Player"), LAYER_TYPE_PLAYER);
	m_pPlayer = (CPlayer*)pFind;

	// TransformCom
	CTransformCom* pTransformCom;

	// StorageSign
	for(size_t i = 0; i < m_StorageSign.size(); ++i)
	{
		if(m_StorageSign[i]->IsOver())
			m_StorageSign[i]->EnableItemMessage();
		else
			m_StorageSign[i]->DisableItemMessage();
	}

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	/*
	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// HelmsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pHelmsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// SholdersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pSholdersBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// ChestArmorBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// BracersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBracersBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// GlovesBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pGlovesBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// BeltBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBeltBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// PantsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pPantsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

	// BootsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBootsBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
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

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}
	*/

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

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStorage();
				UpdateNonePickInStorage();
			}
			break;

		case 0:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickIn();
			UpdateInventoryPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStorage();
				UpdatePickInStorage();
				UpdateInventoryPickInStorage();
			}
			break;

		case 1:
			UpdatePick();
			UpdateEquipmentPick();
			UpdatePickIn();
			UpdateEquipmentPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStorage();
				UpdatePickInStorage();
				UpdateEquipmentPickInStorage();
			}
			break;

		case 2:
			UpdatePick();
			UpdateStoragePick();
			UpdatePickIn();
			UpdateStoragePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStorage();
				UpdatePickInStorage();
				UpdateStoragePickInStorage();
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

		case 2:
			UpdatePick();
			UpdateStoragePick();
			UpdatePickOut();
			UpdateStoragePickOut();
			break;
		}
	}

	// StorageButton
	for(int i = 0; i < 5; ++i)
		m_pStorageButton[i]->SetState(0);

	m_pStorageButton[m_iPage]->SetState(UI_L_DOWN);

	CWindowUI::Update();

	return 0;
}

void CStorageWindow::Render()
{
	CWindowUI::Render();

	TCHAR tszGold[MIN_STR];
	ZeroMemory(tszGold, sizeof(tszGold));
	StringCbPrintf(tszGold, sizeof(tszGold), _T("보유금화: %d"), CItemMgr::GetInstance()->GetGold());

	RECT rcText;
	SetRect(&rcText, -131, 551, 509, 563);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszGold, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CStorageWindow::Release()
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

	// StorageButton
	for(int i = 0; i < 5; ++i)
	{
		if(m_pStorageButton[i] != NULL)
		{
			m_pStorageButton[i]->Destroy();
			m_pStorageButton[i] = NULL;
		}
	}

	// StorageSign
	for(size_t i = 0; i < m_StorageSign.size(); ++i)
	{
		m_StorageSign[i]->Destroy();
		m_StorageSign[i] = NULL;
	}
	m_StorageSign.clear();

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pBorderSign[i] != NULL)
		{
			m_pBorderSign[i]->Destroy();
			m_pBorderSign[i] = NULL;
		}
	}

	/*
	// MainWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pMainWeaponBorderSign[i] != NULL)
		{
			m_pMainWeaponBorderSign[i]->Destroy();
			m_pMainWeaponBorderSign[i] = NULL;
		}
	}

	// HelmsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pHelmsBorderSign[i] != NULL)
		{
			m_pHelmsBorderSign[i]->Destroy();
			m_pHelmsBorderSign[i] = NULL;
		}
	}

	// SholdersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pSholdersBorderSign[i] != NULL)
		{
			m_pSholdersBorderSign[i]->Destroy();
			m_pSholdersBorderSign[i] = NULL;
		}
	}

	// ChestArmorBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pChestArmorBorderSign[i] != NULL)
		{
			m_pChestArmorBorderSign[i]->Destroy();
			m_pChestArmorBorderSign[i] = NULL;
		}
	}

	// BracersBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pBracersBorderSign[i] != NULL)
		{
			m_pBracersBorderSign[i]->Destroy();
			m_pBracersBorderSign[i] = NULL;
		}
	}

	// GlovesBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pGlovesBorderSign[i] != NULL)
		{
			m_pGlovesBorderSign[i]->Destroy();
			m_pGlovesBorderSign[i] = NULL;
		}
	}

	// BeltBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pBeltBorderSign[i] != NULL)
		{
			m_pBeltBorderSign[i]->Destroy();
			m_pBeltBorderSign[i] = NULL;
		}
	}

	// PantsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pPantsBorderSign[i] != NULL)
		{
			m_pPantsBorderSign[i]->Destroy();
			m_pPantsBorderSign[i] = NULL;
		}
	}

	// BootsBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pBootsBorderSign[i] != NULL)
		{
			m_pBootsBorderSign[i]->Destroy();
			m_pBootsBorderSign[i] = NULL;
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

	// SubWeaponBorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pSubWeaponBorderSign[i] != NULL)
		{
			m_pSubWeaponBorderSign[i]->Destroy();
			m_pSubWeaponBorderSign[i] = NULL;
		}
	}
	*/
}

void CStorageWindow::Renew()
{
	// StorageSign Clear
	for(size_t i = 0; i < m_StorageSign.size(); ++i)
	{
		m_StorageSign[i]->Destroy();
		m_StorageSign[i] = NULL;
	}
	m_StorageSign.clear();

	// StorageSign
	for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfStorage(m_iPage); ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInStorage(m_iPage, i);
		if(pItem == NULL)
			continue;

		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pItem);
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		// LT
		D3DXVECTOR2 vLT;
		vLT.x = -0.955495f + pItem->iPosX * 0.0655711f;
		vLT.y = 0.606999f + pItem->iPosY * -0.1093995f;

		// RB
		D3DXVECTOR2 vRB;
		vRB.x = vLT.x + pItem->iWidth * 0.0655711f;
		vRB.y = vLT.y + pItem->iHeight * -0.1093995f;

		CTransformCom* pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
		pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;
		pTransformCom->m_vSize.x = pItem->iWidth * 0.0655711f;
		pTransformCom->m_vSize.y = pItem->iHeight * 0.1093995f;

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableSockSign();
		if(pItemSign->IsOver()) { pItemSign->EnableItemMessage(); }

		m_StorageSign.push_back(pItemSign);
	}
}

////////////////////////////////////////////////////////////////////////// Pick
void CStorageWindow::UpdateNonePick()
{
}
void CStorageWindow::UpdatePick()
{
}
void CStorageWindow::UpdateInventoryPick()
{
}
void CStorageWindow::UpdateEquipmentPick()
{
}
void CStorageWindow::UpdateStoragePick()
{
	/*
	Item* pItem = m_pMouse->GetItem();

	// MainWeapon & SubWeapon
	if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
	{
		if((pItem->dwItemID & m_dwBothSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
		else if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
		else if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
		else
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
	}
	// MainWeapon
	else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
	{
		if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
	}
	// SubWeapon
	else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
	{
		if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
	}
	// Helms
	else if(pItem->dwItemType & ITEM_TYPE_HELMS)
	{
		if((pItem->dwItemID & m_dwHelms) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
		}
	}
	// Shoulders
	else if(pItem->dwItemType & ITEM_TYPE_SHOULDERS)
	{
		if((pItem->dwItemID & m_dwShoulders) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
		}
	}
	// ChestArmor
	else if(pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
	{
		if((pItem->dwItemID & m_dwChestArmor) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
		}
	}
	// Bracers
	else if(pItem->dwItemType & ITEM_TYPE_BRACERS)
	{
		if((pItem->dwItemID & m_dwBracers) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
	}
	// Gloves
	else if(pItem->dwItemType & ITEM_TYPE_GLOVES)
	{
		if((pItem->dwItemID & m_dwGloves) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
	}
	// Belt
	else if(pItem->dwItemType & ITEM_TYPE_BELT)
	{
		if((pItem->dwItemID & m_dwBelt) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
		}
	}
	// Pants
	else if(pItem->dwItemType & ITEM_TYPE_PANTS)
	{
		if((pItem->dwItemID & m_dwPants) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
	}
	// Boots
	else if(pItem->dwItemType & ITEM_TYPE_BOOTS)
	{
		if((pItem->dwItemID & m_dwBoots) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
	}
	// Amulet
	else if(pItem->dwItemType & ITEM_TYPE_AMULET)
	{
		if((pItem->dwItemID & m_dwAmulet) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
		}
	}
	// Ring
	else if(pItem->dwItemType & ITEM_TYPE_RING)
	{
		if((pItem->dwItemID & m_dwRing) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		}
	}
	*/
}

////////////////////////////////////////////////////////////////////////// In
void CStorageWindow::UpdateIn()
{
}
void CStorageWindow::UpdateNonePickIn()
{
	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	for(int i = 0; i < 5; ++i)
	{
		if(m_iPage == i)
			continue;

		if(m_pStorageButton[i]->IsLDown())
		{
			m_pStorageButton[m_iPage]->SetState(0);
			m_iPage = i;
			Renew();
			break;
		}
	}
}
void CStorageWindow::UpdatePickIn()
{
}
void CStorageWindow::UpdateInventoryPickIn()
{
}
void CStorageWindow::UpdateEquipmentPickIn()
{
}
void CStorageWindow::UpdateStoragePickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CStorageWindow::UpdateOut()
{
}
void CStorageWindow::UpdateNonePickOut()
{
	// LButton
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		D3DXVECTOR3 vPos;
		ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

		if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.4389982f, -1.0f), &D3DXVECTOR2(0.4529938f, 1.0f)))
		{
			// DropItemVec
			vector<CObject*> DropItemVec;
			m_pLayer->FindObjects(DropItemVec, _T("Item"), LAYER_TYPE_DROP);

			bool bFind = false;
			for(size_t i = 0; i < DropItemVec.size(); ++i)
			{
				CDropItem* pDropItem = (CDropItem*)DropItemVec[i];
				if(pDropItem->IsOver())
				{
					bFind = true;
					break;
				}
			}

			if(bFind == false)
				Destroy();
		}
	}
}
void CStorageWindow::UpdatePickOut()
{
}
void CStorageWindow::UpdateInventoryPickOut()
{
}
void CStorageWindow::UpdateEquipmentPickOut()
{
}
void CStorageWindow::UpdateStoragePickOut()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		// StaticProbVec
		vector<CObject*> StaticProbVec;
		m_pLayer->FindObjects(StaticProbVec, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);

		for(size_t i = 0; i < StaticProbVec.size(); ++i)
		{
			CStaticProb* pStaticProb = (CStaticProb*)StaticProbVec[i];
			if(pStaticProb->GetProbType() == PROB_TYPE_TRISTRAM_STASH)
			{
				// TransformComA
				CTransformCom* pTransformComA = (CTransformCom*)pStaticProb->GetComponent(COM_TYPE_TRANSFORM);

				// TransformComB
				CTransformCom* pTransformComB = (CTransformCom*)m_pPlayer->GetComponent(COM_TYPE_TRANSFORM);

				// Dist
				float fDist = D3DXVec3Length(&(pTransformComA->m_vPos - pTransformComB->m_vPos));

				if(fDist > 150.0f)
					Destroy();

				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////// InStorage
void CStorageWindow::UpdateInStorage()
{
}
void CStorageWindow::UpdateNonePickInStorage()
{
	for(size_t i = 0; i < m_StorageSign.size(); ++i)
	{
		// Break
		bool bBreak = false;

		// LDown
		if(m_StorageSign[i]->IsLDown())
		{
			if(m_StorageSign[i]->GetItem()->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL) && (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
			{
				CAmountTextField* pAmountTextField = new CAmountTextField(NULL, OBJ_TYPE_STATIC, 2, i, m_iPage);
				m_pLayer->AddObject(pAmountTextField, LAYER_TYPE_UI);

				CTransformCom* pTransformComA = (CTransformCom*)pAmountTextField->GetComponent(COM_TYPE_TRANSFORM);
				CTransformCom* pTransformComB = (CTransformCom*)m_StorageSign[i]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformComA->m_vPos.x = pTransformComB->m_vPos.x + pTransformComB->m_vSize.x / 2.0f + pTransformComA->m_vSize.x / 2.0f;
				pTransformComA->m_vPos.y = pTransformComB->m_vPos.y + pTransformComB->m_vSize.y / 2.0f;

				pAmountTextField->Initialize();
				bBreak = true;
			}
			else
			{
				m_pMouse->Pick(2, i, m_StorageSign[i]->GetItem());
				bBreak = true;
			}
		}

		// RDown
		else if(m_StorageSign[i]->IsRDown())
		{
			// InvenWindow
			CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

			if(CItemMgr::GetInstance()->MoveStorageToInven(m_iPage, i, -1, -1))
			{
				CItemMgr::GetInstance()->CommitInven();
				CItemMgr::GetInstance()->CommitStorage(m_iPage);
				pInvenWindow->Renew();
				Renew();
				break;
			}
			else
			{
				CItemMgr::GetInstance()->RollbackInven();
				CItemMgr::GetInstance()->RollbackStorage(m_iPage);
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			}

			bBreak = true;
		}

		// Over
		if(m_StorageSign[i]->IsOver())
		{
			// Item
			Item* pItem = m_StorageSign[i]->GetItem();

			// Border
			CTransformCom* pTransformComA = (CTransformCom*)m_StorageSign[i]->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComB->m_vPos = pTransformComA->m_vPos;
			pTransformComB->m_vSize = pTransformComA->m_vSize;

			/*
			// MainWeapon & SubWeapon
			if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
			{
				if((pItem->dwItemID & m_dwBothSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
					pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
				else if(pItem->dwItemID & m_dwLeftSide && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
					pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
				else if(pItem->dwItemID & m_dwRightSide && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
					pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
					pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
			}
			// MainWeapon
			else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			{
				if((pItem->dwItemID & m_dwLeftSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
			}
			// SubWeapon
			else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
			{
				if((pItem->dwItemID & m_dwRightSide) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
				}
			}
			// Helms
			else if(pItem->dwItemType & ITEM_TYPE_HELMS)
			{
				if((pItem->dwItemID & m_dwHelms) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
				}
			}
			// Shoulders
			else if(pItem->dwItemType & ITEM_TYPE_SHOULDERS)
			{
				if((pItem->dwItemID & m_dwShoulders) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
				}
			}
			// ChestArmor
			else if(pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
			{
				if((pItem->dwItemID & m_dwChestArmor) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
				}
			}
			// Bracers
			else if(pItem->dwItemType & ITEM_TYPE_BRACERS)
			{
				if((pItem->dwItemID & m_dwBracers) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
				}
			}
			// Gloves
			else if(pItem->dwItemType & ITEM_TYPE_GLOVES)
			{
				if((pItem->dwItemID & m_dwGloves) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
				}
			}
			// Belt
			else if(pItem->dwItemType & ITEM_TYPE_BELT)
			{
				if((pItem->dwItemID & m_dwBelt) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
				}
			}
			// Pants
			else if(pItem->dwItemType & ITEM_TYPE_PANTS)
			{
				if((pItem->dwItemID & m_dwPants) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
				}
			}
			// Boots
			else if(pItem->dwItemType & ITEM_TYPE_BOOTS)
			{
				if((pItem->dwItemID & m_dwBoots) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
				}
			}
			// Amulet
			else if(pItem->dwItemType & ITEM_TYPE_AMULET)
			{
				if((pItem->dwItemID & m_dwAmulet) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
				}
			}
			// Ring
			else if(pItem->dwItemType & ITEM_TYPE_RING)
			{
				if((pItem->dwItemID & m_dwRing) && pItem->iLevel <= m_pPlayer->GetStat()->iLevel && (pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender))
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
					pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
				}
				else
				{
					CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
					pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
					pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
				}
			}
			*/

			bBreak = true;
		}

		if(bBreak)
			break;
	}
}
void CStorageWindow::UpdatePickInStorage()
{
}
void CStorageWindow::UpdateInventoryPickInStorage()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 7 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 10)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInStorage(m_iPage, pItem);
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			// InvenWindow
			CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

			if(pItem->iNum == CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->iNum)
			{
				// Move
				if(CItemMgr::GetInstance()->MoveInvenToStorage(m_pMouse->GetSelect(), m_iPage, pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					pInvenWindow->Renew();
					Renew();
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInvenToStorage(m_pMouse->GetSelect(), pItem, m_iPage))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					pInvenWindow->Renew();
					Renew();
				}
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfStorage(m_iPage); ++i)
			{
				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInStorage(m_iPage, i)))
				{
					iIndex = i;
					break;
				}
			}

			// InvenWindow
			CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

			// EquipType
			DWORD dwEquipType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_BELT | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS | ITEM_TYPE_AMULET | ITEM_TYPE_RING | ITEM_TYPE_SUB_WEAPON;

			if((CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->dwItemType & ITEM_TYPE_GEM) && (CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & dwEquipType))
			{
				// Enchant
				if(CItemMgr::GetInstance()->EnchantInvenToStorage(m_pMouse->GetSelect(), m_iPage, iIndex))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					pInvenWindow->Renew();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
				}
			}
			else if(pItem->iNum == CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->iNum)
			{
				// Swap
				if(CItemMgr::GetInstance()->SwapInvenToStorage(m_pMouse->GetSelect(), m_iPage, iIndex, pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					pInvenWindow->Renew();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInvenToStorage(m_pMouse->GetSelect(), pItem, m_iPage))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					pInvenWindow->Renew();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = -0.955495f + pItem->iPosX * 0.0655711f;
	vLT.y = 0.606999f + pItem->iPosY * -0.1093995f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0655711f;
	vRB.y = vLT.y + pItem->iHeight * -0.1093995f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0655711f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.1093995f;
}
void CStorageWindow::UpdateEquipmentPickInStorage()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 7 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 10)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInStorage(m_iPage, pItem);
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			// InvenWindow
			CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

			// Move
			if(CItemMgr::GetInstance()->MoveEquipToStorage(m_pMouse->GetSelect(), m_iPage, pItem->iPosX, pItem->iPosY))
			{
				CItemMgr::GetInstance()->CommitEquip();
				CItemMgr::GetInstance()->CommitStorage(m_iPage);
				m_pMouse->Drop();
				m_pPlayer->Renew();
				pInvenWindow->Renew();
				Renew();
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfStorage(m_iPage); ++i)
			{
				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInStorage(m_iPage, i)))
				{
					iIndex = i;
					break;
				}
			}

			// Success
			int iSuccess = -1;

			// InvenWindow
			CInvenWindow* pInvenWindow = (CInvenWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_INVENTORY);

			// Sholders
			if(m_pMouse->GetSelect() == 0)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_SHOULDERS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwShoulders) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 0, pItem->iPosX, pItem->iPosY);
			}
			// Helms
			else if(m_pMouse->GetSelect() == 1)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_HELMS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwHelms) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 1, pItem->iPosX, pItem->iPosY);
			}
			// Amulet
			else if(m_pMouse->GetSelect() == 2)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_AMULET) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwAmulet) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 2, pItem->iPosX, pItem->iPosY);
			}
			// Gloves
			else if(m_pMouse->GetSelect() == 3)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_GLOVES) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwGloves) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 3, pItem->iPosX, pItem->iPosY);
			}
			// ChestArmor
			else if(m_pMouse->GetSelect() == 4)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_CHESTARMOR) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwChestArmor) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 4, pItem->iPosX, pItem->iPosY);
			}
			// Bracers
			else if(m_pMouse->GetSelect() == 5)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_BRACERS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwBracers) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 5, pItem->iPosX, pItem->iPosY);
			}
			// LeftRing
			else if(m_pMouse->GetSelect() == 6)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwRing) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 6, pItem->iPosX, pItem->iPosY);
			}
			// Belt
			else if(m_pMouse->GetSelect() == 7)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_BELT) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwBelt) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 7, pItem->iPosX, pItem->iPosY);
			}
			// RightRing
			else if(m_pMouse->GetSelect() == 8)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwRing) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 8, pItem->iPosX, pItem->iPosY);
			}
			// MainWeapon
			else if(m_pMouse->GetSelect() == 9)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 9, pItem->iPosX, pItem->iPosY);
			}
			// Pants
			else if(m_pMouse->GetSelect() == 10)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_PANTS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwPants) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 10, pItem->iPosX, pItem->iPosY);
			}
			// SubWeapon
			else if(m_pMouse->GetSelect() == 11)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_SUB_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & (m_dwBothSide | m_dwRightSide)) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 11, pItem->iPosX, pItem->iPosY);
			}
			// Boots
			else if(m_pMouse->GetSelect() == 12)
			{
				if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & ITEM_TYPE_BOOTS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemID & m_dwBoots) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(m_iPage, iIndex, 12, pItem->iPosX, pItem->iPosY);
			}

			if(iSuccess == 1)
			{
				CItemMgr::GetInstance()->CommitEquip();
				CItemMgr::GetInstance()->CommitStorage(m_iPage);
				m_pMouse->Drop();
				m_pPlayer->Renew();
				pInvenWindow->Renew();
				Renew();
			}
			else if(iSuccess == 0)
			{
				CItemMgr::GetInstance()->RollbackEquip();
				CItemMgr::GetInstance()->RollbackStorage(m_iPage);
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = -0.955495f + pItem->iPosX * 0.0655711f;
	vLT.y = 0.606999f + pItem->iPosY * -0.1093995f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0655711f;
	vRB.y = vLT.y + pItem->iHeight * -0.1093995f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0655711f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.1093995f;
}
void CStorageWindow::UpdateStoragePickInStorage()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 7 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 10)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInStorage(m_iPage, pItem);
	if(CItemMgr::GetInstance()->ItemToItem(pItem, m_StorageSign[m_pMouse->GetSelect()]->GetItem()))
		--iCnt;

	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			if(pItem->iNum == CItemMgr::GetInstance()->GetItemInStorage(m_iPage, m_pMouse->GetSelect())->iNum)
			{
				// Move
				if(CItemMgr::GetInstance()->MoveInStorage(m_iPage, m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					Renew();
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInStorage(m_iPage, m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					Renew();
				}
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfStorage(m_iPage); ++i)
			{
				if(i == m_pMouse->GetSelect())
					continue;

				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInStorage(m_iPage, i)))
				{
					iIndex = i;
					break;
				}
			}

			// EquipType
			DWORD dwEquipType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_BELT | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS | ITEM_TYPE_AMULET | ITEM_TYPE_RING | ITEM_TYPE_SUB_WEAPON;

			if((CItemMgr::GetInstance()->GetItemInStorage(m_iPage, m_pMouse->GetSelect())->dwItemType & ITEM_TYPE_GEM) && (CItemMgr::GetInstance()->GetItemInStorage(m_iPage, iIndex)->dwItemType & dwEquipType))
			{
				// Enchant
				if(CItemMgr::GetInstance()->EnchantInStorage(m_iPage, m_pMouse->GetSelect(), iIndex))
				{
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
				}
			}
			else if(pItem->iNum == CItemMgr::GetInstance()->GetItemInStorage(m_iPage, m_pMouse->GetSelect())->iNum)
			{
				// Swap
				if(CItemMgr::GetInstance()->SwapInStorage(m_iPage, m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY, iIndex))
				{
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInStorage(m_iPage, m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitStorage(m_iPage);
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackStorage(m_iPage);
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));

	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = -0.955495f + pItem->iPosX * 0.0655711f;
	vLT.y = 0.606999f + pItem->iPosY * -0.1093995f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0655711f;
	vRB.y = vLT.y + pItem->iHeight * -0.1093995f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0655711f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.1093995f;
}

Item* CStorageWindow::GetOverItemInStorage()
{
	for(size_t i = 0; i < m_StorageSign.size(); ++i)
	{
		if(m_StorageSign[i]->IsOver())
			return m_StorageSign[i]->GetItem();
	}

	return NULL;
}