#include "StdAfx.h"
#include "RenderTarget.h"

CRenderTarget::CRenderTarget(DWORD _dwSizeX, DWORD _dwSizeY, D3DFORMAT _Format, D3DXCOLOR _dwColor)
{
	m_bUse = true;
	m_dwColor = _dwColor;

	if(FAILED(CDeviceMgr::GetInstance()->GetDevice()->CreateTexture(_dwSizeX, _dwSizeY, 1, D3DUSAGE_RENDERTARGET, _Format, D3DPOOL_DEFAULT, &m_pTexture, NULL)))
		cout << "CreateTexture() Error" << endl;

	if(FAILED(m_pTexture->GetSurfaceLevel(0, &m_pSurface)))
		cout << "GetSurfaceLevel() Error" << endl;

	if(FAILED(CDeviceMgr::GetInstance()->GetDevice()->CreateDepthStencilSurface(_dwSizeX, _dwSizeY, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pDepthStencil, NULL)))
		cout << "CreateDepthStencilSurface() Error" << endl;

	m_pBackSurface = NULL;
	m_pBackDepthStencil = NULL;

	m_pVB = NULL;
	m_pIB = NULL;
}

CRenderTarget::~CRenderTarget()
{
	if(m_pVB != NULL)
		m_pVB->Release();

	if(m_pIB != NULL)
		m_pIB->Release();

	if(m_pSurface != NULL)
		m_pSurface->Release();

	if(m_pDepthStencil != NULL)
		m_pDepthStencil->Release();

	if(m_pTexture != NULL)
		m_pTexture->Release();
}

void CRenderTarget::Clear()
{
	if(m_bUse == false)
		return;

	m_bUse = false;
	CDeviceMgr::GetInstance()->GetDevice()->GetRenderTarget(0, &m_pBackSurface);
	CDeviceMgr::GetInstance()->GetDevice()->GetDepthStencilSurface(&m_pBackDepthStencil);
	
	CDeviceMgr::GetInstance()->GetDevice()->SetRenderTarget(0, m_pSurface);
	CDeviceMgr::GetInstance()->GetDevice()->SetDepthStencilSurface(m_pDepthStencil);
	CDeviceMgr::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_dwColor, 1.0f, 0);
	
	CDeviceMgr::GetInstance()->GetDevice()->SetRenderTarget(0, m_pBackSurface);
	CDeviceMgr::GetInstance()->GetDevice()->SetDepthStencilSurface(m_pBackDepthStencil);
	
	if(m_pBackSurface != NULL)
	{
		m_pBackSurface->Release();
		m_pBackSurface = NULL;
	}

	if(m_pBackDepthStencil != NULL)
	{
		m_pBackDepthStencil->Release();
		m_pBackDepthStencil = NULL;
	}
}

void CRenderTarget::Begin(DWORD _dwIndex)
{
	m_bUse = true;
	CDeviceMgr::GetInstance()->GetDevice()->GetRenderTarget(_dwIndex, &m_pBackSurface);
	CDeviceMgr::GetInstance()->GetDevice()->GetDepthStencilSurface(&m_pBackDepthStencil);

	CDeviceMgr::GetInstance()->GetDevice()->SetRenderTarget(_dwIndex, m_pSurface);
	CDeviceMgr::GetInstance()->GetDevice()->SetDepthStencilSurface(m_pDepthStencil);
}

void CRenderTarget::End(DWORD _dwIndex)
{
	CDeviceMgr::GetInstance()->GetDevice()->SetRenderTarget(_dwIndex, m_pBackSurface);
	CDeviceMgr::GetInstance()->GetDevice()->SetDepthStencilSurface(m_pBackDepthStencil);

	if(m_pBackSurface != NULL)
	{
		m_pBackSurface->Release();
		m_pBackSurface = NULL;
	}

	if(m_pBackDepthStencil != NULL)
	{
		m_pBackDepthStencil->Release();
		m_pBackDepthStencil = NULL;
	} 
}

void CRenderTarget::CreateDebugBuffer(float _fX, float _fY, float _fSizeX, float _fSizeY)
{
	if(FAILED(CDeviceMgr::GetInstance()->GetDevice()->CreateVertexBuffer(4 * sizeof(Vertex), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_pVB, NULL)))
		cout << "CreateVertexBuffer() Error" << endl;

	if(FAILED(CDeviceMgr::GetInstance()->GetDevice()->CreateIndexBuffer(2 * sizeof(Index), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, 0)))
		cout << "CreateIndexBuffer() Error" << endl;

	Vertex* pVS;
	m_pVB->Lock(0, 0, (void**)&pVS, 0);

	pVS[0].vPos.x = _fX;			pVS[0].vPos.y = _fY;			pVS[0].vPos.z = 0.0f;		pVS[0].vNormal.x = 0.0f;	pVS[0].vNormal.y = 0.0f;	pVS[0].vNormal.z = -1.0f;	pVS[0].vTexUV.x = 0.0f;		pVS[0].vTexUV.y = 1.0f;
	pVS[1].vPos.x = _fX;			pVS[1].vPos.y = _fY + _fSizeY;	pVS[1].vPos.z = 0.0f;		pVS[1].vNormal.x = 0.0f;	pVS[1].vNormal.y = 0.0f;	pVS[1].vNormal.z = -1.0f;	pVS[1].vTexUV.x = 0.0f;		pVS[1].vTexUV.y = 0.0f;
	pVS[2].vPos.x = _fX + _fSizeX;	pVS[2].vPos.y = _fY + _fSizeY;	pVS[2].vPos.z = 0.0f;		pVS[2].vNormal.x = 0.0f;	pVS[2].vNormal.y = 0.0f;	pVS[2].vNormal.z = -1.0f;	pVS[2].vTexUV.x = 1.0f;		pVS[2].vTexUV.y = 0.0f;
	pVS[3].vPos.x = _fX + _fSizeX;	pVS[3].vPos.y = _fY;			pVS[3].vPos.z = 0.0f;		pVS[3].vNormal.x = 0.0f;	pVS[3].vNormal.y = 0.0f;	pVS[3].vNormal.z = -1.0f;	pVS[3].vTexUV.x = 1.0f;		pVS[3].vTexUV.y = 1.0f;

	m_pVB->Unlock();

	Index* pIS;
	m_pIB->Lock(0, 0, (void**)&pIS, 0);

	pIS[0]._1 = 0;		pIS[0]._2 = 1;		pIS[0]._3 = 2;
	pIS[1]._1 = 0;		pIS[1]._2 = 2;		pIS[1]._3 = 3;

	m_pIB->Unlock();
}

void CRenderTarget::RenderDebugBuffer()
{
	CDeviceMgr::GetInstance()->GetDevice()->SetTexture(0, m_pTexture);
	CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
	CDeviceMgr::GetInstance()->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);
	CDeviceMgr::GetInstance()->GetDevice()->SetIndices(m_pIB);
	CDeviceMgr::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}