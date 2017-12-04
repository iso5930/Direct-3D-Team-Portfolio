#include "StdAfx.h"
#include "WitchDoctor_LocustsSwarm_CloudEffect.h"

CWitchDoctor_LocustsSwarm_CloudEffect::CWitchDoctor_LocustsSwarm_CloudEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner,D3DXVECTOR3& _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 8;
	AddComponent(pRenderCom);
	
	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_LocustsSwarm_Cloud"));
	AddComponent(pMaterialCom);

	m_fAlpha = 0.5f;
	m_fTime = 0.f;
	m_fSizeTime = (rand() % 50) + 30.f ; 

	m_vDir = _vDir; 
}

CWitchDoctor_LocustsSwarm_CloudEffect::~CWitchDoctor_LocustsSwarm_CloudEffect(void)
{
	Release();
}

void CWitchDoctor_LocustsSwarm_CloudEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_pTransformCom->m_vAngle.y += D3DXToRadian((rand() % 360) - 0.f);
}

int CWitchDoctor_LocustsSwarm_CloudEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vAngle.y += D3DXToRadian(5.f) * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos += (m_vDir +D3DXVECTOR3(0.f, 1.f, 0.f)) * 15.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * m_fSizeTime * CTimeMgr::GetInstance()->GetDeltaTime();

	if (m_fTime >= 0.3f )
	{
		m_fTime = 0.0f;
		m_fAlpha +=  0.05f;
	}

	if(m_fAlpha <= 0.f) 
		Destroy();


	return 0;
}

void CWitchDoctor_LocustsSwarm_CloudEffect::Render()
{
	CEffect::Render();
}

void CWitchDoctor_LocustsSwarm_CloudEffect::Release()
{

}
