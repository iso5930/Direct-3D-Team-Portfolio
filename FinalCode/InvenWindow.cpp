#include "StdAfx.h"
#include "InvenWindow.h"

CInvenWindow::CInvenWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, NULL)
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

		// BackTexture
		if(pAccount->info.iGender == 0)
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_BarbarianMale_Inven"));
		else
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_BarbarianFemale_Inven"));
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

		// BackTexture
		if(pAccount->info.iGender == 0)
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_DemonHunterMale_Inven"));
		else
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_DemonHunterFemale_Inven"));
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

		// BackTexture
		if(pAccount->info.iGender == 0)
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_MonkMale_Inven"));
		else
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_MonkFemale_Inven"));
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

		// BackTexture
		if(pAccount->info.iGender == 0)
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_WitchDoctorMale_Inven"));
		else
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_WitchDoctorFemale_Inven"));
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

		// BackTexture
		if(pAccount->info.iGender == 0)
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_WizardMale_Inven"));
		else
			m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Window_WizardFemale_Inven"));
	}

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

	// BorderSign
	ZeroMemory(m_pBorderSign, sizeof(m_pBorderSign));

	// MainWeaponBorderSign
	ZeroMemory(m_pMainWeaponBorderSign, sizeof(m_pMainWeaponBorderSign));

	// HelmsBorderSign
	ZeroMemory(m_pHelmsBorderSign, sizeof(m_pHelmsBorderSign));

	// SholdersBorderSign
	ZeroMemory(m_pSholdersBorderSign, sizeof(m_pSholdersBorderSign));

	// ChestArmorBorderSign
	ZeroMemory(m_pChestArmorBorderSign, sizeof(m_pChestArmorBorderSign));

	// BracersBorderSign
	ZeroMemory(m_pBracersBorderSign, sizeof(m_pBracersBorderSign));

	// GlovesBorderSign
	ZeroMemory(m_pGlovesBorderSign, sizeof(m_pGlovesBorderSign));

	// BeltBorderSign
	ZeroMemory(m_pBeltBorderSign, sizeof(m_pBeltBorderSign));

	// PantsBorderSign
	ZeroMemory(m_pPantsBorderSign, sizeof(m_pPantsBorderSign));

	// BootsBorderSign
	ZeroMemory(m_pBootsBorderSign, sizeof(m_pBootsBorderSign));

	// AmuletBorderSign
	ZeroMemory(m_pAmuletBorderSign, sizeof(m_pAmuletBorderSign));

	// LeftRingBorderSign
	ZeroMemory(m_pLeftRingBorderSign, sizeof(m_pLeftRingBorderSign));

	// RightRingBorderSign
	ZeroMemory(m_pRightRingBorderSign, sizeof(m_pRightRingBorderSign));

	// SubWeaponBorderSign
	ZeroMemory(m_pSubWeaponBorderSign, sizeof(m_pSubWeaponBorderSign));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.225f, 0.0f);
}

CInvenWindow::~CInvenWindow()
{
	Release();
}

void CInvenWindow::Initialize()
{
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));

	CWindowUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.982f, 0.969f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);

	// DetailButton(1)
	CBasicButton* pDetailButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Detail"), _T("Button_Over_Detail"), _T("Button_Down_Detail"));
	m_pLayer->AddObject(pDetailButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDetailButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.579005f, 0.0150089f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.117f, 0.061f, 0.0f);
	pDetailButton->Initialize();
	AddButton(pDetailButton);

	// TexKey
	TCHAR tszTexKey[3][MIN_STR];
	_tcscpy_s(tszTexKey[0], MIN_STR, _T("Sign_WhiteBorder"));
	_tcscpy_s(tszTexKey[1], MIN_STR, _T("Sign_YellowBorder"));
	_tcscpy_s(tszTexKey[2], MIN_STR, _T("Sign_RedBorder"));

	// TextKey
	TCHAR tszTextKey[13][MIN_STR];
	_tcscpy_s(tszTextKey[0], MIN_STR, _T("어깨"));
	_tcscpy_s(tszTextKey[1], MIN_STR, _T("머리"));
	_tcscpy_s(tszTextKey[2], MIN_STR, _T("목"));
	_tcscpy_s(tszTextKey[3], MIN_STR, _T("손"));
	_tcscpy_s(tszTextKey[4], MIN_STR, _T("몸통"));
	_tcscpy_s(tszTextKey[5], MIN_STR, _T("손목"));
	_tcscpy_s(tszTextKey[6], MIN_STR, _T("손가락"));
	_tcscpy_s(tszTextKey[7], MIN_STR, _T("허리"));
	_tcscpy_s(tszTextKey[8], MIN_STR, _T("손가락"));
	_tcscpy_s(tszTextKey[9], MIN_STR, _T("한손 무기"));
	_tcscpy_s(tszTextKey[10], MIN_STR, _T("다리"));
	_tcscpy_s(tszTextKey[11], MIN_STR, _T("보조 장비"));
	_tcscpy_s(tszTextKey[12], MIN_STR, _T("발"));

	// EquipMessage
	for(int i = 0; i < 13; ++i)
	{
		m_EquipMessage[i] = new CBasicMessage(NULL, OBJ_TYPE_STATIC, _T("Message_Equip"), tszTextKey[i]);
		m_pLayer->AddObject(m_EquipMessage[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_EquipMessage[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		m_EquipMessage[i]->Initialize();
	}

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		m_pBorderSign[i] = new CBasicSign(NULL, OBJ_TYPE_STATIC, tszTexKey[i]);
		m_pLayer->AddObject(m_pBorderSign[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pBorderSign[i]->Initialize();
	}

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

	Renew();
}

int CInvenWindow::Update()
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

	// InvenSign
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		if(m_InvenSign[i]->IsOver())
			m_InvenSign[i]->EnableItemMessage();
		else
			m_InvenSign[i]->DisableItemMessage();
	}

	// EquipSign
	for(int i = 0; i < 13; ++ i)
	{
		if(m_EquipSign[i] != NULL)
		{
			if(m_EquipSign[i]->IsOver())
				m_EquipSign[i]->EnableItemMessage();
			else
				m_EquipSign[i]->DisableItemMessage();
		}
	}

	// EquipMessage
	for(int i = 0; i < 13; ++i)
	{
		pTransformCom = (CTransformCom*)m_EquipMessage[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	}

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBorderSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		ZeroMemory(&pTransformCom->m_vSize, sizeof(D3DXVECTOR3));
	}

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

	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.447499f, -1.0f), &D3DXVECTOR2(1.0f, 1.0f)))
	{
		UpdateIn();

		switch(m_pMouse->GetPickType())
		{
		case -1:
			UpdateNonePick();
			UpdateNonePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdateNonePickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdateNonePickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
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

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateInventoryPickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateInventoryPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
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

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateEquipmentPickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateEquipmentPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateEquipmentPickInStat();
			}
			break;

		case 2:
			UpdatePick();
			UpdateStoragePick();
			UpdatePickIn();
			UpdateStoragePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateStoragePickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateStoragePickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateStoragePickInStat();
			}
			break;

		case 3:
			UpdatePick();
			UpdateStorePick();
			UpdatePickIn();
			UpdateStorePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateStorePickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateStorePickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateStorePickInStat();
			}
			break;

		case 4:
			UpdatePick();
			UpdateDecomposePick();
			UpdatePickIn();
			UpdateDecomposePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateDecomposePickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateDecomposePickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateDecomposePickInStat();
			}
			break;

		case 5:
			UpdatePick();
			UpdateFollowerEquipPick();
			UpdatePickIn();
			UpdateFollowerEquipPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.456997f, -0.58483f), &D3DXVECTOR2(0.990497f, -0.0185015f)))
			{
				UpdateInInven();
				UpdatePickInInven();
				UpdateFollowerEquipPickInInven();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.665996f, -0.0163315f), &D3DXVECTOR2(0.957496f, 0.7089955f)))
			{
				UpdateInEquip();
				UpdatePickInEquip();
				UpdateFollowerEquipPickInEquip();
			}
			else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.494999f, -0.0163315f), &D3DXVECTOR2(0.660499f, 0.7089955f)))
			{
				UpdateInStat();
				UpdatePickInStat();
				UpdateFollowerEquipPickInStat();
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

		case 3:
			UpdatePick();
			UpdateStorePick();
			UpdatePickOut();
			UpdateStorePickOut();
			break;

		case 4:
			UpdatePick();
			UpdateDecomposePick();
			UpdatePickOut();
			UpdateDecomposePickOut();
			break;

		case 5:
			UpdatePick();
			UpdateFollowerEquipPick();
			UpdatePickOut();
			UpdateFollowerEquipPickOut();
			break;
		}
	}

	CWindowUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	pUpdateCom->m_dwPriority = 0xFFFFFFF4;

	return 0;
}

