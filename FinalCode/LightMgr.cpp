#include "StdAfx.h"
#include "LightMgr.h"

#include "Light.h"

IMPLEMENT_SINGLETON(CLightMgr)

CLightMgr::CLightMgr()
{
	D3DXCreateSphere(CDeviceMgr::GetInstance()->GetDevice(), 10.0f, 4, 4, &m_pSphere, NULL);

	ZeroMemory(m_pLightArr, sizeof(m_pLightArr));
	m_pLight = NULL;

	ZeroMemory(&m_vPos3D, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vPos4D, sizeof(D3DXVECTOR4));

	m_fNear = 0.0f;
	m_fFar = 0.0f;
	m_fDist = 0.0f;

	D3DXMatrixIdentity(&m_mView);
	D3DXMatrixIdentity(&m_mProj);
	D3DXMatrixIdentity(&m_mViewProj);

	D3DXMatrixIdentity(&m_mInvView);
	D3DXMatrixIdentity(&m_mInvProj);
	D3DXMatrixIdentity(&m_mInvViewProj);

	D3DXMatrixIdentity(&m_mPreView);
	D3DXMatrixIdentity(&m_mPreProj);
	D3DXMatrixIdentity(&m_mPreViewProj);

	for(int i = 0; i < CASCADED_END; ++i)
		D3DXMatrixIdentity(&m_matLightView[i]);
	for(int i = 0; i < CASCADED_END; ++i)
		D3DXMatrixIdentity(&m_matLightProj[i]);
	for(int i = 0; i < CASCADED_END; ++i)
		D3DXMatrixIdentity(&m_matLightViewProj[i]);
	for(int i = 0; i < CASCADED_END; ++i)
		m_fCascadedFar[i] = 0.0f;
}

CLightMgr::~CLightMgr()
{
	Release();
}

void CLightMgr::Initialize()
{
}

int CLightMgr::Update()
{
	// PreView
	m_mPreView = m_mView;

	// PreProj
	m_mPreProj = m_mProj;

	// PreViewProj
	m_mPreViewProj = m_mViewProj;

	if(m_pLight != NULL)
	{
		// View
		memcpy_s(&m_mView, sizeof(D3DXMATRIX), m_pLight->GetView(), sizeof(D3DXMATRIX));

		// Proj
		memcpy_s(&m_mProj, sizeof(D3DXMATRIX), m_pLight->GetProj(), sizeof(D3DXMATRIX));

		// InvView
		D3DXMatrixInverse(&m_mInvView, NULL, &m_mView);

		// InvProj
		D3DXMatrixInverse(&m_mInvProj, NULL, &m_mProj);

		// Pos3D
		MatrixToPos(&m_vPos3D, &m_mInvView);

		// Pos4D
		memcpy_s(&m_vPos4D, sizeof(D3DXVECTOR3), &m_vPos3D, sizeof(D3DXVECTOR3));
		m_vPos4D.w = 1.0f;

		// Near
		m_fNear = m_pLight->GetNear();

		// Far
		m_fFar = m_pLight->GetFar();

		// Dist
		m_fDist = m_pLight->GetDist();

		// Aspect
		float fAspect = (float)WINCX / (float)WINCY;

		// 1단계
		float fNear[CASCADED_END], fFar[CASCADED_END];
		fNear[0] = CCameraMgr::GetInstance()->GetNear();
		fFar[0] = CCameraMgr::GetInstance()->GetFar() * 0.2f + fNear[0];

		// 2단계
		fNear[1] = fFar[0];
		fFar[1] = CCameraMgr::GetInstance()->GetFar() * 0.4f + fNear[1];

		// 3단계
		fNear[2] = fFar[1];
		fFar[2] = CCameraMgr::GetInstance()->GetFar();

		// CascadeCameraProj
		D3DXMATRIX mCascadeCameraProj[CASCADED_END];

		for(int i = 0; i < CASCADED_END; ++i)
		{
			m_fCascadedFar[i] = fFar[i];

			// CascadeCameraProj
			D3DXMatrixPerspectiveFovLH(&mCascadeCameraProj[i], D3DXToRadian(60.f), fAspect, fNear[i], fFar[i]);

			// ViewProj
			D3DXMATRIX mViewProj;
			D3DXMatrixMultiply(&mViewProj, CCameraMgr::GetInstance()->GetView(), &mCascadeCameraProj[i]);

			// InvViewProj
			D3DXMATRIX mInvViewProj;
			D3DXMatrixInverse(&mInvViewProj, NULL, &mViewProj);

			// To World
			D3DXVECTOR3 vWorld[8] = 
			{
				D3DXVECTOR3(-1.f, 1.f, 0.f),
				D3DXVECTOR3(1.f, 1.f, 0.f),
				D3DXVECTOR3(1.f, -1.f, 0.f),
				D3DXVECTOR3(-1.f, -1.f, 0.f),
				D3DXVECTOR3(-1.f, 1.f, 1.f),
				D3DXVECTOR3(1.f, 1.f, 1.f),
				D3DXVECTOR3(1.f, -1.f, 1.f),
				D3DXVECTOR3(-1.f, -1.f, 1.f)
			};

			for(int j = 0; j < 8; ++j)
				D3DXVec3TransformCoord(&vWorld[j], &vWorld[j], &mInvViewProj);

			// Center
			D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);

			for(int j = 0; j < 8; ++j)
				vCenter += vWorld[j];

			vCenter /= 8.0f;
			vCenter.x = (float)floor(vCenter.x);
			vCenter.y = (float)floor(vCenter.y);

			// Ray
			D3DXVECTOR3 vRay = vWorld[0] - vWorld[6];

			// Radius
			float fRadius = D3DXVec3Length(&vRay) / 2.0f;

			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)m_pLight->GetComponent(COM_TYPE_TRANSFORM);

			// Dir
			D3DXVECTOR3 vLightDir = pTransformCom->m_vAxisZ;

			// Eye
			D3DXVECTOR3 vEye = vCenter - (vLightDir * fRadius * 2.0f);

			D3DXMATRIX matLightView, matLightProj;
			D3DXMatrixLookAtLH(&matLightView, &vEye, &vCenter, &pTransformCom->m_vAxisY);	
			D3DXMatrixOrthoOffCenterLH(&matLightProj, -fRadius, fRadius, -fRadius, fRadius, -fRadius * 6.f, fRadius * 6.f);

			m_matLightViewProj[i] = matLightView * matLightProj;
		}
	}
	else
	{
		// View
		D3DXMatrixIdentity(&m_mView);

		// Proj
		D3DXMatrixIdentity(&m_mProj);

		// InvView
		D3DXMatrixInverse(&m_mInvView, NULL, &m_mView);

		// InvProj
		D3DXMatrixInverse(&m_mInvProj, NULL, &m_mProj);

		// Pos3D
		MatrixToPos(&m_vPos3D, &m_mInvView);

		// Pos4D
		memcpy_s(&m_vPos4D, sizeof(D3DXVECTOR3), &m_vPos3D, sizeof(D3DXVECTOR3));
		m_vPos4D.w = 1.0f;

		// Near
		m_fNear = 0.0f;

		// Far
		m_fFar = 0.0f;

		// Dist
		m_fDist = 0.0f;

		for(int i = 0; i < CASCADED_END; ++i)
			D3DXMatrixIdentity(&m_matLightView[i]);
		for(int i = 0; i < CASCADED_END; ++i)
			D3DXMatrixIdentity(&m_matLightProj[i]);
		for(int i = 0; i < CASCADED_END; ++i)
			D3DXMatrixIdentity(&m_matLightViewProj[i]);
		for(int i = 0; i < CASCADED_END; ++i)
			m_fCascadedFar[i] = 0.0f;
	}

	// ViewProj
	D3DXMatrixMultiply(&m_mViewProj, &m_mView, &m_mProj);

	// InvViewProj
	D3DXMatrixInverse(&m_mInvViewProj, NULL, &m_mViewProj);

	return 0;
}

