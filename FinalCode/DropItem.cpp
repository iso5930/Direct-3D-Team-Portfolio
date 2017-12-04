#include "StdAfx.h"
#include "DropItem.h"

CDropItem::CDropItem(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CObject(_tszObjKey, _eObjType)
{
	// Item
	m_pItem = new Item(_pItem);

	// Get
	m_bGet = false;

	// IsOver
	m_bIsOver = false;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// Acc
	m_fAcc = 20.0f;

	// StartY
	m_fStartY = 0.0f;

	// Ray
	ZeroMemory(&m_ray, sizeof(Ray));

	// Vertex
	for(int i = 0; i < 4; ++i)
		ZeroMemory(&m_vVertex[i], sizeof(D3DXVECTOR3));

	// DropMessage
	m_pDropMessage = NULL;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_DROP);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_DROP);
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, m_pItem->tszTexKey);
	AddComponent(pMaterialCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);
}

CDropItem::~CDropItem()
{
	Release();
}

void CDropItem::Initialize()
{
	// PlaySoundForUI
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("DropItem.ogg"));

	CObject::Initialize();

	// StartY
	m_fStartY = m_pTransformCom->m_vPos.y;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(30.0f * m_pItem->iWidth , 30.0f * m_pItem->iHeight, 1.0f);

	// PosY
	m_pTransformCom->m_vPos.y += 30.0f;

	// FindObjects
	vector<CObject*> pFindObjects;
	m_pLayer->FindObjects(pFindObjects, _T("Item"), LAYER_TYPE_DROP);

	// Cnt
	int iCnt = 0;

	// Collision
	bool bCollision = true;

	do
	{
		bCollision = true;
		for(int i = -iCnt; i <= iCnt && bCollision; ++i)
		{
			for(int j = -iCnt; j <= iCnt && bCollision; ++j)
			{
				// Check Cnt
				if(i != -iCnt && i != iCnt && j != -iCnt && j != iCnt)
					continue;

				// Pos
				D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + AXIS_Z * float(i * 30.0f) + AXIS_X * float(j * 30.0f);

				// Check Collision
				bCollision = false;
				for(size_t k = 0; k < pFindObjects.size() && !bCollision; ++k)
				{
					// Check this
					if(pFindObjects[k] == this)
						continue;

					// Check Collision
					CTransformCom* pTransformCom = (CTransformCom*)pFindObjects[k]->GetComponent(COM_TYPE_TRANSFORM);
					if(AABBToAABB(&D3DXVECTOR2(vPos.x - m_pTransformCom->m_vSize.x / 2.0f, vPos.z - m_pTransformCom->m_vSize.y / 2.0f), &D3DXVECTOR2(vPos.x + m_pTransformCom->m_vSize.x / 2.0f, vPos.z + m_pTransformCom->m_vSize.y / 2.0f),
								  &D3DXVECTOR2(pTransformCom->m_vPos.x - pTransformCom->m_vSize.x / 2.0f, pTransformCom->m_vPos.z - pTransformCom->m_vSize.y / 2.0f), &D3DXVECTOR2(pTransformCom->m_vPos.x + pTransformCom->m_vSize.x / 2.0f, pTransformCom->m_vPos.z + pTransformCom->m_vSize.y / 2.0f)))
						bCollision = true;
				}

				if(bCollision == false)
					m_pTransformCom->m_vPos = vPos;
			}
		}
	} while(bCollision && ++iCnt);
}

int CDropItem::Update()
{
	CObject::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;
	}

	return 0;
}

void CDropItem::Render()
{
	CObject::Render();
}

void CDropItem::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	// DropMessage
	if(m_pDropMessage != NULL)
	{
		m_pDropMessage->Destroy();
		m_pDropMessage = NULL;
	}
}

void CDropItem::DisOver()
{
	// IsOver
	m_bIsOver = false;

	// DropMessage
	if(m_pDropMessage != NULL)
	{
		m_pDropMessage->Destroy();
		m_pDropMessage = NULL;
	}
}

