#include "StdAfx.h"
#include "FactoryWindow.h"

CFactoryWindow::CFactoryWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, NULL)
{
	// Texture
	m_pTexture[0] = CTextureMgr::GetInstance()->GetTexture(_T("Window_WeaponFactory"));
	m_pTexture[1] = CTextureMgr::GetInstance()->GetTexture(_T("Window_ArmorFactory"));
	m_pTexture[2] = CTextureMgr::GetInstance()->GetTexture(_T("Window_DecompositionFactory"));
	m_pBackTexture = m_pTexture[0];

	// Page
	m_iPage = 0;

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;

	// Type
	m_iType = -1;

	// Select
	m_iSelect = -1;

	// Mouse
	m_pMouse = NULL;

	// Player
	m_pPlayer = NULL;

	// FactoryButton
	ZeroMemory(m_pFactoryButton, sizeof(m_pFactoryButton));

	// WeaponCategoryButton
	ZeroMemory(m_pWeaponCategoryButton, sizeof(m_pWeaponCategoryButton));

	// ArmorCategoryButton
	ZeroMemory(m_pArmorCategoryButton, sizeof(m_pArmorCategoryButton));

	// VScroll
	m_pVScroll = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CFactoryWindow::~CFactoryWindow()
{
	Release();
}

void CFactoryWindow::Initialize()
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

	// WeaponFactoryButton
	m_pFactoryButton[0] = new CFactoryButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_WeaponFactory"), _T("Button_Over_WeaponFactory"), _T("Button_Down_WeaponFactory"));
	m_pLayer->AddObject(m_pFactoryButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFactoryButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.532f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pFactoryButton[0]->SetState(UI_L_DOWN);
	m_pFactoryButton[0]->Initialize();

	// ArmorFactoryButton
	m_pFactoryButton[1] = new CFactoryButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ArmorFactory"), _T("Button_Over_ArmorFactory"), _T("Button_Down_ArmorFactory"));
	m_pLayer->AddObject(m_pFactoryButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFactoryButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.332f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pFactoryButton[1]->Initialize();

	// DecompositionFactoryButton
	m_pFactoryButton[2] = new CFactoryButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_DecompositionFactory"), _T("Button_Over_DecompositionFactory"), _T("Button_Down_DecompositionFactory"));
	m_pLayer->AddObject(m_pFactoryButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFactoryButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.132f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pFactoryButton[2]->Initialize();

	// WeaponCategoryButton
	TCHAR tszWeaponCategory[21][MIN_STR];
	_tcscpy_s(tszWeaponCategory[0], MIN_STR, _T("도끼"));
	_tcscpy_s(tszWeaponCategory[1], MIN_STR, _T("활"));
	_tcscpy_s(tszWeaponCategory[2], MIN_STR, _T("의식용칼"));
	_tcscpy_s(tszWeaponCategory[3], MIN_STR, _T("너클"));
	_tcscpy_s(tszWeaponCategory[4], MIN_STR, _T("손쇠뇌"));
	_tcscpy_s(tszWeaponCategory[5], MIN_STR, _T("철퇴"));
	_tcscpy_s(tszWeaponCategory[6], MIN_STR, _T("폴암"));
	_tcscpy_s(tszWeaponCategory[7], MIN_STR, _T("화살통"));
	_tcscpy_s(tszWeaponCategory[8], MIN_STR, _T("한손거대무기"));
	_tcscpy_s(tszWeaponCategory[9], MIN_STR, _T("두손거대무기"));
	_tcscpy_s(tszWeaponCategory[10], MIN_STR, _T("방패"));
	_tcscpy_s(tszWeaponCategory[11], MIN_STR, _T("창"));
	_tcscpy_s(tszWeaponCategory[12], MIN_STR, _T("지팡이"));
	_tcscpy_s(tszWeaponCategory[13], MIN_STR, _T("검"));
	_tcscpy_s(tszWeaponCategory[14], MIN_STR, _T("양손도끼"));
	_tcscpy_s(tszWeaponCategory[15], MIN_STR, _T("양손철퇴"));
	_tcscpy_s(tszWeaponCategory[16], MIN_STR, _T("양손검"));
	_tcscpy_s(tszWeaponCategory[17], MIN_STR, _T("완드"));
	_tcscpy_s(tszWeaponCategory[18], MIN_STR, _T("액막이"));
	_tcscpy_s(tszWeaponCategory[19], MIN_STR, _T("석궁"));
	_tcscpy_s(tszWeaponCategory[20], MIN_STR, _T("오브"));

	for(int i = 0; i < 21; ++i)
	{
		m_pWeaponCategoryButton[i] = new CCategoryButton(NULL, OBJ_TYPE_STATIC, tszWeaponCategory[i]);
		m_pLayer->AddObject(m_pWeaponCategoryButton[i], LAYER_TYPE_UI);
		m_pWeaponCategoryButton[i]->Initialize();
	}

	// ArmorCategoryButton
	TCHAR tszArmorCategory[8][MIN_STR];
	_tcscpy_s(tszArmorCategory[0], MIN_STR, _T("모자"));
	_tcscpy_s(tszArmorCategory[1], MIN_STR, _T("어깨보호대"));
	_tcscpy_s(tszArmorCategory[2], MIN_STR, _T("흉갑"));
	_tcscpy_s(tszArmorCategory[3], MIN_STR, _T("손목보호대"));
	_tcscpy_s(tszArmorCategory[4], MIN_STR, _T("장갑"));
	_tcscpy_s(tszArmorCategory[5], MIN_STR, _T("벨트"));
	_tcscpy_s(tszArmorCategory[6], MIN_STR, _T("바지"));
	_tcscpy_s(tszArmorCategory[7], MIN_STR, _T("신발"));

	for(int i = 0; i < 8; ++i)
	{
		m_pArmorCategoryButton[i] = new CCategoryButton(NULL, OBJ_TYPE_STATIC, tszArmorCategory[i]);
		m_pLayer->AddObject(m_pArmorCategoryButton[i], LAYER_TYPE_UI);
		m_pArmorCategoryButton[i]->Initialize();
	}

	// DecomposeButton(1)
	CBasicButton* pDecomposeButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Decompose"), _T("Button_Over_Decompose"), _T("Button_Down_Decompose"));
	m_pLayer->AddObject(pDecomposeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDecomposeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.83f, 0.38f, 0.0f);
	pDecomposeButton->Initialize();
	AddButton(pDecomposeButton);

	// DecomposeNormalButton(2)
	CBasicButton* pDecomposeNormalButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_DecomposeNormal"), _T("Button_Over_DecomposeNormal"), _T("Button_Down_DecomposeNormal"));
	m_pLayer->AddObject(pDecomposeNormalButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDecomposeNormalButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.745f, 0.423f, 0.0f);
	pDecomposeNormalButton->Initialize();
	AddButton(pDecomposeNormalButton);

	// DecomposeMagicButton(3)
	CBasicButton* pDecomposeMagicButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_DecomposeMagic"), _T("Button_Over_DecomposeMagic"), _T("Button_Down_DecomposeMagic"));
	m_pLayer->AddObject(pDecomposeMagicButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDecomposeMagicButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.69f, 0.423f, 0.0f);
	pDecomposeMagicButton->Initialize();
	AddButton(pDecomposeMagicButton);

	// DecomposeUniqueButton(4)
	CBasicButton* pDecomposeUniqueButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_DecomposeUnique"), _T("Button_Over_DecomposeUnique"), _T("Button_Down_DecomposeUnique"));
	m_pLayer->AddObject(pDecomposeUniqueButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDecomposeUniqueButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.635f, 0.423f, 0.0f);
	pDecomposeUniqueButton->Initialize();
	AddButton(pDecomposeUniqueButton);

	// ScrollUpButton(5)
	CBasicButton* pScrollUpButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Up"), _T("Button_Over_Up"), _T("Button_Down_Up"));
	m_pLayer->AddObject(pScrollUpButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, 0.568997f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollUpButton->Initialize();
	AddButton(pScrollUpButton);

	// ScrollDownButton(6)
	CBasicButton* pScrollDownButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Down"), _T("Button_Over_Down"), _T("Button_Down_Down"));
	m_pLayer->AddObject(pScrollDownButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, -0.0189988f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollDownButton->Initialize();
	AddButton(pScrollDownButton);

	// VScroll
	m_pVScroll = new CVScroll(NULL, OBJ_TYPE_STATIC);
	m_pLayer->AddObject(m_pVScroll, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos.x = -0.535f;
	pTransformCom->m_vSize.x = 0.025f;
	//m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.5499982f, 0.0f);
	m_pVScroll->Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pVScroll->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pVScroll->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;

	// ItemMakeButton(7)
	CBasicButton* pItemMakeButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ItemMake"), _T("Button_Over_ItemMake"), _T("Button_Down_ItemMake"));
	m_pLayer->AddObject(pItemMakeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pItemMakeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.677998f, -0.422997f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);
	pItemMakeButton->Initialize();
	AddButton(pItemMakeButton);

	Renew();
}

int CFactoryWindow::Update()
{
	// Mouse
	CObject* pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Mouse"), LAYER_TYPE_MOUSE);
	m_pMouse = (CMouse*)pFind;

	// Player
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Player"), LAYER_TYPE_PLAYER);
	m_pPlayer = (CPlayer*)pFind;

	// WeaponeItemSign
	for(size_t i = 0; i < m_WeaponItemSign.size(); ++i)
	{
		if(m_WeaponItemSign[i]->IsOver())
			m_WeaponItemSign[i]->EnableItemMessage();
		else
			m_WeaponItemSign[i]->DisableItemMessage();
	}

	// ArmorItemSign
	for(size_t i = 0; i < m_ArmorItemSign.size(); ++i)
	{
		if(m_ArmorItemSign[i]->IsOver())
			m_ArmorItemSign[i]->EnableItemMessage();
		else
			m_ArmorItemSign[i]->DisableItemMessage();
	}

	// DecomposeItemSign
	for(size_t i = 0; i < m_DecomposeItemSign.size(); ++i)
	{
		if(m_DecomposeItemSign[i]->IsOver())
			m_DecomposeItemSign[i]->EnableItemMessage();
		else
			m_DecomposeItemSign[i]->DisableItemMessage();
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

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInFactory();
				UpdatePickInFactory();
				UpdateNonePickInFactory();
			}
			break;

		case 4:
			UpdatePick();
			UpdateDecomposePick();
			UpdatePickIn();
			UpdateDecomposePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInFactory();
				UpdatePickInFactory();
				UpdateDecomposePickInFactory();
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

		case 4:
			UpdatePick();
			UpdateDecomposePick();
			UpdatePickOut();
			UpdateDecomposePickOut();
			break;
		}
	}

	// FactoryButton
	for(int i = 0; i < 3; ++i)
		m_pFactoryButton[i]->SetState(0);

	m_pFactoryButton[m_iPage]->SetState(UI_L_DOWN);

	// Select
	if(m_iType != -1 && m_iSelect != -1)
	{
		if(m_iPage == 0)
			m_WeaponFormulaButton[m_iType][m_iSelect]->SetState(UI_L_DOWN);
		else
			m_ArmorFormulaButton[m_iType][m_iSelect]->SetState(UI_L_DOWN);
	}

	// Scroll
	if(m_iScroll != m_pVScroll->GetScroll())
	{
		m_iScroll = m_pVScroll->GetScroll();
		UpdateScroll();

		if(m_iPage == 0)
			UpdateWeaponCategory();
		else if(m_iPage == 1)
			UpdateArmorCategory();
	}

	CWindowUI::Update();

	return 0;
}

void CFactoryWindow::Render()
{
	CWindowUI::Render();

	TCHAR tszGold[MIN_STR];
	_itot_s(CItemMgr::GetInstance()->GetGold(), tszGold, 10);

	// Gold
	RECT rcText;
	SetRect(&rcText, 96, 551, 296, 563);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszGold, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	if(m_WeaponItemSign.size() > 0)
	{
		SetRect(&rcText, 71, 429, 171, 441);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("필요한 재료"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.031372f, 0.00392156f, 0.00784313f, 1.0f));
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_WeaponFormula[m_iType][m_iSelect]->pItem->tszName, -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
	else if(m_ArmorItemSign.size() > 0)
	{
		SetRect(&rcText, 71, 429, 171, 441);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("필요한 재료"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.031372f, 0.00392156f, 0.00784313f, 1.0f));
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_ArmorFormula[m_iType][m_iSelect]->pItem->tszName, -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
	else if(m_iPage != 2)
	{
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, _T("제조법을 선택하면 자세한 정보를 확인할 수 있습니다."), -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}

	// DecomposeItem
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		TCHAR tszDecompose[MIN_STR];
		StringCbPrintf(tszDecompose, sizeof(tszDecompose), _T("%s x %d"), m_DecomposeItem[i]->tszName, m_DecomposeItem[i]->iNum);

		SetRect(&rcText, 125, 335 + 36 * i, 425, 351 + 36 * i);
		CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, tszDecompose, -1, &rcText, DT_LEFT, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
}

void CFactoryWindow::Release()
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

	// FactoryButton
	for(int i = 0; i < 3; ++i)
	{
		if(m_pFactoryButton[i] != NULL)
		{
			m_pFactoryButton[i]->Destroy();
			m_pFactoryButton[i] = NULL;
		}
	}

	// WeaponFormula
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormula[i].size(); ++j)
		{
			delete m_WeaponFormula[i][j];
			m_WeaponFormula[i][j] = NULL;
		}
		m_WeaponFormula[i].clear();
	}

	// ArmorFormula
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormula[i].size(); ++j)
		{
			delete m_ArmorFormula[i][j];
			m_ArmorFormula[i][j] = NULL;
		}
		m_ArmorFormula[i].clear();
	}

	// WeaponCategoryButton
	for(int i = 0; i < 21; ++i)
	{
		if(m_pWeaponCategoryButton[i] != NULL)
		{
			m_pWeaponCategoryButton[i]->Destroy();
			m_pWeaponCategoryButton[i] = NULL;
		}
	}

	// ArmorCategoryButton
	for(int i = 0; i < 8; ++i)
	{
		if(m_pArmorCategoryButton[i] != NULL)
		{
			m_pArmorCategoryButton[i]->Destroy();
			m_pArmorCategoryButton[i] = NULL;
		}
	}

	// WeaponFormulaButton
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			m_WeaponFormulaButton[i][j]->Destroy();
			m_WeaponFormulaButton[i][j] = NULL;
		}
		m_WeaponFormulaButton[i].clear();
	}

	// ArmorFormulaButton
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			m_ArmorFormulaButton[i][j]->Destroy();
			m_ArmorFormulaButton[i][j] = NULL;
		}
		m_ArmorFormulaButton[i].clear();
	}

	// WeaponItemSign
	for(size_t i = 0; i < m_WeaponItemSign.size(); ++i)
	{
		m_WeaponItemSign[i]->Destroy();
		m_WeaponItemSign[i] = NULL;
	}
	m_WeaponItemSign.clear();

	// ArmorItemSign
	for(size_t i = 0; i < m_ArmorItemSign.size(); ++i)
	{
		m_ArmorItemSign[i]->Destroy();
		m_ArmorItemSign[i] = NULL;
	}
	m_ArmorItemSign.clear();

	// DecomposeItem
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		delete m_DecomposeItem[i];
		m_DecomposeItem[i] = NULL;
	}
	m_DecomposeItem.clear();

	// DecomposeItemSign
	for(size_t i = 0; i < m_DecomposeItemSign.size(); ++i)
	{
		m_DecomposeItemSign[i]->Destroy();
		m_DecomposeItemSign[i] = NULL;
	}
	m_DecomposeItemSign.clear();

	// VScroll
	if(m_pVScroll != NULL)
	{
		m_pVScroll->Destroy();
		m_pVScroll = NULL;
	}
}

