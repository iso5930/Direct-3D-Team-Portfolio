#include "Stdafx.h"
#include "Object.h"

CObject::CObject(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
{
	// Layer
	m_pLayer = NULL;

	// ObjKey
	m_tszObjKey = NULL;
	if(_tszObjKey != NULL)
	{
		m_tszObjKey = new TCHAR[MIN_STR];
		_tcscpy_s(m_tszObjKey, MIN_STR, _tszObjKey);
	}

	// ObjType
	m_eObjType = _eObjType;

	// Component
	ZeroMemory(m_pComponent, sizeof(m_pComponent));

	// Transform Component
	m_pTransformCom = new CTransformCom;
	AddComponent(m_pTransformCom);

	// Destroy
	m_bDestroy = false;
}

CObject::~CObject()
{
	Release();
}

void CObject::Initialize()
{
	for(int i = 0; i < COM_TYPE_END; ++i)
	{
		if(m_pComponent[i] != NULL)
			m_pComponent[i]->Initialize();
	}
}

int CObject::Update()
{
	for(int i = 0; i < COM_TYPE_END; ++i)
	{
		if(m_pComponent[i] != NULL)
			m_pComponent[i]->Update();
	}

	return 0;
}

void CObject::Render()
{
}

void CObject::Release()
{
	if(m_tszObjKey != NULL)
	{
		delete m_tszObjKey;
		m_tszObjKey = NULL;
	}

	for(int i = 0; i < COM_TYPE_END; ++i)
	{
		if(m_pComponent[i] != NULL)
		{
			delete m_pComponent[i];
			m_pComponent[i] = NULL;
		}
	}
}

void CObject::AddComponent(CComponent* _pComponent)
{
	COM_TYPE eComType = _pComponent->GetComType();

	if(m_pComponent[eComType] != NULL)
		delete m_pComponent[eComType];

	_pComponent->SetOwner(this);
	m_pComponent[eComType] = _pComponent;
}

void CObject::RemoveComponent(COM_TYPE _eComType)
{
	if(m_pComponent[_eComType] != NULL)
	{
		delete m_pComponent[_eComType];
		m_pComponent[_eComType] = NULL;
	}
}

void CObject::Destroy()
{
	m_bDestroy = true;
}