void CInvenWindow::Render()
{
	CWindowUI::Render();

	TCHAR tszText[MIN_STR];
	_itot_s(CItemMgr::GetInstance()->GetGold(), tszText, 10);

	// Gold
	RECT rcText;
	SetRect(&rcText, 1037, 579, 1237, 591);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Level
	_itot_s(m_pPlayer->GetStat()->iLevel, tszText, 10);
	SetRect(&rcText, 750, 130, 1050, 142);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Strength
	_itot_s(m_pPlayer->GetStrength(), tszText, 10);
	SetRect(&rcText, 750, 175, 1050, 187);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Agility
	_itot_s(m_pPlayer->GetAgility(), tszText, 10);
	SetRect(&rcText, 750, 193, 1050, 205);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Intelligence
	_itot_s(m_pPlayer->GetIntelligence(), tszText, 10);
	SetRect(&rcText, 750, 212, 1050, 224);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Vitality
	_itot_s(m_pPlayer->GetVitality(), tszText, 10);
	SetRect(&rcText, 750, 230, 1050, 242);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 공격력 : MainStat, AttackStat, ResourceStat
	_itot_s(m_pPlayer->TotalStat1(), tszText, 10);
	SetRect(&rcText, 810, 269, 1210, 281);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 강인함 : DefenseStat
	_itot_s(m_pPlayer->TotalStat2(), tszText, 10);
	SetRect(&rcText, 810, 297, 1210, 309);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// 회복력 : LifeStat
	_itot_s(m_pPlayer->TotalStat3(), tszText, 10);
	SetRect(&rcText, 810, 325, 1210, 337);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CInvenWindow::Release()
{
	// InvenSign
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		m_InvenSign[i]->Destroy();
		m_InvenSign[i] = NULL;
	}
	m_InvenSign.clear();

	// EquipSign
	for(int i = 0; i < 13; ++i)
	{
		if(m_EquipSign[i] != NULL)
		{
			m_EquipSign[i]->Destroy();
			m_EquipSign[i] = NULL;
		}
	}

	// EquipMessage
	for(int i = 0; i < 13; ++i)
	{
		if(m_EquipMessage[i] != NULL)
		{
			m_EquipMessage[i]->Destroy();
			m_EquipMessage[i] = NULL;
		}
	}

	// BorderSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pBorderSign[i] != NULL)
		{
			m_pBorderSign[i]->Destroy();
			m_pBorderSign[i] = NULL;
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
}

void CInvenWindow::Renew()
{
	// InvenSign Clear
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		m_InvenSign[i]->Destroy();
		m_InvenSign[i] = NULL;
	}
	m_InvenSign.clear();

	// EquipSign Clear
	for(int i = 0; i < 13; ++i)
	{
		if(m_EquipSign[i] != NULL)
		{
			m_EquipSign[i]->Destroy();
			m_EquipSign[i] = NULL;
		}
	}

	// InvenSign
	for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInInven(i);
		if(pItem == NULL)
			continue;

		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pItem);
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		// LT
		D3DXVECTOR2 vLT;
		vLT.x = 0.4635f + pItem->iPosX * 0.0525f;
		vLT.y = -0.0355f + pItem->iPosY * -0.09216667f;

		// RB
		D3DXVECTOR2 vRB;
		vRB.x = vLT.x + pItem->iWidth * 0.0525f;
		vRB.y = vLT.y + pItem->iHeight * -0.09216667f;

		CTransformCom* pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
		pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;
		pTransformCom->m_vSize.x = pItem->iWidth * 0.0525f;
		pTransformCom->m_vSize.y = pItem->iHeight * 0.09216667f;

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableSockSign();
		if(pItemSign->IsOver()) { pItemSign->EnableItemMessage(); }

		m_InvenSign.push_back(pItemSign);
	}

	// EquipSign
	for(int i = 0; i < 13; ++i)
	{
		Item* pItem = CItemMgr::GetInstance()->GetItemInEquip(i);
		if(pItem == NULL)
			continue;

		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pItem);
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		CTransformCom* pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);

		switch(i)
		{
		case 0:
			pTransformCom->m_vPos = D3DXVECTOR3(0.735747f, 0.580329f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
			break;
		case 1:
			pTransformCom->m_vPos = D3DXVECTOR3(0.812747f, 0.635329f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
			break;
		case 2:
			pTransformCom->m_vPos = D3DXVECTOR3(0.886745f, 0.57333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
			break;
		case 3:
			pTransformCom->m_vPos = D3DXVECTOR3(0.711747f, 0.416332f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
			break;
		case 4:
			pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.481331f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
			break;
		case 5:
			pTransformCom->m_vPos = D3DXVECTOR3(0.913744f, 0.416332f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
			break;
		case 6:
			pTransformCom->m_vPos = D3DXVECTOR3(0.710747f, 0.286333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
			break;
		case 7:
			pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.349332f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
			break;
		case 8:
			pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.286333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
			break;
		case 9:
			pTransformCom->m_vPos = D3DXVECTOR3(0.711747f, 0.122333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			break;
		case 10:
			pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.241334f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
			break;
		case 11:
			pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.122333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
			break;
		case 12:
			pTransformCom->m_vPos = D3DXVECTOR3(0.812747f, 0.089333f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
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
void CInvenWindow::UpdateNonePick()
{
}

void CInvenWindow::UpdatePick()
{
}
void CInvenWindow::UpdateInventoryPick()
{
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
}
void CInvenWindow::UpdateEquipmentPick()
{
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
}
void CInvenWindow::UpdateStoragePick()
{
	// Item
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
}
void CInvenWindow::UpdateStorePick()
{
}
void CInvenWindow::UpdateDecomposePick()
{
}
void CInvenWindow::UpdateFollowerEquipPick()
{
	// Item
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
}

////////////////////////////////////////////////////////////////////////// In
void CInvenWindow::UpdateIn()
{
}
void CInvenWindow::UpdateNonePickIn()
{
	if(m_ButtonVec[0]->IsLUp())
	{
		Destroy();
		CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_DETAIL);
	}
}
void CInvenWindow::UpdatePickIn()
{
}
void CInvenWindow::UpdateInventoryPickIn()
{
}
void CInvenWindow::UpdateEquipmentPickIn()
{
}
void CInvenWindow::UpdateStoragePickIn()
{
}
void CInvenWindow::UpdateStorePickIn()
{
}
void CInvenWindow::UpdateDecomposePickIn()
{
}
void CInvenWindow::UpdateFollowerEquipPickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CInvenWindow::UpdateOut()
{
}
void CInvenWindow::UpdateNonePickOut()
{
	// StorageWindow
	if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE) != NULL)
	{
		// StorageWindow
		CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

		if(pStorageWindow->GetOverItemInStorage() != NULL)
		{
			// Item
			Item* pItem = pStorageWindow->GetOverItemInStorage();

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
		}
	}
	else if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER) != NULL)
	{
		// FollowerWindow
		CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

		if(pFollowerWindow->GetOverItemInFollowerEquip() != NULL)
		{
			// Item
			Item* pItem = pFollowerWindow->GetOverItemInFollowerEquip();

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
		}
	}
}
void CInvenWindow::UpdatePickOut()
{
}
void CInvenWindow::UpdateInventoryPickOut()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		D3DXVECTOR3 vPos;
		ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

		if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.4389982f, -1.0f), &D3DXVECTOR2(0.4529938f, 1.0f)))
		{
			CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect()));
			m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

			CTransformCom* pTransformComA = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pPlayer->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComA->m_vPos = pTransformComB->m_vPos;

			pDropItem->Initialize();

			CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
			CItemMgr::GetInstance()->RemoveItemInInven(m_pMouse->GetSelect());
			CItemMgr::GetInstance()->CommitInven();
			m_pMouse->Drop();
			Renew();
		}
	}
}
void CInvenWindow::UpdateEquipmentPickOut()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		D3DXVECTOR3 vPos;
		ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

		if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.4389982f, -1.0f), &D3DXVECTOR2(0.4529938f, 1.0f)))
		{
			CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, CItemMgr::GetInstance()->GetItemInEquip(m_pMouse->GetSelect()));
			m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

			CTransformCom* pTransformComA = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pPlayer->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComA->m_vPos = pTransformComB->m_vPos;

			pDropItem->Initialize();

			CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
			CItemMgr::GetInstance()->RemoveItemInEquip(m_pMouse->GetSelect());
			CItemMgr::GetInstance()->CommitEquip();
			m_pMouse->Drop();
			m_pPlayer->Renew();
			Renew();
		}
	}
}
void CInvenWindow::UpdateStoragePickOut()
{
}
void CInvenWindow::UpdateStorePickOut()
{
}
void CInvenWindow::UpdateDecomposePickOut()
{
}
void CInvenWindow::UpdateFollowerEquipPickOut()
{
}

