#include "StdAfx.h"
#include "UIMgr.h"

IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr()
{
	// Enable
	m_bEnable = false;
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
}

int CUIMgr::Update()
{
	// Is Enable?
	if(!m_bEnable)
		return 0;

	return 0;
}

void CUIMgr::Render()
{
}

void CUIMgr::Release()
{
}

void CUIMgr::Enable()
{
	// Enable
	m_bEnable = true;

	CSlotWindow* pSlotWindow = new CSlotWindow(_T("SlotWindow"), OBJ_TYPE_STATIC);
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->AddObject(pSlotWindow);
	pSlotWindow->Initialize();
}

void CUIMgr::Disable()
{
	// Disable
	m_bEnable = false;

	for(int i = 0; i < WINDOW_TYPE_END; ++i)
		DeleteWindow((WINDOW_TYPE)i);
}

CObject* CUIMgr::GetWindow(WINDOW_TYPE _eWindowType)
{
	CObject* pWindow = NULL;
	switch(_eWindowType)
	{
	case WINDOW_TYPE_SLOT:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("SlotWindow"));
		break;
	case WINDOW_TYPE_SKILL:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("SkillWindow"));
		break;
	case WINDOW_TYPE_INVENTORY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("InventoryWindow"));
		break;
	case WINDOW_TYPE_STORAGE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("StorageWindow"));
		break;
	case WINDOW_TYPE_STORE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("StoreWindow"));
		break;
	case WINDOW_TYPE_FACTORY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("FactoryWindow"));
		break;
	case WINDOW_TYPE_ENCHANT:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("EnchantWindow"));
		break;
	case WINDOW_TYPE_SETTING:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("SettingWindow"));
		break;
	case WINDOW_TYPE_QUEST:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("QuestWindow"));
		break;
	case WINDOW_TYPE_ACHIEVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("AchieveWindow"));
		break;
	case WINDOW_TYPE_DETAIL:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DetailWindow"));
		break;
	case WINDOW_TYPE_FOLLOWER:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("FollowerWindow"));
		break;
	case WINDOW_TYPE_GATE_WAY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("GateWayWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_PRIMARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianPrimaryWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_SECONDARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianSecondaryWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_DEFENSIVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianDefensiveWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_MIGHT:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianMightWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_TACTICS:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianTacticsWindow"));
		break;
	case WINDOW_TYPE_BARBARIAN_RAGE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("BarbarianRageWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_PRIMARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterPrimaryWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_SECONDARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterSecondaryWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_DEFENSIVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterDefensiveWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_HUNTING:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterHuntingWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_DEVICES:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterDevicesWindow"));
		break;
	case WINDOW_TYPE_DEMONHUNTER_ARCHERY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("DemonHunterArcheryWindow"));
		break;
	case WINDOW_TYPE_MONK_PRIMARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkPrimaryWindow"));	
		break;
	case WINDOW_TYPE_MONK_SECONDARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkSecondaryWindow"));
		break;
	case WINDOW_TYPE_MONK_DEFENSIVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkDefensiveWindow"));	
		break;
	case WINDOW_TYPE_MONK_TECHNIQUES:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkTechniquesWindow"));	
		break;
	case WINDOW_TYPE_MONK_FOCUS:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkFocusWindow"));	
		break;
	case WINDOW_TYPE_MONK_MANTRAS:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("MonkMantrasWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_PRIMARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorPrimaryWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_SECONDARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorSecondaryWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorDefensiveWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_TERROR:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorTerrorWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_DECAY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorDecayWindow"));
		break;
	case WINDOW_TYPE_WITCHDOCTOR_VOODOO:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WitchDoctorVoodooWindow"));
		break;
	case WINDOW_TYPE_WIZARD_PRIMARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardPrimaryWindow"));	
		break;
	case WINDOW_TYPE_WIZARD_SECONDARY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardScondaryWindow"));		
		break;
	case WINDOW_TYPE_WIZARD_DEFENSIVE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardDefensiveWindow"));	
		break;
	case WINDOW_TYPE_WIZARD_FORCE:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardForceWindow"));
		break;
	case WINDOW_TYPE_WIZARD_CONJURATION:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardConjurationWindow"));
		break;
	case WINDOW_TYPE_WIZARD_MASTERY:
		CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pWindow, _T("WizardMasteryWindow"));	
		break;
	}

	return pWindow;
}

