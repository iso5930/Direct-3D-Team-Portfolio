#include "StdAfx.h"
#include "SkillWindow.h"

CSkillWindow::CSkillWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Skill"))
{
	// Text
	for(int i = 0; i < 6; ++i)
		ZeroMemory(m_tszText[i], sizeof(m_tszText[i]));

	// Rect
	SetRect(&m_rcText[0], 459, 224, 559, 244);
	SetRect(&m_rcText[1], 717, 224, 817, 244);
	SetRect(&m_rcText[2], 459, 310, 559, 330);
	SetRect(&m_rcText[3], 717, 310, 817, 330);
	SetRect(&m_rcText[4], 459, 119, 559, 139);
	SetRect(&m_rcText[5], 717, 119, 817, 139);

	// SkillButton
	ZeroMemory(m_pSkillButton, sizeof(m_pSkillButton));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.03f, 1.5782f, 0.0f);
}

CSkillWindow::~CSkillWindow()
{
	Release();
}

void CSkillWindow::Initialize()
{
	CWindowUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.477f, 0.851f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);

	// CloseButton(1)
	CBasicButton* pCloseButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Close"), _T("Button_Over_Close"), _T("Button_Down_Close"));
	m_pLayer->AddObject(pCloseButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCloseButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.485f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2444f, 0.0838f, 0.0f);
	pCloseButton->Initialize();
	AddButton(pCloseButton);

	// Renew
	Renew();
}

int CSkillWindow::Update()
{
	CWindowUI::Update();

	CUpdateCom* pUpdateCom;
	CRenderCom* pRenderCom;
	for(int i = 0; i < 6; ++i)
	{
		pUpdateCom = (CUpdateCom*)m_pSkillButton[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF6;

		pRenderCom = (CRenderCom*)m_pSkillButton[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000009;
	}

	if(m_ButtonVec[0]->IsLUp() || m_ButtonVec[1]->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_ESCAPE))
	{
		for(int i = 0; i < WINDOW_TYPE_END; ++i)
		{
			if(i == WINDOW_TYPE_SLOT)
				continue;

			if(CUIMgr::GetInstance()->GetWindow((WINDOW_TYPE)i) != NULL)
			{
				CInputMgr::GetInstance()->KeyInvalidate(DIK_ESCAPE);
				CUIMgr::GetInstance()->DeleteWindow((WINDOW_TYPE)i);
			}
		}
	}

	for(int i = 0; i < 6; ++i)
	{
		if(m_pSkillButton[i]->IsLUp())
		{
			switch(m_pSkillButton[i]->GetSlotType())
			{
			case SLOT_TYPE_BARBARIAN_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_PRIMARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_SECONDARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_DEFENSIVE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_MIGHT:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_MIGHT, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_TACTICS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_TACTICS, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_BARBARIAN_RAGE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_BARBARIAN_RAGE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_PRIMARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_SECONDARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_DEFENSIVE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_HUNTING:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_HUNTING, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_DEVICES:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_DEVICES, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_DEMONHUNTER_ARCHERY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_DEMONHUNTER_ARCHERY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_PRIMARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_SECONDARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_DEFENSIVE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_TECHNIQUES:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_TECHNIQUES, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_FOCUS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_FOCUS, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_MONK_MANTRAS:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_MONK_MANTRAS, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_PRIMARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_SECONDARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_DEFENSIVE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_TERROR:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_TERROR, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_DECAY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_DECAY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WITCHDOCTOR_VOODOO:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WITCHDOCTOR_VOODOO, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_PRIMARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_PRIMARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_SECONDARY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_SECONDARY, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_DEFENSIVE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_DEFENSIVE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_FORCE:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_FORCE, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_CONJURATION:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_CONJURATION, i, m_pSkillButton[i]->GetSlotID());
				break;
			case SLOT_TYPE_WIZARD_MASTERY:
				CUIMgr::GetInstance()->NewWindow(WINDOW_TYPE_WIZARD_MASTERY, i, m_pSkillButton[i]->GetSlotID());
				break;
			}
		}
	}

	return 0;
}

void CSkillWindow::Render()
{
	CWindowUI::Render();

	for(int i = 0; i < 6; ++i)
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText[i], -1, &m_rcText[i], DT_CENTER, D3DXCOLOR(0.7686f, 0.698f, 0.501f, 1.0f));
}

