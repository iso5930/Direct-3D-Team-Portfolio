#include "StdAfx.h"
#include "EnchantWindow.h"

CEnchantWindow::CEnchantWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, NULL)
{
	// Texture
	m_pTexture[0] = CTextureMgr::GetInstance()->GetTexture(_T("Window_GemFactory"));
	m_pTexture[1] = CTextureMgr::GetInstance()->GetTexture(_T("Window_AccessoryFactory"));
	m_pTexture[2] = CTextureMgr::GetInstance()->GetTexture(_T("Window_DisenchantStore"));
	m_pBackTexture = m_pTexture[0];

	// Page
	m_iPage = 0;

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;

	// FormulaType
	m_iFormulaType = -1;

	// FormulaSelect
	m_iFormulaSelect = -1;

	// DisenchantType
	m_iDisenchantType = -1;

	// DisenchantSelect
	m_iDisenchatSelect = -1;

	// Mouse
	m_pMouse = NULL;

	// Player
	m_pPlayer = NULL;

	// EnchantButton
	ZeroMemory(m_pEnchantButton, sizeof(m_pEnchantButton));

	// GemCategoryButton
	ZeroMemory(m_pGemCategoryButton, sizeof(m_pGemCategoryButton));

	// AccessoryCategoryButton
	ZeroMemory(m_pAccessoryCategoryButton, sizeof(m_pAccessoryCategoryButton));

	// DisenchantItemSign
	m_pDisenchantItemSign = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CEnchantWindow::~CEnchantWindow()
{
	Release();
}

void CEnchantWindow::Initialize()
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

	// GemFactory
	m_pEnchantButton[0] = new CEnchantButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_GemFactory"), _T("Button_Over_GemFactory"), _T("Button_Down_GemFactory"));
	m_pLayer->AddObject(m_pEnchantButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pEnchantButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.532f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pEnchantButton[0]->SetState(UI_L_DOWN);
	m_pEnchantButton[0]->Initialize();

	// AccessoryFactory
	m_pEnchantButton[1] = new CEnchantButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_AccessoryFactory"), _T("Button_Over_AccessoryFactory"), _T("Button_Down_AccessoryFactory"));
	m_pLayer->AddObject(m_pEnchantButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pEnchantButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.332f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pEnchantButton[1]->Initialize();

	// DisenchantStore
	m_pEnchantButton[2] = new CEnchantButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_DisenchantStore"), _T("Button_Over_DisenchantStore"), _T("Button_Down_DisenchantStore"));
	m_pLayer->AddObject(m_pEnchantButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pEnchantButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.132f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pEnchantButton[2]->Initialize();

	// GemCategoryButton
	TCHAR tszGemCategory[6][MIN_STR];
	_tcscpy_s(tszGemCategory[0], MIN_STR, _T("토파즈"));
	_tcscpy_s(tszGemCategory[1], MIN_STR, _T("사파이어"));
	_tcscpy_s(tszGemCategory[2], MIN_STR, _T("루비"));
	_tcscpy_s(tszGemCategory[3], MIN_STR, _T("에메랄드"));
	_tcscpy_s(tszGemCategory[4], MIN_STR, _T("다이아몬드"));
	_tcscpy_s(tszGemCategory[5], MIN_STR, _T("자수정"));

	for(int i = 0; i < 6; ++i)
	{
		m_pGemCategoryButton[i] = new CCategoryButton(NULL, OBJ_TYPE_STATIC, tszGemCategory[i]);
		m_pLayer->AddObject(m_pGemCategoryButton[i], LAYER_TYPE_UI);
		m_pGemCategoryButton[i]->Initialize();
	}

	// AccessoryCategoryButton
	TCHAR tszAccessoryCategory[2][MIN_STR];
	_tcscpy_s(tszAccessoryCategory[0], MIN_STR, _T("목걸이"));
	_tcscpy_s(tszAccessoryCategory[1], MIN_STR, _T("반지"));

	for(int i = 0; i < 2; ++i)
	{
		m_pAccessoryCategoryButton[i] = new CCategoryButton(NULL, OBJ_TYPE_STATIC, tszAccessoryCategory[i]);
		m_pLayer->AddObject(m_pAccessoryCategoryButton[i], LAYER_TYPE_UI);
		m_pAccessoryCategoryButton[i]->Initialize();
	}

	// ScrollUpButton(1)
	CBasicButton* pScrollUpButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Up"), _T("Button_Over_Up"), _T("Button_Down_Up"));
	m_pLayer->AddObject(pScrollUpButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, 0.568997f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollUpButton->Initialize();
	AddButton(pScrollUpButton);

	// ScrollDownButton(2)
	CBasicButton* pScrollDownButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Down"), _T("Button_Over_Down"), _T("Button_Down_Down"));
	m_pLayer->AddObject(pScrollDownButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, -0.0189988f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollDownButton->Initialize();
	AddButton(pScrollDownButton);

	// ItemMakeButton(3)
	CBasicButton* pItemMakeButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ItemMake"), _T("Button_Over_ItemMake"), _T("Button_Down_ItemMake"));
	m_pLayer->AddObject(pItemMakeButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pItemMakeButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.677998f, -0.422997f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);
	pItemMakeButton->Initialize();
	AddButton(pItemMakeButton);

	// DisenchantButton(4)
	CBasicButton* pDisenchantButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Disenchant"), _T("Button_Over_Disenchant"), _T("Button_Down_Disenchant"));
	m_pLayer->AddObject(pDisenchantButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDisenchantButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.726997f, 0.252001f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);
	pDisenchantButton->Initialize();
	AddButton(pDisenchantButton);

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

	Renew();
}

int CEnchantWindow::Update()
{
	// Mouse
	CObject* pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Mouse"), LAYER_TYPE_MOUSE);
	m_pMouse = (CMouse*)pFind;

	// Player
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Player"), LAYER_TYPE_PLAYER);
	m_pPlayer = (CPlayer*)pFind;

	// GemItemSign
	for(size_t i = 0; i < m_GemItemSign.size(); ++i)
	{
		if(m_GemItemSign[i]->IsOver())
			m_GemItemSign[i]->EnableItemMessage();
		else
			m_GemItemSign[i]->DisableItemMessage();
	}

	// AccessoryItemSign
	for(size_t i = 0; i < m_AccessoryItemSign.size(); ++i)
	{
		if(m_AccessoryItemSign[i]->IsOver())
			m_AccessoryItemSign[i]->EnableItemMessage();
		else
			m_AccessoryItemSign[i]->DisableItemMessage();
	}

	// DisenchantItemSign
	if(m_pDisenchantItemSign != NULL)
	{
		if(m_pDisenchantItemSign->IsOver())
			m_pDisenchantItemSign->EnableItemMessage();
		else
			m_pDisenchantItemSign->DisableItemMessage();
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
				UpdateInEnchant();
				UpdateNonePickInEnchant();
			}
			break;

		case 0:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickIn();
			UpdateInventoryPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInEnchant();
				UpdatePickInEnchant();
				UpdateInventoryPickInEnchant();
			}
			break;

		case 1:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickIn();
			UpdateInventoryPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInEnchant();
				UpdatePickInEnchant();
				UpdateEquipmentPickInEnchant();
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
		}
	}

	// EnchantButton
	for(int i = 0; i < 3; ++i)
		m_pEnchantButton[i]->SetState(0);

	m_pEnchantButton[m_iPage]->SetState(UI_L_DOWN);

	// Select
	if(m_iFormulaType != -1 && m_iFormulaSelect != -1)
	{
		if(m_iPage == 0)
			m_GemFormulaButton[m_iFormulaType][m_iFormulaSelect]->SetState(UI_L_DOWN);
		else
			m_AccessoryFormulaButton[m_iFormulaType][m_iFormulaSelect]->SetState(UI_L_DOWN);
	}

	// Scroll
	if(m_iScroll != m_pVScroll->GetScroll())
	{
		m_iScroll = m_pVScroll->GetScroll();
		UpdateScroll();

		if(m_iPage == 0)
			UpdateGemCategory();
		else if(m_iPage == 1)
			UpdateAccessoryCategory();
	}

	CWindowUI::Update();

	return 0;
}

void CEnchantWindow::Render()
{
	CWindowUI::Render();

	TCHAR tszGold[MIN_STR];
	_itot_s(CItemMgr::GetInstance()->GetGold(), tszGold, 10);

	// Gold
	RECT rcText;
	SetRect(&rcText, 96, 551, 296, 563);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszGold, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if(m_GemItemSign.size() > 0)
	{
		SetRect(&rcText, 71, 429, 171, 441);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("필요한 재료"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.031372f, 0.00392156f, 0.00784313f, 1.0f));
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_GemFormula[m_iFormulaType][m_iFormulaSelect]->pItem->tszName, -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
	else if(m_AccessoryItemSign.size() > 0)
	{
		SetRect(&rcText, 71, 429, 171, 441);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("필요한 재료"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.031372f, 0.00392156f, 0.00784313f, 1.0f));
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_AccessoryFormula[m_iFormulaType][m_iFormulaSelect]->pItem->tszName, -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
	else if(m_iPage != 2)
	{
		SetRect(&rcText, 21, 408, 321, 420);
		CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, _T("제조법을 선택하면 자세한 정보를 확인할 수 있습니다."), -1, &rcText, DT_CENTER, D3DXCOLOR(0.917647f, 0.913725f, 0.90196f, 1.0f));
	}
}

void CEnchantWindow::Release()
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

	// EnchantButton
	for(int i = 0; i < 3; ++i)
	{
		if(m_pEnchantButton[i] != NULL)
		{
			m_pEnchantButton[i]->Destroy();
			m_pEnchantButton[i] = NULL;
		}
	}

	// GemFormula
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormula[i].size(); ++j)
		{
			delete m_GemFormula[i][j];
			m_GemFormula[i][j] = NULL;
		}
		m_GemFormula[i].clear();
	}

	// AccessoryFormula
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormula[i].size(); ++j)
		{
			delete m_AccessoryFormula[i][j];
			m_AccessoryFormula[i][j] = NULL;
		}
		m_AccessoryFormula[i].clear();
	}

	// GemCategoryButton
	for(int i = 0; i < 6; ++i)
	{
		if(m_pGemCategoryButton[i] != NULL)
		{
			m_pGemCategoryButton[i]->Destroy();
			m_pGemCategoryButton[i] = NULL;
		}
	}

	// AccessoryCategoryButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pAccessoryCategoryButton[i] != NULL)
		{
			m_pAccessoryCategoryButton[i]->Destroy();
			m_pAccessoryCategoryButton[i] = NULL;
		}
	}

	// GemFormulaButton
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			m_GemFormulaButton[i][j]->Destroy();
			m_GemFormulaButton[i][j] = NULL;
		}
		m_GemFormulaButton[i].clear();
	}

	// AccessoryFormulaButton
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			m_AccessoryFormulaButton[i][j]->Destroy();
			m_AccessoryFormulaButton[i][j] = NULL;
		}
		m_AccessoryFormulaButton[i].clear();
	}

	// GemItemSign
	for(size_t i = 0; i < m_GemItemSign.size(); ++i)
	{
		m_GemItemSign[i]->Destroy();
		m_GemItemSign[i] = NULL;
	}
	m_GemItemSign.clear();

	// AccessoryItemSign
	for(size_t i = 0; i < m_AccessoryItemSign.size(); ++i)
	{
		m_AccessoryItemSign[i]->Destroy();
		m_AccessoryItemSign[i] = NULL;
	}
	m_AccessoryItemSign.clear();

	// DisenchantItemSign
	if(m_pDisenchantItemSign != NULL)
	{
		m_pDisenchantItemSign->Destroy();
		m_pDisenchantItemSign = NULL;
	}

	// VScroll
	if(m_pVScroll != NULL)
	{
		m_pVScroll->Destroy();
		m_pVScroll = NULL;
	}
}

