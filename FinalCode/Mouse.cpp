#include "StdAfx.h"
#include "Mouse.h"

CMouse::CMouse(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CObject(_tszObjKey, _eObjType)
{
	// Texture
	m_pTexture[0] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_Arrow"));
	m_pTexture[1] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_PickInven"));
	m_pTexture[2] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_PickEquip"));
	m_pTexture[3] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_PickStorage"));
	m_pTexture[4] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_PickStore"));
	m_pTexture[5] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_Decompose"));
	m_pTexture[6] = CTextureMgr::GetInstance()->GetTexture(_T("Mouse_PickFollowerEquip"));

	// PickType
	m_iPickType = -1;

	// OverType
	m_eMouseOverType = MOUSE_OVER_TYPE_NONE;

	// Select
	m_iSelect = -1;

	// ItemSign
	m_pItemSign = NULL;

	// OverObject
	m_pOverObject = NULL;

	// UpdateCom
	AddComponent(new CUpdateCom(UPDATE_TYPE_MOUSE));

	// RenderCom
	AddComponent(new CRenderCom(RENDER_TYPE_MOUSE));

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0333f, 0.0592f, 0.0f);
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	CObject::Initialize();

	// Texture
	m_pMaterialCom->m_pTexture = m_pTexture[0];
}

int CMouse::Update()
{
	CObject::Update();

	// Pos
	ScreenToProj(&m_pTransformCom->m_vPos, CInputMgr::GetInstance()->GetMousePos());
	m_pTransformCom->m_vPos += D3DXVECTOR3(0.0166f, -0.0296f, 0.0f);

	// ItemSign
	if(m_pItemSign != NULL)
	{
		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pItemSign->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFE;

		CRenderCom* pRenderCom = (CRenderCom*)m_pItemSign->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000001;

		CTransformCom* pTransformCom = (CTransformCom*)m_pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos - D3DXVECTOR3(0.0166f, -0.0296f, 0.0f);
	}

	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON) || CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON))
	{
		if(CInputMgr::GetInstance()->GetPickPos() != NULL)
		{
			CMousePickEffect* pMousePickEffect = new CMousePickEffect(NULL, OBJ_TYPE_STATIC);
			m_pLayer->AddObject(pMousePickEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pMousePickEffect->GetComponent(COM_TYPE_TRANSFORM);
			memcpy_s(&pTransformCom->m_vPos, sizeof(D3DXVECTOR3), CInputMgr::GetInstance()->GetPickPos(), sizeof(D3DXVECTOR3));

			pMousePickEffect->Initialize();
		}
	}

	// Escape
	if(CInputMgr::GetInstance()->KeyDown(DIK_ESCAPE) && m_iPickType != -1)
	{
		CInputMgr::GetInstance()->KeyStop(DIK_ESCAPE);
		Drop();
	}

	// RButton
	if(CInputMgr::GetInstance()->MouseDown(DIM_RBUTTON) && m_iPickType != -1)
	{
		CInputMgr::GetInstance()->MouseStop(DIM_RBUTTON);
		Drop();
	}

	// LButton
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON) && m_iPickType != -1 && m_iPickType != 0 && m_iPickType != 1 && m_iPickType != 2 && m_iPickType != 5)
	{
		D3DXVECTOR3 vPos;
		ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

		if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.4389982f, -1.0f), &D3DXVECTOR2(0.4529938f, 1.0f)))
		{
			CInputMgr::GetInstance()->MouseStop(DIM_LBUTTON);
			Drop();
		}
	}

	// Pos
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.447499f, -1.0f), &D3DXVECTOR2(1.0f, 1.0f)))
		UpdateInInventory();
	else if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(-0.955495f, -0.486996f), &D3DXVECTOR2(-0.496497f, 0.606999f)))
		UpdateInStorage();

	// OverType
	m_eMouseOverType = MOUSE_OVER_TYPE_NONE;

	// OverObject
	m_pOverObject = NULL;

	return 0;
}

void CMouse::Render()
{
	CObject::Render();

	// Texture
	m_pMaterialCom->m_pTexture = m_pTexture[m_iPickType + 1];
}

void CMouse::Release()
{
	// ItemSign
	if(m_pItemSign != NULL)
	{
		m_pItemSign->Destroy();
		m_pItemSign = NULL;
	}
}

