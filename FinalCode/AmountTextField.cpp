#include "StdAfx.h"
#include "AmountTextField.h"

CAmountTextField::CAmountTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iType, int _iIndex, int _iPage /*= -1*/)
: CTextFieldUI(_tszObjKey, _eObjType, _T("TextField_Back_Amount"), _T("TextField_Over_Amount"))
{
	// Enable
	m_bEnable = true;

	// Text
	m_tszText[m_iCnt++] = _T('0');

	// Type
	m_iType = _iType;

	// Index
	m_iIndex = _iIndex;

	// Page
	m_iPage = _iPage;

	// LeftButton
	m_pLeftButton = NULL;

	// RightButton
	m_pRightButton = NULL;

	// ConfirmButton
	m_pConfirmButton = NULL;

	// CancelButton
	m_pCancelButton = NULL;

	// WhiteCursor
	m_pWhiteCursor = NULL;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.2f, 0.15f, 0.0f);
}

CAmountTextField::~CAmountTextField()
{
	Release();
}

void CAmountTextField::Initialize()
{
	CTextFieldUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// LeftButton
	m_pLeftButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Left"), _T("Button_Over_Left"), _T("Button_Down_Left"));
	m_pLayer->AddObject(m_pLeftButton, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pLeftButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.07f, 0.03f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.026f, 0.047f, 0.0f);
	m_pLeftButton->Initialize();

	// RightButton
	m_pRightButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Right"), _T("Button_Over_Right"), _T("Button_Down_Right"));
	m_pLayer->AddObject(m_pRightButton, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pRightButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.07f, 0.03f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.026f, 0.047f, 0.0f);
	m_pRightButton->Initialize();

	// ConfirmButton
	m_pConfirmButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Confirm2"), _T("Button_Over_Confirm2"), _T("Button_Down_Confirm2"));
	m_pLayer->AddObject(m_pConfirmButton, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pConfirmButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.04f, -0.025f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.076f, 0.047f, 0.0f);
	m_pConfirmButton->Initialize();

	// CancelButton
	m_pCancelButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cancel2"), _T("Button_Over_Cancel2"), _T("Button_Down_Cancel2"));
	m_pLayer->AddObject(m_pCancelButton, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pCancelButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.04f, -0.025f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.076f, 0.047f, 0.0f);
	m_pCancelButton->Initialize();

	// WhiteCursor
	m_pWhiteCursor = new CWhiteCursor(NULL, OBJ_TYPE_STATIC);
	m_pLayer->AddObject(m_pWhiteCursor, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.05f, 0.03f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.002f, 0.035f, 0.0f);
	m_pWhiteCursor->Initialize();
}

