#include "StdAfx.h"
#include "LoginScene.h"

CLoginScene::CLoginScene(CScene* _pScene)
: CScene(_pScene)
{
	// IDTextField
	m_pIDTextField = NULL;

	// PWTextField
	m_pPWTextField = NULL;

	// SettingButton
	m_pSettingButton = NULL;

	// ProducerButton
	m_pProducerButton = NULL;

	// AccessButton
	m_pAccessButton = NULL;

	// DestroyButton
	m_pDestroyButton = NULL;

	// WhiteCursor
	m_pWhiteCursor = NULL;

	// AdviceButton
	m_pAdviceButton = NULL;
}

CLoginScene::~CLoginScene()
{
	Release();
}

void CLoginScene::Initialize()
{
	CScene::Initialize();
}

CScene* CLoginScene::Update()
{
	return CScene::Update();
}

void CLoginScene::Render()
{
	CScene::Render();
}

void CLoginScene::Release()
{
}

CScene* CLoginScene::UpdateLoad()
{
	return CScene::UpdateLoad();
}

CScene* CLoginScene::UpdateComplete()
{
	// PlaySoundForSystemBGM
	CSoundMgr::GetInstance()->StopSoundForSystemBGM();
	CSoundMgr::GetInstance()->PlaySoundForSystemBGM(_T("BGM1.ogg"));

	// TransformCom
	CTransformCom* pTransformCom;

	// Mouse
	CMouse* pMouse = new CMouse(_T("Mouse"), OBJ_TYPE_STATIC);
	m_pLayer[LAYER_TYPE_MOUSE]->AddObject(pMouse);
	pMouse->Initialize();

	// LoginSceneBack
	CLoginSceneBack* pLoginSceneBack = new CLoginSceneBack(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_BACK]->AddObject(pLoginSceneBack);
	pLoginSceneBack->Initialize();

	// IDTextField
	m_pIDTextField = new CIDTextField(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pIDTextField);
	m_pIDTextField->Initialize();
	m_pIDTextField->Enable();

	// PWTextField
	m_pPWTextField = new CPWTextField(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pPWTextField);
	m_pPWTextField->Initialize();

	// AccessButton
	m_pAccessButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Access"), _T("Button_Over_Access"), _T("Button_Down_Access"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pAccessButton);
	pTransformCom = (CTransformCom*)m_pAccessButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.55f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.4092f, 0.105f, 0.0f);
	m_pAccessButton->Initialize();

	// SettingButton
	m_pSettingButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Setting"), _T("Button_Over_Setting"), _T("Button_Down_Setting"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pSettingButton);
	pTransformCom = (CTransformCom*)m_pSettingButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.6666f, -0.31f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3f, 0.105f, 0.0f);
	m_pSettingButton->Initialize();

	// ProducerButton
	m_pProducerButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Producer"), _T("Button_Over_Producer"), _T("Button_Down_Producer"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pProducerButton);
	pTransformCom = (CTransformCom*)m_pProducerButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.6666f, -0.43f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3f, 0.105f, 0.0f);
	m_pProducerButton->Initialize();

	// AdviceButton
	m_pAdviceButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Advice"), _T("Button_Over_Advice"), _T("Button_Down_Advice"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pAdviceButton);
	pTransformCom = (CTransformCom*)m_pAdviceButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.6666f, -0.55f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3f, 0.105f, 0.0f);
	m_pAdviceButton->Initialize();

	// DestroyButton
	m_pDestroyButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Destroy"), _T("Button_Over_Destroy"), _T("Button_Down_Destroy"));
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pDestroyButton);
	pTransformCom = (CTransformCom*)m_pDestroyButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.6666f, -0.7f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3f, 0.105f, 0.0f);
	m_pDestroyButton->Initialize();

	// WhiteCursor
	m_pWhiteCursor = new CWhiteCursor(NULL, OBJ_TYPE_DYNAMIC);
	m_pLayer[LAYER_TYPE_UI]->AddObject(m_pWhiteCursor);
	pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.17f, -0.1f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.002f, 0.05f, 0.0f);
	m_pWhiteCursor->Initialize();

	return CScene::UpdateComplete();
}

CScene* CLoginScene::UpdatePlay()
{
	if(m_pIDTextField->IsLUp() || (CInputMgr::GetInstance()->KeyDown(DIK_TAB) && m_pPWTextField->IsEnable()))
	{
		m_pIDTextField->Enable();
		m_pPWTextField->Disable();
		m_pWhiteCursor->Visible();
	}
	else if(m_pPWTextField->IsLUp() || (CInputMgr::GetInstance()->KeyDown(DIK_TAB) && m_pIDTextField->IsEnable()))
	{
		m_pIDTextField->Disable();
		m_pPWTextField->Enable();
		m_pWhiteCursor->Visible();
	}
	else if(m_pAccessButton->IsLUp() || CInputMgr::GetInstance()->KeyDown(DIK_RETURN))
	{
		int iResult = CDataMgr::GetInstance()->Load(m_pIDTextField->GetText(), m_pPWTextField->GetText());
		if(iResult == 0)
		{
			CLoadScene* pLoadScene = new CLoadScene(NULL, true);
			pLoadScene->SetNextScene(new CLobbyScene(this));
			pLoadScene->AddLoadVec(LOAD_TYPE_LOBBY_SCENE);

			return pLoadScene;
		}
		else if(iResult == 1)
		{
			CIDEmptyMessage* pIDEmptyMessage = new CIDEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pIDEmptyMessage);
			pIDEmptyMessage->Initialize();
		}
		else if(iResult == 2)
		{
			CPWEmptyMessage* pPWEmptyMessage = new CPWEmptyMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pPWEmptyMessage);
			pPWEmptyMessage->Initialize();
		}
		else if(iResult == 3)
		{
			CPWErrorMessage* pPWErrorMessage = new CPWErrorMessage(NULL, OBJ_TYPE_DYNAMIC);
			m_pLayer[LAYER_TYPE_UI]->AddObject(pPWErrorMessage);
			pPWErrorMessage->Initialize();
		}
	}
	else if(m_pSettingButton->IsLUp())
	{
		cout << "Setting Button LUp" << endl;
	}
	else if(m_pProducerButton->IsLUp())
	{
		CProducerMessage* pProducerMessage = new CProducerMessage(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer[LAYER_TYPE_UI]->AddObject(pProducerMessage);
		pProducerMessage->Initialize();
	}
	else if(m_pAdviceButton->IsLUp())
	{
		CAdviceMessage* pAdviceMessage = new CAdviceMessage(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer[LAYER_TYPE_UI]->AddObject(pAdviceMessage);
		pAdviceMessage->Initialize();
	}
	else if(m_pDestroyButton->IsLUp())
		CSceneMgr::GetInstance()->Destroy();

	if(m_pIDTextField->IsEnable())
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.17f, -0.1f, 0.0f);
		pTransformCom->m_vPos.x = pTransformCom->m_vPos.x + m_pIDTextField->GetWidth() / float(WINCX) * 2.0f;
	}
	else if(m_pPWTextField->IsEnable())
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pWhiteCursor->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.17f, -0.31f, 0.0f);
		pTransformCom->m_vPos.x = pTransformCom->m_vPos.x + m_pPWTextField->GetWidth() / float(WINCX) * 2.0f;
	}

	return CScene::UpdatePlay();
}