void CFactoryWindow::Renew()
{
	// BackTexture
	m_pBackTexture = m_pTexture[m_iPage];

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;

	// Type
	m_iType = -1;

	// Select
	m_iSelect = -1;

	// WeaponCategoryButton
	for(int i = 0; i < 21; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pWeaponCategoryButton[i]->Close();
	}

	// ArmorCategoryButton
	for(int i = 0; i < 8; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pArmorCategoryButton[i]->Close();
	}

	// WeaponFormulaButton
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			m_WeaponFormulaButton[i][j]->Destroy();
			m_WeaponFormulaButton[i][j] = NULL;
		}
		m_WeaponFormulaButton[i].clear();
	}

	// ArmorFormulaButton
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			m_ArmorFormulaButton[i][j]->Destroy();
			m_ArmorFormulaButton[i][j] = NULL;
		}
		m_ArmorFormulaButton[i].clear();
	}

	// WeaponItemSign
	for(size_t i = 0; i < m_WeaponItemSign.size(); ++i)
	{
		m_WeaponItemSign[i]->Destroy();
		m_WeaponItemSign[i] = NULL;
	}
	m_WeaponItemSign.clear();

	// ArmorItemSign
	for(size_t i = 0; i < m_ArmorItemSign.size(); ++i)
	{
		m_ArmorItemSign[i]->Destroy();
		m_ArmorItemSign[i] = NULL;
	}
	m_ArmorItemSign.clear();

	// DecomposeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// DecomposeNormalButton
	pTransformCom = (CTransformCom*)m_ButtonVec[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// DecomposeMagicButton
	pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// DecomposeUniqueButton
	pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ItemMakeButton
	pTransformCom = (CTransformCom*)m_ButtonVec[7]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if(m_iPage == 0)
	{
		// Scroll
		m_iScroll = 0;

		// MaxScroll
		m_iMaxScroll = 5;

		// WeaponCategoryButton
		for(int i = 0; i < 16; ++i)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * i, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}
	}
	else if(m_iPage == 1)
	{
		// Scroll
		m_iScroll = 0;

		// MaxScroll
		m_iMaxScroll = 0;

		// ArmorCategoryButton
		for(int i = 0; i < 8; ++i)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * i, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}
	}
	else if(m_iPage == 2)
	{
		// Scroll
		m_iScroll = 0;

		// MaxScroll
		m_iMaxScroll = 0;

		// DecomposeButton
		pTransformCom = (CTransformCom*)m_ButtonVec[1]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.105f, 0.172f, 0.0f);

		// DecomposeNormalButton
		pTransformCom = (CTransformCom*)m_ButtonVec[2]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0525f, 0.086f, 0.0f);

		// DecomposeMagicButton
		pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0525f, 0.086f, 0.0f);

		// DecomposeUniqueButton
		pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0525f, 0.086f, 0.0f);

		// ItemSign
		for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
		{
			CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, m_DecomposeItem[i]);
			m_pLayer->AddObject(pItemSign);

			CTransformCom* pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize.x = m_DecomposeItem[i]->iWidth * 0.0525f;
			pTransformCom->m_vSize.y = m_DecomposeItem[i]->iHeight * 0.09216667f;
			pTransformCom->m_vPos = D3DXVECTOR3(-0.85f, i * -0.1f + 0.05f, 0.0f);

			pItemSign->Initialize();
			m_DecomposeItemSign.push_back(pItemSign);
		}
	}

	// UpdateScroll
	UpdateScroll();
}

