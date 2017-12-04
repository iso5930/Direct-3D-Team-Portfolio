#include "StdAfx.h"
#include "WitchDoctorCorpseSpiders_SpiderEffect.h"

CWitchDoctorCorpseSpiders_SpiderEffect::CWitchDoctorCorpseSpiders_SpiderEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_CorpseSpider_Spider"));
	m_pMesh = (CDynamicMesh*)(pBufferCom->m_BufferVec[0]);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 16;
	AddComponent(pRenderCom);

	m_iMode = 0;
	m_fTime = 0.f;
	m_fAccTime = 0.f;

	m_bCheck = false;


}

CWitchDoctorCorpseSpiders_SpiderEffect::~CWitchDoctorCorpseSpiders_SpiderEffect(void)
{
	Release();
}

void CWitchDoctorCorpseSpiders_SpiderEffect::Initialize()
{
	CEffect::Initialize();

	m_pMesh->m_pAnimController->SetAnimation(0);
}

int CWitchDoctorCorpseSpiders_SpiderEffect::Update()
{
	m_fTime +=	CTimeMgr::GetInstance()->GetDeltaTime();

 	if(m_fTime >= 5.f )
 		Destroy();

 	CEffect::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;

	}

	return 0;
}

void CWitchDoctorCorpseSpiders_SpiderEffect::Render()
{
	CEffect::Render();
}

void CWitchDoctorCorpseSpiders_SpiderEffect::Release()
{

}

void CWitchDoctorCorpseSpiders_SpiderEffect::Mode0()
{

}

void CWitchDoctorCorpseSpiders_SpiderEffect::Mode1()
{
	
}

void CWitchDoctorCorpseSpiders_SpiderEffect::Mode2()
{
	
}


