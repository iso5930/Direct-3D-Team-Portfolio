#include "Stdafx.h"
#include "MaterialCom.h"

CMaterialCom::CMaterialCom(const D3DMATERIAL9* _pMaterial, TCHAR* _tszTexKey)
{
	// Component Type
	m_eComType = COM_TYPE_MATERIAL;

	// Material
	if(_pMaterial != NULL)
	{
		m_pMaterial = new D3DMATERIAL9;
		memcpy_s(m_pMaterial, sizeof(D3DMATERIAL9), _pMaterial, sizeof(D3DMATERIAL9));
	}
	else
		m_pMaterial = NULL;

	// Texture
	if(_tszTexKey != NULL)
		m_pTexture = CTextureMgr::GetInstance()->GetTexture(_tszTexKey);
	else
		m_pTexture = NULL;
}

CMaterialCom::~CMaterialCom()
{
	Release();
}

void CMaterialCom::Initialize()
{
}

int CMaterialCom::Update()
{
	return 0;
}

void CMaterialCom::Render()
{
	if(m_pMaterial != NULL)
		CDeviceMgr::GetInstance()->GetDevice()->SetMaterial(m_pMaterial);
	if(m_pTexture != NULL)
		CDeviceMgr::GetInstance()->GetDevice()->SetTexture(0, m_pTexture);
}

void CMaterialCom::Release()
{
	if(m_pMaterial != NULL)
		delete m_pMaterial;
}