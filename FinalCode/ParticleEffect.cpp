#include "StdAfx.h"
#include "ParticleEffect.h"

CParticleEffect::CParticleEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, DWORD _dwParticleCnt, DWORD _dwParticleOffset, TCHAR* _tszTexKey)
:CObject(_tszObjKey, _eObjType)
{
	//Particle
	m_pVS = new Particle[_dwParticleCnt];
	ZeroMemory(m_pVS, sizeof(Particle) * _dwParticleCnt);

	//ParticleValue
	m_pParticleValue = new ParticleValue[_dwParticleCnt];
	ZeroMemory(m_pParticleValue, sizeof(ParticleValue) * _dwParticleCnt);

	//Owner
	m_pOwner = _pOwner;

	//ParticleCnt
	m_dwParticleMaxCnt = _dwParticleCnt;

	//ParticleOffset
	m_dwParticleOffset = _dwParticleOffset;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Particle"));
	AddComponent(pBufferCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _tszTexKey);
	AddComponent(pMaterialCom);

	m_pParticle = (CParticle*)pBufferCom->m_BufferVec[0];

	m_dwCount	= 0;
}

CParticleEffect::~CParticleEffect(void)
{
	Release();
}

void CParticleEffect::Initialize()
{
	CObject::Initialize();
}

int CParticleEffect::Update()
{
	CObject::Update();

	return 0;
}

void CParticleEffect::Render()
{
	CObject::Render();

	m_pParticle->RenderParticle(m_pVS, m_dwCount, m_dwParticleOffset);
}

void CParticleEffect::Release()
{
	delete[] m_pVS;
	delete[] m_pParticleValue;
}

int CParticleEffect::Add_Particle(ParticleValue _ParticleValue)
{
	if(m_dwCount == m_dwParticleMaxCnt)
	{
		return -1;
	}

	m_pParticleValue[m_dwCount] = _ParticleValue;
	++m_dwCount;

	return 0;
}

void CParticleEffect::Release_Particle(DWORD _dwCur)
{
	if(&m_pParticleValue[m_dwCount] != &m_pParticleValue[_dwCur]) //지워야 하는 파티클이 배열의 마지막이 아닐경우.
	{
		ParticleValue pTemp = m_pParticleValue[_dwCur];
		m_pParticleValue[_dwCur] = m_pParticleValue[m_dwCount];
		m_pParticleValue[m_dwCount] = pTemp;
	}

	ZeroMemory(&m_pParticleValue[m_dwCount], sizeof(ParticleValue));
	--m_dwCount;
}