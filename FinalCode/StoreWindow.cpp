#include "StdAfx.h"
#include "StoreWindow.h"

CStoreWindow::CStoreWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Store"))
{
	// Page
	m_iPage = 0;

	// Mouse
	m_pMouse = NULL;

	// Player
	m_pPlayer = NULL;

	// StoreButton
	ZeroMemory(m_pStoreButton, sizeof(m_pStoreButton));

	// PuzzleItem
	m_StoreVec[3].push_back(new Item(_T("수수께끼 장신구"), _T("Item_Puzzle_Accessory"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_AMULET | ITEM_TYPE_RING, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 벨트"), _T("Item_Puzzle_Belt"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_BELT, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 신발"), _T("Item_Puzzle_Boots"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_BOOTS, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 손목 보호대"), _T("Item_Puzzle_Bracers"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_BRACERS, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 흉갑"), _T("Item_Puzzle_ChestArmor"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_CHESTARMOR, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 장갑"), _T("Item_Puzzle_Gloves"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_GLOVES, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 모자"), _T("Item_Puzzle_Helm"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_HELMS, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 바지"), _T("Item_Puzzle_Pants"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_PANTS, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 어깨 보호대"), _T("Item_Puzzle_Shoulder"), NULL, ITEM_CLASS_PUZZLE, ITEM_TYPE_SHOULDERS, 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));
	m_StoreVec[3].push_back(new Item(_T("수수께끼 무기"), _T("Item_Puzzle_Weapon"), NULL, ITEM_CLASS_PUZZLE, (ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON), 0, 0, 0, 1, 2, 0, 1, 100, 1, 0, 0));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CStoreWindow::~CStoreWindow()
{
	Release();
}

void CStoreWindow::Initialize()
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

	// WeaponStoreButton
	m_pStoreButton[0] = new CStoreButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_WeaponStore"), _T("Button_Over_WeaponStore"), _T("Button_Down_WeaponStore"));
	m_pLayer->AddObject(m_pStoreButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStoreButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.532f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStoreButton[0]->SetState(UI_L_DOWN);
	m_pStoreButton[0]->Initialize();

	// ArmorStoreButton
	m_pStoreButton[1] = new CStoreButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ArmorStore"), _T("Button_Over_ArmorStore"), _T("Button_Down_ArmorStore"));
	m_pLayer->AddObject(m_pStoreButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStoreButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.332f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStoreButton[1]->Initialize();

	// AccessoryStoreButton
	m_pStoreButton[2] = new CStoreButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_AccessoryStore"), _T("Button_Over_AccessoryStore"), _T("Button_Down_AccessoryStore"));
	m_pLayer->AddObject(m_pStoreButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStoreButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, 0.132f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStoreButton[2]->Initialize();

	// PuzzleStoreButton
	m_pStoreButton[3] = new CStoreButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_PuzzleStore"), _T("Button_Over_PuzzleStore"), _T("Button_Down_PuzzleStore"));
	m_pLayer->AddObject(m_pStoreButton[3], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStoreButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, -0.068f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStoreButton[3]->Initialize();

	// RepurchaseStoreButton
	m_pStoreButton[4] = new CStoreButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_RepurchaseStore"), _T("Button_Over_RepurchaseStore"), _T("Button_Down_RepurchaseStore"));
	m_pLayer->AddObject(m_pStoreButton[4], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pStoreButton[4]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.415f, -0.268f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.085f, 0.2f, 0.0f);
	m_pStoreButton[4]->Initialize();

	Renew();
}

int CStoreWindow::Update()
{
	// Mouse
	CObject* pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Mouse"), LAYER_TYPE_MOUSE);
	m_pMouse = (CMouse*)pFind;

	// Player
	pFind = NULL;
	m_pLayer->FindObject(pFind, _T("Player"), LAYER_TYPE_PLAYER);
	m_pPlayer = (CPlayer*)pFind;

	// StorageSign
	for(size_t i = 0; i < m_StoreSign.size(); ++i)
	{
		if(m_StoreSign[i]->IsOver())
			m_StoreSign[i]->EnableItemMessage();
		else
			m_StoreSign[i]->DisableItemMessage();
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
				UpdateInStore();
				UpdateNonePickInStore();
			}
			break;

		case 0:
			UpdatePick();
			UpdateInventoryPick();
			UpdatePickIn();
			UpdateInventoryPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStore();
				UpdatePickInStore();
				UpdateInventoryPickInStore();
			}
			break;

		case 1:
			UpdatePick();
			UpdateEquipmentPick();
			UpdatePickIn();
			UpdateEquipmentPickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStore();
				UpdatePickInStore();
				UpdateEquipmentPickInStore();
			}
			break;

		case 3:
			UpdatePick();
			UpdateStorePick();
			UpdatePickIn();
			UpdateStorePickIn();

			if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
			{
				UpdateInStore();
				UpdatePickInStore();
				UpdateStorePickInStore();
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

		case 3:
			UpdatePick();
			UpdateStorePick();
			UpdatePickOut();
			UpdateStorePickOut();
			break;
		}
	}

	// StoreButton
	for(int i = 0; i < 5; ++i)
		m_pStoreButton[i]->SetState(0);

	m_pStoreButton[m_iPage]->SetState(UI_L_DOWN);

	CWindowUI::Update();

	return 0;
}

void CStoreWindow::Render()
{
	CWindowUI::Render();

	TCHAR tszGold[MIN_STR];
	_itot_s(CItemMgr::GetInstance()->GetGold(), tszGold, 10);

	RECT rcText;
	SetRect(&rcText, 96, 551, 296, 563);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszGold, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CStoreWindow::Release()
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

	// StoreButton
	for(int i = 0; i < 5; ++i)
	{
		if(m_pStoreButton[i] != NULL)
		{
			m_pStoreButton[i]->Destroy();
			m_pStoreButton[i] = NULL;
		}
	}

	// StoreVec
	for(int i = 0; i < 5; ++i)
	{
		for(size_t j = 0; j < m_StoreVec[i].size(); ++j)
		{
			delete m_StoreVec[i][j];
			m_StoreVec[i][j] = NULL;
		}
		m_StoreVec[i].clear();
	}

	// StoreSign
	for(size_t i = 0; i < m_StoreSign.size(); ++i)
	{
		m_StoreSign[i]->Destroy();
		m_StoreSign[i] = NULL;
	}
	m_StoreSign.clear();
}

void CStoreWindow::Renew()
{
	// StoreSign Clear
	for(size_t i = 0; i < m_StoreSign.size(); ++i)
	{
		m_StoreSign[i]->Destroy();
		m_StoreSign[i] = NULL;
	}
	m_StoreSign.clear();

	// StoreSign
	for(size_t i = 0; i < m_StoreVec[m_iPage].size(); ++i)
	{
		CStoreSign* pStoreSign = new CStoreSign(NULL, OBJ_TYPE_STATIC, m_StoreVec[m_iPage][i]);
		m_pLayer->AddObject(pStoreSign, LAYER_TYPE_UI);

		CTransformCom* pTransformCom = (CTransformCom*)pStoreSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.838995f + 0.229998f * (i % 2), 0.492001f - 0.216249f * (i / 2), 0.0f);

		pStoreSign->Initialize();
		m_StoreSign.push_back(pStoreSign);
	}
}