int CAmountTextField::Update()
{
	// Input
	if(CInputMgr::GetInstance()->KeyDown(DIK_0) || CInputMgr::GetInstance()->KeyDown(DIK_1) || CInputMgr::GetInstance()->KeyDown(DIK_2) || CInputMgr::GetInstance()->KeyDown(DIK_3) || CInputMgr::GetInstance()->KeyDown(DIK_4) || CInputMgr::GetInstance()->KeyDown(DIK_5) || CInputMgr::GetInstance()->KeyDown(DIK_6) || CInputMgr::GetInstance()->KeyDown(DIK_7) || CInputMgr::GetInstance()->KeyDown(DIK_8) || CInputMgr::GetInstance()->KeyDown(DIK_9) || CInputMgr::GetInstance()->KeyDown(DIK_BACK))
	{
		m_pWhiteCursor->Visible();
		CTextFieldUI::Update();
	}
	else
		CUI::Update();

	// Destroy
	if(CInputMgr::GetInstance()->KeyDown(DIK_ESCAPE) || m_pCancelButton->IsLUp())
		Destroy();

	// Item
	Item* pItem;
	if(m_iType == 0)
		pItem = CItemMgr::GetInstance()->GetItemInInven(m_iIndex);
	else if(m_iType == 1)
		pItem = CItemMgr::GetInstance()->GetItemInEquip(m_iIndex);
	else if(m_iType == 2)
		pItem = CItemMgr::GetInstance()->GetItemInStorage(m_iPage, m_iIndex);

	// If, Len == 0..
	if(_tcslen(m_tszText) == 0)
	{
		// Init
		ZeroMemory(m_tszText, sizeof(m_tszText));
		m_iCnt = 0;

		// Set
		m_tszText[0] = _T('0');
		m_iCnt = _tcslen(m_tszText);
	}
	// If, Len >= 2..
	else if(_tcslen(m_tszText) >= 2)
	{
		int iTemp = _ttoi(m_tszText);

		// Init
		ZeroMemory(m_tszText, sizeof(m_tszText));
		m_iCnt = 0;

		// Set
		_itot_s(iTemp, m_tszText, 10);
		m_iCnt = _tcslen(m_tszText);
	}

	// Len, Amount
	int iLen = _tcslen(m_tszText);
	int iAmount = _ttoi(m_tszText);

	// LeftButton
	if(m_pLeftButton->IsLUp())
	{
		if(iAmount - 1 >= 0)
		{
			// Init
			ZeroMemory(m_tszText, sizeof(m_tszText));
			m_iCnt = 0;

			// Set
			_itot_s(--iAmount, m_tszText, 10);
			m_iCnt = iLen = _tcslen(m_tszText);
		}
	}

	// RightButton
	if(m_pRightButton->IsLUp())
	{
		if(iAmount < pItem->iNum)
		{
			// Init
			ZeroMemory(m_tszText, sizeof(m_tszText));
			m_iCnt = 0;

			// Set
			_itot_s(++iAmount, m_tszText, 10);
			m_iCnt = iLen = _tcslen(m_tszText);
		}
	}

	// Amount
	if(iAmount > pItem->iNum)
	{
		_itot_s(pItem->iNum, m_tszText, 10);
		m_iCnt = _tcslen(m_tszText);
	}

	// Confirm
	if(m_pConfirmButton->IsLUp())
	{
		if(iAmount != 0)
		{
			// Temp
			Item* pTemp = new Item(pItem);
			pTemp->iNum = iAmount;

			// FindObject
			CObject* pFindObject = NULL;
			m_pLayer->FindObject(pFindObject, _T("Mouse"), LAYER_TYPE_MOUSE);

			// Mouse
			CMouse* pMouse = (CMouse*)pFindObject;
			pMouse->Pick(m_iType, m_iIndex, pTemp);

			delete pTemp;
		}

		Destroy();
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(-0.045f, 0.03f, 0.0f);
	pTransformCom->m_vPos.x = pTransformCom->m_vPos.x + m_iWidth / float(WINCX) * 2.0f;

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFD;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000002;

	// LeftButton
	pUpdateCom = (CUpdateCom*)m_pLeftButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	pRenderCom = (CRenderCom*)m_pLeftButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;

	// RightButton
	pUpdateCom = (CUpdateCom*)m_pRightButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	pRenderCom = (CRenderCom*)m_pRightButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;

	// ConfirmButton
	pUpdateCom = (CUpdateCom*)m_pConfirmButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	pRenderCom = (CRenderCom*)m_pConfirmButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;

	// CancelButton
	pUpdateCom = (CUpdateCom*)m_pCancelButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	pRenderCom = (CRenderCom*)m_pCancelButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;
	
	// WhiteCursor
	pUpdateCom = (CUpdateCom*)m_pWhiteCursor->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFE;

	pRenderCom = (CRenderCom*)m_pWhiteCursor->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000001;

	CInputMgr::GetInstance()->KeyInvalidate();
	CInputMgr::GetInstance()->MouseInvalidate();
	CInputMgr::GetInstance()->MousePosInvalidate();

	return 0;
}

void CAmountTextField::Render()
{
	CTextFieldUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 30.0f), long(vPos.y - 15.0f), long(vPos.x + 30.0f), long(vPos.y - 3.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_iWidth = rcText.right - rcText.left;
	m_iHeight = rcText.bottom - rcText.top;
}

void CAmountTextField::Release()
{
	// LeftButton
	if(m_pLeftButton != NULL)
	{
		m_pLeftButton->Destroy();
		m_pLeftButton = NULL;
	}

	// RightButton
	if(m_pRightButton != NULL)
	{
		m_pRightButton->Destroy();
		m_pRightButton = NULL;
	}

	// ConfirmButton
	if(m_pConfirmButton != NULL)
	{
		m_pConfirmButton->Destroy();
		m_pConfirmButton = NULL;
	}

	// CancelButton
	if(m_pCancelButton != NULL)
	{
		m_pCancelButton->Destroy();
		m_pCancelButton = NULL;
	}

	// WhiteCursor
	if(m_pWhiteCursor != NULL)
	{
		m_pWhiteCursor->Destroy();
		m_pWhiteCursor = NULL;
	}
}