void CEnchantWindow::Renew()
{
	// BackTexture
	m_pBackTexture = m_pTexture[m_iPage];

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;

	// FormulaType
	m_iFormulaType = -1;

	// FormulaSelect
	m_iFormulaSelect = -1;

	// DisenchantType
	m_iDisenchantType = -1;

	// DisenchantSelect
	m_iDisenchatSelect = -1;

	// GemCategoryButton
	for(int i = 0; i < 6; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pGemCategoryButton[i]->Close();
	}

	// AccessoryCategoryButton
	for(int i = 0; i < 2; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pAccessoryCategoryButton[i]->Close();
	}

	// GemFormulaButton
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			m_GemFormulaButton[i][j]->Destroy();
			m_GemFormulaButton[i][j] = NULL;
		}
		m_GemFormulaButton[i].clear();
	}

	// AccessoryFormulaButton
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			m_AccessoryFormulaButton[i][j]->Destroy();
			m_AccessoryFormulaButton[i][j] = NULL;
		}
		m_AccessoryFormulaButton[i].clear();
	}

	// GemItemSign
	for(size_t i = 0; i < m_GemItemSign.size(); ++i)
	{
		m_GemItemSign[i]->Destroy();
		m_GemItemSign[i] = NULL;
	}
	m_GemItemSign.clear();

	// AccessoryItemSign
	for(size_t i = 0; i < m_AccessoryItemSign.size(); ++i)
	{
		m_AccessoryItemSign[i]->Destroy();
		m_AccessoryItemSign[i] = NULL;
	}
	m_AccessoryItemSign.clear();

	// DisenchantItemSign
	if(m_pDisenchantItemSign != NULL)
	{
		m_pDisenchantItemSign->Destroy();
		m_pDisenchantItemSign = NULL;
	}

	// ItemMakeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// DisenchantButton
	pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if(m_iPage == 0)
	{
		// GemCategoryButton
		for(int i = 0; i < 6; ++i)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * i, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}
	}
	else if(m_iPage == 1)
	{
		// AccessoryCategoryButton
		for(int i = 0; i < 2; ++i)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * i, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}
	}
	else if(m_iPage == 2)
	{
	}

	// UpdateScroll
	UpdateScroll();
}