void CMouse::UpdateInInventory()
{
	// ItemSign
	if(m_pItemSign != NULL)
	{
		// TransformCom
		CTransformCom* pTransformCom = (CTransformCom*)m_pItemSign->GetComponent(COM_TYPE_TRANSFORM);

		// Item
		Item* pItem = m_pItemSign->GetItem();

		// LT
		D3DXVECTOR2 vLT;
		vLT.x = pTransformCom->m_vPos.x - pTransformCom->m_vSize.x / 2.0f;
		vLT.y = pTransformCom->m_vPos.y + pTransformCom->m_vSize.y / 2.0f;

		// RB
		D3DXVECTOR2 vRB;
		vRB.x = pTransformCom->m_vPos.x + pTransformCom->m_vSize.x / 2.0f;
		vRB.y = pTransformCom->m_vPos.y - pTransformCom->m_vSize.y / 2.0f;

		// Pos
		float fPosX = (vLT.x - 0.4635f) / 0.0525f;
		float fPosY = (vLT.y + 0.0355f) / -0.09216667f;

		pItem->iPosX = fPosX < 0.0f ? int(fPosX - 0.5f) : int(fPosX + 0.5f);
		pItem->iPosY = fPosY < 0.0f ? int(fPosY - 0.5f) : int(fPosY + 0.5f);
	}
}

void CMouse::UpdateInStorage()
{
	// ItemSign
	if(m_pItemSign != NULL)
	{
		// TransformCom
		CTransformCom* pTransformCom = (CTransformCom*)m_pItemSign->GetComponent(COM_TYPE_TRANSFORM);

		// Item
		Item* pItem = m_pItemSign->GetItem();

		// LT
		D3DXVECTOR2 vLT;
		vLT.x = pTransformCom->m_vPos.x - pTransformCom->m_vSize.x / 2.0f;
		vLT.y = pTransformCom->m_vPos.y + pTransformCom->m_vSize.y / 2.0f;

		// RB
		D3DXVECTOR2 vRB;
		vRB.x = pTransformCom->m_vPos.x + pTransformCom->m_vSize.x / 2.0f;
		vRB.y = pTransformCom->m_vPos.y - pTransformCom->m_vSize.y / 2.0f;

		// Pos
		float fPosX = (vLT.x + 0.955495f) / 0.0655711f;
		float fPosY = (vLT.y - 0.606999f) / -0.1093995f;

		pItem->iPosX = fPosX < 0.0f ? int(fPosX - 0.5f) : int(fPosX + 0.5f);
		pItem->iPosY = fPosY < 0.0f ? int(fPosY - 0.5f) : int(fPosY + 0.5f);
	}
}

void CMouse::Pick(int _iPickType, int _iSelect, Item* _pItem)
{
	// PickType
	m_iPickType = _iPickType;

	// Select
	m_iSelect = _iSelect;

	// ItemSign
	if(_pItem != NULL)
	{
		m_pItemSign = new CItemSign(NULL, OBJ_TYPE_DYNAMIC, _pItem);
		m_pLayer->AddObject(m_pItemSign, LAYER_TYPE_UI);

		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pItemSign->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFE;

		CRenderCom* pRenderCom = (CRenderCom*)m_pItemSign->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000001;

		CTransformCom* pTransformCom = (CTransformCom*)m_pItemSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos - D3DXVECTOR3(0.0166f, -0.0296f, 0.0f);

		// Inventory
		if(m_iPickType == 0)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
			pTransformCom->m_vSize.x = _pItem->iWidth * 0.0525f;
			pTransformCom->m_vSize.y = _pItem->iHeight * 0.09216667f;
		}
		// Equipment
		else if(m_iPickType == 1)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
			pTransformCom->m_vSize.x = _pItem->iWidth * 0.0525f;
			pTransformCom->m_vSize.y = _pItem->iHeight * 0.09216667f;
		}
		// Storage
		else if(m_iPickType == 2)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
			pTransformCom->m_vSize.x = _pItem->iWidth * 0.0655711f;
			pTransformCom->m_vSize.y = _pItem->iHeight * 0.1093995f;
		}
		// Store
		else if(m_iPickType == 3)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
			pTransformCom->m_vSize.x = _pItem->iWidth * 0.0655711f;
			pTransformCom->m_vSize.y = _pItem->iHeight * 0.1093995f;
		}
		// Decompose
		else if(m_iPickType == 4)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
		}
		// FollowerEquip
		else if(m_iPickType == 5)
		{
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("Pick_Mouse.ogg"));
			pTransformCom->m_vSize.x = _pItem->iWidth * 0.0525f;
			pTransformCom->m_vSize.y = _pItem->iHeight * 0.09216667f;
		}

		m_pItemSign->Initialize();
	}
}