////////////////////////////////////////////////////////////////////////// Category
void CFactoryWindow::OpenWeaponCategory(int _iIndex)
{
	// Add
	for(size_t i = 0; i < m_WeaponFormula[_iIndex].size(); ++i)
	{
		CFormulaButton* pFormulaButton = new CFormulaButton(NULL, OBJ_TYPE_STATIC, m_WeaponFormula[_iIndex][i]);
		m_pLayer->AddObject(pFormulaButton, LAYER_TYPE_UI);
		pFormulaButton->Initialize();
		m_WeaponFormulaButton[_iIndex].push_back(pFormulaButton);
	}

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 21; ++i)
		m_iMaxScroll = m_iMaxScroll + m_WeaponFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// WeaponCategoryButton Init
	for(int i = 0; i < 21; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// WeaponFormulaButton Init
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 21 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// WeaponCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_WeaponFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// WeaponFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CFactoryWindow::CloseWeaponCategory(int _iIndex)
{
	// NoneSelect
	if(_iIndex == m_iType)
	{
		m_iType = -1;
		m_iSelect = -1;

		// WeaponItemSign
		for(size_t i = 0; i < m_WeaponItemSign.size(); ++i)
		{
			m_WeaponItemSign[i]->Destroy();
			m_WeaponItemSign[i] = NULL;
		}
		m_WeaponItemSign.clear();

		// ItemMakeButton
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[7]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// Remove
	for(size_t i = 0; i < m_WeaponFormulaButton[_iIndex].size(); ++i)
	{
		m_WeaponFormulaButton[_iIndex][i]->Destroy();
		m_WeaponFormulaButton[_iIndex][i] = NULL;
	}
	m_WeaponFormulaButton[_iIndex].clear();
	
	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 21; ++i)
		m_iMaxScroll = m_iMaxScroll + m_WeaponFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// WeaponCategoryButton Init
	for(int i = 0; i < 21; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// WeaponFormulaButton Init
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 21 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// WeaponCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_WeaponFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// WeaponFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CFactoryWindow::OpenArmorCategory(int _iIndex)
{
	// Add
	for(size_t i = 0; i < m_ArmorFormula[_iIndex].size(); ++i)
	{
		CFormulaButton* pFormulaButton = new CFormulaButton(NULL, OBJ_TYPE_STATIC, m_ArmorFormula[_iIndex][i]);
		m_pLayer->AddObject(pFormulaButton, LAYER_TYPE_UI);
		pFormulaButton->Initialize();
		m_ArmorFormulaButton[_iIndex].push_back(pFormulaButton);
	}

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 8; ++i)
		m_iMaxScroll = m_iMaxScroll + m_ArmorFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// ArmorCategoryButton Init
	for(int i = 0; i < 8; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ArmorFormulaButton Init
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 8 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// ArmorCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_ArmorFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// ArmorFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CFactoryWindow::CloseArmorCategory(int _iIndex)
{
	// NoneSelect
	if(_iIndex == m_iType)
	{
		m_iType = -1;
		m_iSelect = -1;

		// ArmorItemSign
		for(size_t i = 0; i < m_ArmorItemSign.size(); ++i)
		{
			m_ArmorItemSign[i]->Destroy();
			m_ArmorItemSign[i] = NULL;
		}
		m_ArmorItemSign.clear();

		// ItemMakeButton
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[7]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// Remove
	for(size_t i = 0; i < m_ArmorFormulaButton[_iIndex].size(); ++i)
	{
		m_ArmorFormulaButton[_iIndex][i]->Destroy();
		m_ArmorFormulaButton[_iIndex][i] = NULL;
	}
	m_ArmorFormulaButton[_iIndex].clear();

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 8; ++i)
		m_iMaxScroll = m_iMaxScroll + m_ArmorFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// ArmorCategoryButton Init
	for(int i = 0; i < 8; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ArmorFormulaButton Init
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 8 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// ArmorCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_ArmorFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// ArmorFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CFactoryWindow::UpdateScroll()
{
	m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.5399982f, 0.01f);
	if(m_iMaxScroll > 0)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[5]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);

		pTransformCom = (CTransformCom*)m_ButtonVec[6]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.025f;
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[5]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_ButtonVec[6]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.0f;
	}
}

void CFactoryWindow::UpdateWeaponCategory()
{
	// WeaponCategoryButton Init
	for(int i = 0; i < 21; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// WeaponFormulaButton Init
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 21 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// WeaponCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pWeaponCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_WeaponFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// WeaponFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_WeaponFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}
}

void CFactoryWindow::UpdateArmorCategory()
{
	// ArmorCategoryButton Init
	for(int i = 0; i < 8; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ArmorFormulaButton Init
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 8 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// ArmorCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pArmorCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_ArmorFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// ArmorFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_ArmorFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}
}

void CFactoryWindow::CreateWeaponFormula()
{
	// WeaponItemSign Clear
	for(size_t i = 0; i < m_WeaponItemSign.size(); ++i)
	{
		m_WeaponItemSign[i]->Destroy();
		m_WeaponItemSign[i] = NULL;
	}
	m_WeaponItemSign.clear();

	// ItemMakeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[7]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);

	// Formula
	Formula* pFormula = m_WeaponFormula[m_iType][m_iSelect];

	// Item
	CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pFormula->pItem);
	m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f, -0.279f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.169009f, 0.0f);

	pItemSign->Initialize();
	pItemSign->EnableGridSign();
	pItemSign->EnableSockSign();
	m_WeaponItemSign.push_back(pItemSign);

	// Iron
	int iCnt = 0;
	if(pFormula->iIronNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("쇠조각"), _T("Item_Materials_1"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_IRON, -1, -1, 1, 1, 2, 0, 1000, pFormula->iIronNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// Crystal
	if(pFormula->iCrystalNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("수정"), _T("Item_Materials_2"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_CRYSTAL, -1, -1, 1, 1, 2, 0, 3000, pFormula->iCrystalNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// Patterns
	if(pFormula->iPatternsNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("문양"), _T("Item_Materials_3"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_PATTERNS, -1, -1, 1, 1, 2, 0, 3000, pFormula->iPatternsNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// Diamond
	if(pFormula->iDiamondNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("다이아몬드"), _T("Item_Materials_4"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_DIAMOND, -1, -1, 1, 1, 2, 0, 5000, pFormula->iDiamondNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// ManaSource
	if(pFormula->iManaSourceNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("마력원"), _T("Item_Materials_5"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_MANA_SOURCE, -1, -1, 1, 1, 2, 0, 10000, pFormula->iManaSourceNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// Adamantium
	if(pFormula->iAdamantiumNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("아다만티움"), _T("Item_Materials_6"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_ADAMANTIUM, -1, -1, 1, 1, 2, 0, 10000, pFormula->iAdamantiumNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
	// MetalStain
	if(pFormula->iMetalStainNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("쇳물"), _T("Item_Materials_7"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_METAL_STAIN, -1, -1, 1, 1, 2, 0, 10000, pFormula->iMetalStainNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_WeaponItemSign.push_back(pItemSign);
	}
}

void CFactoryWindow::CreateArmorFormula()
{
	// ArmorItemSign Clear
	for(size_t i = 0; i < m_ArmorItemSign.size(); ++i)
	{
		m_ArmorItemSign[i]->Destroy();
		m_ArmorItemSign[i] = NULL;
	}
	m_ArmorItemSign.clear();

	// ItemMakeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[7]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);

	// Formula
	Formula* pFormula = m_ArmorFormula[m_iType][m_iSelect];

	// ItemSign
	CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pFormula->pItem);
	m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f, -0.279f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.169009f, 0.0f);

	pItemSign->Initialize();
	pItemSign->EnableGridSign();
	pItemSign->EnableSockSign();
	m_ArmorItemSign.push_back(pItemSign);

	// Iron
	int iCnt = 0;
	if(pFormula->iIronNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("쇠조각"), _T("Item_Materials_1"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_IRON, -1, -1, 1, 1, 2, 0, 1000, pFormula->iIronNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// Crystal
	if(pFormula->iCrystalNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("수정"), _T("Item_Materials_2"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_CRYSTAL, -1, -1, 1, 1, 2, 0, 3000, pFormula->iCrystalNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// Patterns
	if(pFormula->iPatternsNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("문양"), _T("Item_Materials_3"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_PATTERNS, -1, -1, 1, 1, 2, 0, 3000, pFormula->iPatternsNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// Diamond
	if(pFormula->iDiamondNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("다이아몬드"), _T("Item_Materials_4"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_DIAMOND, -1, -1, 1, 1, 2, 0, 5000, pFormula->iDiamondNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// ManaSource
	if(pFormula->iManaSourceNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("마력원"), _T("Item_Materials_5"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_MANA_SOURCE, -1, -1, 1, 1, 2, 0, 10000, pFormula->iManaSourceNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// Adamantium
	if(pFormula->iAdamantiumNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("아다만티움"), _T("Item_Materials_6"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_ADAMANTIUM, -1, -1, 1, 1, 2, 0, 10000, pFormula->iAdamantiumNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
	// MetalStain
	if(pFormula->iMetalStainNum != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("쇳물"), _T("Item_Materials_7"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_METAL_STAIN, -1, -1, 1, 1, 2, 0, 10000, pFormula->iMetalStainNum, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_ArmorItemSign.push_back(pItemSign);
	}
}
void CFactoryWindow::MakeWeapon()
{
	// Formula
	Formula* pFormula = m_WeaponFormula[m_iType][m_iSelect];

	// Iron
	if(pFormula->iIronNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("쇠조각"), _T("Item_Materials_1"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_IRON, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iIronNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Crystal
	if(pFormula->iCrystalNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("수정"), _T("Item_Materials_2"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_CRYSTAL, -1, -1, 1, 1, 2, 0, 3000, pFormula->iCrystalNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iCrystalNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Patterns
	if(pFormula->iPatternsNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("문양"), _T("Item_Materials_3"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_PATTERNS, -1, -1, 1, 1, 2, 0, 3000, pFormula->iPatternsNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iPatternsNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Diamond
	if(pFormula->iDiamondNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("다이아몬드"), _T("Item_Materials_4"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_DIAMOND, -1, -1, 1, 1, 2, 0, 5000, pFormula->iDiamondNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iDiamondNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// ManaSource
	if(pFormula->iManaSourceNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("마력원"), _T("Item_Materials_5"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_MANA_SOURCE, -1, -1, 1, 1, 2, 0, 10000, pFormula->iManaSourceNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iManaSourceNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}
	
	// Adamantium
	if(pFormula->iAdamantiumNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("아다만티움"), _T("Item_Materials_6"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_ADAMANTIUM, -1, -1, 1, 1, 2, 0, 10000, pFormula->iAdamantiumNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iAdamantiumNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// MetalStain
	if(pFormula->iMetalStainNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("쇳물"), _T("Item_Materials_7"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_METAL_STAIN, -1, -1, 1, 1, 2, 0, 10000, pFormula->iMetalStainNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iMetalStainNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	if(CItemMgr::GetInstance()->AddItemInInven(new Item(pFormula->pItem)) == false)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
		return;
	}

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST8) == NULL)
	{
		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(7);
				break;
			}
		}
	}

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("MakeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
}

void CFactoryWindow::MakeArmor()
{
	// Formula
	Formula* pFormula = m_ArmorFormula[m_iType][m_iSelect];

	// Iron
	if(pFormula->iIronNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("쇠조각"), _T("Item_Materials_1"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_IRON, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iIronNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Crystal
	if(pFormula->iCrystalNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("수정"), _T("Item_Materials_2"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_CRYSTAL, -1, -1, 1, 1, 2, 0, 3000, pFormula->iCrystalNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iCrystalNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Patterns
	if(pFormula->iPatternsNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("문양"), _T("Item_Materials_3"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_PATTERNS, -1, -1, 1, 1, 2, 0, 3000, pFormula->iPatternsNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iPatternsNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Diamond
	if(pFormula->iDiamondNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("다이아몬드"), _T("Item_Materials_4"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_DIAMOND, -1, -1, 1, 1, 2, 0, 5000, pFormula->iDiamondNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iDiamondNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// ManaSource
	if(pFormula->iManaSourceNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("마력원"), _T("Item_Materials_5"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_MANA_SOURCE, -1, -1, 1, 1, 2, 0, 10000, pFormula->iManaSourceNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iManaSourceNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// Adamantium
	if(pFormula->iAdamantiumNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("아다만티움"), _T("Item_Materials_6"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_ADAMANTIUM, -1, -1, 1, 1, 2, 0, 10000, pFormula->iAdamantiumNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iAdamantiumNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	// MetalStain
	if(pFormula->iMetalStainNum > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("쇳물"), _T("Item_Materials_7"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_METAL_STAIN, -1, -1, 1, 1, 2, 0, 10000, pFormula->iMetalStainNum, 0, 0));

		// Sort
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
			{
				if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j])->iNum > CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[j + 1])->iNum)
				{
					int iTemp = FindIndexVec[j];
					FindIndexVec[j] = FindIndexVec[j + 1];
					FindIndexVec[j + 1] = iTemp;
				}
			}
		}

		int iNum = pFormula->iMetalStainNum;
		vector<int> RemoveIndexVec;

		for(size_t i = 0; i < FindIndexVec.size() && 0 < iNum; ++i)
		{
			if(CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum <= iNum)
			{
				iNum -= CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;
				RemoveIndexVec.push_back(FindIndexVec[i]);
			}
			else
			{
				CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum -= iNum;
				iNum = 0;
			}
		}

		// Fail
		if(iNum > 0)
		{
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("재료가 부족합니다."));
			return;
		}

		// Sort
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
		{
			for(size_t j = 0; j < RemoveIndexVec.size() - 1; ++j)
			{
				if(RemoveIndexVec[j] < RemoveIndexVec[j + 1])
				{
					int iTemp = RemoveIndexVec[j];
					RemoveIndexVec[j] = RemoveIndexVec[j + 1];
					RemoveIndexVec[j + 1] = iTemp;
				}
			}
		}

		// Remove
		for(size_t i = 0; i < RemoveIndexVec.size(); ++i)
			CItemMgr::GetInstance()->RemoveItemInInven(RemoveIndexVec[i]);
	}

	if(CItemMgr::GetInstance()->AddItemInInven(new Item(pFormula->pItem)) == false)
	{
		CItemMgr::GetInstance()->RollbackInven();
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
		return;
	}

	if(CQuestMgr::GetInstance()->GetAchieve(ACHIEVE_TYPE_MAIN_QUEST8) == NULL)
	{
		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(7);
				break;
			}
		}
	}

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("MakeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
}

////////////////////////////////////////////////////////////////////////// Decompose
Item* CFactoryWindow::Decompose(DWORD _dwItemClass)
{
	// Type
	int iRand;
	if(_dwItemClass & ITEM_CLASS_NORMAL)
		iRand = rand() % 1;
	else if(_dwItemClass & ITEM_CLASS_MAGIC)
		iRand = rand() % 3;
	else if(_dwItemClass & ITEM_CLASS_UNIQUE)
		iRand = rand() % 5;
	else if(_dwItemClass & ITEM_CLASS_LEGEND)
		iRand = rand() % 7;
	else if(_dwItemClass & ITEM_CLASS_SET)
		iRand = rand() % 7;

	// Num
	int iNum;
	if(_dwItemClass & ITEM_CLASS_SET)
		iNum = rand() % 3 + 3;
	else
		iNum = rand() % 3 + 1;

	// Item
	Item* pItem = new Item;
	pItem->dwItemClass = 0;
	pItem->dwItemType = ITEM_TYPE_MATERIAL;
	pItem->iLevel = 0;
	pItem->iGender = 2;
	pItem->iPosX = -1;
	pItem->iPosY = -1;
	pItem->iWidth = 1;
	pItem->iHeight = 1;
	pItem->iNum = iNum;

	if(iRand == 0)
	{
		pItem->dwItemID = MATERIAL_ID_IRON;
		_tcscat_s(pItem->tszName, MIN_STR, _T("쇠조각"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_1"));
		pItem->iValue = 1000;
	}
	else if(iRand == 1)
	{
		pItem->dwItemID = MATERIAL_ID_CRYSTAL;
		_tcscat_s(pItem->tszName, MIN_STR, _T("수정"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_2"));
		pItem->iValue = 3000;
	}
	else if(iRand == 2)
	{
		pItem->dwItemID = MATERIAL_ID_PATTERNS;
		_tcscat_s(pItem->tszName, MIN_STR, _T("문양"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_3"));
		pItem->iValue = 3000;
	}
	else if(iRand == 3)
	{
		pItem->dwItemID = MATERIAL_ID_DIAMOND;
		_tcscat_s(pItem->tszName, MIN_STR, _T("다이아몬드"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_4"));
		pItem->iValue = 5000;
	}
	else if(iRand == 4)
	{
		pItem->dwItemID = MATERIAL_ID_MANA_SOURCE;
		_tcscat_s(pItem->tszName, MIN_STR, _T("마력원"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_5"));
		pItem->iValue = 10000;
	}
	else if(iRand == 5)
	{
		pItem->dwItemID = MATERIAL_ID_ADAMANTIUM;
		_tcscat_s(pItem->tszName, MIN_STR, _T("아다만티움"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_6"));
		pItem->iValue = 10000;
	}
	else if(iRand == 6)
	{
		pItem->dwItemID = MATERIAL_ID_METAL_STAIN;
		_tcscat_s(pItem->tszName, MIN_STR, _T("쇳물"));
		_tcscpy_s(pItem->tszTexKey, MIN_STR, _T("Item_Materials_7"));
		pItem->iValue = 10000;
	}

	return pItem;
}

bool CFactoryWindow::DecomposeInInven(int _iIndex)
{
	// Class
	DWORD dwItemClass = CItemMgr::GetInstance()->GetItemInInven(_iIndex)->dwItemClass;

	// Check Class
	if(dwItemClass == 0)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분해할 수 없는 아이템입니다."));
		return false;
	}

	// Loop
	int iLoop;
	if(dwItemClass & ITEM_CLASS_NORMAL)
		iLoop = 1;
	else if(dwItemClass & ITEM_CLASS_MAGIC)
		iLoop = 2;
	else if(dwItemClass & ITEM_CLASS_UNIQUE)
		iLoop = 3;
	else if(dwItemClass & ITEM_CLASS_LEGEND)
		iLoop = 4;
	else if(dwItemClass & ITEM_CLASS_SET)
		iLoop = 5;

	// RemoveItemInInven
	CItemMgr::GetInstance()->RemoveItemInInven(_iIndex);

	// DecomposeItem
	vector<Item*> DecomposeItem;

	for(int i = 0; i < iLoop; ++i)
	{
		Item* pItem = Decompose(dwItemClass);

		int iIndex = -1;
		for(size_t j = 0; j < DecomposeItem.size() && iIndex == -1; ++j)
		{
			if(DecomposeItem[j]->dwItemID == pItem->dwItemID)
				iIndex = j;
		}

		if(iIndex == -1)
			DecomposeItem.push_back(new Item(pItem));
		else
			DecomposeItem[iIndex]->iNum += pItem->iNum;

		if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
		{
			for(size_t j = 0; j < DecomposeItem.size(); ++j)
				delete DecomposeItem[j];
			DecomposeItem.clear();

			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			return false;
		}
	}

	// DecomposeItem
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		delete m_DecomposeItem[i];
		m_DecomposeItem[i] = NULL;
	}
	m_DecomposeItem.clear();

	// DecomposeItemSign
	for(size_t i = 0; i < m_DecomposeItemSign.size(); ++i)
	{
		m_DecomposeItemSign[i]->Destroy();
		m_DecomposeItemSign[i] = NULL;
	}
	m_DecomposeItemSign.clear();

	// DecomposeItem Copy
	for(size_t i = 0; i < DecomposeItem.size(); ++i)
		m_DecomposeItem.push_back(DecomposeItem[i]);

	// DecomposeItem Sort
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		for(size_t j = 0; j < m_DecomposeItem.size() - 1; ++j)
		{
			if(m_DecomposeItem[j]->dwItemID > m_DecomposeItem[j + 1]->dwItemID)
			{
				Item* pTemp = m_DecomposeItem[j];
				m_DecomposeItem[j] = m_DecomposeItem[j + 1];
				m_DecomposeItem[j + 1] = pTemp;
			}
		}
	}

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("DecomposeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
	Renew();
	return true;
}

bool CFactoryWindow::DecomposeInEquip(int _iIndex)
{
	// Class
	DWORD dwItemClass = CItemMgr::GetInstance()->GetItemInEquip(_iIndex)->dwItemClass;

	// Check Class
	if(dwItemClass == 0)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분해할 수 없는 아이템입니다."));
		return false;
	}

	// Loop
	int iLoop;
	if(dwItemClass & ITEM_CLASS_NORMAL)
		iLoop = 1;
	else if(dwItemClass & ITEM_CLASS_MAGIC)
		iLoop = 2;
	else if(dwItemClass & ITEM_CLASS_UNIQUE)
		iLoop = 3;
	else if(dwItemClass & ITEM_CLASS_LEGEND)
		iLoop = 4;
	else if(dwItemClass & ITEM_CLASS_SET)
		iLoop = 5;

	// RemoveItem
	CItemMgr::GetInstance()->RemoveItemInEquip(_iIndex);

	// DecomposeItem
	vector<Item*> DecomposeItem;

	for(int i = 0; i < iLoop; ++i)
	{
		Item* pItem = Decompose(dwItemClass);

		int iIndex = -1;
		for(size_t j = 0; j < DecomposeItem.size() && iIndex == -1; ++j)
		{
			if(DecomposeItem[j]->dwItemID == pItem->dwItemID)
				iIndex = j;
		}

		if(iIndex == -1)
			DecomposeItem.push_back(new Item(pItem));
		else
			DecomposeItem[iIndex]->iNum += pItem->iNum;

		if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
		{
			for(size_t j = 0; j < DecomposeItem.size(); ++j)
				delete DecomposeItem[j];
			DecomposeItem.clear();

			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
			CItemMgr::GetInstance()->RollbackEquip();
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
			return false;
		}
	}

	// DecomposeItem
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		delete m_DecomposeItem[i];
		m_DecomposeItem[i] = NULL;
	}
	m_DecomposeItem.clear();

	// DecomposeItemSign
	for(size_t i = 0; i < m_DecomposeItemSign.size(); ++i)
	{
		m_DecomposeItemSign[i]->Destroy();
		m_DecomposeItemSign[i] = NULL;
	}
	m_DecomposeItemSign.clear();

	// DecomposeItem Copy
	for(size_t i = 0; i < DecomposeItem.size(); ++i)
		m_DecomposeItem.push_back(DecomposeItem[i]);

	// DecomposeItem Sort
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		for(size_t j = 0; j < m_DecomposeItem.size() - 1; ++j)
		{
			if(m_DecomposeItem[j]->dwItemID > m_DecomposeItem[j + 1]->dwItemID)
			{
				Item* pTemp = m_DecomposeItem[j];
				m_DecomposeItem[j] = m_DecomposeItem[j + 1];
				m_DecomposeItem[j + 1] = pTemp;
			}
		}
	}

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("DecomposeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CItemMgr::GetInstance()->CommitEquip();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
	m_pPlayer->Renew();
	Renew();
	return true;
}

bool CFactoryWindow::DecomposeAll(DWORD _dwItemClass)
{
	// FindIndexVec
	vector<int> FindIndexVec;
	for(int i = 0; i < CItemMgr::GetInstance()->GetSizeOfInven(); ++i)
	{
		if(CItemMgr::GetInstance()->GetItemInInven(i)->dwItemClass & _dwItemClass)
			FindIndexVec.push_back(i);
	}

	// Check FindItem
	if(FindIndexVec.size() == 0)
	{
		if(_dwItemClass & ITEM_CLASS_NORMAL)
			CUIMgr::GetInstance()->CreateTextMessage(_T("일반 아이템이 없습니다."));
		else if(_dwItemClass & ITEM_CLASS_MAGIC)
			CUIMgr::GetInstance()->CreateTextMessage(_T("마법 아이템이 없습니다."));
		else if(_dwItemClass & ITEM_CLASS_UNIQUE)
			CUIMgr::GetInstance()->CreateTextMessage(_T("희귀 아이템이 없습니다."));
		return false;
	}

	// FindIndexVec Sort
	for(size_t i = 0; i < FindIndexVec.size(); ++i)
	{
		for(size_t j = 0; j < FindIndexVec.size() - 1; ++j)
		{
			if(FindIndexVec[j] < FindIndexVec[j + 1])
			{
				int iTemp = FindIndexVec[j];
				FindIndexVec[j] = FindIndexVec[j + 1];
				FindIndexVec[j + 1] = iTemp;
			}
		}
	}

	// Loop
	int iLoop;
	if(_dwItemClass & ITEM_CLASS_NORMAL)
		iLoop = 1;
	else if(_dwItemClass & ITEM_CLASS_MAGIC)
		iLoop = 2;
	else if(_dwItemClass & ITEM_CLASS_UNIQUE)
		iLoop = 3;

	// DecomposeItem
	vector<Item*> DecomposeItem;

	// RemoveItemInInven
	for(size_t i = 0; i < FindIndexVec.size(); ++i)
		CItemMgr::GetInstance()->RemoveItemInInven(FindIndexVec[i]);

	for(size_t i = 0; i < FindIndexVec.size(); ++i)
	{
		for(int j = 0; j < iLoop; ++j)
		{
			Item* pItem = Decompose(_dwItemClass);

			int iIndex = -1;
			for(size_t k = 0; k < DecomposeItem.size() && iIndex == -1; ++k)
			{
				if(DecomposeItem[k]->dwItemID == pItem->dwItemID)
					iIndex = k;
			}

			if(iIndex == -1)
				DecomposeItem.push_back(new Item(pItem));
			else
				DecomposeItem[iIndex]->iNum += pItem->iNum;

			if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
			{
				for(size_t k = 0; k < DecomposeItem.size(); ++k)
					delete DecomposeItem[k];
				DecomposeItem.clear();

				delete pItem;
				CItemMgr::GetInstance()->RollbackInven();
				CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
				return false;
			}
		}
	}

	// DecomposeItem
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		delete m_DecomposeItem[i];
		m_DecomposeItem[i] = NULL;
	}
	m_DecomposeItem.clear();

	// DecomposeItemSign
	for(size_t i = 0; i < m_DecomposeItemSign.size(); ++i)
	{
		m_DecomposeItemSign[i]->Destroy();
		m_DecomposeItemSign[i] = NULL;
	}
	m_DecomposeItemSign.clear();

	// DecomposeItem Copy
	for(size_t i = 0; i < DecomposeItem.size(); ++i)
		m_DecomposeItem.push_back(DecomposeItem[i]);

	// DecomposeItem Sort
	for(size_t i = 0; i < m_DecomposeItem.size(); ++i)
	{
		for(size_t j = 0; j < m_DecomposeItem.size() - 1; ++j)
		{
			if(m_DecomposeItem[j]->dwItemID > m_DecomposeItem[j + 1]->dwItemID)
			{
				Item* pTemp = m_DecomposeItem[j];
				m_DecomposeItem[j] = m_DecomposeItem[j + 1];
				m_DecomposeItem[j + 1] = pTemp;
			}
		}
	}


	CSoundMgr::GetInstance()->PlaySoundForUI(_T("DecomposeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
	Renew();
	return true;
}

////////////////////////////////////////////////////////////////////////// Pick
void CFactoryWindow::UpdateNonePick()
{
}
void CFactoryWindow::UpdatePick()
{
}
void CFactoryWindow::UpdateDecomposePick()
{
}

////////////////////////////////////////////////////////////////////////// In
void CFactoryWindow::UpdateIn()
{
}
void CFactoryWindow::UpdateNonePickIn()
{
	// DestroyButton
	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	// PageButton
	for(int i = 0; i < 3; ++i)
	{
		if(m_iPage == i)
			continue;

		if(m_pFactoryButton[i]->IsLDown())
		{
			// DecomposeItem
			for(size_t j = 0; j < m_DecomposeItem.size(); ++j)
			{
				delete m_DecomposeItem[j];
				m_DecomposeItem[j] = NULL;
			}
			m_DecomposeItem.clear();

			// DecomposeItemSign
			for(size_t j = 0; j < m_DecomposeItemSign.size(); ++j)
			{
				m_DecomposeItemSign[j]->Destroy();
				m_DecomposeItemSign[j] = NULL;
			}
			m_DecomposeItemSign.clear();

			m_pFactoryButton[m_iPage]->SetState(0);
			m_iPage = i;
			Renew();
			break;
		}
	}
}
void CFactoryWindow::UpdatePickIn()
{
}
void CFactoryWindow::UpdateDecomposePickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CFactoryWindow::UpdateOut()
{
}
void CFactoryWindow::UpdateNonePickOut()
{
	// LButton
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_BLACKSMITH)
			{
				// TransformComA
				CTransformCom* pTransformComA = (CTransformCom*)pNPC->GetComponent(COM_TYPE_TRANSFORM);

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
void CFactoryWindow::UpdatePickOut()
{
}
void CFactoryWindow::UpdateDecomposePickOut()
{
}

////////////////////////////////////////////////////////////////////////// InFactory
void CFactoryWindow::UpdateInFactory()
{
}
void CFactoryWindow::UpdateNonePickInFactory()
{
	// WeaponCategoryButton
	for(int i = 0; i < 21; ++i)
	{
		if(m_pWeaponCategoryButton[i]->IsLUp())
		{
			if(m_pWeaponCategoryButton[i]->IsOpen())
			{
				m_pWeaponCategoryButton[i]->Close();
				CloseWeaponCategory(i);
			}
			else
			{
				m_pWeaponCategoryButton[i]->Open();
				OpenWeaponCategory(i);
			}

			break;
		}
	}

	// ArmorCategoryButton
	for(int i = 0; i < 8; ++i)
	{
		if(m_pArmorCategoryButton[i]->IsLUp())
		{
			if(m_pArmorCategoryButton[i]->IsOpen())
			{
				m_pArmorCategoryButton[i]->Close();
				CloseArmorCategory(i);
			}
			else
			{
				m_pArmorCategoryButton[i]->Open();
				OpenArmorCategory(i);
			}

			break;
		}
	}

	// WeaponFormulaButton
	for(int i = 0; i < 21; ++i)
	{
		for(size_t j = 0; j < m_WeaponFormulaButton[i].size(); ++j)
		{
			if(m_iType == i && m_iSelect == j)
				continue;

			if(m_WeaponFormulaButton[i][j]->IsLUp())
			{
				m_iType = i;
				m_iSelect = j;
				CreateWeaponFormula();
				break;
			}
		}
	}

	// ArmorFormulaButton
	for(int i = 0; i < 8; ++i)
	{
		for(size_t j = 0; j < m_ArmorFormulaButton[i].size(); ++j)
		{
			if(m_iType == i && m_iSelect == j)
				continue;

			if(m_ArmorFormulaButton[i][j]->IsLUp())
			{
				m_iType = i;
				m_iSelect = j;
				CreateArmorFormula();
				break;
			}
		}
	}

	// DecomposeButton
	if(m_ButtonVec[1]->IsLUp())
		m_pMouse->Pick(4, 0, NULL);

	// DecomposeNormalButton
	if(m_ButtonVec[2]->IsLUp())
		DecomposeAll(ITEM_CLASS_NORMAL);

	// DecomposeMagicButton
	if(m_ButtonVec[3]->IsLUp())
		DecomposeAll(ITEM_CLASS_MAGIC);

	// DecomposeUniqueButton
	if(m_ButtonVec[4]->IsLUp())
		DecomposeAll(ITEM_CLASS_UNIQUE);

	// ScrollUpButton
	if(m_ButtonVec[5]->IsLUp())
	{
		if(--m_iScroll < 0)
			m_iScroll = 0;

		UpdateScroll();

		if(m_iPage == 0)
			UpdateWeaponCategory();
		else if(m_iPage == 1)
			UpdateArmorCategory();
	}

	// ScrollDownButton
	if(m_ButtonVec[6]->IsLUp())
	{
		if(++m_iScroll > m_iMaxScroll)
			m_iScroll = m_iMaxScroll;

		UpdateScroll();

		if(m_iPage == 0)
			UpdateWeaponCategory();
		else if(m_iPage == 1)
			UpdateArmorCategory();
	}

	// ItemMakeButton
	if(m_ButtonVec[7]->IsLUp())
	{
		if(m_iPage == 0)
			MakeWeapon();
		else if(m_iPage == 1)
			MakeArmor();
	}
}
void CFactoryWindow::UpdatePickInFactory()
{
}
void CFactoryWindow::UpdateDecomposePickInFactory()
{
	// DecomposeButton
	if(m_ButtonVec[1]->IsLUp())
		m_pMouse->Drop();
}