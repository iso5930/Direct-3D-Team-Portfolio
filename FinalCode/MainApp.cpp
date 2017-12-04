#include "StdAfx.h"
#include "MainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Initialize()
{
	ShowCursor(FALSE);
	
	// System Lv - DeviceMgr
	CDeviceMgr::GetInstance()->Initialize();
	// System Lv - TimeMgr
	CTimeMgr::GetInstance()->Initialize();
	// System Lv - InputMgr
	CInputMgr::GetInstance()->Initialize();
	// System Lv - SettingMgr
	CSettingMgr::GetInstance()->Initialize();
	// System Lv - ItemMgr
	CItemMgr::GetInstance()->Initialize();
	// System Lv - QuestMgr
	CQuestMgr::GetInstance()->Initialize();
	// System Lv - DataMgr
	CDataMgr::GetInstance()->Initialize();

	// Resource Lv - FontMgr
	CFontMgr::GetInstance()->Initialize();
	// Resource Lv - SoundMgr
	CSoundMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->LoadSystemSoundFile();
	CSoundMgr::GetInstance()->LoadUISoundFile();
	CSoundMgr::GetInstance()->LoadPlayerSoundFile();
	CSoundMgr::GetInstance()->LoadMonsterSoundFile();

	// Resource Lv - ShaderMgr
	CShaderMgr::GetInstance()->Initialize();
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Shadow"), new CShader(_T("../Resource/Shader/Shader_Shadow.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Velocity"), new CShader(_T("../Resource/Shader/Shader_Velocity.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Blur"), new CShader(_T("../Resource/Shader/Shader_Blur.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Back"), new CShader(_T("../Resource/Shader/Shader_Back.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_SkyBox"), new CShader(_T("../Resource/Shader/Shader_SkyBox.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Mesh"), new CShader(_T("../Resource/Shader/Shader_Mesh.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Light"), new CShader(_T("../Resource/Shader/Shader_Light.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Fog"), new CShader(_T("../Resource/Shader/Shader_Fog.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Blend"), new CShader(_T("../Resource/Shader/Shader_Blend.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_UI"), new CShader(_T("../Resource/Shader/Shader_UI.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_HDR"), new CShader(_T("../Resource/Shader/Shader_HDR.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Mouse"), new CShader(_T("../Resource/Shader/Shader_Mouse.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_SSAO"), new CShader(_T("../Resource/Shader/Shader_SSAO.hpp")));
	CShaderMgr::GetInstance()->AddShader(_T("Shader_Effect"), new CShader(_T("../Resource/Shader/Shader_Effect.hpp")));
	// Resource Lv - TextureMgr
	CTextureMgr::GetInstance()->Initialize();
	
	// Game Lv
	CLoadMgr::GetInstance()->Initialize();
	CLoadMgr::GetInstance()->LoadForBase();
	CSeamlessMgr::GetInstance()->Initialize();
	CUIMgr::GetInstance()->Initialize();
	CLightMgr::GetInstance()->Initialize();
	CCameraMgr::GetInstance()->Initialize();
	CCollisionMgr::GetInstance()->Initialize();
	CPathFindMgr::GetInstance()->Initialize();
	CUpdateMgr::GetInstance()->Initialize();
	CRenderMgr::GetInstance()->Initialize();

	CLoadScene* pLoadScene = new CLoadScene(NULL, false);
	pLoadScene->SetNextScene(new CTitleScene(NULL));
	pLoadScene->AddLoadVec(LOAD_TYPE_TITLE_SCENE);

	CSceneMgr::GetInstance()->Initialize(pLoadScene);
}

int CMainApp::Update()
{
	// System Lv
	CDeviceMgr::GetInstance()->Update();
	CTimeMgr::GetInstance()->Update();
	CInputMgr::GetInstance()->Update();
	CSettingMgr::GetInstance()->Update();
	CItemMgr::GetInstance()->Update();
	CQuestMgr::GetInstance()->Update();
	CDataMgr::GetInstance()->Update();

	// Resource Lv
	CFontMgr::GetInstance()->Update();
	CSoundMgr::GetInstance()->Update();
	CShaderMgr::GetInstance()->Update();
	CTextureMgr::GetInstance()->Update();
	CBufferMgr::GetInstance()->Update();

	// Game Lv
	CLoadMgr::GetInstance()->Update();
	CSeamlessMgr::GetInstance()->Update();
	CUIMgr::GetInstance()->Update();
	CLightMgr::GetInstance()->Update();
	CCameraMgr::GetInstance()->Update();
	CPathFindMgr::GetInstance()->Update();
	CCollisionMgr::GetInstance()->Update();
	CUpdateMgr::GetInstance()->Update();
	CRenderMgr::GetInstance()->Update();
	return CSceneMgr::GetInstance()->Update();
}

void CMainApp::Render()
{
	CDeviceMgr::GetInstance()->RenderBegin();

	// Game Lv
	CSceneMgr::GetInstance()->Render();
	CRenderMgr::GetInstance()->Render();
	CUpdateMgr::GetInstance()->Render();
	CPathFindMgr::GetInstance()->Render();
	CCollisionMgr::GetInstance()->Render();
	CCameraMgr::GetInstance()->Render();
	CLightMgr::GetInstance()->Render();
	CUIMgr::GetInstance()->Render();
	CSeamlessMgr::GetInstance()->Render();
	CLoadMgr::GetInstance()->Render();

	// Resource Lv
	CBufferMgr::GetInstance()->Render();
	CTextureMgr::GetInstance()->Render();
	CShaderMgr::GetInstance()->Render();
	CSoundMgr::GetInstance()->Render();
	CFontMgr::GetInstance()->Render();

	// System Lv
	CDataMgr::GetInstance()->Render();
	CQuestMgr::GetInstance()->Render();
	CItemMgr::GetInstance()->Render();
	CSettingMgr::GetInstance()->Render();
	CInputMgr::GetInstance()->Render();
	CTimeMgr::GetInstance()->Render();

	CDeviceMgr::GetInstance()->RenderEnd();
}

void CMainApp::Release()
{
	// Game Lv
	CSceneMgr::GetInstance()->DestroyInstance();
	CRenderMgr::GetInstance()->DestroyInstance();
	CUpdateMgr::GetInstance()->DestroyInstance();
	CPathFindMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CCameraMgr::GetInstance()->DestroyInstance();
	CLightMgr::GetInstance()->DestroyInstance();
	CUIMgr::GetInstance()->DestroyInstance();
	CSeamlessMgr::GetInstance()->DestroyInstance();
	CLoadMgr::GetInstance()->UnloadForBase();
	CLoadMgr::GetInstance()->DestroyInstance();

	// Resource Lv
	CBufferMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CShaderMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
	CFontMgr::GetInstance()->DestroyInstance();

	// System Lv
	CDataMgr::GetInstance()->DestroyInstance();
	CQuestMgr::GetInstance()->DestroyInstance();
	CItemMgr::GetInstance()->DestroyInstance();
	CSettingMgr::GetInstance()->DestroyInstance();
	CInputMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CDeviceMgr::GetInstance()->DestroyInstance();
}