////////////////////////////////////////////////////////////////////////// InInven
void CInvenWindow::UpdateInInven()
{
}
void CInvenWindow::UpdateNonePickInInven()
{
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		// Break
		bool bBreak = false;

		// LDown
		if(m_InvenSign[i]->IsLDown())
		{
			if(m_InvenSign[i]->GetItem()->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL) && (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
			{
				CAmountTextField* pAmountTextField = new CAmountTextField(NULL, OBJ_TYPE_STATIC, 0, i);
				m_pLayer->AddObject(pAmountTextField, LAYER_TYPE_UI);

				CTransformCom* pTransformComA = (CTransformCom*)pAmountTextField->GetComponent(COM_TYPE_TRANSFORM);
				CTransformCom* pTransformComB = (CTransformCom*)m_InvenSign[i]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformComA->m_vPos.x = pTransformComB->m_vPos.x - pTransformComB->m_vSize.x / 2.0f - pTransformComA->m_vSize.x / 2.0f;
				pTransformComA->m_vPos.y = pTransformComB->m_vPos.y + pTransformComB->m_vSize.y / 2.0f;

				pAmountTextField->Initialize();
				bBreak = true;
			}
			else
			{
				m_pMouse->Pick(0, i, m_InvenSign[i]->GetItem());
				bBreak = true;
			}
		}

		// RDown
		else if(m_InvenSign[i]->IsRDown())
		{
			// StoreWindow
			CStoreWindow* pStoreWindow = (CStoreWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORE);

			// StorageWindow
			CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

			if(pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInInven(i)));
				CItemMgr::GetInstance()->SellOfItemInInven(i);
				CItemMgr::GetInstance()->CommitInven();
				pStoreWindow->Renew();
				Renew();
				break;
			}
			else if(pStorageWindow != NULL)
			{
				if(CItemMgr::GetInstance()->MoveInvenToStorage(i, pStorageWindow->GetPage(), -1, -1))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					Renew();
					pStorageWindow->Renew();
					break;
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
			{
				// Item
				Item* pItem = m_InvenSign[i]->GetItem();

				// Success
				int iSuccess = -1;

				// MainWeapon & SubWeapon
				if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) && (pItem->dwItemType & ITEM_TYPE_SUB_WEAPON))
				{
					if(pItem->dwItemID & m_dwBothSide)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 9);
								else if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 11);
								else if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL && CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 9);
								else if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL && CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 9);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else if(pItem->dwItemID & m_dwLeftSide)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 9);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 9);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else if(pItem->dwItemID & m_dwRightSide)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 11);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 11);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// MainWeapon
				else if(pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON)
				{
					if(pItem->dwItemID & m_dwLeftSide)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 9);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 9);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// SubWeapon
				else if(pItem->dwItemType & ITEM_TYPE_SUB_WEAPON)
				{
					if(pItem->dwItemID & m_dwRightSide)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{

								if(CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 11);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 11);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Helms
				else if(pItem->dwItemType & ITEM_TYPE_HELMS)
				{
					if(pItem->dwItemID & m_dwHelms)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(1) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 1);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 1);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Shoulders
				else if(pItem->dwItemType & ITEM_TYPE_SHOULDERS)
				{
					if(pItem->dwItemID & m_dwShoulders)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(0) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 0);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 0);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// ChestArmor
				else if(pItem->dwItemType & ITEM_TYPE_CHESTARMOR)
				{
					if(pItem->dwItemID & m_dwChestArmor)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(4) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 4);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 4);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Bracers
				else if(pItem->dwItemType & ITEM_TYPE_BRACERS)
				{
					if(pItem->dwItemID & m_dwBracers)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(5) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 5);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 5);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Gloves
				else if(pItem->dwItemType & ITEM_TYPE_GLOVES)
				{
					if(pItem->dwItemID & m_dwGloves)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(3) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 3);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 3);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Belt
				else if(pItem->dwItemType & ITEM_TYPE_BELT)
				{
					if(pItem->dwItemID & m_dwBelt)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(7) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 7);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 7);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Pants
				else if(pItem->dwItemType & ITEM_TYPE_PANTS)
				{
					if(pItem->dwItemID & m_dwPants)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(10) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 10);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 10);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Boots
				else if(pItem->dwItemType & ITEM_TYPE_BOOTS)
				{
					if(pItem->dwItemID & m_dwBoots)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(12) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 12);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 12);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Amulet
				else if(pItem->dwItemType & ITEM_TYPE_AMULET)
				{
					if(pItem->dwItemID & m_dwAmulet)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(2) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 2);
								else
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 2);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}
				// Ring
				else if(pItem->dwItemType & ITEM_TYPE_RING)
				{
					if(pItem->dwItemID & m_dwRing)
					{
						if(pItem->iLevel <= m_pPlayer->GetStat()->iLevel)
						{
							if(pItem->iGender == 2 || pItem->iGender == m_pPlayer->GetInfo()->iGender)	
							{
								if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL && CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
									iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(i, 6);
								else if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL && CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 8);
								else if(CItemMgr::GetInstance()->GetItemInEquip(6) == NULL && CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 6);
								else if(CItemMgr::GetInstance()->GetItemInEquip(6) == NULL && CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
									iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(i, 6);
							}
							else
								CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
						}
						else
							CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					}
					else
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				}

				// Check
				if(iSuccess == 1)
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitEquip();
					Renew();
					m_pPlayer->Renew();
					break;
				}
				else if(iSuccess == 0)
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackEquip();
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}

			bBreak = true;
		}

		// Over
		if(m_InvenSign[i]->IsOver())
		{
			// Item
			Item* pItem = m_InvenSign[i]->GetItem();

			// Border
			CTransformCom* pTransformComA = (CTransformCom*)m_InvenSign[i]->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComB->m_vPos = pTransformComA->m_vPos;
			pTransformComB->m_vSize = pTransformComA->m_vSize;

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

			bBreak = true;
		}

		// IsBreak?
		if(bBreak)
			break;
	}
}
void CInvenWindow::UpdatePickInInven()
{
}
void CInvenWindow::UpdateInventoryPickInInven()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 10 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 6)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInInven(pItem);
	if(CItemMgr::GetInstance()->ItemToItem(pItem, m_InvenSign[m_pMouse->GetSelect()]->GetItem()))
		--iCnt;

	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			if(pItem->iNum == CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->iNum)
			{
				// Move
				if(CItemMgr::GetInstance()->MoveInInven(m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					Renew();
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInInven(m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					Renew();
				}
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
			{
				if(i == m_pMouse->GetSelect())
					continue;

				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInInven(i)))
				{
					iIndex = i;
					break;
				}
			}

			// EquipType
			DWORD dwEquipType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_BELT | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS | ITEM_TYPE_AMULET | ITEM_TYPE_RING | ITEM_TYPE_SUB_WEAPON;

			if((CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->dwItemType & ITEM_TYPE_GEM) && (CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & dwEquipType))
			{
				// Enchant
				if(CItemMgr::GetInstance()->EnchantInInven(m_pMouse->GetSelect(), iIndex))
				{
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
				}
			}
			else if(pItem->iNum == CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())->iNum)
			{
				// Swap
				if(CItemMgr::GetInstance()->SwapInInven(m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY, iIndex))
				{
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideInInven(m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = 0.4635f + pItem->iPosX * 0.0525f;
	vLT.y = -0.0355f + pItem->iPosY * -0.09216667f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0525f;
	vRB.y = vLT.y + pItem->iHeight * -0.09216667f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0525f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.09216667f;
}
void CInvenWindow::UpdateEquipmentPickInInven()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 10 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 6)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInInven(pItem);
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			// MoveEquipToInven
			if(CItemMgr::GetInstance()->MoveEquipToInven(m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY))
			{
				CItemMgr::GetInstance()->CommitInven();
				CItemMgr::GetInstance()->CommitEquip();
				m_pMouse->Drop();
				m_pPlayer->Renew();
				Renew();
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
			{
				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInInven(i)))
				{
					iIndex = i;
					break;
				}
			}

			// Success
			int iSuccess = -1;

			// Shoulders
			if(m_pMouse->GetSelect() == 0)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_SHOULDERS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwShoulders) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 0, pItem->iPosX, pItem->iPosY);
			}
			// Helms
			else if(m_pMouse->GetSelect() == 1)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_HELMS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwHelms) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 1, pItem->iPosX, pItem->iPosY);
			}
			// Amulet
			else if(m_pMouse->GetSelect() == 2)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_AMULET) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwAmulet) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 2, pItem->iPosX, pItem->iPosY);
			}
			// Gloves
			else if(m_pMouse->GetSelect() == 3)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_GLOVES) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwGloves) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 3, pItem->iPosX, pItem->iPosY);
			}
			// ChestArmor
			else if(m_pMouse->GetSelect() == 4)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_CHESTARMOR) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwChestArmor) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 4, pItem->iPosX, pItem->iPosY);
			}
			// Bracers
			else if(m_pMouse->GetSelect() == 5)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_BRACERS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwBracers) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 5, pItem->iPosX, pItem->iPosY);
			}
			// LeftRing
			else if(m_pMouse->GetSelect() == 6)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwRing) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 6, pItem->iPosX, pItem->iPosY);
			}
			// Belt
			else if(m_pMouse->GetSelect() == 7)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_BELT) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwBelt) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 7, pItem->iPosX, pItem->iPosY);
			}
			// RightRing
			else if(m_pMouse->GetSelect() == 8)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwRing) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 8, pItem->iPosX, pItem->iPosY);
			}
			// MainWeapon
			else if(m_pMouse->GetSelect() == 9)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 9, pItem->iPosX, pItem->iPosY);
			}
			// Pants
			else if(m_pMouse->GetSelect() == 10)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_PANTS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwPants) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 10, pItem->iPosX, pItem->iPosY);
			}
			// SubWeapon
			else if(m_pMouse->GetSelect() == 11)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_SUB_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & (m_dwBothSide | m_dwRightSide)) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 11, pItem->iPosX, pItem->iPosY);
			}
			// Boots
			else if(m_pMouse->GetSelect() == 12)
			{
				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_BOOTS) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & m_dwBoots) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pPlayer->GetStat()->iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != 2 && CItemMgr::GetInstance()->GetItemInInven(iIndex)->iGender != m_pPlayer->GetInfo()->iGender)
					CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(iIndex, 12, pItem->iPosX, pItem->iPosY);
			}

			if(iSuccess == 1)
			{
				CItemMgr::GetInstance()->CommitInven();
				CItemMgr::GetInstance()->CommitEquip();
				m_pMouse->Drop();
				m_pPlayer->Renew();
				Renew();
			}
			else if(iSuccess == 0)
			{
				CItemMgr::GetInstance()->RollbackInven();
				CItemMgr::GetInstance()->RollbackEquip();
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = 0.4635f + pItem->iPosX * 0.0525f;
	vLT.y = -0.0355f + pItem->iPosY * -0.09216667f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0525f;
	vRB.y = vLT.y + pItem->iHeight * -0.09216667f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0525f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.09216667f;
}
void CInvenWindow::UpdateStoragePickInInven()
{
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 10 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 6)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInInven(pItem);
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			// StorageWindow
			CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

			if(pItem->iNum == CItemMgr::GetInstance()->GetItemInStorage(pStorageWindow->GetPage(), m_pMouse->GetSelect())->iNum)
			{
				// Move
				if(CItemMgr::GetInstance()->MoveStorageToInven(pStorageWindow->GetPage(), m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					m_pMouse->Drop();
					Renew();
					pStorageWindow->Renew();
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideStorageToInven(pStorageWindow->GetPage(), m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					m_pMouse->Drop();
					Renew();
					pStorageWindow->Renew();
				}
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
			{
				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInInven(i)))
				{
					iIndex = i;
					break;
				}
			}

			// StorageWindow
			CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

			// EquipType
			DWORD dwEquipType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_HELMS | ITEM_TYPE_SHOULDERS | ITEM_TYPE_CHESTARMOR | ITEM_TYPE_BRACERS | ITEM_TYPE_GLOVES | ITEM_TYPE_BELT | ITEM_TYPE_PANTS | ITEM_TYPE_BOOTS | ITEM_TYPE_AMULET | ITEM_TYPE_RING | ITEM_TYPE_SUB_WEAPON;

			if((CItemMgr::GetInstance()->GetItemInStorage(pStorageWindow->GetPage(), m_pMouse->GetSelect())->dwItemType & ITEM_TYPE_GEM) && (CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & dwEquipType))
			{
				// Enchant
				if(CItemMgr::GetInstance()->EnchantStorageToInven(pStorageWindow->GetPage(), m_pMouse->GetSelect(), iIndex))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					m_pMouse->Drop();
					Renew();
					pStorageWindow->Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
					CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
				}
			}
			else if(pItem->iNum == CItemMgr::GetInstance()->GetItemInStorage(pStorageWindow->GetPage(), m_pMouse->GetSelect())->iNum)
			{
				// Swap
				if(CItemMgr::GetInstance()->SwapStorageToInven(pStorageWindow->GetPage(), m_pMouse->GetSelect(), iIndex, pItem->iPosX, pItem->iPosY))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					m_pMouse->Drop();
					Renew();
					pStorageWindow->Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
			{
				// Devide
				if(CItemMgr::GetInstance()->DevideStorageToInven(pStorageWindow->GetPage(), m_pMouse->GetSelect(), pItem))
				{
					CItemMgr::GetInstance()->CommitInven();
					CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
					m_pMouse->Drop();
					Renew();
					pStorageWindow->Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = 0.4635f + pItem->iPosX * 0.0525f;
	vLT.y = -0.0355f + pItem->iPosY * -0.09216667f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0525f;
	vRB.y = vLT.y + pItem->iHeight * -0.09216667f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0525f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.09216667f;
}
void CInvenWindow::UpdateStorePickInInven()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(CItemMgr::GetInstance()->GetGold() >= m_pMouse->GetItem()->iValue * m_pMouse->GetItem()->iNum)
		{
			if(CItemMgr::GetInstance()->BuyOfItem(m_pMouse->GetItem()))
			{
				// StoreWindow
				CStoreWindow* pStoreWindow = (CStoreWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORE);

				pStoreWindow->RemoveRepurchase(m_pMouse->GetSelect());
				CItemMgr::GetInstance()->CommitInven();
				m_pMouse->Drop();
				pStoreWindow->Renew();
				Renew();
			}
			else
			{
				CItemMgr::GetInstance()->RollbackInven();
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			}
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("골드가 부족합니다."));
	}
}
void CInvenWindow::UpdateDecomposePickInInven()
{
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		// Break
		bool bBreak = false;

		// Over
		if(m_InvenSign[i]->IsOver())
		{
			// Item
			Item* pItem = m_InvenSign[i]->GetItem();

			// Border
			CTransformCom* pTransformComA = (CTransformCom*)m_InvenSign[i]->GetComponent(COM_TYPE_TRANSFORM);
			CTransformCom* pTransformComB = (CTransformCom*)m_pBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformComB->m_vPos = pTransformComA->m_vPos;
			pTransformComB->m_vSize = pTransformComA->m_vSize;

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

			bBreak = true;
		}

		// LDown
		if(m_InvenSign[i]->IsLDown())
		{
			CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
			pFactoryWindow->DecomposeInInven(i);
			bBreak = true;
		}

		// IsBreak?
		if(bBreak)
			break;
	}
}
void CInvenWindow::UpdateFollowerEquipPickInInven()
{
	// Item
	Item* pItem = m_pMouse->GetItem();
	if(pItem->iPosX < 0 || pItem->iPosX + pItem->iWidth > 10 || pItem->iPosY < 0 || pItem->iPosY + pItem->iHeight > 6)
		return;

	int iCnt = CItemMgr::GetInstance()->IsEmptyInInven(pItem);
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		if(iCnt == 0)
		{
			// MoveFollowerEquipToInven
			if(CItemMgr::GetInstance()->MoveFollowerEquipToInven(m_pMouse->GetSelect(), pItem->iPosX, pItem->iPosY))
			{
				CItemMgr::GetInstance()->CommitInven();
				CItemMgr::GetInstance()->CommitFollowerEquip();
				CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_FOLLOWER);
				Renew();

				m_pMouse->Drop();
				m_pFollower->Renew();
			}
		}
		else if(iCnt == 1)
		{
			// Index
			int iIndex;
			for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
			{
				if(CItemMgr::GetInstance()->ItemToItem(pItem, CItemMgr::GetInstance()->GetItemInInven(i)))
				{
					iIndex = i;
					break;
				}
			}

			// Success
			int iSuccess = -1;

			// FollowerWindow
			CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

			if(m_pMouse->GetSelect() == 0)
			{
				// ID
				DWORD dwID = pFollowerWindow->GetID(0) | pFollowerWindow->GetID(1);

				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & dwID) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToInven(0, iIndex, pItem->iPosX, pItem->iPosY);
			}
			else if(m_pMouse->GetSelect() == 1)
			{
				// ID
				DWORD dwID = pFollowerWindow->GetID(0) | pFollowerWindow->GetID(2);

				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_SUB_WEAPON) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & dwID) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToInven(1, iIndex, pItem->iPosX, pItem->iPosY);
			}
			else if(m_pMouse->GetSelect() == 2)
			{
				// ID
				DWORD dwID = pFollowerWindow->GetID(3);

				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_AMULET) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & dwID) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToInven(2, iIndex, pItem->iPosX, pItem->iPosY);
			}
			else if(m_pMouse->GetSelect() == 3)
			{
				// ID
				DWORD dwID = pFollowerWindow->GetID(4);

				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & dwID) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToInven(3, iIndex, pItem->iPosX, pItem->iPosY);
			}
			else if(m_pMouse->GetSelect() == 4)
			{
				// ID
				DWORD dwID = pFollowerWindow->GetID(4);

				if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemType & ITEM_TYPE_RING) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
				else if((CItemMgr::GetInstance()->GetItemInInven(iIndex)->dwItemID & dwID) == false)
					CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
				else if(CItemMgr::GetInstance()->GetItemInInven(iIndex)->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
					CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
				else
					iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToInven(4, iIndex, pItem->iPosX, pItem->iPosY);
			}

			if(iSuccess == 1)
			{
				CItemMgr::GetInstance()->CommitInven();
				CItemMgr::GetInstance()->CommitFollowerEquip();
				CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_FOLLOWER);
				Renew();

				m_pMouse->Drop();
				m_pFollower->Renew();
			}
			else if(iSuccess == 0)
			{
				CItemMgr::GetInstance()->RollbackInven();
				CItemMgr::GetInstance()->RollbackFollowerEquip();
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			}
		}
		else if(iCnt == 2)
			CUIMgr::GetInstance()->CreateTextMessage(_T("그 위치에 사용할 수 없는 아이템입니다."));
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pBorderSign[iCnt]->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR2 vLT;
	vLT.x = 0.4635f + pItem->iPosX * 0.0525f;
	vLT.y = -0.0355f + pItem->iPosY * -0.09216667f;

	D3DXVECTOR2 vRB;
	vRB.x = vLT.x + pItem->iWidth * 0.0525f;
	vRB.y = vLT.y + pItem->iHeight * -0.09216667f;

	pTransformCom->m_vPos.x = (vLT.x + vRB.x) / 2.0f;
	pTransformCom->m_vPos.y = (vLT.y + vRB.y) / 2.0f;

	pTransformCom->m_vSize.x = pItem->iWidth * 0.0525f;
	pTransformCom->m_vSize.y = pItem->iHeight * 0.09216667f;
}

