#include "StdAfx.h"
#include "DemonHunter_Grenades_BombEffect.h"

CDemonHunter_Grenades_BombEffect::CDemonHunter_Grenades_BombEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades0")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades1")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades2")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades3")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades4")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades5")));
	m_TextureVec.push_back((LPDIRECT3DTEXTURE9)CTextureMgr::GetInstance()->GetTexture(_T("Effect_Grenades6")));

	m_Frame.iStart = 0;
	m_Frame.iEnd = 6;
	m_Frame.iCur = 0;
	m_Frame.fAccTime = 0.f;
	m_Frame.fFrameTime = 0.05f;

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

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f));
	AddComponent(pCollisionCom);

	// Coef
	m_fCoef = 1.6f;

	m_iMaxCnt = 999999;
}

CDemonHunter_Grenades_BombEffect::~CDemonHunter_Grenades_BombEffect(void)
{
	Release();
}

void CDemonHunter_Grenades_BombEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(250.f, 250.f, 250.f);
}

int CDemonHunter_Grenades_BombEffect::Update()
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

	D3DXMATRIX matBill;
	D3DXMatrixInverse(&matBill, NULL, CCameraMgr::GetInstance()->GetView());
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	D3DXMATRIX matTrans, matScale, matRotate;
	D3DXMatrixTranslation(&matTrans, m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y, m_pTransformCom->m_vPos.z);
	D3DXMatrixScaling(&matScale, m_pTransformCom->m_vSize.x, m_pTransformCom->m_vSize.y, m_pTransformCom->m_vSize.z);
	MatrixRotation(&matRotate, m_pTransformCom->m_vAngle.x, m_pTransformCom->m_vAngle.y, m_pTransformCom->m_vAngle.z);

	m_pTransformCom->m_mWorld = matScale * matRotate * matBill * matTrans;

	return 0;
}

void CDemonHunter_Grenades_BombEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Grenades_BombEffect::Release()
{
	m_TextureVec.clear();
}