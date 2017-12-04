#include "StdAfx.h"
#include "DemonHunter_SmokeScreen_SmokeEffect.h"

CDemonHunter_SmokeScreen_SmokeEffect::CDemonHunter_SmokeScreen_SmokeEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_SmokeScreen_Smoke5")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 5;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.1f;

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 5;
	AddComponent(pRenderCom);
}

CDemonHunter_SmokeScreen_SmokeEffect::~CDemonHunter_SmokeScreen_SmokeEffect(void)
{
	Release();
}

void CDemonHunter_SmokeScreen_SmokeEffect::Initialize()
{
	CEffect::Initialize();

	//m_pTransformCom->m_vPos = D3DXVECTOR3(0.f, 30.f, 0.f);
	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CDemonHunter_SmokeScreen_SmokeEffect::Update()
{
	CEffect::Update();

	m_Frame.fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_Frame.fAccTime >= m_Frame.fFrameTime)
	{
		m_Frame.fAccTime = 0.f;

		if(++m_Frame.iCur > m_Frame.iEnd)
		{
			m_Frame.iCur = m_Frame.iStart;

			Destroy();
		}
	}

	m_pTransformCom->m_vPos += D3DXVECTOR3(0.f, 1.f, 0.f) * 150.f * CTimeMgr::GetInstance()->GetDeltaTime();

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mTrans;

	return 0;
}

void CDemonHunter_SmokeScreen_SmokeEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SmokeScreen_SmokeEffect::Release()
{

}