bool CUIMgr::NewWindow(WINDOW_TYPE _eWindowType, int _iIndex /*= -1*/, SLOT_ID _eSlotID /*= SLOT_ID_END*/)
{
	for(int i = 0; i < WINDOW_TYPE_END; ++i)
	{
		if(i == WINDOW_TYPE_SLOT)
			continue;

		DeleteWindow((WINDOW_TYPE)i);
	}

	CObject* pWindow;

	switch(_eWindowType)
	{
	case WINDOW_TYPE_SLOT:
		pWindow = new CSlotWindow(_T("SlotWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_SKILL:
		pWindow = new CSkillWindow(_T("SkillWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_INVENTORY:
		pWindow = new CInvenWindow(_T("InventoryWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_STORAGE:
		pWindow = new CStorageWindow(_T("StorageWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_STORE:
		pWindow = new CStoreWindow(_T("StoreWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_FACTORY:
		pWindow = new CFactoryWindow(_T("FactoryWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_ENCHANT:
		pWindow = new CEnchantWindow(_T("EnchantWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_SETTING:
		pWindow = new CSettingWindow(_T("SettingWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_QUEST:
		pWindow = new CQuestWindow(_T("QuestWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_ACHIEVE:
		pWindow = new CAchieveWindow(_T("AchieveWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_DETAIL:
		pWindow = new CDetailWindow(_T("DetailWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_FOLLOWER:
		pWindow = new CFollowerWindow(_T("FollowerWindow"), OBJ_TYPE_STATIC);
		break;
	case WINDOW_TYPE_GATE_WAY:
		pWindow = new CGateWayWindow(_T("GateWayWindow"), OBJ_TYPE_STATIC, (GATE_WAY_TYPE)_iIndex);
		break;
	case WINDOW_TYPE_BARBARIAN_PRIMARY:
		pWindow = new CBarbarianPrimaryWindow(_T("BarbarianPrimaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_BARBARIAN_SECONDARY:
		pWindow = new CBarbarianSecondaryWindow(_T("BarbarianSecondaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_BARBARIAN_DEFENSIVE:
		pWindow = new CBarbarianDefensiveWindow(_T("BarbarianDefensiveWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_BARBARIAN_MIGHT:
		pWindow = new CBarbarianMightWindow(_T("BarbarianMightWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_BARBARIAN_TACTICS:
		pWindow = new CBarbarianTacticsWindow(_T("BarbarianTacticsWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_BARBARIAN_RAGE:
		pWindow = new CBarbarianRageWindow(_T("BarbarianRageWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_PRIMARY:
		pWindow = new CDemonHunterPrimaryWindow(_T("DemonHunterPrimaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_SECONDARY:
		pWindow = new CDemonHunterSecondaryWindow(_T("DemonHunterSecondaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_DEFENSIVE:
		pWindow = new CDemonHunterDefensiveWindow(_T("DemonHunterDefensiveWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_HUNTING:
		pWindow = new CDemonHunterHuntingWindow(_T("DemonHunterHuntingWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_DEVICES:
		pWindow = new CDemonHunterDevicesWindow(_T("DemonHunterDevicesWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_DEMONHUNTER_ARCHERY:
		pWindow = new CDemonHunterArcheryWindow(_T("DemonHunterArcheryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_PRIMARY:
		pWindow = new CMonkPrimaryWindow(_T("MonkPrimaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_SECONDARY:
		pWindow = new CMonkSecondaryWindow(_T("MonkSecondaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_DEFENSIVE:
		pWindow = new CMonkDefensiveWindow(_T("MonkDefensiveWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_TECHNIQUES:
		pWindow = new CMonkTechniquesWindow(_T("MonkTechniquesWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_FOCUS:
		pWindow = new CMonkFocusWindow(_T("MonkFocusWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_MONK_MANTRAS:
		pWindow = new CMonkMantrasWindow(_T("MonkMantrasWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_PRIMARY:
		pWindow = new CWitchDoctorPrimaryWindow(_T("WitchDoctorPrimaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_SECONDARY:
		pWindow = new CWitchDoctorSecondaryWindow(_T("WitchDoctorSecondaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE:
		pWindow = new CWitchDoctorDefensiveWindow(_T("WitchDoctorDefensiveWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_TERROR:
		pWindow = new CWitchDoctorTerrorWindow(_T("WitchDoctorTerrorWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_DECAY:	
		pWindow = new CWitchDoctorDecayWindow(_T("WitchDoctorDecayWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WITCHDOCTOR_VOODOO:
		pWindow = new CWitchDoctorVoodooWindow(_T("WitchDoctorVoodooWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_PRIMARY:
		pWindow = new CWizardPrimaryWindow(_T("WizardPrimaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_SECONDARY:
		pWindow = new CWizardSecondaryWindow(_T("WizardScondaryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_DEFENSIVE:
		pWindow = new CWizardDefensiveWindow(_T("WizardDefensiveWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_FORCE:
		pWindow = new CWizardForceWindow(_T("WizardForceWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_CONJURATION:
		pWindow = new CWizardConjurationWindow(_T("WizardConjurationWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	case WINDOW_TYPE_WIZARD_MASTERY:
		pWindow = new CWizardMasteryWindow(_T("WizardMasteryWindow"), OBJ_TYPE_STATIC, _iIndex, _eSlotID);
		break;
	}

	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->AddObject(pWindow);
	pWindow->Initialize();

	return true;
}

bool CUIMgr::DeleteWindow(WINDOW_TYPE _eWindowType)
{
	CObject* pWindow = GetWindow(_eWindowType);
	if(pWindow == NULL)
		return false;

	pWindow->Destroy();
	return true;
}

bool CUIMgr::DeleteLeftWindow()
{
	DeleteWindow(WINDOW_TYPE_STORAGE);
	DeleteWindow(WINDOW_TYPE_STORE);
	DeleteWindow(WINDOW_TYPE_FACTORY);
	DeleteWindow(WINDOW_TYPE_ENCHANT);
	DeleteWindow(WINDOW_TYPE_QUEST);
	DeleteWindow(WINDOW_TYPE_ACHIEVE);
	DeleteWindow(WINDOW_TYPE_FOLLOWER);
	DeleteWindow(WINDOW_TYPE_GATE_WAY);

	return true;
}

bool CUIMgr::DeleteRightWindow()
{
	DeleteWindow(WINDOW_TYPE_INVENTORY);
	DeleteWindow(WINDOW_TYPE_DETAIL);

	return true;
}

bool CUIMgr::DeleteCenterWindow()
{
	DeleteWindow(WINDOW_TYPE_SKILL);
	DeleteWindow(WINDOW_TYPE_SETTING);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_PRIMARY);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_SECONDARY);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_MIGHT);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_TACTICS);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_RAGE);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_SECONDARY);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_HUNTING);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_ARCHERY);
	DeleteWindow(WINDOW_TYPE_MONK_PRIMARY);
	DeleteWindow(WINDOW_TYPE_MONK_SECONDARY);
	DeleteWindow(WINDOW_TYPE_MONK_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_MONK_TECHNIQUES);
	DeleteWindow(WINDOW_TYPE_MONK_FOCUS);
	DeleteWindow(WINDOW_TYPE_MONK_MANTRAS);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_PRIMARY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_SECONDARY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_TERROR);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_DECAY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_VOODOO);
	DeleteWindow(WINDOW_TYPE_WIZARD_PRIMARY);
	DeleteWindow(WINDOW_TYPE_WIZARD_SECONDARY);
	DeleteWindow(WINDOW_TYPE_WIZARD_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_WIZARD_FORCE);
	DeleteWindow(WINDOW_TYPE_WIZARD_CONJURATION);
	DeleteWindow(WINDOW_TYPE_WIZARD_MASTERY);

	return true;
}

bool CUIMgr::DeleteAllWindow()
{
	DeleteWindow(WINDOW_TYPE_SKILL);
	DeleteWindow(WINDOW_TYPE_INVENTORY);
	DeleteWindow(WINDOW_TYPE_STORAGE);
	DeleteWindow(WINDOW_TYPE_STORE);
	DeleteWindow(WINDOW_TYPE_FACTORY);
	DeleteWindow(WINDOW_TYPE_ENCHANT);
	DeleteWindow(WINDOW_TYPE_SETTING);
	DeleteWindow(WINDOW_TYPE_QUEST);
	DeleteWindow(WINDOW_TYPE_ACHIEVE);
	DeleteWindow(WINDOW_TYPE_DETAIL);
	DeleteWindow(WINDOW_TYPE_FOLLOWER);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_PRIMARY);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_SECONDARY);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_MIGHT);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_TACTICS);
	DeleteWindow(WINDOW_TYPE_BARBARIAN_RAGE);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_SECONDARY);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_HUNTING);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES);
	DeleteWindow(WINDOW_TYPE_DEMONHUNTER_ARCHERY);
	DeleteWindow(WINDOW_TYPE_MONK_PRIMARY);
	DeleteWindow(WINDOW_TYPE_MONK_SECONDARY);
	DeleteWindow(WINDOW_TYPE_MONK_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_MONK_TECHNIQUES);
	DeleteWindow(WINDOW_TYPE_MONK_FOCUS);
	DeleteWindow(WINDOW_TYPE_MONK_MANTRAS);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_PRIMARY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_SECONDARY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_TERROR);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_DECAY);
	DeleteWindow(WINDOW_TYPE_WITCHDOCTOR_VOODOO);
	DeleteWindow(WINDOW_TYPE_WIZARD_PRIMARY);
	DeleteWindow(WINDOW_TYPE_WIZARD_SECONDARY);
	DeleteWindow(WINDOW_TYPE_WIZARD_DEFENSIVE);
	DeleteWindow(WINDOW_TYPE_WIZARD_FORCE);
	DeleteWindow(WINDOW_TYPE_WIZARD_CONJURATION);
	DeleteWindow(WINDOW_TYPE_WIZARD_MASTERY);

	return true;
}

bool CUIMgr::RenewWindow(WINDOW_TYPE _eWindowType)
{
	CObject* pWindow = GetWindow(_eWindowType);
	if(pWindow == NULL)
		return false;

	((CWindowUI*)pWindow)->Renew();
	return true;
}

bool CUIMgr::CreateTextMessage(TCHAR* _tszText)
{
	CObject* pFindObject = NULL;
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->FindObject(pFindObject, _T("TextMessage"));
	if(pFindObject != NULL)
	{
		CTextMessage* pTextMessage = (CTextMessage*)pFindObject;
		if(_tcscmp(pTextMessage->GetText(), _tszText) == 0)
			return true;

		pFindObject->Destroy();
	}

	CTextMessage* pTextMessage = new CTextMessage(_T("TextMessage"), OBJ_TYPE_DYNAMIC, _tszText);
	CSceneMgr::GetInstance()->GetScene()->GetLayer(LAYER_TYPE_UI)->AddObject(pTextMessage);
	pTextMessage->Initialize();

	return true;
}