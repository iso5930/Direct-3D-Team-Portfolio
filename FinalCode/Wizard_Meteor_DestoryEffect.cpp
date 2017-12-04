#include "StdAfx.h"
#include "Wizard_Meteor_DestoryEffect.h"

CWizard_Meteor_DestoryEffect::CWizard_Meteor_DestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory5")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory6")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory7")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory8")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory9")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory10")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory11")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory12")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory13")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory14")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory15")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory16")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory17")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory18")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory19")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory20")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory21")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory22")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory23")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory24")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory25")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory26")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory27")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory28")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory29")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory30")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory31")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory32")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory33")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory34")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory35")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory36")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory37")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory38")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory39")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory40")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory41")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory42")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory43")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory44")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory45")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory46")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory47")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory48")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory49")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory50")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory51")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory52")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory53")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory54")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory55")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory56")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory57")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory58")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory59")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory60")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Meteor_Destory61")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 61;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.01f;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	m_pMaterialCom = new CMaterialCom(NULL, NULL);
	AddComponent(m_pMaterialCom);
}

CWizard_Meteor_DestoryEffect::~CWizard_Meteor_DestoryEffect(void)
{
	Release();
}

void CWizard_Meteor_DestoryEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(400.f, 400.f, 1.f);
}

int CWizard_Meteor_DestoryEffect::Update()
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

	m_pMaterialCom->m_pTexture = m_TextureVec[m_Frame.iCur];

	// World
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mScale, &m_pTransformCom->m_mRotate);
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, CCameraMgr::GetInstance()->GetBillBoard());
	D3DXMatrixMultiply(&m_pTransformCom->m_mWorld, &m_pTransformCom->m_mWorld, &m_pTransformCom->m_mTrans);

	/*
	D3DXMATRIX matBill = *CCameraMgr::GetInstance()->GetBillBoard();

	D3DXMATRIX matTrans, matScale, matRotate;
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);

	m_pTransformCom->m_mWorld = matScale * matBill * matTrans;
	*/

	return 0;
}

void CWizard_Meteor_DestoryEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_DestoryEffect::Release()
{

}