void CMouse::Drop()
{
	// Inventory
	if(m_iPickType == 0)
	{
		if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_HELMS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SHOULDERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_CHESTARMOR)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BRACERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GLOVES)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BELT)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_PANTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BOOTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_AMULET)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_RING)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SUB_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GEM)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GemDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MATERIAL)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("MaterialDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_QUEST)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("QuestDrop_Mouse.ogg"));
	}
	// Equipment
	else if(m_iPickType == 1)
	{
		if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_HELMS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SHOULDERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_CHESTARMOR)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BRACERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GLOVES)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BELT)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_PANTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BOOTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_AMULET)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_RING)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SUB_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GEM)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GemDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MATERIAL)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("MaterialDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_QUEST)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("QuestDrop_Mouse.ogg"));
	}
	// Storage
	else if(m_iPickType == 2)
	{
		if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_HELMS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SHOULDERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_CHESTARMOR)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BRACERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GLOVES)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BELT)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_PANTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BOOTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_AMULET)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_RING)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SUB_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GEM)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GemDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MATERIAL)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("MaterialDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_QUEST)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("QuestDrop_Mouse.ogg"));
	}
	// Store
	else if(m_iPickType == 3)
	{
		if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_HELMS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SHOULDERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_CHESTARMOR)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BRACERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GLOVES)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BELT)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_PANTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BOOTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_AMULET)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_RING)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SUB_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GEM)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GemDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MATERIAL)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("MaterialDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_QUEST)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("QuestDrop_Mouse.ogg"));
	}
	// Decompose
	else if(m_iPickType == 4)
	{
	}
	// FollowerEquip
	else if(m_iPickType == 5)
	{
		if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MAIN_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_HELMS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SHOULDERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_CHESTARMOR)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BRACERS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GLOVES)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BELT)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_PANTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_BOOTS)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("ArmorDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_AMULET)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_RING)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("AccessoryDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_SUB_WEAPON)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("WeaponDrop_Mouse.ogg"));
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_GEM)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GemDrop_Mouse.ogg"));		
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_MATERIAL)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("MaterialDrop_Mouse.ogg"));	
		else if(m_pItemSign->GetItem()->dwItemType & ITEM_TYPE_QUEST)
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("QuestDrop_Mouse.ogg"));
	}

	// PickType
	m_iPickType = -1;

	// Select
	m_iSelect = -1;

	// ItemSign
	if(m_pItemSign != NULL)
	{
		m_pItemSign->Destroy();
		m_pItemSign = NULL;
	}
}

void CMouse::Over(MOUSE_OVER_TYPE _eMouseOverType, CObject* _pOverObject)
{
	if(m_pOverObject != NULL)
	{
		if(m_eMouseOverType == MOUSE_OVER_TYPE_NPC)
			((CNPC*)m_pOverObject)->DisOver();
		else if(m_eMouseOverType == MOUSE_OVER_TYPE_DROP_ITEM)
			((CDropItem*)m_pOverObject)->DisOver();
		else if(m_eMouseOverType == MOUSE_OVER_TYPE_STATIC_PROB)
			((CStaticProb*)m_pOverObject)->DisOver();
		else if(m_eMouseOverType == MOUSE_OVER_TYPE_DYNAMIC_PROB)
			((CDynamicProb*)m_pOverObject)->DisOver();
		else if(m_eMouseOverType == MOUSE_OVER_TYPE_MONSTER)
			((CMonster*)m_pOverObject)->DisOver();

		m_pOverObject = NULL;
	}

	// OverType
	m_eMouseOverType = _eMouseOverType;

	// OverObject
	m_pOverObject = _pOverObject;
}

Item* CMouse::GetItem()
{
	if(m_pItemSign == NULL)
		return NULL;

	return m_pItemSign->GetItem();
}