////////////////////////////////////////////////////////////////////////// InEquip
void CInvenWindow::UpdateInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)) && CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[9]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.711747f, 0.2914995f, 0.0f);
	}
	// Helms
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)) && CItemMgr::GetInstance()->GetItemInEquip(1) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[1]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812747f, 0.7454955f, 0.0f);
	}
	// Sholders
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)) && CItemMgr::GetInstance()->GetItemInEquip(0) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.735747f, 0.7114955f, 0.0f);
	}
	// ChestArmor
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)) && CItemMgr::GetInstance()->GetItemInEquip(4) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[4]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.6334975f, 0.0f);
	}
	// Bracers
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)) && CItemMgr::GetInstance()->GetItemInEquip(5) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[5]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.913744f, 0.5474985f, 0.0f);
	}
	// Gloves
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)) && CItemMgr::GetInstance()->GetItemInEquip(3) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[3]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.711744f, 0.5474985f, 0.0f);
	}
	// Belt
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)) && CItemMgr::GetInstance()->GetItemInEquip(7) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[7]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.43299855f, 0.0f);
	}
	// Pants
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)) && CItemMgr::GetInstance()->GetItemInEquip(10) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[10]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.3605005f, 0.0f);
	}
	// Boots
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)) && CItemMgr::GetInstance()->GetItemInEquip(12) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[12]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.812746f, 0.2184995f, 0.0f);
	}
	// Amulet
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)) && CItemMgr::GetInstance()->GetItemInEquip(2) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[2]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.886745f, 0.67499655f, 0.0f);
	}
	// LeftRing
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)) && CItemMgr::GetInstance()->GetItemInEquip(6) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[6]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.710747f, 0.37849955f, 0.0f);
	}
	// RightRing
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)) && CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[8]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.37849955f, 0.0f);
	}
	// SubWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)) && CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_EquipMessage[11]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.914744f, 0.2914995f, 0.0f);
	}
}
void CInvenWindow::UpdateNonePickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Success
	int iSuccess = -1;

	// StoreWindow
	CStoreWindow* pStoreWindow = (CStoreWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORE);

	// StorageWindow
	CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(9)));
				CItemMgr::GetInstance()->SellOfItemInEquip(9);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(9, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 9, m_EquipSign[9]->GetItem());
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(1) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(1)));
				CItemMgr::GetInstance()->SellOfItemInEquip(1);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(1, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 1, m_EquipSign[1]->GetItem());
		}
	}
	// Sholders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(0) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(0)));
				CItemMgr::GetInstance()->SellOfItemInEquip(0);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(0, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 0, m_EquipSign[0]->GetItem());
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(4) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(4)));
				CItemMgr::GetInstance()->SellOfItemInEquip(4);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(4, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 4, m_EquipSign[4]->GetItem());
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(5) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(5)));
				CItemMgr::GetInstance()->SellOfItemInEquip(5);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(5, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 5, m_EquipSign[5]->GetItem());
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(3) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(3)));
				CItemMgr::GetInstance()->SellOfItemInEquip(3);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(3, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 3, m_EquipSign[3]->GetItem());
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(7) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(7)));
				CItemMgr::GetInstance()->SellOfItemInEquip(7);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(7, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 7, m_EquipSign[7]->GetItem());
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(10) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(10)));
				CItemMgr::GetInstance()->SellOfItemInEquip(10);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(10, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 10, m_EquipSign[10]->GetItem());
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(12) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(12)));
				CItemMgr::GetInstance()->SellOfItemInEquip(12);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(12, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 12, m_EquipSign[12]->GetItem());
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(2) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(2)));
				CItemMgr::GetInstance()->SellOfItemInEquip(2);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(2, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 2, m_EquipSign[2]->GetItem());
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(6)));
				CItemMgr::GetInstance()->SellOfItemInEquip(6);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(6, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 6, m_EquipSign[6]->GetItem());
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pRightRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(8)));
				CItemMgr::GetInstance()->SellOfItemInEquip(8);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(8, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 8, m_EquipSign[8]->GetItem());
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStoreWindow != NULL)
			{
				pStoreWindow->AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(11)));
				CItemMgr::GetInstance()->SellOfItemInEquip(11);
				CItemMgr::GetInstance()->CommitEquip();
				m_pPlayer->Renew();
				pStoreWindow->Renew();
				Renew();
			}
			else if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && pStorageWindow != NULL)
				iSuccess = CItemMgr::GetInstance()->MoveEquipToStorage(11, pStorageWindow->GetPage(), -1, -1);
			else if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				m_pMouse->Pick(1, 11, m_EquipSign[11]->GetItem());
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitEquip();
		CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
		m_pMouse->Drop();
		m_pPlayer->Renew();
		Renew();
		pStorageWindow->Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackEquip();
		CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
	}
}
void CInvenWindow::UpdatePickInEquip()
{
	// Item
	Item* pItem = m_pMouse->GetItem();
	if(pItem == NULL)
		return;

	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_MAIN_WEAPON) == false || (pItem->dwItemID & (m_dwBothSide | m_dwLeftSide)) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_HELMS) == false || (pItem->dwItemID & m_dwHelms) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pHelmsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(1) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pHelmsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);
		}
	}
	// Shoulders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_SHOULDERS) == false || (pItem->dwItemID & m_dwShoulders) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pSholdersBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(0) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pSholdersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_CHESTARMOR) == false || (pItem->dwItemID & m_dwChestArmor) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(4) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_BRACERS) == false || (pItem->dwItemID & m_dwBracers) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pBracersBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(5) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pBracersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_GLOVES) == false || (pItem->dwItemID & m_dwGloves) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pGlovesBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(3) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pGlovesBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_BELT) == false || (pItem->dwItemID & m_dwBelt) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pBeltBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(7) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pBeltBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_PANTS) == false || (pItem->dwItemID & m_dwPants) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pPantsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(10) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pPantsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_BOOTS) == false || (pItem->dwItemID & m_dwBoots) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pBootsBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(12) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pBootsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_AMULET) == false || (pItem->dwItemID & m_dwAmulet) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pAmuletBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(2) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pAmuletBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_RING) == false || (pItem->dwItemID & m_dwRing) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pRightRingBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if((pItem->dwItemType & ITEM_TYPE_RING) == false || (pItem->dwItemID & m_dwRing) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pRightRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[0]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Item* pItem = m_pMouse->GetItem();
		if((pItem->dwItemType & ITEM_TYPE_SUB_WEAPON) == false || (pItem->dwItemID & (m_dwBothSide | m_dwRightSide)) == false || pItem->iLevel > m_pPlayer->GetStat()->iLevel || (pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender))
		{
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
		else if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
		{
			pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);
		}
	}
}
void CInvenWindow::UpdateInventoryPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 9))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 9);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 9);
			}
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 1))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_HELMS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwHelms) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(1) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 1);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 1);
			}
		}
	}
	// Shoulders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 0))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_SHOULDERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwShoulders) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(0) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 0);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 0);
			}
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 4))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_CHESTARMOR) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwChestArmor) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(4) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 4);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 4);
			}
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 5))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BRACERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBracers) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(5) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 5);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 5);
			}
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 3))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_GLOVES) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwGloves) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(3) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 3);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 3);
			}
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 7))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BELT) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBelt) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(7) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 7);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 7);
			}
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 10))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_PANTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwPants) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(10) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 10);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 10);
			}
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 12))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BOOTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBoots) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(12) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 12);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 12);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 2))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(2) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 2);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 6))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(6) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 6);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 6);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 8))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 8);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 8);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantInvenToEquip(m_pMouse->GetSelect(), 11))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInvenToEquip(m_pMouse->GetSelect(), 11);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInvenToEquip(m_pMouse->GetSelect(), 11);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitInven();
		CItemMgr::GetInstance()->CommitEquip();
		m_pMouse->Drop();
		m_pPlayer->Renew();
		Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
	}
	else if(iSuccess == 2)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
	}
}
void CInvenWindow::UpdateEquipmentPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
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
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 9);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 9);
			}
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_HELMS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwHelms) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(1) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 1);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 1);
			}
		}
	}
	// Shoulders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_SHOULDERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwShoulders) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(0) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 0);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 0);
			}
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_CHESTARMOR) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwChestArmor) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(4) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 4);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 4);
			}
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_BRACERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBracers) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(5) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 5);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 5);
			}
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_GLOVES) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwGloves) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(3) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 3);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 3);
			}
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_BELT) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBelt) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(7) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 7);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 7);
			}
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_PANTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwPants) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 10);
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_BOOTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBoots) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(12) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 12);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 12);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
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
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(2) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 2);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(6) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 6);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 6);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 8);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 8);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
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
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveInEquip(m_pMouse->GetSelect(), 11);
				else
					iSuccess = CItemMgr::GetInstance()->SwapInEquip(m_pMouse->GetSelect(), 11);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitInven();
		CItemMgr::GetInstance()->CommitEquip();
		m_pMouse->Drop();
		m_pPlayer->Renew();
		Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CItemMgr::GetInstance()->RollbackEquip();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
}
void CInvenWindow::UpdateStoragePickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// StorageWindow
	CStorageWindow* pStorageWindow = (CStorageWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORAGE);

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 9))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 9);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 9, -1, -1);
			}
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 1))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_HELMS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwHelms) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(1) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 1);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 1, -1, -1);
			}
		}
	}
	// Shoulders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 0))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_SHOULDERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwShoulders) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(0) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 0);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 0, -1, -1);
			}
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 4))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_CHESTARMOR) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwChestArmor) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(4) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 4);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 4, -1, -1);
			}
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 5))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BRACERS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBracers) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(5) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 5);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 5, -1, -1);
			}
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 3))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_GLOVES) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwGloves) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(3) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 3);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 3, -1, -1);
			}
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 7))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BELT) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBelt) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(7) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 7);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 7, -1, -1);
			}
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 10))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_PANTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwPants) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(10) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 10);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 10, -1, -1);
			}
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 12))
					iSuccess = 1;
				else
					iSuccess = 2;
			}
		}
		else if((pItem->dwItemType & ITEM_TYPE_BOOTS) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwBoots) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(12) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 12);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 12, -1, -1);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 2))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(2) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 2);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 2, -1, -1);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 6))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(6) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 6);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 6, -1, -1);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 8))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(8) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 8);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 8, -1, -1);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		if(pItem->dwItemType & ITEM_TYPE_GEM)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->EnchantStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 11))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(11) == NULL)
					iSuccess = CItemMgr::GetInstance()->MoveStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 11);
				else
					iSuccess = CItemMgr::GetInstance()->SwapStorageToEquip(pStorageWindow->GetPage(), m_pMouse->GetSelect(), 11, -1, -1);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitEquip();
		CItemMgr::GetInstance()->CommitStorage(pStorageWindow->GetPage());
		m_pMouse->Drop();
		m_pPlayer->Renew();
		Renew();
		pStorageWindow->Renew();
	}
	else if(iSuccess == 0)
	{
		CItemMgr::GetInstance()->RollbackEquip();
		CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
	}
	else if(iSuccess == 2)
	{
		CItemMgr::GetInstance()->RollbackEquip();
		CItemMgr::GetInstance()->RollbackStorage(pStorageWindow->GetPage());
		CUIMgr::GetInstance()->CreateTextMessage(_T("남는 소켓이 없습니다."));
	}
}
void CInvenWindow::UpdateStorePickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)) || 
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)) ||
		PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(CItemMgr::GetInstance()->GetGold() >= m_pMouse->GetItem()->iValue * m_pMouse->GetItem()->iNum)
			{
				if(CItemMgr::GetInstance()->BuyOfItem(m_pMouse->GetItem()))
				{
					// StoreWindow
					CStoreWindow* pStoreWindow = (CStoreWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_STORE);

					pStoreWindow->RemoveRepurchase(m_pMouse->GetSelect());
					CItemMgr::GetInstance()->CommitInven();
					m_pMouse->Drop();
					pStoreWindow->Renew();
					Renew();
				}
				else
				{
					CItemMgr::GetInstance()->RollbackInven();
					CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				}
			}
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("골드가 부족합니다."));
		}
	}
}
void CInvenWindow::UpdateDecomposePickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pMainWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(9);
			}
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(1) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pHelmsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.100333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(1);
			}
		}
	}
	// Sholders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(0) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSholdersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0565f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(0);
			}
		}
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(4) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pChestArmorBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0725f, 0.184333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(4);
			}
		}
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(5) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBracersBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(5);
			}
		}
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(3) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pGlovesBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.142333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(3);
			}
		}
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(7) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBeltBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0745f, 0.0473331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(7);
			}
		}
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(10) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pPantsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(10);
			}
		}
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(12) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pBootsBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.138333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(12);
			}
		}
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(2) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAmuletBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0465f, 0.0833331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pLeftRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(6);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pRightRingBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0355f, 0.0643331f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(8);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pSubWeaponBorderSign[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0575f, 0.218333f, 0.0f);

			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				CFactoryWindow* pFactoryWindow = (CFactoryWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FACTORY);
				pFactoryWindow->DecomposeInEquip(11);
			}
		}
	}
}
void CInvenWindow::UpdateFollowerEquipPickInEquip()
{
	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	// Item
	Item* pItem = m_pMouse->GetItem();

	// Success
	int iSuccess = -1;

	// MainWeapon
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.0131665f), &D3DXVECTOR2(0.740497f, 0.2314995f)))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL)
				{
					// EquipItem
					Item* pEquipItem = CItemMgr::GetInstance()->GetItemInEquip(9);

					// FollowerWindow
					CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

					// ID
					DWORD dwID = pFollowerWindow->GetID(0) | pFollowerWindow->GetID(1);

					if((pEquipItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
					else if(pEquipItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToEquip(m_pMouse->GetSelect(), 9);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveFollowerEquipToEquip(m_pMouse->GetSelect(), 9);
			}
		}
	}
	// Helms
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783997f, 0.5851625f), &D3DXVECTOR2(0.841497f, 0.6854955f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Shoulders
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.707497f, 0.5091625f), &D3DXVECTOR2(0.763997f, 0.6514955f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// ChestArmor
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.776496f, 0.3891645f), &D3DXVECTOR2(0.848996f, 0.5734975f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Bracers
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.884994f, 0.3451655f), &D3DXVECTOR2(0.942494f, 0.4874985f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Gloves
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.682997f, 0.3451655f), &D3DXVECTOR2(0.740497f, 0.4874985f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Belt
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.775496f, 0.32566565f), &D3DXVECTOR2(0.849996f, 0.37299855f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Pants
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.1721675f), &D3DXVECTOR2(0.841496f, 0.3105005f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Boots
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.783996f, 0.0201665f), &D3DXVECTOR2(0.841496f, 0.1584995f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
	}
	// Amulet
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.863495f, 0.53166345f), &D3DXVECTOR2(0.909995f, 0.61499655f)))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(2) != NULL)
				{
					// EquipItem
					Item* pEquipItem = CItemMgr::GetInstance()->GetItemInEquip(2);

					// FollowerWindow
					CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

					// ID
					DWORD dwID = pFollowerWindow->GetID(3);

					if((pEquipItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
					else if(pEquipItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToEquip(m_pMouse->GetSelect(), 2);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveFollowerEquipToEquip(m_pMouse->GetSelect(), 2);
			}
		}
	}
	// LeftRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.692997f, 0.25416645f), &D3DXVECTOR2(0.728497f, 0.31849955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(6) != NULL)
				{
					// EquipItem
					Item* pEquipItem = CItemMgr::GetInstance()->GetItemInEquip(6);

					// FollowerWindow
					CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

					// ID
					DWORD dwID = pFollowerWindow->GetID(4);

					if((pEquipItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
					else if(pEquipItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToEquip(m_pMouse->GetSelect(), 6);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveFollowerEquipToEquip(m_pMouse->GetSelect(), 6);
			}
		}
	}
	// RightRing
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.896994f, 0.25416645f), &D3DXVECTOR2(0.932494f, 0.31849955f)))
	{
		if((pItem->dwItemType & ITEM_TYPE_RING) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 장비 칸에 맞지 않는 아이템 유형입니다."));
		}
		else if((pItem->dwItemID & m_dwRing) == false)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
		}
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else 
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(8) != NULL)
				{
					// EquipItem
					Item* pEquipItem = CItemMgr::GetInstance()->GetItemInEquip(8);

					// FollowerWindow
					CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

					// ID
					DWORD dwID = pFollowerWindow->GetID(4);

					if((pEquipItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
					else if(pEquipItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToEquip(m_pMouse->GetSelect(), 8);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveFollowerEquipToEquip(m_pMouse->GetSelect(), 8);
			}
		}
	}
	// SubWeapon
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.885994f, 0.0131665f), &D3DXVECTOR2(0.943494f, 0.2314995f)))
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
		else if(pItem->iLevel > m_pPlayer->GetStat()->iLevel)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
		}
		else if(pItem->iGender != 2 && pItem->iGender != m_pPlayer->GetInfo()->iGender)
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
				CUIMgr::GetInstance()->CreateTextMessage(_T("성별이 맞지 않습니다."));
		}
		else
		{
			if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
			{
				if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL)
				{
					// EquipItem
					Item* pEquipItem = CItemMgr::GetInstance()->GetItemInEquip(11);

					// FollowerWindow
					CFollowerWindow* pFollowerWindow = (CFollowerWindow*)CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_FOLLOWER);

					// ID
					DWORD dwID = pFollowerWindow->GetID(0) | pFollowerWindow->GetID(2);

					if((pEquipItem->dwItemID & dwID) == false)
						CUIMgr::GetInstance()->CreateTextMessage(_T("지금 직업으로는 착용할 수 없습니다."));
					else if(pEquipItem->iLevel > m_pFollower->GetFollowerInfo()->stat.iLevel)
						CUIMgr::GetInstance()->CreateTextMessage(_T("레벨이 부족합니다."));
					else
						iSuccess = CItemMgr::GetInstance()->SwapFollowerEquipToEquip(m_pMouse->GetSelect(), 11);
				}
				else
					iSuccess = CItemMgr::GetInstance()->MoveFollowerEquipToEquip(m_pMouse->GetSelect(), 11);
			}
		}
	}

	// Check
	if(iSuccess == 1)
	{
		CItemMgr::GetInstance()->CommitInven();
		CItemMgr::GetInstance()->CommitFollowerEquip();
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_FOLLOWER);
		Renew();

		m_pMouse->Drop();
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

