#include "StdAfx.h"
#include "DetailWindow.h"

CDetailWindow::CDetailWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Detail"))
{
	// TextMessage
	ZeroMemory(m_pTextMessage, sizeof(m_pTextMessage));

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.248f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.414f, 2.03904f, 0.0f);
}

CDetailWindow::~CDetailWindow()
{
	Release();
}

void CDetailWindow::Initialize()
{
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));

	CWindowUI::Initialize();

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	CTransformCom* pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.431007f, 0.969f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);
}

int CDetailWindow::Update()
{
	D3DXVECTOR3 vPos;
	ScreenToProj(&vPos, CInputMgr::GetInstance()->GetMousePos());

	////////////////////////////////////////////////////////////////////////// ����
	// ���� ���ð� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.714837f), &D3DXVECTOR2(0.409009f, 0.750504f)))
	{
		if(m_pTextMessage[0] == NULL)
		{
			m_pTextMessage[0] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("��� ��� ����� ���� ���ð��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[0], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[0]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.714837f, 0.0f) + D3DXVECTOR3(0.409009f, 0.750504f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[0]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[0] != NULL)
		{
			m_pTextMessage[0]->Destroy();
			m_pTextMessage[0] = NULL;
		}
	}

	// �ش�ȭ Ȯ��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.67917f), &D3DXVECTOR2(0.409009f, 0.714837f)))
	{
		if(m_pTextMessage[1] == NULL)
		{
			m_pTextMessage[1] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �ش�ȭ�� �����ϸ� �߰� ���ظ� �ݴϴ�."));
			m_pLayer->AddObject(m_pTextMessage[1], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[1]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.67917f, 0.0f) + D3DXVECTOR3(0.409009f, 0.714837f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[1]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[1] != NULL)
		{
			m_pTextMessage[1]->Destroy();
			m_pTextMessage[1] = NULL;
		}
	}

	// �ش�ȭ ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.643503f), &D3DXVECTOR2(0.409009f, 0.67917f)))
	{
		if(m_pTextMessage[2] == NULL)
		{
			m_pTextMessage[2] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ش�ȭ ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[2], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[2]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.643503f, 0.0f) + D3DXVECTOR3(0.409009f, 0.67917f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[2]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[2] != NULL)
		{
			m_pTextMessage[2]->Destroy();
			m_pTextMessage[2] = NULL;
		}
	}
	
	////////////////////////////////////////////////////////////////////////// ���
	// ���� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.535507f), &D3DXVECTOR2(0.409009f, 0.573007f)))
	{
		if(m_pTextMessage[3] == NULL)
		{
			m_pTextMessage[3] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� ���� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[3], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[3]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.535507f, 0.0f) + D3DXVECTOR3(0.409009f, 0.573007f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[3]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[3] != NULL)
		{
			m_pTextMessage[3]->Destroy();
			m_pTextMessage[3] = NULL;
		}
	}

	// �ñ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.498007f), &D3DXVECTOR2(0.409009f, 0.535507f)))
	{
		if(m_pTextMessage[4] == NULL)
		{
			m_pTextMessage[4] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� �ñ� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[4], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[4]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.498007f, 0.0f) + D3DXVECTOR3(0.409009f, 0.535507f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[4]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[4] != NULL)
		{
			m_pTextMessage[4]->Destroy();
			m_pTextMessage[4] = NULL;
		}
	}

	// ȭ�� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.460507f), &D3DXVECTOR2(0.409009f, 0.498007f)))
	{
		if(m_pTextMessage[5] == NULL)
		{
			m_pTextMessage[5] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� ȭ�� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[5], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[5]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.460507f, 0.0f) + D3DXVECTOR3(0.409009f, 0.498007f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[5]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[5] != NULL)
		{
			m_pTextMessage[5]->Destroy();
			m_pTextMessage[5] = NULL;
		}
	}

	// ���� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.423007f), &D3DXVECTOR2(0.409009f, 0.460507f)))
	{
		if(m_pTextMessage[6] == NULL)
		{
			m_pTextMessage[6] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� ���� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[6], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[6]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.423007f, 0.0f) + D3DXVECTOR3(0.409009f, 0.460507f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[6]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[6] != NULL)
		{
			m_pTextMessage[6]->Destroy();
			m_pTextMessage[6] = NULL;
		}
	}

	// �� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.385507f), &D3DXVECTOR2(0.409009f, 0.423007f)))
	{
		if(m_pTextMessage[7] == NULL)
		{
			m_pTextMessage[7] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� �� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[7], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[7]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.385507f, 0.0f) + D3DXVECTOR3(0.409009f, 0.423007f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[7]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[7] != NULL)
		{
			m_pTextMessage[7]->Destroy();
			m_pTextMessage[7] = NULL;
		}
	}

	// �ż� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.348007f), &D3DXVECTOR2(0.409009f, 0.385507f)))
	{
		if(m_pTextMessage[8] == NULL)
		{
			m_pTextMessage[8] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �޴� ���� �� �ż� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[8], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[8]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.348007f, 0.0f) + D3DXVECTOR3(0.409009f, 0.385507f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[8]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[8] != NULL)
		{
			m_pTextMessage[8]->Destroy();
			m_pTextMessage[8] = NULL;
		}
	}

	// ���� ���� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.310507f), &D3DXVECTOR2(0.409009f, 0.348007f)))
	{
		if(m_pTextMessage[9] == NULL)
		{
			m_pTextMessage[9] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� �������� �޴� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[9], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[9]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.310507f, 0.0f) + D3DXVECTOR3(0.409009f, 0.348007f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[9]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[9] != NULL)
		{
			m_pTextMessage[9]->Destroy();
			m_pTextMessage[9] = NULL;
		}
	}

	// ����ü ���� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.273007f), &D3DXVECTOR2(0.409009f, 0.310507f)))
	{
		if(m_pTextMessage[10] == NULL)
		{
			m_pTextMessage[10] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("����ü �������� �޴� ���ذ� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[10], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[10]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.273007f, 0.0f) + D3DXVECTOR3(0.409009f, 0.310507f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[10]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[10] != NULL)
		{
			m_pTextMessage[10]->Destroy();
			m_pTextMessage[10] = NULL;
		}
	}

	////////////////////////////////////////////////////////////////////////// �����
	// ��ü ����� ���ʽ�
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.167675f), &D3DXVECTOR2(0.409009f, 0.203009f)))
	{
		if(m_pTextMessage[11] == NULL)
		{
			m_pTextMessage[11] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("��ü ������� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[11], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[11]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.167675f, 0.0f) + D3DXVECTOR3(0.409009f, 0.203009f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[11]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[11] != NULL)
		{
			m_pTextMessage[11]->Destroy();
			m_pTextMessage[11] = NULL;
		}
	}

	// �ʴ� ����� ȸ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.132342f), &D3DXVECTOR2(0.409009f, 0.167675f)))
	{
		if(m_pTextMessage[12] == NULL)
		{
			m_pTextMessage[12] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� ȸ���Ǵ� ������Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[12], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[12]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.132342f, 0.0f) + D3DXVECTOR3(0.409009f, 0.167675f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[12]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[12] != NULL)
		{
			m_pTextMessage[12]->Destroy();
			m_pTextMessage[12] = NULL;
		}
	}

	// ���ߴ� ����� ȸ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, 0.097009f), &D3DXVECTOR2(0.409009f, 0.132342f)))
	{
		if(m_pTextMessage[13] == NULL)
		{
			m_pTextMessage[13] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ ������ ������ ������ ������� ȸ���մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[13], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[13]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, 0.097009f, 0.0f) + D3DXVECTOR3(0.409009f, 0.132342f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[13]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[13] != NULL)
		{
			m_pTextMessage[13]->Destroy();
			m_pTextMessage[13] = NULL;
		}
	}

	////////////////////////////////////////////////////////////////////////// �ڿ�
	// ���� ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.01124f), &D3DXVECTOR2(0.409009f, 0.0265076f)))
	{
		if(m_pTextMessage[14] == NULL)
		{
			m_pTextMessage[14] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� ���� ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[14], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[14]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.01124f, 0.0f) + D3DXVECTOR3(0.409009f, 0.0265076f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[14]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[14] != NULL)
		{
			m_pTextMessage[14]->Destroy();
			m_pTextMessage[14] = NULL;
		}
	}

	// ���� ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.04899f), &D3DXVECTOR2(0.409009f, -0.01124f)))
	{
		if(m_pTextMessage[15] == NULL)
		{
			m_pTextMessage[15] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� ���� ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[15], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[15]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.04899f, 0.0f) + D3DXVECTOR3(0.409009f, -0.01124f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[15]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[15] != NULL)
		{
			m_pTextMessage[15]->Destroy();
			m_pTextMessage[15] = NULL;
		}
	}

	// ���� ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.08674f), &D3DXVECTOR2(0.409009f, -0.04899f)))
	{
		if(m_pTextMessage[16] == NULL)
		{
			m_pTextMessage[16] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� ���� ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[16], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[16]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.08674f, 0.0f) + D3DXVECTOR3(0.409009f, -0.04899f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[16]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[16] != NULL)
		{
			m_pTextMessage[16]->Destroy();
			m_pTextMessage[16] = NULL;
		}
	}

	// ���� ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.12449f), &D3DXVECTOR2(0.409009f, -0.08674f)))
	{
		if(m_pTextMessage[17] == NULL)
		{
			m_pTextMessage[17] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� ���� ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[17], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[17]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.12449f, 0.0f) + D3DXVECTOR3(0.409009f, -0.08674f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[17]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[17] != NULL)
		{
			m_pTextMessage[17]->Destroy();
			m_pTextMessage[17] = NULL;
		}
	}

	// �г� ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.16224f), &D3DXVECTOR2(0.409009f, -0.12449f)))
	{
		if(m_pTextMessage[18] == NULL)
		{
			m_pTextMessage[18] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� �г� ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[18], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[18]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.16224f, 0.0f) + D3DXVECTOR3(0.409009f, -0.12449f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[18]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[18] != NULL)
		{
			m_pTextMessage[18]->Destroy();
			m_pTextMessage[18] = NULL;
		}
	}

	// ������ ȸ����/��
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.19999f), &D3DXVECTOR2(0.409009f, -0.16224f)))
	{
		if(m_pTextMessage[19] == NULL)
		{
			m_pTextMessage[19] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�ʴ� ������ ȸ�����Դϴ�."));
			m_pLayer->AddObject(m_pTextMessage[19], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[19]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.19999f, 0.0f) + D3DXVECTOR3(0.409009f, -0.16224f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[19]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[19] != NULL)
		{
			m_pTextMessage[19]->Destroy();
			m_pTextMessage[19] = NULL;
		}
	}

	// ���� �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.23774f), &D3DXVECTOR2(0.409009f, -0.19999f)))
	{
		if(m_pTextMessage[20] == NULL)
		{
			m_pTextMessage[20] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[20], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[20]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.23774f, 0.0f) + D3DXVECTOR3(0.409009f, -0.19999f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[20]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[20] != NULL)
		{
			m_pTextMessage[20]->Destroy();
			m_pTextMessage[20] = NULL;
		}
	}

	// ���� �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.27549f), &D3DXVECTOR2(0.409009f, -0.23774f)))
	{
		if(m_pTextMessage[21] == NULL)
		{
			m_pTextMessage[21] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[21], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[21]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.27549f, 0.0f) + D3DXVECTOR3(0.409009f, -0.23774f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[21]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[21] != NULL)
		{
			m_pTextMessage[21]->Destroy();
			m_pTextMessage[21] = NULL;
		}
	}

	// ���� �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.31324f), &D3DXVECTOR2(0.409009f, -0.27549f)))
	{
		if(m_pTextMessage[22] == NULL)
		{
			m_pTextMessage[22] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[22], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[22]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.31324f, 0.0f) + D3DXVECTOR3(0.409009f, -0.27549f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[22]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[22] != NULL)
		{
			m_pTextMessage[22]->Destroy();
			m_pTextMessage[22] = NULL;
		}
	}

	// ���� �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.35099f), &D3DXVECTOR2(0.409009f, -0.31324f)))
	{
		if(m_pTextMessage[23] == NULL)
		{
			m_pTextMessage[23] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[23], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[23]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.35099f, 0.0f) + D3DXVECTOR3(0.409009f, -0.31324f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[23]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[23] != NULL)
		{
			m_pTextMessage[23]->Destroy();
			m_pTextMessage[23] = NULL;
		}
	}

	// �г� �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.38874f), &D3DXVECTOR2(0.409009f, -0.35099f)))
	{
		if(m_pTextMessage[24] == NULL)
		{
			m_pTextMessage[24] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("�г� �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[24], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[24]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.38874f, 0.0f) + D3DXVECTOR3(0.409009f, -0.35099f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[24]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[24] != NULL)
		{
			m_pTextMessage[24]->Destroy();
			m_pTextMessage[24] = NULL;
		}
	}

	// ������ �Ҹ� ����
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.42649f), &D3DXVECTOR2(0.409009f, -0.38874f)))
	{
		if(m_pTextMessage[25] == NULL)
		{
			m_pTextMessage[25] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("������ �Ҹ��� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[25], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[25]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.42649f, 0.0f) + D3DXVECTOR3(0.409009f, -0.38874f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[25]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[25] != NULL)
		{
			m_pTextMessage[25]->Destroy();
			m_pTextMessage[25] = NULL;
		}
	}

	////////////////////////////////////////////////////////////////////////// ����
	// �߰� ����ġ
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.530156f), &D3DXVECTOR2(0.409009f, -0.494488f)))
	{
		if(m_pTextMessage[26] == NULL)
		{
			m_pTextMessage[26] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� óġ�� ȹ���ϴ� ����ġ�� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[26], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[26]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.530156f, 0.0f) + D3DXVECTOR3(0.409009f, -0.494488f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[26]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[26] != NULL)
		{
			m_pTextMessage[26]->Destroy();
			m_pTextMessage[26] = NULL;
		}
	}

	// ���� ������ �߰�
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.565822f), &D3DXVECTOR2(0.409009f, -0.530156f)))
	{
		if(m_pTextMessage[27] == NULL)
		{
			m_pTextMessage[27] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("��� �������� �߰��� Ȯ���� �������ϴ�."));
			m_pLayer->AddObject(m_pTextMessage[27], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[27]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.565822f, 0.0f) + D3DXVECTOR3(0.409009f, -0.530156f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[27]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[27] != NULL)
		{
			m_pTextMessage[27]->Destroy();
			m_pTextMessage[27] = NULL;
		}
	}

	// ��ȭ �߰�
	if(PointToAABB(&D3DXVECTOR2(vPos.x, vPos.y), &D3DXVECTOR2(0.0790097f, -0.601488f), &D3DXVECTOR2(0.409009f, -0.565822f)))
	{
		if(m_pTextMessage[28] == NULL)
		{
			m_pTextMessage[28] = new CDetailMessage(NULL, OBJ_TYPE_STATIC, _T("���� ����߸��� ��ȭ�� �����մϴ�."));
			m_pLayer->AddObject(m_pTextMessage[28], LAYER_TYPE_UI);

			CTransformCom* pTransformCom = (CTransformCom*)m_pTextMessage[28]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = (D3DXVECTOR3(0.0790097f, -0.601488f, 0.0f) + D3DXVECTOR3(0.409009f, -0.565822f, 0.0f)) / 2.0f;
			pTransformCom->m_vPos.y += 0.06f;

			m_pTextMessage[28]->Initialize();
		}
	}
	else
	{
		if(m_pTextMessage[28] != NULL)
		{
			m_pTextMessage[28]->Destroy();
			m_pTextMessage[28] = NULL;
		}
	}

	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	CWindowUI::Update();

	return 0;
}