void CDropItem::Mode0()
{
	// Acc
	m_fAcc -= 80.0f * CTimeMgr::GetInstance()->GetDeltaTime();

	// PosY
	m_pTransformCom->m_vPos.y += m_fAcc;

	// Rotate
	m_pTransformCom->m_vAngle.x += D3DXToRadian(1440.0f) * CTimeMgr::GetInstance()->GetDeltaTime();

	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.5f)
	{
		// Angle
		m_pTransformCom->m_vAngle = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);

		// Pos
		m_pTransformCom->m_vPos.y = m_fStartY + 1.0f;

		// Vertex
		m_vVertex[0].x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f;
		m_vVertex[0].y = m_pTransformCom->m_vPos.y;
		m_vVertex[0].z = m_pTransformCom->m_vPos.z - m_pTransformCom->m_vSize.y / 2.0f;

		m_vVertex[1].x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f;
		m_vVertex[1].y = m_pTransformCom->m_vPos.y;
		m_vVertex[1].z = m_pTransformCom->m_vPos.z + m_pTransformCom->m_vSize.y / 2.0f;

		m_vVertex[2].x = m_pTransformCom->m_vPos.x + m_pTransformCom->m_vSize.x / 2.0f;
		m_vVertex[2].y = m_pTransformCom->m_vPos.y;
		m_vVertex[2].z = m_pTransformCom->m_vPos.z + m_pTransformCom->m_vSize.y / 2.0f;

		m_vVertex[3].x = m_pTransformCom->m_vPos.x + m_pTransformCom->m_vSize.x / 2.0f;
		m_vVertex[3].y = m_pTransformCom->m_vPos.y;
		m_vVertex[3].z = m_pTransformCom->m_vPos.z - m_pTransformCom->m_vSize.y / 2.0f;

		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CDropItem::Mode1()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 30.0f)
		Destroy();

	// Is Get?
	if(m_bGet)
	{
		Item* pItem = new Item(m_pItem);
		pItem->iPosX = -1;
		pItem->iPosY = -1;

		if(CItemMgr::GetInstance()->AddItemInInven(pItem))
		{
			// PlaySoundForUI
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("GetItem.ogg"));

			CItemMgr::GetInstance()->CommitInven();
			CUIMgr::GetInstance()->RenewWindow(WINDOW_TYPE_INVENTORY);
			Destroy();
		}
		else
		{
			// PlaySoundForUI
			CSoundMgr::GetInstance()->PlaySoundForUI(_T("DropItem.ogg"));

			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
			CUIMgr::GetInstance()->CreateTextMessage(_T("이 작업을 수행하려면 보관함에 공간이 더 필요합니다."));

			// PosY
			m_pTransformCom->m_vPos.y += 30.0f;

			// Acc
			m_fAcc = 20.0f;

			// Time
			m_fTime = 0.0f;

			// Mode
			m_iMode = 0;
		}

		// Get
		m_bGet = false;

		// IsOver
		m_bIsOver = false;

		// DropMessage
		if(m_pDropMessage != NULL)
		{
			m_pDropMessage->Destroy();
			m_pDropMessage = NULL;
		}

		return;
	}

	// IsOver
	m_bIsOver = false;

	// FindMouse
	CObject* pFindObject = NULL;
	m_pLayer->FindObject(pFindObject, _T("Mouse"), LAYER_TYPE_MOUSE);

	if(pFindObject != NULL)
	{
		// Mouse
		CMouse* pMouse = (CMouse*)pFindObject;

		// Check
		bool bCheck = false;
		if(pMouse->GetMouseOverType() != MOUSE_OVER_TYPE_NONE)
		{
			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);

			if(D3DXVec3Length(&(pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())) > D3DXVec3Length(&(m_pTransformCom->m_vPos - *CCameraMgr::GetInstance()->GetPos3D())))
				bCheck = true;
		}

		if(pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_NONE || bCheck)
		{
			// ScreenToWorld
			ScreenToWorld(&m_ray, CInputMgr::GetInstance()->GetMousePos(), CCameraMgr::GetInstance()->GetProj(), CCameraMgr::GetInstance()->GetInvView());

			// Intersect
			float u, v, dist;
			if(D3DXIntersectTri(&(m_vVertex[0]), &(m_vVertex[1]), &(m_vVertex[2]), &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist) || D3DXIntersectTri(&(m_vVertex[0]), &(m_vVertex[2]), &(m_vVertex[3]), &(m_ray.vSrc), &(m_ray.vDir), &u, &v, &dist))
				m_bIsOver = true;
		}
	}

	if(m_bIsOver || CInputMgr::GetInstance()->KeyDown(DIK_LCONTROL) || CInputMgr::GetInstance()->KeyPress(DIK_LCONTROL) || CInputMgr::GetInstance()->KeyDown(DIK_RCONTROL) || CInputMgr::GetInstance()->KeyPress(DIK_RCONTROL))
	{
		if(m_bIsOver)
		{
			// Over
			CMouse* pMouse = (CMouse*)pFindObject;
			pMouse->Over(MOUSE_OVER_TYPE_DROP_ITEM, this);
		}

		// DropMessage
		if(m_pDropMessage == NULL)
		{
			m_pDropMessage = new CDropMessage(NULL, OBJ_TYPE_STATIC, m_pItem);
			m_pLayer->AddObject(m_pDropMessage, LAYER_TYPE_UI);

			RECT rcCalc;
			CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_pItem->tszName, -1, &rcCalc, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			CTransformCom* pTransformCom = (CTransformCom*)m_pDropMessage->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize.x = (rcCalc.right - rcCalc.left) / float(WINCX) * 2.0f + 0.04f;
			pTransformCom->m_vSize.y = (rcCalc.bottom - rcCalc.top) / float(WINCY) * 2.0f + 0.04f;
			pTransformCom->m_vSize.z = 0.0f;

			m_pDropMessage->Initialize();
		}

		CTransformCom* pTransformCom = (CTransformCom*)m_pDropMessage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 75.0f, 0.0f);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, CCameraMgr::GetInstance()->GetViewProj());

		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pDropMessage->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF4;

		CRenderCom* pRenderCom = (CRenderCom*)m_pDropMessage->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x0000000B;
	}
	else
	{
		// DropMessage
		if(m_pDropMessage != NULL)
		{
			m_pDropMessage->Destroy();
			m_pDropMessage = NULL;
		}
	}
}