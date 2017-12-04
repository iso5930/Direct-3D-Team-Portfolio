#include "StdAfx.h"
#include "Particle.h"

CParticle::CParticle(void)
{
	// BufType
	m_eBufType = BUF_TYPE_PARTICLE;

	//FVF
	m_dwFVF = D3DFVF_XYZ | D3DFVF_PSIZE;

	//VtxSize
	m_dwVtxSize = sizeof(Particle);

	//VtxCnt
	m_dwVtxCnt = 1000;

	//Offset
	m_dwOffset = 0;

	CDeviceMgr::GetInstance()->GetDevice()->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize, D3DUSAGE_POINTS, 0, D3DPOOL_MANAGED, &m_pVB, 0);
}

CParticle::CParticle(CParticle* _pParticle)
{
	// RefCnt
	m_dwRefCnt = _pParticle->m_dwRefCnt + 1;

	// FVF
	m_dwFVF = _pParticle->m_dwFVF;

	// VtxSize
	m_dwVtxSize = _pParticle->m_dwVtxSize;

	// VtxCnt
	m_dwVtxCnt = _pParticle->m_dwVtxCnt;

	// IdxSize
	m_dwIdxSize = _pParticle->m_dwIdxSize;

	// TriCnt
	m_dwTriCnt = _pParticle->m_dwTriCnt;

	// VB
	m_pVB = _pParticle->m_pVB;

	// IB
	m_pIB = _pParticle->m_pIB;

	// VS
	m_pVS = _pParticle->m_pVS;

	// IS
	m_pIS = _pParticle->m_pIS;

	//Offset
	m_dwOffset = 0;
}

CParticle::~CParticle(void)
{

}

int CParticle::Update()
{
	return 0;
}

void CParticle::Render()
{

}

CParticle* CParticle::Clone()
{
	return new CParticle(this);
}

void CParticle::RenderParticle(Particle* _pParticle, DWORD _dwVtxCnt, DWORD _dwOffSet)
{
	//Offset
	m_dwOffset = _dwOffSet;

	//VtxCnt
	m_dwVtxCnt = _dwVtxCnt;

	Particle* pParticle;

	DWORD dwOffSet = 0;
	DWORD dwCur = 0;

	if(m_dwVtxCnt >= m_dwOffset)
	{
		int iCnt = int(m_dwVtxCnt / m_dwOffset);

		CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(Particle));

		for(int i = 0; i < iCnt; ++i)
		{
			m_pVB->Lock(dwCur * m_dwVtxSize, dwOffSet * m_dwVtxSize, (void**)&pParticle, 0);
			memcpy_s(&pParticle[dwCur], m_dwVtxSize * dwOffSet, &_pParticle[dwCur], m_dwVtxSize * dwOffSet);
			m_pVB->Unlock();

			CDeviceMgr::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, dwCur, dwOffSet);

			dwCur += dwOffSet;
		}

		if(dwCur <= m_dwVtxCnt)
		{
			DWORD dwCnt = m_dwVtxCnt - dwCur;

			//남은게 있다는거.
			m_pVB->Lock(dwCur * m_dwVtxSize, dwCnt * m_dwVtxSize, (void**)&pParticle, 0);
			memcpy_s(&pParticle[dwCur], m_dwVtxSize * dwCnt, &_pParticle[dwCur], m_dwVtxSize * dwCnt);
			m_pVB->Unlock();

			CDeviceMgr::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, dwCur, dwCnt);
		}
	}
	else 
	{
		m_pVB->Lock(0, 0, (void**)&pParticle, 0);
		memcpy_s(pParticle, m_dwVtxSize * m_dwVtxCnt, _pParticle, m_dwVtxSize * m_dwVtxCnt);
		m_pVB->Unlock();

		CDeviceMgr::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(Particle));
		CDeviceMgr::GetInstance()->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, m_dwVtxCnt);
	}
}