////////////////////////////////////////////////////////////////////////// InStat
void CInvenWindow::UpdateInStat()
{
}
void CInvenWindow::UpdateNonePickInStat()
{
	if(m_ButtonVec[1]->IsLUp())
	{
		if(CUIMgr::GetInstance()->GetWindow(WINDOW_TYPE_DETAIL) == NULL)
		{
			CObject* pWindow = new CDetailWindow(_T("DetailWindow"), OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pWindow, LAYER_TYPE_UI);
			pWindow->Initialize();
		}
		else
			CUIMgr::GetInstance()->DeleteWindow(WINDOW_TYPE_DETAIL);
	}
}
void CInvenWindow::UpdatePickInStat()
{
}
void CInvenWindow::UpdateInventoryPickInStat()
{
}
void CInvenWindow::UpdateEquipmentPickInStat()
{
}
void CInvenWindow::UpdateStoragePickInStat()
{
}
void CInvenWindow::UpdateStorePickInStat()
{
}
void CInvenWindow::UpdateDecomposePickInStat()
{
}
void CInvenWindow::UpdateFollowerEquipPickInStat()
{
}

////////////////////////////////////////////////////////////////////////// Share
Item* CInvenWindow::GetOverItemInInven()
{
	for(size_t i = 0; i < m_InvenSign.size(); ++i)
	{
		if(m_InvenSign[i]->IsOver())
			return m_InvenSign[i]->GetItem();
	}

	return NULL;
}

// GetOverItemInEquip
Item* CInvenWindow::GetOverItemInEquip()
{
	for(int i = 0; i < 13; ++i)
	{
		if(m_EquipSign[i] != NULL && m_EquipSign[i]->IsOver())
			return m_EquipSign[i]->GetItem();
	}

	return NULL;
}

DWORD CInvenWindow::GetID(int _iIndex)
{
	if(_iIndex == 0)
		return m_dwBothSide;
	else if(_iIndex == 1)
		return m_dwLeftSide;
	else if(_iIndex == 2)
		return m_dwRightSide;
	else if(_iIndex == 3)
		return m_dwShoulders;
	else if(_iIndex == 4)
		return m_dwHelms;
	else if(_iIndex == 5)
		return m_dwAmulet;
	else if(_iIndex == 6)
		return m_dwGloves;
	else if(_iIndex == 7)
		return m_dwChestArmor;
	else if(_iIndex == 8)
		return m_dwBracers;
	else if(_iIndex == 9)
		return m_dwRing;
	else if(_iIndex == 10)
		return m_dwBelt;
	else if(_iIndex == 11)
		return m_dwPants;
	else if(_iIndex == 12)
		return m_dwBoots;

	return 0;
}