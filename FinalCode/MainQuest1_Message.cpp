#include "StdAfx.h"
#include "MainQuest1_Message.h"

CMainQuest1_Message::CMainQuest1_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// AnuAndTathametSign
	m_pAnuAndTathametSign = NULL;

	// TyraelSign
	m_pTyraelSign = NULL;

	// AurielSign
	m_pAurielSign = NULL;

	// MalthaelSign
	m_pMalthaelSign = NULL;

	// ImperiusSign
	m_pImperiusSign = NULL;

	// ItheraelSign
	m_pItheraelSign = NULL;

	// MephistoSign
	m_pMephistoSign = NULL;

	// BaalSign
	m_pBaalSign = NULL;

	// DiabloSign
	m_pDiabloSign = NULL;

	// AzmodanSign
	m_pAzmodanSign = NULL;

	// BelialSign
	m_pBelialSign = NULL;

	// DuriekSign
	m_pDuriekSign = NULL;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("미스티나"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("모든 것의 시작에는 공허가 있었다. 그 어떠한 빛도, 어둠도 없는\n그저 공허가 하나의 완벽한 정수(Pearl)를 이루고 있었으며 그\n정수 속에는 모든것 들의 근원(선/악, 빛/어둠, 그림자, 물질적,"));
}

CMainQuest1_Message::~CMainQuest1_Message()
{
	Release();
}

void CMainQuest1_Message::Initialize()
{
	CQuestMessage::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Mystic"));
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CMainQuest1_Message::Update()
{
	CQuestMessage::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;

	case 3:
		Mode3();
		break;

	case 4:
		Mode4();
		break;

	case 5:
		Mode5();
		break;

	case 6:
		Mode6();
		break;

	case 7:
		Mode7();
		break;

	case 8:
		Mode8();
		break;

	case 9:
		Mode9();
		break;

	case 10:
		Mode10();
		break;

	case 11:
		Mode11();
		break;

	case 12:
		Mode12();
		break;

	case 13:
		Mode13();
		break;

	case 14:
		Mode14();
		break;

	case 15:
		Mode15();
		break;

	case 16:
		Mode16();
		break;

	case 17:
		Mode17();
		break;

	case 18:
		Mode18();
		break;

	case 19:
		Mode19();
		break;

	case 20:
		Mode20();
		break;

	case 21:
		Mode21();
		break;

	case 22:
		Mode22();
		break;

	case 23:
		Mode23();
		break;

	case 24:
		Mode24();
		break;

	case 25:
		Mode25();
		break;

	case 26:
		Mode26();
		break;

	case 27:
		Mode27();
		break;

	case 28:
		Mode28();
		break;
	}

	return 0;
}

void CMainQuest1_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest1_Message::Release()
{
	// AnuAndTathametSign
	if(m_pAnuAndTathametSign != NULL)
	{
		m_pAnuAndTathametSign->Destroy();
		m_pAnuAndTathametSign = NULL;
	}

	// TyraelSign
	if(m_pTyraelSign != NULL)
	{
		m_pTyraelSign->Destroy();
		m_pTyraelSign = NULL;
	}

	// AurielSign
	if(m_pAurielSign != NULL)
	{
		m_pAurielSign->Destroy();
		m_pAurielSign = NULL;
	}

	// MalthaelSign
	if(m_pMalthaelSign != NULL)
	{
		m_pMalthaelSign->Destroy();
		m_pMalthaelSign = NULL;
	}

	// ImperiusSign
	if(m_pImperiusSign != NULL)
	{
		m_pImperiusSign->Destroy();
		m_pImperiusSign = NULL;
	}

	// ItheraelSign
	if(m_pItheraelSign != NULL)
	{
		m_pItheraelSign->Destroy();
		m_pItheraelSign = NULL;
	}

	// MephistoSign
	if(m_pMephistoSign != NULL)
	{
		m_pMephistoSign->Destroy();
		m_pMephistoSign = NULL;
	}

	// BaalSign
	if(m_pBaalSign != NULL)
	{
		m_pBaalSign->Destroy();
		m_pBaalSign = NULL;
	}

	// DiabloSign
	if(m_pDiabloSign != NULL)
	{
		m_pDiabloSign->Destroy();
		m_pDiabloSign = NULL;
	}

	// AzmodanSign
	if(m_pAzmodanSign != NULL)
	{
		m_pAzmodanSign->Destroy();
		m_pAzmodanSign = NULL;
	}

	// BelialSign
	if(m_pBelialSign != NULL)
	{
		m_pBelialSign->Destroy();
		m_pBelialSign = NULL;
	}

	// DuriekSign
	if(m_pDuriekSign != NULL)
	{
		m_pDuriekSign->Destroy();
		m_pDuriekSign = NULL;
	}
}