void CStoreWindow::AddWeapon(Item* _pWeapon)
{
	if(m_StoreVec[0].size() < 10)
		m_StoreVec[0].push_back(_pWeapon);
}

void CStoreWindow::AddArmor(Item* _pArmor)
{
	if(m_StoreVec[1].size() < 10)
		m_StoreVec[1].push_back(_pArmor);
}

void CStoreWindow::AddAccessory(Item* _pAccessory)
{
	if(m_StoreVec[2].size() < 10)
		m_StoreVec[2].push_back(_pAccessory);
}

void CStoreWindow::AddRepurchase(Item* _pRepurchase)
{
	if(m_StoreVec[4].size() >= 10)
	{
		delete m_StoreVec[4][0];
		for(int i = 1; i < 10; ++i)
			m_StoreVec[4][i - 1] = m_StoreVec[4][i];
		m_StoreVec[4].pop_back();
	}

	m_StoreVec[4].push_back(_pRepurchase);
}

void CStoreWindow::RemoveRepurchase(int _iIndex)
{
	if(m_iPage != 4)
		return;

	vector<Item*>::iterator Iter = m_StoreVec[4].begin();
	for(int i = 0; i < _iIndex; ++i, ++Iter);

	delete *Iter;
	m_StoreVec[4].erase(Iter);
}