void CLightMgr::Render()
{
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_POINT_LIGHT)
	{
		// Trans
		D3DXMATRIX mTrans;

		for(int i = 0; i < 100; ++i)
		{
			if(m_pLightArr[i] != NULL && m_pLightArr[i]->GetLightType() == LIGHT_TYPE_POINT)
			{
				// Trans
				D3DXMatrixTranslation(&mTrans, m_pLightArr[i]->GetPos()->x, m_pLightArr[i]->GetPos()->y, m_pLightArr[i]->GetPos()->z);
				D3DXMatrixMultiply(&mTrans, &mTrans, CCameraMgr::GetInstance()->GetViewProj());

				// SetTransform
				CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &mTrans);

				// DrawSubset
				m_pSphere->DrawSubset(0);
			}
		}
	}
}

void CLightMgr::Release()
{
	if(m_pSphere != NULL)
	{
		m_pSphere->Release();
		m_pSphere = NULL;
	}

	for(int i = 0; i < 100; ++i)
	{
		if(m_pLightArr[i] != NULL)
		{
			m_pLightArr[i]->Destroy();
			m_pLightArr[i] = NULL;
		}
	}
}

void CLightMgr::AddLight(DWORD _dwIndex, CLight* _pLight)
{
	if(m_pLightArr[_dwIndex] != NULL)
		RemoveLight(_dwIndex, m_pLightArr[_dwIndex]);

	m_pLightArr[_dwIndex] = _pLight;
}

void CLightMgr::RemoveLight(DWORD _dwIndex, CLight* _pLight)
{
	if(m_pLightArr[_dwIndex] == _pLight)
	{
		m_pLightArr[_dwIndex]->Destroy();
		m_pLightArr[_dwIndex] = NULL;
	}

	if(m_pLight == _pLight)
		m_pLight = NULL;
}

void CLightMgr::Enable(DWORD _dwIndex)
{
	m_pLight = m_pLightArr[_dwIndex];
}