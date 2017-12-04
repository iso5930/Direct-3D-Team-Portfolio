#include "StdAfx.h"
#include "AchieveWindow.h"

CAchieveWindow::CAchieveWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, NULL)
{
	// Texture
	m_pTexture[0] = CTextureMgr::GetInstance()->GetTexture(_T("Window_AchievePage0"));
	m_pTexture[1] = CTextureMgr::GetInstance()->GetTexture(_T("Window_AchievePage1"));
	m_pBackTexture = m_pTexture[0];

	// Page
	m_iPage = 0;

	// Scroll
	m_iScroll = 0;

	// MaxScroll
	m_iMaxScroll = 0;

	// VScroll
	m_pVScroll = NULL;

	// Title
	ZeroMemory(m_tszTitle, sizeof(m_tszTitle));

	// Content
	ZeroMemory(m_tszContent, sizeof(m_tszContent));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.725f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.61f, 2.04f, 0.0f);
}

CAchieveWindow::~CAchieveWindow()
{
	Release();
}

void CAchieveWindow::Initialize()
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

	// ScrollUpButton(1)
	CBasicButton* pScrollUpButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Up"), _T("Button_Over_Up"), _T("Button_Down_Up"));
	m_pLayer->AddObject(pScrollUpButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollUpButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, 0.512998f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollUpButton->Initialize();
	AddButton(pScrollUpButton);

	// ScrollDownButton(2)
	CBasicButton* pScrollDownButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Down"), _T("Button_Over_Down"), _T("Button_Down_Down"));
	m_pLayer->AddObject(pScrollDownButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pScrollDownButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.535f, -0.515996f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.03258f, 0.0486f, 0.0f);
	pScrollDownButton->Initialize();
	AddButton(pScrollDownButton);

	// ListButton(3)
	CBasicButton* pListButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_List"), _T("Button_Over_List"), _T("Button_Down_List"));
	m_pLayer->AddObject(pListButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pListButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.726f, -0.485f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.269f, 0.09f, 0.0f);
	pListButton->Initialize();
	AddButton(pListButton);

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

	// AchieveButtonVec
	for(int i = 0; i < CQuestMgr::GetInstance()->GetSizeOfAchieve(); ++i)
	{
		CAchieveButton* pAchieveButton = new CAchieveButton(NULL, OBJ_TYPE_STATIC, CQuestMgr::GetInstance()->GetAchieve(i));
		m_pLayer->AddObject(pAchieveButton, LAYER_TYPE_UI);
		pAchieveButton->Initialize();

		m_AchieveButtonVec.push_back(pAchieveButton);
	}

	Renew();
}

int CAchieveWindow::Update()
{
	// Destroy
	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	// ScrollUpButton
	if(m_ButtonVec[1]->IsLUp())
	{
		if(--m_iScroll < 0)
			m_iScroll = 0;

		UpdateScroll();
	}

	// ScrollDownButton
	if(m_ButtonVec[2]->IsLUp())
	{
		if(++m_iScroll > m_iMaxScroll)
			m_iScroll = m_iMaxScroll;

		UpdateScroll();
	}

	// Scroll
	if(m_iScroll != m_pVScroll->GetScroll())
	{
		m_iScroll = m_pVScroll->GetScroll();
		UpdateScroll();
	}

	// ListButton
	if(m_ButtonVec[3]->IsLUp())
	{
		m_iPage = 0;
		Renew();
	}

	// AchieveButtonVec
	for(size_t i = 0; i < m_AchieveButtonVec.size(); ++i)
	{
		if(m_AchieveButtonVec[i]->IsLUp())
		{
			m_iPage = 1;
			UpdateContent(m_AchieveButtonVec[i]->GetAchieve());
			Renew();
		}
	}

	CWindowUI::Update();

	return 0;
}

void CAchieveWindow::Render()
{
	CWindowUI::Render();

	if(m_iPage == 1)
	{
		RECT rcText;
		SetRect(&rcText, 31, 131, 331, 147);
		CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszTitle, -1, &rcText, DT_CENTER, D3DXCOLOR(0.85098f, 0.6f, 0.247058f, 1.0f));

		SetRect(&rcText, 80, 205, 380, 565);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszContent, -1, &rcText, DT_LEFT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void CAchieveWindow::Release()
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

	// AchieveButtonVec
	for(size_t i = 0; i < m_AchieveButtonVec.size(); ++i)
	{
		m_AchieveButtonVec[i]->Destroy();
		m_AchieveButtonVec[i] = NULL;
	}
	m_AchieveButtonVec.clear();

	// VScroll
	if(m_pVScroll != NULL)
	{
		m_pVScroll->Destroy();
		m_pVScroll = NULL;
	}
}