void CDetailWindow::Render()
{
	CWindowUI::Render();

	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
	if(pFindObject == NULL)
		return;

	// Player
	CPlayer* pPlayer = (CPlayer*)pFindObject;

	// Variable
	TCHAR tszText[MIN_STR];
	RECT rcText;

	// ���� ���ð� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedCooldownTime() * 100.0f);
	SetRect(&rcText, 600, 90, 900, 102);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �ش�ȭ Ȯ��
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetCriticalProbability() * 100.0f);
	SetRect(&rcText, 600, 104, 900, 116);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �ش�ȭ ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetCriticalDamage() * 100.0f);
	SetRect(&rcText, 600, 117, 900, 129);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetPhysicalResistance(), tszText, 10);
	SetRect(&rcText, 600, 155, 900, 167);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �ñ� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetColdResistance(), tszText, 10);
	SetRect(&rcText, 600, 168, 900, 180);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ȭ�� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetFlameResistance(), tszText, 10);
	SetRect(&rcText, 600, 182, 900, 194);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetLightningResistance(), tszText, 10);
	SetRect(&rcText, 600, 196, 900, 208);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetPoisonResistance(), tszText, 10);
	SetRect(&rcText, 600, 209, 900, 221);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �ż� ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetHolyResistance(), tszText, 10);
	SetRect(&rcText, 600, 223, 900, 235);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ���� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedNearDamage() * 100.0f);
	SetRect(&rcText, 600, 236, 900, 248);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ����ü ���� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedFarDamage() * 100.0f);
	SetRect(&rcText, 600, 250, 900, 262);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ��ü ����� ���ʽ�
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetRestoresBonus() * 100.0f);
	SetRect(&rcText, 600, 287, 900, 299);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �ʴ� ����� ȸ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetLifeRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 301, 900, 313);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���ߴ� ����� ȸ����
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetLifeRecoveryOfHit(), tszText, 10);
	SetRect(&rcText, 600, 315, 900, 327);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetControlRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 352, 900, 364);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetEffortRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 365, 900, 377);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetHateRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 379, 900, 391);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetManaRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 392, 900, 404);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �г� ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetRageRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 406, 900, 418);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ������ ȸ����/��
	ZeroMemory(tszText, sizeof(tszText));
	_itot_s(pPlayer->GetVisionRecoveryOfSecond(), tszText, 10);
	SetRect(&rcText, 600, 420, 900, 432);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedControlConsumption() * 100.0f);
	SetRect(&rcText, 600, 433, 900, 445);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedEffortConsumption() * 100.0f);
	SetRect(&rcText, 600, 447, 900, 459);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedHateConsumption() * 100.0f);
	SetRect(&rcText, 600, 460, 900, 472);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedManaConsumption() * 100.0f);
	SetRect(&rcText, 600, 474, 900, 486);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �г� �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedRageConsumption() * 100.0f);
	SetRect(&rcText, 600, 488, 900, 500);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ������ �Ҹ� ����
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetReducedVisionConsumption() * 100.0f);
	SetRect(&rcText, 600, 501, 900, 513);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �߰� ����ġ
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetExperience() * 100.0f);
	SetRect(&rcText, 600, 539, 900, 551);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���� ������ �߰�
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetMagicItemsFound() * 100.0f);
	SetRect(&rcText, 600, 553, 900, 565);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ��ȭ �߰�
	ZeroMemory(tszText, sizeof(tszText));
	StringCbPrintf(tszText, sizeof(tszText), _T("%g%%"), pPlayer->GetDiscoveryOfGoldCoins() * 100.0f);
	SetRect(&rcText, 600, 566, 900, 578);
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, tszText, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CDetailWindow::Release()
{
	// TextMessage
	for(int i = 0; i < 29; ++i)
	{
		if(m_pTextMessage[i] != NULL)
		{
			m_pTextMessage[i]->Destroy();
			m_pTextMessage[i] = NULL;
		}
	}
}

void CDetailWindow::Renew()
{
}