void CMainQuest1_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("상징적, 기쁨, 슬픔 그리고 그 모든것)의 근원. 강대하고 심오한\n아누(Anu)의 영혼이 꿈꾸고 있었음이다. 또한, 찬란하게 빛나는\n다이아몬드로 구성된 아누(Anu)의 육신에 무수히 많은 측면 그"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("모든 것이 투영되고 있었다. 아누(Anu)는 영원한 꿈속에서 수없이\n많은 측면들을 탐구했으며 그 속의 모든 악과 불화를 찾아 지워버\n렸다. 그러나 그 혹독한 증오와 교만한 악의 부분들은 그 분리로"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode2()
{
	if(m_pXButton->IsLUp())
	{
		// AnuAndTathametSign
		m_pAnuAndTathametSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_AnuAndTathamet"));
		m_pLayer->AddObject(m_pAnuAndTathametSign, LAYER_TYPE_UI);
		m_pAnuAndTathametSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pAnuAndTathametSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("인해 결국은 사라지지 않았고 결집하게 되었다. 그렇게 탄생한 존\n재가 바로 짐승과도 같은 용의 모습을 한 드래곤(dragon), 타챠메\n트(Tathamet) 이다."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode3()
{
	if(m_pXButton->IsLUp())
	{
		// AnuAndTathametSign Destroy
		m_pAnuAndTathametSign->Destroy();
		m_pAnuAndTathametSign = NULL;

		_tcscpy_s(m_tszText, MAX_STR, _T("그 용의 형상은 7개의 머리로 숨을 쉬며 끝없는 죽음과 어둠을 내\n뿜었고 결국 상반된 두 존재는 정수의 어두운 심층부(womb:자궁)\n에서 끝없는 싸움을 시작하게 된다. 하나로부터 분리되어 생겨난"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode4()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("동등한 존재였기에 근 능력 또한 동등한 수준이었다. 때문에 수없\n이 기나긴 세월 간 싸움은 끝없이 반복되었으며, 그 둘의 힘이 모\n두 다했을 무렵 그들의 마지막 남은 분노에서 비롯된 충돌에서 거"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode5()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("대한 \"빛의 폭발\" 을 일으키게 되었고 바로 여기에서 우리들 모두\n가 알고 있는 세상이 태어났다."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode6()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("이 모든 것은 처음부터 하나였으며 둘이 된 그들의 싸움과 죽음에\n서 비롯된 것이다. 그리고 세상이 탄생한 시초의 지점에는 세상의\n격렬한 탄생의 증거로 \"판데모니엄(pandemonium:대혼란))\"이"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode7()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("생겨났고 죽음을 맞이한 아누(Anu)의 찬란한 눈동자는 세상의 모\n든 것들을 분류하는 세계석(World-stone)이 되었으며 아누(Anu)\n와 타챠메트(Tathamet)를 이루던 선과 악의 근원들은 온 세상으"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode8()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("로 스며들어갔다. 또한, 아누(Anu)의 척추는 태고의 어둠 속으로\n잡아 늘여져서 천상의 크리스털 아치(Crystal Arch)가 되었으며,\n이곳에 아누(Anu)의 영혼을 계승하는 천사들이 태어나 천상이 되"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode9()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("었다. 천상에서 태어난 천사들 중에서도 가장 강력한 힘(아누의\n근원적 선을 이어받은 능력)을 지닌 자들인 대천사들이 5명이 존\n재하는데, 이들은 \"앙기라스의회\" 라는 기구를 창설하여 천상을"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode10()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("운영해 나가기 시작했다. 그들 5명의 대천사는 다음과 같다."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode11()
{
	if(m_pXButton->IsLUp())
	{
		// TyraelSign
		m_pTyraelSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Tyrael"));
		m_pLayer->AddObject(m_pTyraelSign, LAYER_TYPE_UI);
		m_pTyraelSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pTyraelSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("1. 대천사 티리엘(Tyrael) : 정의의 대천사\n - 금빛 로브와 갑옥을 입고 천상의 질서를 호령하는 자."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode12()
{
	if(m_pXButton->IsLUp())
	{
		// TyraelSign
		m_pTyraelSign->Destroy();
		m_pTyraelSign = NULL;

		// AurielSign
		m_pAurielSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Auriel"));
		m_pLayer->AddObject(m_pAurielSign, LAYER_TYPE_UI);
		m_pAurielSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pAurielSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("2. 대천사 아우리엘(Auriel) : 희망의 대천사\n - 옅은 푸른빛의 로브를 입고 천상의 질서를 호려하는 자."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode13()
{
	if(m_pXButton->IsLUp())
	{
		// AurielSign Destroy
		m_pAurielSign->Destroy();
		m_pAurielSign = NULL;

		// MalthaelSign
		m_pMalthaelSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Malthael"));
		m_pLayer->AddObject(m_pMalthaelSign, LAYER_TYPE_UI);
		m_pMalthaelSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pMalthaelSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("3. 대천사 말타엘(Malthael) : 지혜의 대천사\n - 검은 로브와 흉갑을 입은 수척한 모습의 현자."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode14()
{
	if(m_pXButton->IsLUp())
	{
		// MalthaelSign Destroy
		m_pMalthaelSign->Destroy();
		m_pMalthaelSign = NULL;

		// ImperiusSign
		m_pImperiusSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Imperius"));
		m_pLayer->AddObject(m_pImperiusSign, LAYER_TYPE_UI);
		m_pImperiusSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pImperiusSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("4. 대천사 임페리우스(Imperius) : 용기의 대천사\n - 붉은 빛의 갑옷에 불타오르는 창을 쥔 헌신적인 용자."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode15()
{
	if(m_pXButton->IsLUp())
	{
		// ImperiusSign Destroy
		m_pImperiusSign->Destroy();
		m_pImperiusSign = NULL;

		// ItheraelSign
		m_pItheraelSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Itherael"));
		m_pLayer->AddObject(m_pItheraelSign, LAYER_TYPE_UI);
		m_pItheraelSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pItheraelSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("5. 대천사 이더리얼(Itherael) : 운명의 대천사\n - 운명을안내하는 회색 빛의 현자."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode16()
{
	if(m_pXButton->IsLUp())
	{
		// ItheraelSign Destroy
		m_pItheraelSign->Destroy();
		m_pItheraelSign = NULL;

		_tcscpy_s(m_tszText, MAX_STR, _T("그리고 티리엘(Tyrael)의 형제인 태양빛으로 찬란히 빛나는 아름\n다운 천사, 이나리우스(Inarius)는 앙기리스 의회의 조언자로써 이\n들과 의회에 참여했다. 이들은 세상의 중심에 있는 세계석(world"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode17()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("-stone)을 수호하며 질서로 세상을 운영하고자 했다. 하지만, 타\n챠메트(Tathamet)의 어두운 근원들 역시 형태를 가지게 되었음,\n그것은 불타는 지옥의 악마들로 구현되었다. 천상을 6명의 천사들"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode18()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("이 운영했듯이, 불타는 지옥 또한 역시 6명의 강력한 악마들이 존\n재했다. 그들은 다음과 같다."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode19()
{
	if(m_pXButton->IsLUp())
	{
		// MephistoSign
		m_pMephistoSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Mephisto"));
		m_pLayer->AddObject(m_pMephistoSign, LAYER_TYPE_UI);
		m_pMephistoSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pMephistoSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("1. 메피스토 (Mephisto) : 증오의 군주\n - 근원의 악을 상징하는 형제중 첫째이자 가장 교활한 두뇌를 갖\n춘 악마들의 수장."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode20()
{
	if(m_pXButton->IsLUp())
	{
		// MephistoSign Destroy
		m_pMephistoSign->Destroy();
		m_pMephistoSign = NULL;

		// BaalSign
		m_pBaalSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Baal"));
		m_pLayer->AddObject(m_pBaalSign, LAYER_TYPE_UI);
		m_pBaalSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pBaalSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("2. 바알(Baal) : 파괴의 군주\n - 근원의 악을 상징하는 형제중 둘째이자 파멸만을 꿈꾸는 멸망\n의 손."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode21()
{
	if(m_pXButton->IsLUp())
	{
		// BaalSign Destroy
		m_pBaalSign->Destroy();
		m_pBaalSign = NULL;

		// DiabloSign
		m_pDiabloSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Diablo"));
		m_pLayer->AddObject(m_pDiabloSign, LAYER_TYPE_UI);
		m_pDiabloSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pDiabloSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("3. 디아블로(Diablo) : 공포의 군주\n - 근원의 악을 상징하는 형제들 중 셋째이자 가장 강력한 힘을 지\n닌 투사."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode22()
{
	if(m_pXButton->IsLUp())
	{
		// DiabloSign Destroy
		m_pDiabloSign->Destroy();
		m_pDiabloSign = NULL;

		// AzmodanSign
		m_pAzmodanSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Azmodan"));
		m_pLayer->AddObject(m_pAzmodanSign, LAYER_TYPE_UI);
		m_pAzmodanSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pAzmodanSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("4. 아즈모단(Azmodan) : 죄악의 군주\n - 절대악마 아래 위치한 악."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode23()
{
	if(m_pXButton->IsLUp())
	{
		// AzmodanSign Destroy
		m_pAzmodanSign->Destroy();
		m_pAzmodanSign = NULL;

		// BelialSign
		m_pBelialSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Belial"));
		m_pLayer->AddObject(m_pBelialSign, LAYER_TYPE_UI);
		m_pBelialSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pBelialSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("5. 베리알(Belial) : 거짓말의 군주\n - 절대악마 아래에 위치한 악."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode24()
{
	if(m_pXButton->IsLUp())
	{
		// BelialSign Destroy
		m_pBelialSign->Destroy();
		m_pBelialSign = NULL;

		// DuriekSign
		m_pDuriekSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Duriek"));
		m_pLayer->AddObject(m_pDuriekSign, LAYER_TYPE_UI);
		m_pDuriekSign->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)m_pDuriekSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.7f, 0.7f, 0.0f);

		_tcscpy_s(m_tszText, MAX_STR, _T("6. 듀리엘(Duriek) : 고통의 왕자\n - 절대악마 아래 충성하는 악."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode25()
{
	if(m_pXButton->IsLUp())
	{
		// DuriekSign Destroy
		m_pDuriekSign->Destroy();
		m_pDuriekSign = NULL;

		_tcscpy_s(m_tszText, MAX_STR, _T("대악마 3형제와 그 아래의 3명의 강력한 악마의 6악마로 구성된\n이들 악마 수뇌부는 세상을 혼란으로 물들이기를 바랬으며 세상을\n질서로 다스리려는 천사들과는 필연적으로 충돌할 수 밖에 없는"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode26()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("존재였다. 결국, 세상의 탄생은 필연적으로 이들의 전쟁을 불러왔\n으며, 이것이 역사의 시작 : 대충돌이었다. 그것이 정확히 어떻게\n비롯되었는가는 정확히 알 수가 없으나, 다만 필연적이었을 뿐이"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode27()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("었다."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode28()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트1 : 혼란의 시대"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST1));

		// AddQuest
		CQuestMgr::GetInstance()->AddQuest(new Quest(QUEST_TYPE_MAIN, 1));

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_MYSTIC)
			{
				pNPC->EventEnd();
				break;
			}
		}

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
			{
				pNPC->SetMode(1);
				break;
			}
		}

		Destroy();
	}
}