#include "StdAfx.h"
#include "Light.h"

#include "LightMgr.h"
#include "TransformCom.h"
#include "UpdateCom.h"

CLight::CLight(TCHAR* _tszObjKey,
			   OBJ_TYPE _eObjType,
			   DWORD _dwIndex,
			   LIGHT_TYPE _eLightType,
			   D3DXVECTOR4* _pDiffuse,
			   D3DXVECTOR4* _pSpecular,
			   D3DXVECTOR4* _pAmbient,
			   D3DXVECTOR4* _pPos,
			   D3DXVECTOR4* _pDir,
			   float _fRange)
			   : CObject(_tszObjKey, _eObjType)
{
	// Index
	m_dwIndex = _dwIndex;

	// Light
	m_eLightType = _eLightType;
	ZeroMemory(m_vDiffuse, sizeof(D3DXVECTOR4));	if(_pDiffuse != NULL) { m_vDiffuse = *_pDiffuse; }
	ZeroMemory(m_vSpecular, sizeof(D3DXVECTOR4));	if(_pSpecular != NULL) { m_vSpecular = *_pSpecular; }
	ZeroMemory(m_vAmbient, sizeof(D3DXVECTOR4));	if(_pAmbient != NULL) { m_vAmbient = *_pAmbient; }
	ZeroMemory(m_vPos, sizeof(D3DXVECTOR4));		if(_pPos != NULL) { m_vPos = *_pPos; }	m_vPos.w = 1.0f;
	ZeroMemory(m_vDir, sizeof(D3DXVECTOR4));		if(_pDir != NULL) { m_vDir = *_pDir; }	m_vDir.w = 0.0f;	D3DXVec4Normalize(&m_vDir, &m_vDir);
	m_fRange = _fRange;

	// Far
	m_fFar = 0.0f;

	// Near
	m_fNear = 0.0f;

	// Dist
	m_fDist = 0.0f;

	// View
	D3DXMatrixIdentity(&m_mView);

	// Proj
	D3DXMatrixIdentity(&m_mProj);

	// Sphere
	m_pSphere = NULL;
	if(m_eLightType == LIGHT_TYPE_POINT)
		D3DXCreateSphere(CDeviceMgr::GetInstance()->GetDevice(), m_fRange, int(m_fRange / 30.0f), int(m_fRange / 30.0f), &m_pSphere, NULL);

	// UpdateCom
	AddComponent(new CUpdateCom(UPDATE_TYPE_LIGHT));
}

CLight::~CLight()
{
	Release();
}

void CLight::Initialize()
{
	CLightMgr::GetInstance()->AddLight(m_dwIndex, this);

	CObject::Initialize();
}

int CLight::Update()
{
	if(CLightMgr::GetInstance()->GetLight() == this)
	{
		// Update
		CObject::Update();

		// Pos
		m_pTransformCom->m_vPos = (*CCameraMgr::GetInstance()->GetPos3D()) - m_pTransformCom->m_vAxisZ * m_fDist;

		// Angle
		m_pTransformCom->m_vAngle.y += CTimeMgr::GetInstance()->GetDeltaTime() * D3DX_PI * 0.002f;

		// View
		MatrixLookAtLH(&m_mView, &(m_pTransformCom->m_vPos), &(m_pTransformCom->m_vAxisX), &(m_pTransformCom->m_vAxisY), &(m_pTransformCom->m_vAxisZ));
	}

	return 0;
}

void CLight::Render()
{
	CObject::Render();
}

void CLight::Release()
{
	CLightMgr::GetInstance()->RemoveLight(m_dwIndex, this);

	if(m_pSphere != NULL)
	{
		m_pSphere->Release();
		m_pSphere = NULL;
	}
}

void CLight::SetView(float _fDist, D3DXVECTOR3* _pAngle)
{
	m_fDist = _fDist;
	m_pTransformCom->m_vAngle = *_pAngle;
}

void CLight::SetProj(float _fFovy, float _fAspect, float _fNear, float _fFar)
{
	// Near
	m_fNear = _fNear;

	// Far
	m_fFar = _fFar;

	// Proj
	D3DXMatrixPerspectiveFovLH(&m_mProj, _fFovy, _fAspect, _fNear, _fFar);
}