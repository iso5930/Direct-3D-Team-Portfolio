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
	_tcscpy_s(m_tszName, MIN_STR, _T("�̽�Ƽ��"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("��� ���� ���ۿ��� ���㰡 �־���. �� ��� ����, ��ҵ� ����\n���� ���㰡 �ϳ��� �Ϻ��� ����(Pearl)�� �̷�� �־����� ��\n���� �ӿ��� ���� ���� �ٿ�(��/��, ��/���, �׸���, ������,"));
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
		_tcscpy_s(m_tszText, MAX_STR, _T("��¡��, ���, ���� �׸��� �� ����)�� �ٿ�. �����ϰ� �ɿ���\n�ƴ�(Anu)�� ��ȥ�� �޲ٰ� �־����̴�. ����, �����ϰ� ������\n���̾Ƹ��� ������ �ƴ�(Anu)�� ���ſ� ������ ���� ���� ��"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("��� ���� �����ǰ� �־���. �ƴ�(Anu)�� ������ �޼ӿ��� ������\n���� ������� Ž�������� �� ���� ��� �ǰ� ��ȭ�� ã�� ������\n�ȴ�. �׷��� �� Ȥ���� ������ ������ ���� �κе��� �� �и���"));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("���� �ᱹ�� ������� �ʾҰ� �����ϰ� �Ǿ���. �׷��� ź���� ��\n�簡 �ٷ� ���°��� ���� ���� ����� �� �巡��(dragon), Ÿí��\nƮ(Tathamet) �̴�."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("�� ���� ������ 7���� �Ӹ��� ���� ���� ������ ������ ����� ��\n�վ��� �ᱹ ��ݵ� �� ����� ������ ��ο� ������(womb:�ڱ�)\n���� ������ �ο��� �����ϰ� �ȴ�. �ϳ��κ��� �и��Ǿ� ���ܳ�"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode4()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("������ ���翴�⿡ �� �ɷ� ���� ������ �����̾���. ������ ����\n�� �⳪�� ���� �� �ο��� ������ �ݺ��Ǿ�����, �� ���� ���� ��\n�� ������ ���� �׵��� ������ ���� �г뿡�� ��Ե� �浹���� ��"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode5()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("���� \"���� ����\" �� ����Ű�� �Ǿ��� �ٷ� ���⿡�� �츮�� ���\n�� �˰� �ִ� ������ �¾��."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode6()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("�� ��� ���� ó������ �ϳ������� ���� �� �׵��� �ο�� ������\n�� ��Ե� ���̴�. �׸��� ������ ź���� ������ �������� ������\n�ݷ��� ź���� ���ŷ� \"�ǵ���Ͼ�(pandemonium:��ȥ��))\"��"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode7()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("���ܳ��� ������ ������ �ƴ�(Anu)�� ������ �����ڴ� ������ ��\n�� �͵��� �з��ϴ� ���輮(World-stone)�� �Ǿ����� �ƴ�(Anu)\n�� Ÿí��Ʈ(Tathamet)�� �̷�� ���� ���� �ٿ����� �� ������"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode8()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("�� �������. ����, �ƴ�(Anu)�� ô�ߴ� �°��� ��� ������\n��� �ÿ����� õ���� ũ������ ��ġ(Crystal Arch)�� �Ǿ�����,\n�̰��� �ƴ�(Anu)�� ��ȥ�� ����ϴ� õ����� �¾ õ���� ��"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode9()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("����. õ�󿡼� �¾ õ��� �߿����� ���� ������ ��(�ƴ���\n�ٿ��� ���� �̾���� �ɷ�)�� ���� �ڵ��� ��õ����� 5���� ��\n���ϴµ�, �̵��� \"�ӱ����ȸ\" ��� �ⱸ�� â���Ͽ� õ����"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode10()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("��� ������ �����ߴ�. �׵� 5���� ��õ��� ������ ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("1. ��õ�� Ƽ����(Tyrael) : ������ ��õ��\n - �ݺ� �κ�� ������ �԰� õ���� ������ ȣ���ϴ� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("2. ��õ�� �ƿ츮��(Auriel) : ����� ��õ��\n - ���� Ǫ������ �κ긦 �԰� õ���� ������ ȣ���ϴ� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("3. ��õ�� ��Ÿ��(Malthael) : ������ ��õ��\n - ���� �κ�� �䰩�� ���� ��ô�� ����� ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("4. ��õ�� ���丮�콺(Imperius) : ����� ��õ��\n - ���� ���� ���ʿ� ��Ÿ������ â�� �� ������� ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("5. ��õ�� �̴�����(Itherael) : ����� ��õ��\n - ������ȳ��ϴ� ȸ�� ���� ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("�׸��� Ƽ����(Tyrael)�� ������ �¾������ ������ ������ �Ƹ�\n�ٿ� õ��, �̳����콺(Inarius)�� �ӱ⸮�� ��ȸ�� �����ڷν� ��\n��� ��ȸ�� �����ߴ�. �̵��� ������ �߽ɿ� �ִ� ���輮(world"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode17()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("-stone)�� ��ȣ�ϸ� ������ ������ ��ϰ��� �ߴ�. ������, Ÿ\ní��Ʈ(Tathamet)�� ��ο� �ٿ��� ���� ���¸� ������ �Ǿ���,\n�װ��� ��Ÿ�� ������ �Ǹ���� �����Ǿ���. õ���� 6���� õ���"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode18()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("�� ��ߵ���, ��Ÿ�� ���� ���� ���� 6���� ������ �Ǹ����� ��\n���ߴ�. �׵��� ������ ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("1. ���ǽ��� (Mephisto) : ������ ����\n - �ٿ��� ���� ��¡�ϴ� ������ ù°���� ���� ��Ȱ�� �γ��� ��\n�� �Ǹ����� ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("2. �پ�(Baal) : �ı��� ����\n - �ٿ��� ���� ��¡�ϴ� ������ ��°���� �ĸ길�� �޲ٴ� ���\n�� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("3. ��ƺ��(Diablo) : ������ ����\n - �ٿ��� ���� ��¡�ϴ� ������ �� ��°���� ���� ������ ���� ��\n�� ����."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("4. ������(Azmodan) : �˾��� ����\n - ����Ǹ� �Ʒ� ��ġ�� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("5. ������(Belial) : �������� ����\n - ����Ǹ� �Ʒ��� ��ġ�� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("6. �ฮ��(Duriek) : ������ ����\n - ����Ǹ� �Ʒ� �漺�ϴ� ��."));
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

		_tcscpy_s(m_tszText, MAX_STR, _T("��Ǹ� 3������ �� �Ʒ��� 3���� ������ �Ǹ��� 6�Ǹ��� ������\n�̵� �Ǹ� �����δ� ������ ȥ������ �����̱⸦ �ٷ����� ������\n������ �ٽ������� õ������ �ʿ������� �浹�� �� �ۿ� ����"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode26()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("���翴��. �ᱹ, ������ ź���� �ʿ������� �̵��� ������ �ҷ���\n����, �̰��� ������ ���� : ���浹�̾���. �װ��� ��Ȯ�� ���\n��ԵǾ��°��� ��Ȯ�� �� ���� ������, �ٸ� �ʿ����̾��� ����"));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode27()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("����."));
		++m_iMode;
	}
}

void CMainQuest1_Message::Mode28()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("��������Ʈ1 : ȥ���� �ô�"));
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