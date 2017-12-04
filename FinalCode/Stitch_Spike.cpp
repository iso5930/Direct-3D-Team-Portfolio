#include "StdAfx.h"
#include "Stitch_Spike.h"

CStitch_Spike::CStitch_Spike(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, Bone* _pBone)
: CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Bone
	m_pBone = _pBone;

	// Scale
	m_iScaleMode = 0;

	// Time
	m_fTime = 0.0f;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(1.f, 0.f, 1.f);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Stitch_Spike"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	//D3DXVec3TransformCoord(&m_pTransformCom->m_vPos, &m_pTransformCom->m_vPos, &m_Bone.mWorld);


}

CStitch_Spike::~CStitch_Spike(void)
{
	Release();
}

void CStitch_Spike::Initialize()
{
	CEffect::Initialize();
}

int CStitch_Spike::Update()
{
	CEffect::Update();

	m_pTransformCom->m_mWorld *= m_pBone->mWorld;

	m_fTime += 2 * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_iScaleMode == 0)
	{
		m_pTransformCom->m_vSize.y = m_fTime;

		if(m_pTransformCom->m_vSize.y >= 1)
		{
			m_pTransformCom->m_vSize.y = 1;
			m_fTime = 0.f;
			m_iScaleMode = 1;
		}
	}

	if(m_iScaleMode == 1)
	{
		m_pTransformCom->m_vSize.y = 1 - m_fTime;
		
		if(m_pTransformCom->m_vSize.y < 0)
		{
			m_pTransformCom->m_vSize.y = 0;
			m_fTime = 0.f;
			m_iScaleMode = 2;
		}
	}
	
	if(m_iScaleMode == 2)
	{
		Destroy();
	}

	return 0;
}

void CStitch_Spike::Render()
{
	CEffect::Render();
}

void CStitch_Spike::Release()
{

}