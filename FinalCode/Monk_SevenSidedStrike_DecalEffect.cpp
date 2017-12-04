#include "StdAfx.h"
#include "Monk_SevenSidedStrike_DecalEffect.h"

CMonk_SevenSidedStrike_DecalEffect::CMonk_SevenSidedStrike_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_SevenSidedStrike_Decal"));
	AddComponent(pMaterialCom);

	m_fAlpha = 0.5f;
	m_fTime = 0.f;
	m_fCreateTime = 0.f; 
}

CMonk_SevenSidedStrike_DecalEffect::~CMonk_SevenSidedStrike_DecalEffect(void)
{
	Release();
}
void CMonk_SevenSidedStrike_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(350.f, 350.f, 350.f);
}

int CMonk_SevenSidedStrike_DecalEffect::Update()
{
	CEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();
	
	m_fCreateTime += fTime;
	m_fTime += fTime;

	if(m_fCreateTime >= 0.3f)
	{
		m_fCreateTime = 0.f;

		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SEVEN_SIDED_STRIKE.ogg"));

		D3DXVECTOR3 vDir(0.f, 0.f, 1.f);

		float fAngle = float(rand() % 360);

		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(fAngle));
		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

		D3DXVECTOR3 vImageDir = (vDir * -1.f) * 1500.f;

		CMonk_SevenSidedStrike_AfterImageEffect* pAfterImageEffect = new CMonk_SevenSidedStrike_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vImageDir);
		m_pLayer->AddObject(pAfterImageEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterImageEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + vDir * 500.f;
		pTransformCom->m_vAngle.y = D3DXToRadian(fAngle);
		pAfterImageEffect->Initialize();
	}

	if(m_fTime >= 2.2f)
		Destroy();

	return 0;
}

void CMonk_SevenSidedStrike_DecalEffect::Render()
{
	CEffect::Render();
}

void CMonk_SevenSidedStrike_DecalEffect::Release()
{

}