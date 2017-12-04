#include "StdAfx.h"
#include "GateWayWindow.h"

CGateWayWindow::CGateWayWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, GATE_WAY_TYPE _eGateWayType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_GateWay"))
{
	// GateWayType
	m_eGateWayType = _eGateWayType;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CGateWayWindow::~CGateWayWindow()
{
	Release();
}

void CGateWayWindow::Initialize()
{
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));

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

	// TristramButton(1)
	CBasicButton* pTristramButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Tristram"), _T("Button_Over_Tristram"), _T("Button_Down_Tristram"));
	m_pLayer->AddObject(pTristramButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pTristramButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, 0.63f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pTristramButton->Initialize();
	AddButton(pTristramButton);

	// TristramFieldButton(2)
	CBasicButton* pTristramFieldButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_TristramField"), _T("Button_Over_TristramField"), _T("Button_Down_TristramField"));
	m_pLayer->AddObject(pTristramFieldButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pTristramFieldButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, 0.48f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pTristramFieldButton->Initialize();
	AddButton(pTristramFieldButton);

	// Cathedral_F1_Button(3)
	CBasicButton* pCathedral_F1_Button = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cathedral_F1"), _T("Button_Over_Cathedral_F1"), _T("Button_Down_Cathedral_F1"));
	m_pLayer->AddObject(pCathedral_F1_Button, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCathedral_F1_Button->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, 0.33f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pCathedral_F1_Button->Initialize();
	AddButton(pCathedral_F1_Button);

	// Cathedral_F2_Button(4)
	CBasicButton* pCathedral_F2_Button = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cathedral_F2"), _T("Button_Over_Cathedral_F2"), _T("Button_Down_Cathedral_F2"));
	m_pLayer->AddObject(pCathedral_F2_Button, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCathedral_F2_Button->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, 0.18f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pCathedral_F2_Button->Initialize();
	AddButton(pCathedral_F2_Button);

	// Cathedral_F3_Button(5)
	CBasicButton* pCathedral_F3_Button = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cathedral_F3"), _T("Button_Over_Cathedral_F3"), _T("Button_Down_Cathedral_F3"));
	m_pLayer->AddObject(pCathedral_F3_Button, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCathedral_F3_Button->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, 0.03f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pCathedral_F3_Button->Initialize();
	AddButton(pCathedral_F3_Button);

	// Cathedral_F4_Button(6)
	CBasicButton* pCathedral_F4_Button = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Cathedral_F4"), _T("Button_Over_Cathedral_F4"), _T("Button_Down_Cathedral_F4"));
	m_pLayer->AddObject(pCathedral_F4_Button, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCathedral_F4_Button->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, -0.12f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pCathedral_F4_Button->Initialize();
	AddButton(pCathedral_F4_Button);

	// Cathedral_F4_Button(7)
	CBasicButton* pRoyalChamberButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_RoyalChamber"), _T("Button_Over_RoyalChamber"), _T("Button_Down_RoyalChamber"));
	m_pLayer->AddObject(pRoyalChamberButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pRoyalChamberButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.723996f, -0.27f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.481997f, 0.144f, 0.0f);
	pRoyalChamberButton->Initialize();
	AddButton(pRoyalChamberButton);
}

int CGateWayWindow::Update()
{
	// Find Player
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

	// Player
	CPlayer* pPlayer = (CPlayer*)pFindObject;

	// Info
	Info* pInfo = pPlayer->GetInfo();

	// Find StaticProbs
	vector<CObject*> StaticProbVec;
	m_pLayer->FindObjects(StaticProbVec, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);
	
	for(size_t i = 0; i < StaticProbVec.size(); ++i)
	{
		CStaticProb* pStaticProb = (CStaticProb*)StaticProbVec[i];
		if(pStaticProb->GetProbType() == PROB_TYPE_GATE_WAY)
		{
			CGateWay* pGateWay = (CGateWay*)pStaticProb;
			if(pGateWay->GetGateWayType() == m_eGateWayType)
			{
				CTransformCom* pTransformComA = (CTransformCom*)pGateWay->GetComponent(COM_TYPE_TRANSFORM);
				CTransformCom* pTransformComB = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

				float fDist = D3DXVec3Length(&(pTransformComA->m_vPos - pTransformComB->m_vPos));
				if(fDist > 150.0f)
					Destroy();

				break;
			}
		}
	}

	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	if(m_ButtonVec[1]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_TRISTREAM)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_TRISTREAM))
		{
			CScene* pScene = new CPlayScene_Tristram(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(7072.33f, 310.0f, 4053.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Tristram"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[2]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_TRISTREAM_FIELD)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_TRISTREAM_FIELD))
		{
			CScene* pScene = new CPlayScene_Tristram(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(6485.0f, 510.0f, 16868.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Tristram"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[3]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_CATHEDRAL_F1)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_CATHEDRAL_F1))
		{
			CScene* pScene = new CPlayScene_Cathedral_F1(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(6704.91f, 377.0f, 8659.27f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Cathedral_F1"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[4]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_CATHEDRAL_F2)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_CATHEDRAL_F2))
		{
			CScene* pScene = new CPlayScene_Cathedral_F2(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(6705.3f, 376.0f, 14781.1f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Cathedral_F2"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[5]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_CATHEDRAL_F3)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_CATHEDRAL_F3))
		{
			CScene* pScene = new CPlayScene_Cathedral_F3(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(496.429f, 352.0f, 4848.03f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Cathedral_F3"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[6]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_CATHEDRAL_F4)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_CATHEDRAL_F4))
		{
			CScene* pScene = new CPlayScene_Cathedral_F4(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(4739.69f, 10.0f, 4689.99f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("Cathedral_F4"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}
	if(m_ButtonVec[7]->IsLUp() && m_eGateWayType != GATE_WAY_TYPE_ROYAL_CHAMBER)
	{
		if(CDataMgr::GetInstance()->IsGateWay(GATE_WAY_TYPE_ROYAL_CHAMBER))
		{
			CScene* pScene = new CPlayScene_RoyalChamber(CSceneMgr::GetInstance()->GetScene());
			CSceneMgr::GetInstance()->SetNextScene(pScene, true, &D3DXVECTOR3(10464.0f, 61.0f, 14047.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			_tcscpy_s(pInfo->tszMapKey, MIN_STR, _T("RoyalChamber"));
		}
		else
			CUIMgr::GetInstance()->CreateTextMessage(_T("게이트웨이가 존재하지 않습니다."));
	}

	CWindowUI::Update();

	return 0;
}

void CGateWayWindow::Render()
{
	CWindowUI::Render();
}

void CGateWayWindow::Release()
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
}