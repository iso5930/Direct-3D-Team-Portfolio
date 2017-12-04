#include "StdAfx.h"
#include "DemonHunter_Strafe_WeaponEffect.h"

CDemonHunter_Strafe_WeaponEffect::CDemonHunter_Strafe_WeaponEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _pWeaponName, CHAR* _pBoneName)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//Item_HandXBow_Base0
	
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_pWeaponName);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 12; //난사 스태틱매쉬
	AddComponent(pRenderCom);

	pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	CDynamicMesh* pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, _pBoneName);

	m_pWorld = &((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;
}

CDemonHunter_Strafe_WeaponEffect::~CDemonHunter_Strafe_WeaponEffect(void)
{
	Release();
}

void CDemonHunter_Strafe_WeaponEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_Strafe_WeaponEffect::Update()
{
	CEffect::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * (*m_pWorld);

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * m_WeaponBone.mWorld;

	return 0; 
}

void CDemonHunter_Strafe_WeaponEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Strafe_WeaponEffect::Release()
{

}