void CSkillWindow::Release()
{
	// SkillButton
	for(int i = 0; i < 6; ++i)
	{
		if(m_pSkillButton[i] != NULL)
		{
			m_pSkillButton[i]->Destroy();
			m_pSkillButton[i] = NULL;
		}
	}
}

void CSkillWindow::Renew()
{
	// SkillButton Clear
	for(int i = 0; i < 6; ++i)
	{
		if(m_pSkillButton[i] != NULL)
		{
			m_pSkillButton[i]->Destroy();
			m_pSkillButton[i] = NULL;
		}
	}

	// Player
	CObject* pPlayer = NULL;
	m_pLayer->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	CSlot* pSlot;
	CTransformCom* pTransformCom;
	for(int i = 0; i < 6; ++i)
	{
		pSlot = ((CPlayer*)pPlayer)->GetSlot(i);

		switch(pSlot->GetSlotType())
		{
		case SLOT_TYPE_BARBARIAN_PRIMARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("주 기술"));
			break;
		case SLOT_TYPE_BARBARIAN_SECONDARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("보조 기술"));
			break;
		case SLOT_TYPE_BARBARIAN_DEFENSIVE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("방어"));
			break;
		case SLOT_TYPE_BARBARIAN_MIGHT:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("무력"));
			break;
		case SLOT_TYPE_BARBARIAN_TACTICS:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("전술"));
			break;
		case SLOT_TYPE_BARBARIAN_RAGE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("격노"));
			break;
		case SLOT_TYPE_DEMONHUNTER_PRIMARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("주 기술"));
			break;
		case SLOT_TYPE_DEMONHUNTER_SECONDARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("보조 기술"));
			break;
		case SLOT_TYPE_DEMONHUNTER_DEFENSIVE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("방어"));
			break;
		case SLOT_TYPE_DEMONHUNTER_HUNTING:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("사냥"));
			break;
		case SLOT_TYPE_DEMONHUNTER_DEVICES:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("장치"));
			break;
		case SLOT_TYPE_DEMONHUNTER_ARCHERY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("궁술"));
			break;
		case SLOT_TYPE_MONK_PRIMARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("주 기술"));
			break;
		case SLOT_TYPE_MONK_SECONDARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("보조 기술"));
			break;
		case SLOT_TYPE_MONK_DEFENSIVE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("방어"));
			break;
		case SLOT_TYPE_MONK_TECHNIQUES:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("무예"));
			break;
		case SLOT_TYPE_MONK_FOCUS:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("집중"));
			break;
		case SLOT_TYPE_MONK_MANTRAS:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("진언"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_PRIMARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("주 기술"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_SECONDARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("보조 기술"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_DEFENSIVE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("방어"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_TERROR:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("공황"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_DECAY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("부패"));
			break;
		case SLOT_TYPE_WITCHDOCTOR_VOODOO:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("부두"));
			break;
		case SLOT_TYPE_WIZARD_PRIMARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("주 기술"));
			break;
		case SLOT_TYPE_WIZARD_SECONDARY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("보조 기술"));
			break;
		case SLOT_TYPE_WIZARD_DEFENSIVE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("방어"));
			break;
		case SLOT_TYPE_WIZARD_FORCE:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("위력"));
			break;
		case SLOT_TYPE_WIZARD_CONJURATION:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("창조"));
			break;
		case SLOT_TYPE_WIZARD_MASTERY:
			_tcscpy_s(m_tszText[i], MIN_STR, _T("통달"));
			break;
		}

		// SkillButton
		m_pSkillButton[i] = new CSkillButton(NULL, OBJ_TYPE_STATIC, pSlot->GetSlotType(), pSlot->GetSlotID());
		m_pLayer->AddObject(m_pSkillButton[i], LAYER_TYPE_UI);
		pTransformCom = (CTransformCom*)m_pSkillButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		if(i == 0)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(-0.207f, 0.257f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}
		else if(i == 1)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(0.195f, 0.257f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}
		else if(i == 2)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(-0.207f, 0.018f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}
		else if(i == 3)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(0.195f, 0.018f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}
		else if(i == 4)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(-0.207f, 0.551f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}
		else if(i == 5)
		{
			pTransformCom->m_vPos = D3DXVECTOR3(0.195f, 0.551f, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.3802f, 0.1866f, 0.0f);
		}

		m_pSkillButton[i]->Initialize();
	}
}