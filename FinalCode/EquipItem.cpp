#include "StdAfx.h"
#include "EquipItem.h"

CEquipItem::CEquipItem(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem, Bone* _pBone)
: CObject(_tszObjKey, _eObjType)
{
	// Item
	m_pItem = new Item(_pItem);

	// Bone
	m_pBone = _pBone;

	// Matrix
	D3DXMatrixIdentity(&m_mMatrix);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_ITEM);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_ITEM);
	AddComponent(pRenderCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_pItem->tszBufKey);
	AddComponent(pBufferCom);
}

CEquipItem::~CEquipItem()
{
	Release();
}

void CEquipItem::Initialize()
{
	CObject::Initialize();
}

int CEquipItem::Update()
{
	CObject::Update();
	m_pTransformCom->m_mWorld = m_mMatrix * m_pTransformCom->m_mWorld * m_pBone->mWorld;

	return 0;
}

void CEquipItem::Render()
{
	CObject::Render();
}

void CEquipItem::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}
}

void CEquipItem::SetMatrix(float _fAngleX, float _fAngleY, float _fAngleZ)
{
	MatrixRotation(&m_mMatrix, D3DXToRadian(_fAngleX), D3DXToRadian(_fAngleY), D3DXToRadian(_fAngleZ));
}