////////////////////////////////////////////////////////////////////////// Pick
void CStoreWindow::UpdateNonePick()
{
}
void CStoreWindow::UpdatePick()
{
}
void CStoreWindow::UpdateInventoryPick()
{
}
void CStoreWindow::UpdateEquipmentPick()
{
}
void CStoreWindow::UpdateStorePick()
{
}

////////////////////////////////////////////////////////////////////////// In
void CStoreWindow::UpdateIn()
{
}
void CStoreWindow::UpdateNonePickIn()
{
	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	for(int i = 0; i < 5; ++i)
	{
		if(m_iPage == i)
			continue;

		if(m_pStoreButton[i]->IsLDown())
		{
			m_pStoreButton[m_iPage]->SetState(0);
			m_iPage = i;
			Renew();
			break;
		}
	}
}
void CStoreWindow::UpdatePickIn()
{
}
void CStoreWindow::UpdateInventoryPickIn()
{
}
void CStoreWindow::UpdateEquipmentPickIn()
{
}
void CStoreWindow::UpdateStorePickIn()
{
}

////////////////////////////////////////////////////////////////////////// Out
void CStoreWindow::UpdateOut()
{
}
void CStoreWindow::UpdateNonePickOut()
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
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_ARGHUS)
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
void CStoreWindow::UpdatePickOut()
{
}
void CStoreWindow::UpdateInventoryPickOut()
{
}
void CStoreWindow::UpdateEquipmentPickOut()
{
}
void CStoreWindow::UpdateStorePickOut()
{
}

////////////////////////////////////////////////////////////////////////// InStorage
void CStoreWindow::UpdateInStore()
{
}
void CStoreWindow::UpdateNonePickInStore()
{
	for(size_t i = 0; i < m_StoreSign.size(); ++i)
	{
		// Break
		bool bBreak = false;

		// LDown
		if(m_StoreSign[i]->IsLDown())
		{
			m_pMouse->Pick(3, i, m_StoreSign[i]->GetItem());
			bBreak = true;
		}

		// RDown
		else if(m_StoreSign[i]->IsRDown())
		{
			if(CItemMgr::GetInstance()->GetGold() >= m_StoreSign[i]->GetItem()->iValue * m_StoreSign[i]->GetItem()->iNum)
			{
				if(CItemMgr::GetInstance()->BuyOfItem(m_StoreSign[i]->GetItem()))
				{
					RemoveRepurchase(i);
					CItemMgr::GetInstance()->CommitInven();
					CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
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

			bBreak = true;
		}

		if(bBreak)
			break;
	}
}
void CStoreWindow::UpdatePickInStore()
{
}
void CStoreWindow::UpdateInventoryPickInStore()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInInven(m_pMouse->GetSelect())));
		CItemMgr::GetInstance()->SellOfItemInInven(m_pMouse->GetSelect());
		CItemMgr::GetInstance()->CommitInven();
		m_pMouse->Drop();
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
		Renew();
	}
}
void CStoreWindow::UpdateEquipmentPickInStore()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
	{
		AddRepurchase(new Item(CItemMgr::GetInstance()->GetItemInEquip(m_pMouse->GetSelect())));
		CItemMgr::GetInstance()->SellOfItemInEquip(m_pMouse->GetSelect());
		CItemMgr::GetInstance()->CommitEquip();
		m_pMouse->Drop();
		CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
		Renew();
	}
}
void CStoreWindow::UpdateStorePickInStore()
{
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		m_pMouse->Drop();
}