void CAchieveWindow::Renew()
{
	// Texture
	m_pBackTexture = m_pTexture[m_iPage];

	// ScrollUpButton
	CTransformCom* pTransformCom = (CTransformCom*)m_ButtonVec[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize.x = 0.0f;

	// ScrollDownButton
	pTransformCom = (CTransformCom*)m_ButtonVec[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize.x = 0.0f;

	// ListButton
	pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize.x = 0.0f;

	// VScroll
	pTransformCom = (CTransformCom*)m_pVScroll->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vSize.x = 0.0f;

	// AchieveButtonVec Init
	for(size_t i = 0; i < m_AchieveButtonVec.size(); ++i)
	{
		pTransformCom = (CTransformCom*)m_AchieveButtonVec[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if(m_iPage == 0)
	{
		UpdateScroll();
	}
	else if(m_iPage == 1)
	{
		// ListButton
		pTransformCom = (CTransformCom*)m_ButtonVec[3]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize.x = 0.269f;
	}
}

void CAchieveWindow::UpdateScroll()
{
	// AchieveButtonVec Init
	for(size_t i = 0; i < m_AchieveButtonVec.size(); ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_AchieveButtonVec[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// MaxScroll
	m_iMaxScroll = int(m_AchieveButtonVec.size()) - 8;
	if(m_iMaxScroll < 0)
		m_iMaxScroll = 0;

	// Scroll
	if(m_iScroll > m_iMaxScroll)
		m_iScroll = m_iMaxScroll;

	// AchieveButtonVec Set
	for(size_t i = m_iScroll; i < m_AchieveButtonVec.size() && i < m_iScroll + 8; ++i)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_AchieveButtonVec[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = D3DXVECTOR3(-0.745f, 0.466f - 0.13357f * (i - m_iScroll), 0.0f);
		pTransformCom->m_vSize = D3DXVECTOR3(0.369f, 0.127f, 0.0f);
	}

	// VScroll Setup
	m_pVScroll->Setup(m_iScroll, m_iMaxScroll, 0.4869992f, -0.4899972f);

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

void CAchieveWindow::UpdateContent(Achieve* _pAchieve)
{
	if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST1)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("혼란의 시대"));
		_tcscpy_s(m_tszContent, 512, _T("- 5대 천사\n1. 티리엘 : 정의의 대천사\n2. 아우리엘 : 희망의 대천사\n3. 말타엘 : 지혜의 대천사\n4. 임페리우스 : 용기의 대천사\n5. 이더리얼 : 운명의 대천사\n\n- 6대 악마\n1. 메피스토 : 증오의 군주\n2. 바알 : 파괴의 군주\n3. 디아블로 : 공포의 군주\n4. 아즈모단 : 죄악의 군주\n5. 베리알 : 거짓말의 군주\n6. 듀리엘 : 고통의 왕자\n"));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST2)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("트리스트럼 입성"));
		_tcscpy_s(m_tszContent, 512, _T("기괴살덩이까지 나타나다니..\n덕분에 목숨을 부지할 수 있었소."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST3)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("용병계약 완료"));
		_tcscpy_s(m_tszContent, 512, _T("용병계약이 완료되었네! 축하하\n네. 최선을 다해주게.."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST4)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("첫 번째 임무"));
		_tcscpy_s(m_tszContent, 512, _T("자네도 알다시피..\n요즘 들어 트리스트럼 부근에\n좀비가 많이 출현하고 있다네.."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST5)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("마을의 평화"));
		_tcscpy_s(m_tszContent, 512, _T("잘 구해 오셨구만. 수고했네!\n자네 덕분에 꽤 오랫동안은 마\n을이 평화롭겠어..."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST6)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("아이템 분해"));
		_tcscpy_s(m_tszContent, 512, _T("용병단에 무기를 지급해야하는\n데.. 무기를 만들 쇠가 부족하다\n네. 쇠조각 10개만 구해주겠나?"));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST7)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("아이템 제련"));
		_tcscpy_s(m_tszContent, 512, _T("부탁하는 김에 장비로 만들어서\n와주면 안되겠나..? 지금 화장실\n이 급해서 말이야.."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST8)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("너무 늦었어.."));
		_tcscpy_s(m_tszContent, 512, _T("헌데.. 이미 많은 용병들이 나가\n버렸다네.. 너무 늦었어...."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST9)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("레오릭 장로"));
		_tcscpy_s(m_tszContent, 512, _T("몇일 전부터 레오릭 장로님이\n보이질 않네. 많은 용병들을\n장로님 집에 보내봤지만 그들도\n돌아오질 않고 있네."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST10)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("침입자"));
		_tcscpy_s(m_tszContent, 512, _T("장로님이.. 장로님이 위험합니\n다. 침입자가 있소. 이 열쇠는\n 장로님 방으로 들어갈 수 있는 열쇠요. 서두르시오.."));
	}
	else if(_pAchieve->eAchieveType == ACHIEVE_TYPE_MAIN_QUEST11)
	{
		_tcscpy_s(m_tszTitle, MIN_STR, _T("엔딩"));
		_tcscpy_s(m_tszContent, 512, _T("서둘러서 집에 가자!"));
	}
}