////////////////////////////////////////////////////////////////////////// Category
void CEnchantWindow::OpenGemCategory(int _iIndex)
{
	// Add
	for(size_t i = 0; i < m_GemFormula[_iIndex].size(); ++i)
	{
		CFormulaButton* pFormulaButton = new CFormulaButton(NULL, OBJ_TYPE_STATIC, m_GemFormula[_iIndex][i]);
		m_pLayer->AddObject(pFormulaButton, LAYER_TYPE_UI);
		pFormulaButton->Initialize();
		m_GemFormulaButton[_iIndex].push_back(pFormulaButton);
	}

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 6; ++i)
		m_iMaxScroll = m_iMaxScroll + m_GemFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// GemCategoryButton Init
	for(int i = 0; i < 6; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// GemFormulaButton Init
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 6 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// GemCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_GemFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// GemFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CEnchantWindow::CloseGemCategory(int _iIndex)
{
	// NoneSelect
	if(_iIndex == m_iFormulaType)
	{
		m_iFormulaType = -1;
		m_iFormulaSelect = -1;

		// GemItemSign
		for(size_t i = 0; i < m_GemItemSign.size(); ++i)
		{
			m_GemItemSign[i]->Destroy();
			m_GemItemSign[i] = NULL;
		}
		m_GemItemSign.clear();

		// ItemMakeButton
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// Remove
	for(size_t i = 0; i < m_GemFormulaButton[_iIndex].size(); ++i)
	{
		m_GemFormulaButton[_iIndex][i]->Destroy();
		m_GemFormulaButton[_iIndex][i] = NULL;
	}
	m_GemFormulaButton[_iIndex].clear();

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 6; ++i)
		m_iMaxScroll = m_iMaxScroll + m_GemFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// GemCategoryButton Init
	for(int i = 0; i < 6; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// GemFormulaButton Init
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 6 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// GemCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_GemFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// GemFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CEnchantWindow::OpenAccessoryCategory(int _iIndex)
{
	// Add
	for(size_t i = 0; i < m_AccessoryFormula[_iIndex].size(); ++i)
	{
		CFormulaButton* pFormulaButton = new CFormulaButton(NULL, OBJ_TYPE_STATIC, m_AccessoryFormula[_iIndex][i]);
		m_pLayer->AddObject(pFormulaButton, LAYER_TYPE_UI);
		pFormulaButton->Initialize();
		m_AccessoryFormulaButton[_iIndex].push_back(pFormulaButton);
	}

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 2; ++i)
		m_iMaxScroll = m_iMaxScroll + m_AccessoryFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// AccessoryCategoryButton Init
	for(int i = 0; i < 2; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// AccessoryFormulaButton Init
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 2 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// AccessoryCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// AccessoryFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CEnchantWindow::CloseAccessoryCategory(int _iIndex)
{
	// NoneSelect
	if(_iIndex == m_iFormulaType)
	{
		m_iFormulaType = -1;
		m_iFormulaSelect = -1;

		// AccessoryItemSign
		for(size_t i = 0; i < m_AccessoryItemSign.size(); ++i)
		{
			m_AccessoryItemSign[i]->Destroy();
			m_AccessoryItemSign[i] = NULL;
		}
		m_AccessoryItemSign.clear();

		// ItemMakeButton
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// Remove
	for(size_t i = 0; i < m_AccessoryFormulaButton[_iIndex].size(); ++i)
	{
		m_AccessoryFormulaButton[_iIndex][i]->Destroy();
		m_AccessoryFormulaButton[_iIndex][i] = NULL;
	}
	m_AccessoryFormulaButton[_iIndex].clear();

	// Counting MaxScroll
	m_iMaxScroll = 0;
	for(int i = 0; i < 2; ++i)
		m_iMaxScroll = m_iMaxScroll + m_AccessoryFormulaButton[i].size() + 1;

	// Check MaxScroll
	if(m_iMaxScroll - 16 < 0)
		m_iMaxScroll = 0;
	else
		m_iMaxScroll -= 16;

	// Check Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// AccessoryCategoryButton Init
	for(int i = 0; i < 2; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// AccessoryFormulaButton Init
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 2 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// AccessoryCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// AccessoryFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}

	// UpdateScroll
	UpdateScroll();
}

void CEnchantWindow::UpdateScroll()
{
	m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.5399982f, 0.01f);
	if(m_iMaxScroll > 0)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[1]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);

		pTransformCom = (CTransformCom*)m_ButtonVec[2]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.025f;
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[1]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_ButtonVec[2]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.0f;
	}
}

void CEnchantWindow::UpdateGemCategory()
{
	// GemCategoryButton Init
	for(int i = 0; i < 6; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// GemFormulaButton Init
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 6 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// GemCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pGemCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_GemFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// GemFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_GemFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}
}

void CEnchantWindow::UpdateAccessoryCategory()
{
	// AccessoryCategoryButton Init
	for(int i = 0; i < 2; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// AccessoryFormulaButton Init
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	int iCnt = 0;
	int iScroll = m_iScroll;
	for(int i = 0; i < 2 && iCnt < 16; ++i)
	{
		if(--iScroll < 0)
		{
			// AccessoryCategoryButton
			CTransformCom* pTransformCom = (CTransformCom*)m_pAccessoryCategoryButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = D3DXVECTOR3(-0.94f, 0.575f - 0.04f * iCnt++, 0.0f);
			pTransformCom->m_vSize = D3DXVECTOR3(0.025f, 0.04f, 0.0f);
		}

		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size() && iCnt < 16; ++j)
		{
			if(--iScroll < 0)
			{
				// ArmorFormulaButton
				CTransformCom* pTransformCom = (CTransformCom*)m_AccessoryFormulaButton[i][j]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.75f, 0.575f - 0.04f * iCnt++, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.325f, 0.04f, 0.0f);
			}
		}
	}
}

void CEnchantWindow::CreateGemFormula()
{
	// GemItemSign Clear
	for(size_t i = 0; i < m_GemItemSign.size(); ++i)
	{
		m_GemItemSign[i]->Destroy();
		m_GemItemSign[i] = NULL;
	}
	m_GemItemSign.clear();

	// ItemMakeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);

	// Formula
	Formula* pFormula = m_GemFormula[m_iFormulaType][m_iFormulaSelect];

	// ItemSign
	CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pFormula->pItem);
	m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f, -0.279f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845f, 0.0f);

	pItemSign->Initialize();
	pItemSign->EnableGridSign();
	pItemSign->EnableSockSign();

	m_GemItemSign.push_back(pItemSign);

	// Topaz1
	int iCnt = 0;
	if(pFormula->iTopazNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 토파즈"), _T("Item_Gems_1"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iTopazNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Topaz2
	if(pFormula->iTopazNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 토파즈"), _T("Item_Gems_2"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iTopazNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Topaz3
	if(pFormula->iTopazNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 토파즈"), _T("Item_Gems_3"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iTopazNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Topaz4
	if(pFormula->iTopazNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 토파즈"), _T("Item_Gems_4"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iTopazNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Topaz5
	if(pFormula->iTopazNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 토파즈"), _T("Item_Gems_5"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iTopazNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Sapphire1
	if(pFormula->iSapphireNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 사파이어"), _T("Item_Gems_6"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iSapphireNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Sapphire2
	if(pFormula->iSapphireNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 사파이어"), _T("Item_Gems_7"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iSapphireNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Sapphire3
	if(pFormula->iSapphireNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 사파이어"), _T("Item_Gems_8"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iSapphireNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Sapphire4
	if(pFormula->iSapphireNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 사파이어"), _T("Item_Gems_9"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iSapphireNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Sapphire5
	if(pFormula->iSapphireNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 사파이어"), _T("Item_Gems_10"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iSapphireNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Ruby1
	if(pFormula->iRubyNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 루비"), _T("Item_Gems_11"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iRubyNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Ruby2
	if(pFormula->iRubyNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 루비"), _T("Item_Gems_12"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iRubyNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Ruby3
	if(pFormula->iRubyNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 루비"), _T("Item_Gems_13"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iRubyNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Ruby4
	if(pFormula->iRubyNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 루비"), _T("Item_Gems_14"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iRubyNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Ruby5
	if(pFormula->iRubyNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 루비"), _T("Item_Gems_15"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iRubyNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Emerald1
	if(pFormula->iEmeraldNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 에메랄드"), _T("Item_Gems_16"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iEmeraldNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Emerald2
	if(pFormula->iEmeraldNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 에메랄드"), _T("Item_Gems_17"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iEmeraldNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Emerald3
	if(pFormula->iEmeraldNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 에메랄드"), _T("Item_Gems_18"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iEmeraldNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Emerald4
	if(pFormula->iEmeraldNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 에메랄드"), _T("Item_Gems_19"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iEmeraldNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Emerald5
	if(pFormula->iEmeraldNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 에메랄드"), _T("Item_Gems_20"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iEmeraldNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Diamond1
	if(pFormula->iDiamondNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 다이아몬드"), _T("Item_Gems_21"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iDiamondNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Diamond2
	if(pFormula->iDiamondNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 다이아몬드"), _T("Item_Gems_22"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iDiamondNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Diamond3
	if(pFormula->iDiamondNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 다이아몬드"), _T("Item_Gems_23"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iDiamondNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Diamond4
	if(pFormula->iDiamondNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 다이아몬드"), _T("Item_Gems_24"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iDiamondNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Diamond5
	if(pFormula->iDiamondNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 다이아몬드"), _T("Item_Gems_25"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iDiamondNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Amethyst1
	if(pFormula->iAmethystNum1 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨1 자수정"), _T("Item_Gems_26"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST1, -1, -1, 1, 1, 2, 0, 1000, pFormula->iAmethystNum1, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Amethyst2
	if(pFormula->iAmethystNum2 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨2 자수정"), _T("Item_Gems_27"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST2, -1, -1, 1, 1, 2, 0, 5000, pFormula->iAmethystNum2, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Amethyst3
	if(pFormula->iAmethystNum3 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨3 자수정"), _T("Item_Gems_28"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST3, -1, -1, 1, 1, 2, 0, 25000, pFormula->iAmethystNum3, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Amethyst4
	if(pFormula->iAmethystNum4 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨4 자수정"), _T("Item_Gems_29"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST4, -1, -1, 1, 1, 2, 0, 75000, pFormula->iAmethystNum4, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
	// Amethyst5
	if(pFormula->iAmethystNum5 != 0 && ++iCnt)
	{
		CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, &Item(_T("레벨5 자수정"), _T("Item_Gems_30"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST5, -1, -1, 1, 1, 2, 0, 155000, pFormula->iAmethystNum5, 0, 0));
		m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f + 0.053f * iCnt, -0.279f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845045f, 0.0f);

		pItemSign->Initialize();
		pItemSign->EnableGridSign();
		pItemSign->EnableItemPannelSign();
		m_GemItemSign.push_back(pItemSign);
	}
}

void CEnchantWindow::CreateAccessoryFormula()
{
	// AccessoryItemSign Clear
	for(size_t i = 0; i < m_AccessoryItemSign.size(); ++i)
	{
		m_AccessoryItemSign[i]->Destroy();
		m_AccessoryItemSign[i] = NULL;
	}
	m_AccessoryItemSign.clear();

	// ItemMakeButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);

	// Formula
	Formula* pFormula = m_AccessoryFormula[m_iFormulaType][m_iFormulaSelect];

	// ItemSign
	CItemSign* pItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, pFormula->pItem);
	m_pLayer->AddObject(pItemSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)pItemSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.920992f, -0.279f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.0490093f, 0.0845f, 0.0f);

	pItemSign->Initialize();
	pItemSign->EnableGridSign();
	pItemSign->EnableSockSign();
	m_AccessoryItemSign.push_back(pItemSign);

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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
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
		m_AccessoryItemSign.push_back(pItemSign);
	}
}

void CEnchantWindow::MakeGem()
{
	// Formula
	Formula* pFormula = m_GemFormula[m_iFormulaType][m_iFormulaSelect];

	// Topaz1
	if(pFormula->iTopazNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 토파즈"), _T("Item_Gems_1"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iTopazNum1;
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

	// Topaz2
	if(pFormula->iTopazNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 토파즈"), _T("Item_Gems_2"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iTopazNum2;
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

	// Topaz3
	if(pFormula->iTopazNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 토파즈"), _T("Item_Gems_3"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iTopazNum3;
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

	// Topaz4
	if(pFormula->iTopazNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 토파즈"), _T("Item_Gems_4"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iTopazNum4;
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

	// Topaz5
	if(pFormula->iTopazNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 토파즈"), _T("Item_Gems_5"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_TOPAZ5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iTopazNum5;
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

	// Sapphire1
	if(pFormula->iSapphireNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 사파이어"), _T("Item_Gems_6"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iSapphireNum1;
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

	// Sapphire2
	if(pFormula->iSapphireNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 사파이어"), _T("Item_Gems_7"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iSapphireNum2;
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

	// Sapphire3
	if(pFormula->iSapphireNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 사파이어"), _T("Item_Gems_8"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iSapphireNum3;
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

	// Sapphire4
	if(pFormula->iSapphireNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 사파이어"), _T("Item_Gems_9"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iSapphireNum4;
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

	// Sapphire5
	if(pFormula->iSapphireNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 사파이어"), _T("Item_Gems_10"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_SAPPHIRE5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iSapphireNum5;
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

	// Ruby1
	if(pFormula->iRubyNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 루비"), _T("Item_Gems_11"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iRubyNum1;
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

	// Ruby2
	if(pFormula->iRubyNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 루비"), _T("Item_Gems_12"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iRubyNum2;
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

	// Ruby3
	if(pFormula->iRubyNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 루비"), _T("Item_Gems_13"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iRubyNum3;
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

	// Ruby4
	if(pFormula->iRubyNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 루비"), _T("Item_Gems_14"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iRubyNum4;
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

	// Ruby5
	if(pFormula->iRubyNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 루비"), _T("Item_Gems_15"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_RUBY5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iRubyNum5;
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

	// Emerald1
	if(pFormula->iEmeraldNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 에메랄드"), _T("Item_Gems_16"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iEmeraldNum1;
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

	// Emerald2
	if(pFormula->iEmeraldNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 에메랄드"), _T("Item_Gems_17"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iEmeraldNum2;
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

	// Emerald3
	if(pFormula->iEmeraldNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 에메랄드"), _T("Item_Gems_18"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iEmeraldNum3;
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

	// Emerald4
	if(pFormula->iEmeraldNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 에메랄드"), _T("Item_Gems_19"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iEmeraldNum4;
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

	// Emerald5
	if(pFormula->iEmeraldNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 에메랄드"), _T("Item_Gems_20"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_EMERALD5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iEmeraldNum5;
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

	// Diamond1
	if(pFormula->iDiamondNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 다이아몬드"), _T("Item_Gems_21"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iDiamondNum1;
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

	// Diamond2
	if(pFormula->iDiamondNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 다이아몬드"), _T("Item_Gems_22"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iDiamondNum2;
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

	// Diamond3
	if(pFormula->iDiamondNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 다이아몬드"), _T("Item_Gems_23"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iDiamondNum3;
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

	// Diamond4
	if(pFormula->iDiamondNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 다이아몬드"), _T("Item_Gems_24"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iDiamondNum4;
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

	// Diamond5
	if(pFormula->iDiamondNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 다이아몬드"), _T("Item_Gems_25"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_DIAMOND5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iDiamondNum5;
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

	// Amethyst1
	if(pFormula->iAmethystNum1 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨1 자수정"), _T("Item_Gems_26"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST1, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

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

		int iNum = pFormula->iAmethystNum1;
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

	// Amethyst2
	if(pFormula->iAmethystNum2 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨2 자수정"), _T("Item_Gems_27"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST2, -1, -1, 1, 1, 2, 0, 5000, 1, 0, 0));

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

		int iNum = pFormula->iAmethystNum2;
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

	// Amethyst3
	if(pFormula->iAmethystNum3 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨3 자수정"), _T("Item_Gems_28"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST3, -1, -1, 1, 1, 2, 0, 25000, 1, 0, 0));

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

		int iNum = pFormula->iAmethystNum3;
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

	// Amethyst4
	if(pFormula->iAmethystNum4 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨4 자수정"), _T("Item_Gems_29"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST4, -1, -1, 1, 1, 2, 0, 75000, 1, 0, 0));

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

		int iNum = pFormula->iAmethystNum4;
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

	// Amethyst5
	if(pFormula->iAmethystNum5 > 0)
	{
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("레벨5 자수정"), _T("Item_Gems_30"), NULL, 0, ITEM_TYPE_GEM, GEM_ID_AMETHYST5, -1, -1, 1, 1, 2, 0, 155000, 1, 0, 0));

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

		int iNum = pFormula->iAmethystNum5;
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

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("MakeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
}

void CEnchantWindow::MakeAccessory()
{
	// Formula
	Formula* pFormula = m_AccessoryFormula[m_iFormulaType][m_iFormulaSelect];

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

	CSoundMgr::GetInstance()->PlaySoundForUI(_T("MakeItem.ogg"));
	CItemMgr::GetInstance()->CommitInven();
	CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
}

////////////////////////////////////////////////////////////////////////// Pick
void CEnchantWindow::UpdateNonePick()
{
}
void CEnchantWindow::UpdatePick()
{
}
void CEnchantWindow::UpdateInventoryPick()
{
}
void CEnchantWindow::UpdateEquipmentPick()
{
}

////////////////////////////////////////////////////////////////////////// In
void CEnchantWindow::UpdateIn()
{
}
void CEnchantWindow::UpdateNonePickIn()
{
	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	// PageButton
	for(int i = 0; i < 3; ++i)
	{
		if(m_iPage == i)
			continue;

		if(m_pEnchantButton[i]->IsLDown())
		{
			m_pEnchantButton[m_iPage]->SetState(0);
			m_iPage = i;
			Renew();
			break;
		}
	}
}
void CEnchantWindow::UpdatePickIn()
{
}
void CEnchantWindow::UpdateInventoryPickIn()
{
}
void CEnchantWindow::UpdateEquipmentPickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CEnchantWindow::UpdateOut()
{
}
void CEnchantWindow::UpdateNonePickOut()
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
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_JEWELER)
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
void CEnchantWindow::UpdatePickOut()
{
}
void CEnchantWindow::UpdateInventoryPickOut()
{
}
void CEnchantWindow::UpdateEquipmentPickOut()
{
}

////////////////////////////////////////////////////////////////////////// InEnchant
void CEnchantWindow::UpdateInEnchant()
{
}
void CEnchantWindow::UpdateNonePickInEnchant()
{
	// GemCategoryButton
	for(int i = 0; i < 6; ++i)
	{
		if(m_pGemCategoryButton[i]->IsLUp())
		{
			if(m_pGemCategoryButton[i]->IsOpen())
			{
				m_pGemCategoryButton[i]->Close();
				CloseGemCategory(i);
			}
			else
			{
				m_pGemCategoryButton[i]->Open();
				OpenGemCategory(i);
			}

			break;
		}
	}

	// AccessoryCategoryButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pAccessoryCategoryButton[i]->IsLUp())
		{
			if(m_pAccessoryCategoryButton[i]->IsOpen())
			{
				m_pAccessoryCategoryButton[i]->Close();
				CloseAccessoryCategory(i);
			}
			else
			{
				m_pAccessoryCategoryButton[i]->Open();
				OpenAccessoryCategory(i);
			}

			break;
		}
	}

	// GemFormulaButton
	for(int i = 0; i < 6; ++i)
	{
		for(size_t j = 0; j < m_GemFormulaButton[i].size(); ++j)
		{
			if(m_iFormulaType == i && m_iFormulaSelect == j)
				continue;

			if(m_GemFormulaButton[i][j]->IsLUp())
			{
				m_iFormulaType = i;
				m_iFormulaSelect = j;
				CreateGemFormula();
				break;
			}
		}
	}

	// AccessoryFormulaButton
	for(int i = 0; i < 2; ++i)
	{
		for(size_t j = 0; j < m_AccessoryFormulaButton[i].size(); ++j)
		{
			if(m_iFormulaType == i && m_iFormulaSelect == j)
				continue;

			if(m_AccessoryFormulaButton[i][j]->IsLUp())
			{
				m_iFormulaType = i;
				m_iFormulaSelect = j;
				CreateAccessoryFormula();
				break;
			}
		}
	}

	// ScrollUpButton
	if(m_ButtonVec[1]->IsLUp())
	{
		if(--m_iScroll < 0)
			m_iScroll = 0;

		UpdateScroll();

		if(m_iPage == 0)
			UpdateGemCategory();
		else if(m_iPage == 1)
			UpdateAccessoryCategory();
	}

	// ScrollDownButton
	if(m_ButtonVec[2]->IsLUp())
	{
		if(++m_iScroll > m_iMaxScroll)
			m_iScroll = m_iMaxScroll;

		UpdateScroll();

		if(m_iPage == 0)
			UpdateGemCategory();
		else if(m_iPage == 1)
			UpdateAccessoryCategory();
	}

	// ItemMakeButton
	if(m_ButtonVec[3]->IsLUp())
	{
		if(m_iPage == 0)
			MakeGem();
		else if(m_iPage == 1)
			MakeAccessory();
	}

	// DisenchantItemSign
	if(m_pDisenchantItemSign != NULL)
	{
		if(m_pDisenchantItemSign->IsLDown())
		{
			// Pick
			m_pMouse->Pick(m_iDisenchantType, m_iDisenchatSelect, m_pDisenchantItemSign->GetItem());

			// Destroy
			m_pDisenchantItemSign->Destroy();
			m_pDisenchantItemSign = NULL;

			// DisenchantType
			m_iDisenchantType = -1;

			// DisenchantSelect
			m_iDisenchatSelect = -1;

			// DisenchantButton
			CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	// DisenchantButton
	if(m_ButtonVec[4]->IsLUp())
	{
		// Item
		Item* pItem;
		if(m_iDisenchantType == 0)
			pItem = CItemMgr::GetInstance()->GetItemInInven(m_iDisenchatSelect);
		else if(m_iDisenchantType == 1)
			pItem = CItemMgr::GetInstance()->GetItemInEquip(m_iDisenchatSelect);

		bool bSuccess = true;
		for(int i = 0; i < pItem->iSockCnt; ++i)
		{
			if(CItemMgr::GetInstance()->AddItemInInven(pItem->SockArr[i]) == false)
			{
				bSuccess = false;
				break;
			}

			pItem->SockArr[i] = NULL;
		}

		// SockCnt
		pItem->iSockCnt = 0;

		if(bSuccess)
		{
			CItemMgr::GetInstance()->CommitInven();
			if(m_iDisenchantType == 1) { CItemMgr::GetInstance()->CommitEquip(); }
			CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
			if(m_iDisenchantType == 1) { m_pPlayer->Renew(); }

			// DisenchantType
			m_iDisenchantType = -1;

			// DisenchantSelect
			m_iDisenchatSelect = -1;

			// DisenchantItemSign
			m_pDisenchantItemSign->Destroy();
			m_pDisenchantItemSign = NULL;

			// DisenchantButton
			CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			CItemMgr::GetInstance()->RollbackInven();
			if(m_iDisenchantType == 1) { CItemMgr::GetInstance()->RollbackEquip(); }
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));
		}
	}
}
void CEnchantWindow::UpdatePickInEnchant()
{
}
void CEnchantWindow::UpdateInventoryPickInEnchant()
{
	if(m_iPage != 2)
		return;

	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.762996f, 0.396006f), &D3DXVECTOR2(-0.686996f, 0.658006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetItem()->iSockCnt > 0)
			{
				// Destroy
				if(m_pDisenchantItemSign != NULL)
				{
					m_pDisenchantItemSign->Destroy();
					m_pDisenchantItemSign = NULL;
				}

				// DisenchantType
				m_iDisenchantType = 0;

				// DisenchantSelect
				m_iDisenchatSelect = m_pMouse->GetSelect();

				m_pDisenchantItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, m_pMouse->GetItem());
				m_pLayer->AddObject(m_pDisenchantItemSign, LAYER_TYPE_UI);

				CTransformCom* pTransformCom = (CTransformCom*)m_pDisenchantItemSign->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.724996f, 0.542006f, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.076f, 0.232f, 0.0f);

				m_pDisenchantItemSign->EnableGridSign();
				m_pDisenchantItemSign->EnableSockSign();
				m_pDisenchantItemSign->Initialize();

				// DisenchantButton
				pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);
			}
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("제거할 보석이 없습니다."));

			m_pMouse->Drop();
		}
	}
}
void CEnchantWindow::UpdateEquipmentPickInEnchant()
{
	if(m_iPage != 2)
		return;

	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.762996f, 0.396006f), &D3DXVECTOR2(-0.686996f, 0.658006f)))
	{
		if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		{
			if(m_pMouse->GetItem()->iSockCnt > 0)
			{
				// Destroy
				if(m_pDisenchantItemSign != NULL)
				{
					m_pDisenchantItemSign->Destroy();
					m_pDisenchantItemSign = NULL;
				}

				// DisenchantType
				m_iDisenchantType = 1;

				// DisenchantSelect
				m_iDisenchatSelect = m_pMouse->GetSelect();

				m_pDisenchantItemSign = new CItemSign(NULL, OBJ_TYPE_STATIC, m_pMouse->GetItem());
				m_pLayer->AddObject(m_pDisenchantItemSign, LAYER_TYPE_UI);

				CTransformCom* pTransformCom = (CTransformCom*)m_pDisenchantItemSign->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vPos = D3DXVECTOR3(-0.724996f, 0.542006f, 0.0f);
				pTransformCom->m_vSize = D3DXVECTOR3(0.076f, 0.232f, 0.0f);

				m_pDisenchantItemSign->EnableGridSign();
				m_pDisenchantItemSign->EnableSockSign();
				m_pDisenchantItemSign->Initialize();

				// DisenchantButton
				pTransformCom = (CTransformCom*)m_ButtonVec[4]->GetComponent(COM_TYPE_TRANSFORM);
				pTransformCom->m_vSize = D3DXVECTOR3(0.30458f, 0.0906f, 0.0f);
			}
			else
				CUIMgr::GetInstance()->CreateTextMessage(_T("제거할 보석이 없습니다."));

			m_pMouse->Drop();
		}
	}
}