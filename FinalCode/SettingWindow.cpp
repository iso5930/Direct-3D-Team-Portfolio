#include "StdAfx.h"
#include "SettingWindow.h"

CSettingWindow::CSettingWindow(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CWindowUI(_tszObjKey, _eObjType, _T("Window_Setting"))
{
	// Page
	m_iPage = 0;

	// BlurSelect
	m_iBlurSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_RADIAL_BLUR)
		m_iBlurSelect = 1;
	else if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_GAUSSIAN_BLUR)
		m_iBlurSelect = 2;
	else if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_MOTION_BLUR)
		m_iBlurSelect = 3;

	// ShadowSelect
	m_iShadowSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_NORMAL_SHADOW)
		m_iShadowSelect = 1;
	else if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_CASCADE_SHADOW)
		m_iShadowSelect = 2;

	// FogSelect
	m_iFogSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_EXPONENT_FOG)
		m_iFogSelect = 1;
	else if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_EXPONENT_SQUARE_FOG)
		m_iFogSelect = 2;
	else if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_HEIGHT_FOG)
		m_iFogSelect = 3;

	// HDRSelect
	m_iHDRSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_HDR)
		m_iHDRSelect = 1;

	// SSAOSelect
	m_iSSAOSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_SSAO)
		m_iSSAOSelect = 1;

	// DistortionSelect
	m_iDistortionSelect = 0;
	if(CSettingMgr::GetInstance()->GetRenderMode() & RENDER_MODE_DISTORTION)
		m_iDistortionSelect = 1;

	// DebugBufferSelect
	m_iDebugBufferSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_DEBUG_TARGET)
		m_iDebugBufferSelect = 1;

	// NavigationMeshSelect
	m_iNavigationMeshSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_NAVIGATION_MESH)
		m_iNavigationMeshSelect = 1;

	// CheckSphereSelect
	m_iCheckSphereSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_CHECK_SPHERE)
		m_iCheckSphereSelect = 1;

	// CollisionSphereSelect
	m_iCollisionSphereSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_COLLISION_SPHERE)
		m_iCollisionSphereSelect = 1;

	// CollisionBoxSelect
	m_iCollisionBoxSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_COLLISION_BOX)
		m_iCollisionBoxSelect = 1;

	// FPSSelect
	m_iFPSSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_FPS)
		m_iFPSSelect = 1;

	// PointLightSelect
	m_iPointLightSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_POINT_LIGHT)
		m_iPointLightSelect = 1;

	// NPCBoxSelect
	m_iNPCBoxSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_NPC_BOX)
		m_iNPCBoxSelect = 1;

	// ProbBoxSelect
	m_iProbBoxSelect = 0;
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_PROB_BOX)
		m_iProbBoxSelect = 1;

	// SettingButton
	// 0(Graphic), 1(Sound)
	ZeroMemory(m_pSettingButton, sizeof(m_pSettingButton));

	// BlurButton
	// 0(None), 1(Radial), 2(Gaussian), 3(Motion)
	ZeroMemory(m_pBlurButton, sizeof(m_pBlurButton));

	// ShadowButton
	// 0(None), 1(Normal), 2(Cascade)
	ZeroMemory(m_pShadowButton, sizeof(m_pShadowButton));

	// FogButton
	// 0(None), 1(Exponent), 2(Exponent^2), 3(Height)
	ZeroMemory(m_pFogButton, sizeof(m_pFogButton));

	// HDRButton
	// 0(None), 1(HDR)
	ZeroMemory(m_pHDRButton, sizeof(m_pHDRButton));

	// SSAOButton
	// 0(None), 1(SSAO)
	ZeroMemory(m_pSSAOButton, sizeof(m_pSSAOButton));

	// DistortionButton
	// 0(None), 1(Distortion)
	ZeroMemory(m_pDistortionButton, sizeof(m_pDistortionButton));

	// DebugBufferButton
	ZeroMemory(m_pDebugBufferButton, sizeof(m_pDebugBufferButton));

	// NavigationMeshButton
	ZeroMemory(m_pNavigationMeshButton, sizeof(m_pNavigationMeshButton));

	// CheckSphereButton
	ZeroMemory(m_pCheckSphereButton, sizeof(m_pCheckSphereButton));

	// CollisionSphereButton
	ZeroMemory(m_pCollisionSphereButton, sizeof(m_pCollisionSphereButton));

	// CollisionBoxButton
	ZeroMemory(m_pCollisionBoxButton, sizeof(m_pCollisionBoxButton));

	// FPSButton
	ZeroMemory(m_pFPSButton, sizeof(m_pFPSButton));

	// PointLightButton
	ZeroMemory(m_pPointLightButton, sizeof(m_pPointLightButton));

	// NPCBoxButton
	ZeroMemory(m_pNPCBoxButton, sizeof(m_pNPCBoxButton));

	// ProbBoxButton
	ZeroMemory(m_pProbBoxButton, sizeof(m_pProbBoxButton));

	// CheatKeyButton
	ZeroMemory(m_pCheatKeyButton, sizeof(m_pCheatKeyButton));

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(2.1f, 2.1f, 0.0f);
}

CSettingWindow::~CSettingWindow()
{
	Release();
}

void CSettingWindow::Initialize()
{
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Open_Window.ogg"));

	CWindowUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF9;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000006;

	// TransformCom
	CTransformCom* pTransformCom;

	// XButton(0)
	CBasicButton* pXButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.677993f, 0.832002f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.033f, 0.055f, 0.0f);
	pXButton->Initialize();
	AddButton(pXButton);

	// DestroyButton(1)
	CBasicButton* pDestroyButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Destroy"), _T("Button_Over_Destroy"), _T("Button_Down_Destroy"));
	m_pLayer->AddObject(pDestroyButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pDestroyButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.55f, -0.646998f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2f, 0.0838f, 0.0f);
	pDestroyButton->Initialize();
	AddButton(pDestroyButton);

	// CloseButton(2)
	CBasicButton* pCloseButton = new CBasicButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Close"), _T("Button_Over_Close"), _T("Button_Down_Close"));
	m_pLayer->AddObject(pCloseButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)pCloseButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.33f, -0.646998f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.2f, 0.0838f, 0.0f);
	pCloseButton->Initialize();
	AddButton(pCloseButton);

	// GraphicSettingButton
	m_pSettingButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_GraphicSetting"), _T("Button_Over_GraphicSetting"), _T("Button_Down_GraphicSetting"));
	m_pLayer->AddObject(m_pSettingButton[0], LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pSettingButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.485f, 0.52f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.275f, 0.08f, 0.0f);

	m_pSettingButton[0]->SetState(UI_L_DOWN);
	m_pSettingButton[0]->Initialize();

	// SoundSettingButton
	m_pSettingButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_SoundSetting"), _T("Button_Over_SoundSetting"), _T("Button_Down_SoundSetting"));
	m_pLayer->AddObject(m_pSettingButton[1], LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pSettingButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.485f, 0.42f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.275f, 0.08f, 0.0f);

	m_pSettingButton[1]->Initialize();

	// GameSettingButton
	m_pSettingButton[2] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_GameSetting"), _T("Button_Over_GameSetting"), _T("Button_Down_GameSetting"));
	m_pLayer->AddObject(m_pSettingButton[2], LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pSettingButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.485f, 0.32f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.275f, 0.08f, 0.0f);

	m_pSettingButton[2]->Initialize();

	// CheatKeySettingButton
	m_pSettingButton[3] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_CheatKey"), _T("Button_Over_CheatKey"), _T("Button_Down_CheatKey"));
	m_pLayer->AddObject(m_pSettingButton[3], LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pSettingButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.485f, 0.22f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.275f, 0.08f, 0.0f);

	m_pSettingButton[3]->Initialize();

	// NoneBlurButton
	m_pBlurButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pBlurButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pBlurButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.491997f, 0.0f);
	m_pBlurButton[0]->Initialize();

	// RadialBlurButton
	m_pBlurButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_RadialBlur"), _T("Button_Over_RadialBlur"), _T("Button_Down_RadialBlur"));
	m_pLayer->AddObject(m_pBlurButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pBlurButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.491997f, 0.0f);
	m_pBlurButton[1]->Initialize();

	// GaussianBlurButton
	m_pBlurButton[2] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_GaussianBlur"), _T("Button_Over_GaussianBlur"), _T("Button_Down_GaussianBlur"));
	m_pLayer->AddObject(m_pBlurButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pBlurButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.136f, 0.491997f, 0.0f);
	m_pBlurButton[2]->Initialize();

	// MotionBlurButton
	m_pBlurButton[3] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_MotionBlur"), _T("Button_Over_MotionBlur"), _T("Button_Down_MotionBlur"));
	m_pLayer->AddObject(m_pBlurButton[3], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pBlurButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.286f, 0.491997f, 0.0f);
	m_pBlurButton[3]->Initialize();

	// NoneShadowButton
	m_pShadowButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pShadowButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pShadowButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.295f, 0.0f);
	m_pShadowButton[0]->Initialize();

	// NormalShadowButton
	m_pShadowButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_NormalShadow"), _T("Button_Over_NormalShadow"), _T("Button_Down_NormalShadow"));
	m_pLayer->AddObject(m_pShadowButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pShadowButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.295f, 0.0f);
	m_pShadowButton[1]->Initialize();

	// CascadeShadowButton
	m_pShadowButton[2] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_CascadeShadow"), _T("Button_Over_CascadeShadow"), _T("Button_Down_CascadeShadow"));
	m_pLayer->AddObject(m_pShadowButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pShadowButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.136f, 0.295f, 0.0f);
	m_pShadowButton[2]->Initialize();

	// NoneFogButton
	m_pFogButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pFogButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFogButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.098f, 0.0f);
	m_pFogButton[0]->Initialize();

	// ExponentFogButton
	m_pFogButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ExponentFog"), _T("Button_Over_ExponentFog"), _T("Button_Down_ExponentFog"));
	m_pLayer->AddObject(m_pFogButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFogButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.098f, 0.0f);
	m_pFogButton[1]->Initialize();

	// ExponentSquareFog
	m_pFogButton[2] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_ExponentSquareFog"), _T("Button_Over_ExponentSquareFog"), _T("Button_Down_ExponentSquareFog"));
	m_pLayer->AddObject(m_pFogButton[2], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFogButton[2]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.136f, 0.098f, 0.0f);
	m_pFogButton[2]->Initialize();

	// HeightFog
	m_pFogButton[3] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_HeightFog"), _T("Button_Over_HeightFog"), _T("Button_Down_HeightFog"));
	m_pLayer->AddObject(m_pFogButton[3], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFogButton[3]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.286f, 0.098f, 0.0f);
	m_pFogButton[3]->Initialize();

	// NoneHDRButton
	m_pHDRButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pHDRButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pHDRButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.091f, 0.0f);
	m_pHDRButton[0]->Initialize();

	// UsingHDRButton
	m_pHDRButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pHDRButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pHDRButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.091f, 0.0f);
	m_pHDRButton[1]->Initialize();

	// NoneSSAOButton
	m_pSSAOButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pSSAOButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pSSAOButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.289f, 0.0f);
	m_pSSAOButton[0]->Initialize();

	// UsingSSAOButton
	m_pSSAOButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pSSAOButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pSSAOButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.289f, 0.0f);
	m_pSSAOButton[1]->Initialize();

	// NoneDistortionButton
	m_pDistortionButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pDistortionButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDistortionButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.477f, 0.0f);
	m_pDistortionButton[0]->Initialize();

	// UsingDistortionButton
	m_pDistortionButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pDistortionButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDistortionButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.477f, 0.0f);
	m_pDistortionButton[1]->Initialize();

	// NoneDebugBufferButton
	m_pDebugBufferButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pDebugBufferButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDebugBufferButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.491997f, 0.0f);
	m_pDebugBufferButton[0]->Initialize();

	// UsingDebugBufferButton
	m_pDebugBufferButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pDebugBufferButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pDebugBufferButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.491997f, 0.0f);
	m_pDebugBufferButton[1]->Initialize();

	// NoneNavigationMeshButton
	m_pNavigationMeshButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pNavigationMeshButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pNavigationMeshButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.295f, 0.0f);
	m_pNavigationMeshButton[0]->Initialize();

	// UsingNavigationMeshButton
	m_pNavigationMeshButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pNavigationMeshButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pNavigationMeshButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.295f, 0.0f);
	m_pNavigationMeshButton[1]->Initialize();

	// NoneCheckSphereButton
	m_pCheckSphereButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pCheckSphereButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCheckSphereButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, 0.098f, 0.0f);
	m_pCheckSphereButton[0]->Initialize();

	// UsingCheckSphereButton
	m_pCheckSphereButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pCheckSphereButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCheckSphereButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, 0.098f, 0.0f);
	m_pCheckSphereButton[1]->Initialize();

	// NoneCollisionSphereButton
	m_pCollisionSphereButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pCollisionSphereButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCollisionSphereButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.091f, 0.0f);
	m_pCollisionSphereButton[0]->Initialize();

	// UsingCollisionSphereButton
	m_pCollisionSphereButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pCollisionSphereButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCollisionSphereButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.091f, 0.0f);
	m_pCollisionSphereButton[1]->Initialize();

	// NoneCollisionBoxButton
	m_pCollisionBoxButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pCollisionBoxButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCollisionBoxButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.289f, 0.0f);
	m_pCollisionBoxButton[0]->Initialize();

	// UsingCollisionBoxButton
	m_pCollisionBoxButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pCollisionBoxButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCollisionBoxButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.289f, 0.0f);
	m_pCollisionBoxButton[1]->Initialize();

	// NoneFPSButton
	m_pFPSButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pFPSButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFPSButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.164f, -0.477f, 0.0f);
	m_pFPSButton[0]->Initialize();

	// UsingFPSButton
	m_pFPSButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pFPSButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pFPSButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.014f, -0.477f, 0.0f);
	m_pFPSButton[1]->Initialize();

	// NonePointLightButton
	m_pPointLightButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pPointLightButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pPointLightButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.234f, 0.491997f, 0.0f);
	m_pPointLightButton[0]->Initialize();

	// UsingPointLightButton
	m_pPointLightButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pPointLightButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pPointLightButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.386f, 0.491997f, 0.0f);
	m_pPointLightButton[1]->Initialize();

	// NoneNPCBoxButton
	m_pNPCBoxButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pNPCBoxButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pNPCBoxButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.234f, 0.295f, 0.0f);
	m_pNPCBoxButton[0]->Initialize();

	// UsingNPCButton
	m_pNPCBoxButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pNPCBoxButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pNPCBoxButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.386f, 0.295f, 0.0f);
	m_pNPCBoxButton[1]->Initialize();

	// NoneProbBoxButton
	m_pProbBoxButton[0] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_None"), _T("Button_Over_None"), _T("Button_Down_None"));
	m_pLayer->AddObject(m_pProbBoxButton[0], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pProbBoxButton[0]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.234f, 0.098f, 0.0f);
	m_pProbBoxButton[0]->Initialize();

	// UsingProbBoxButton
	m_pProbBoxButton[1] = new CSettingButton(NULL, OBJ_TYPE_STATIC, _T("Button_Back_Using"), _T("Button_Over_Using"), _T("Button_Down_Using"));
	m_pLayer->AddObject(m_pProbBoxButton[1], LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pProbBoxButton[1]->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.386f, 0.098f, 0.0f);
	m_pProbBoxButton[1]->Initialize();

	// CheatKeyButton
	TCHAR tszTexKey[3][11][MIN_STR];
	_tcscpy_s(tszTexKey[0][0], MIN_STR, _T("Button_Back_LevelUp"));			_tcscpy_s(tszTexKey[1][0], MIN_STR, _T("Button_Over_LevelUp"));			_tcscpy_s(tszTexKey[2][0], MIN_STR, _T("Button_Down_LevelUp"));
	_tcscpy_s(tszTexKey[0][1], MIN_STR, _T("Button_Back_QuestItem"));		_tcscpy_s(tszTexKey[1][1], MIN_STR, _T("Button_Over_QuestItem"));		_tcscpy_s(tszTexKey[2][1], MIN_STR, _T("Button_Down_QuestItem"));
	_tcscpy_s(tszTexKey[0][2], MIN_STR, _T("Button_Back_NormalItem"));		_tcscpy_s(tszTexKey[1][2], MIN_STR, _T("Button_Over_NormalItem"));		_tcscpy_s(tszTexKey[2][2], MIN_STR, _T("Button_Down_NormalItem"));
	_tcscpy_s(tszTexKey[0][3], MIN_STR, _T("Button_Back_MagicItem"));		_tcscpy_s(tszTexKey[1][3], MIN_STR, _T("Button_Over_MagicItem"));		_tcscpy_s(tszTexKey[2][3], MIN_STR, _T("Button_Down_MagicItem"));
	_tcscpy_s(tszTexKey[0][4], MIN_STR, _T("Button_Back_UniqueItem"));		_tcscpy_s(tszTexKey[1][4], MIN_STR, _T("Button_Over_UniqueItem"));		_tcscpy_s(tszTexKey[2][4], MIN_STR, _T("Button_Down_UniqueItem"));
	_tcscpy_s(tszTexKey[0][5], MIN_STR, _T("Button_Back_LegendItem"));		_tcscpy_s(tszTexKey[1][5], MIN_STR, _T("Button_Over_LegendItem"));		_tcscpy_s(tszTexKey[2][5], MIN_STR, _T("Button_Down_LegendItem"));
	_tcscpy_s(tszTexKey[0][6], MIN_STR, _T("Button_Back_SetItem"));			_tcscpy_s(tszTexKey[1][6], MIN_STR, _T("Button_Over_SetItem"));			_tcscpy_s(tszTexKey[2][6], MIN_STR, _T("Button_Down_SetItem"));
	_tcscpy_s(tszTexKey[0][7], MIN_STR, _T("Button_Back_GemItem"));			_tcscpy_s(tszTexKey[1][7], MIN_STR, _T("Button_Over_GemItem"));			_tcscpy_s(tszTexKey[2][7], MIN_STR, _T("Button_Down_GemItem"));
	_tcscpy_s(tszTexKey[0][8], MIN_STR, _T("Button_Back_MaterialItem"));	_tcscpy_s(tszTexKey[1][8], MIN_STR, _T("Button_Over_MaterialItem"));	_tcscpy_s(tszTexKey[2][8], MIN_STR, _T("Button_Down_MaterialItem"));
	_tcscpy_s(tszTexKey[0][9], MIN_STR, _T("Button_Back_GoldPlus"));		_tcscpy_s(tszTexKey[1][9], MIN_STR, _T("Button_Over_GoldPlus"));		_tcscpy_s(tszTexKey[2][9], MIN_STR, _T("Button_Down_GoldPlus"));
	_tcscpy_s(tszTexKey[0][10], MIN_STR, _T("Button_Back_GoldMinus"));		_tcscpy_s(tszTexKey[1][10], MIN_STR, _T("Button_Over_GoldMinus"));		_tcscpy_s(tszTexKey[2][10], MIN_STR, _T("Button_Down_GoldMinus"));

	for(int i = 0; i < 11; ++i)
	{
		m_pCheatKeyButton[i] = new CBasicButton(NULL, OBJ_TYPE_STATIC, tszTexKey[0][i], tszTexKey[1][i], tszTexKey[2][i]);
		m_pLayer->AddObject(m_pCheatKeyButton[i], LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = -0.164f + 0.152f * (i % 6);
		pTransformCom->m_vPos.y = 0.491997f - 0.092f * (i / 6);

		m_pCheatKeyButton[i]->Initialize();

		pUpdateCom = (CUpdateCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFA;

		pRenderCom = (CRenderCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000005;
	}

	Renew();
}

int CSettingWindow::Update()
{
	CWindowUI::Update();
	CInputMgr::GetInstance()->MousePosInvalidate();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF9;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000006;

	for(size_t i = 0; i < m_ButtonVec.size(); ++i)
	{
		pUpdateCom = (CUpdateCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFA;

		pRenderCom = (CRenderCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000005;
	}

	for(int i = 0; i < 11; ++i)
	{
		pUpdateCom = (CUpdateCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFA;

		pRenderCom = (CRenderCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000005;
	}

	if(m_ButtonVec[0]->IsLUp())
		Destroy();

	if(m_ButtonVec[1]->IsLUp())
	{
		// Account
		Account* pAccount = CDataMgr::GetInstance()->GetAccount(CDataMgr::GetInstance()->GetSelect());

		CLoadScene* pLoadScene = new CLoadScene(NULL, true);
		pLoadScene->SetNextScene(new CLoginScene(NULL));
		pLoadScene->AddUnloadVec(UNLOAD_TYPE_PLAY_SCENE);
		pLoadScene->AddLoadVec(LOAD_TYPE_TITLE_SCENE);

		if(pAccount->info.iJob == 0 && pAccount->info.iGender == 0)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_BARBARIAN_MALE);
		else if(pAccount->info.iJob == 0 && pAccount->info.iGender == 1)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_BARBARIAN_FEMALE);
		else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 0)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_DEMONHUNTER_MALE);
		else if(pAccount->info.iJob == 1 && pAccount->info.iGender == 1)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_DEMONHUNTER_FEMALE);
		else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 0)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_MONK_MALE);
		else if(pAccount->info.iJob == 2 && pAccount->info.iGender == 1)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_MONK_FEMALE);
		else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 0)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_WITCHDOCTOR_MALE);
		else if(pAccount->info.iJob == 3 && pAccount->info.iGender == 1)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_WITCHDOCTOR_FEMALE);
		else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 0)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_WIZARD_MALE);
		else if(pAccount->info.iJob == 4 && pAccount->info.iGender == 1)
			pLoadScene->AddUnloadVec(UNLOAD_TYPE_WIZARD_FEMALE);

		CSceneMgr::GetInstance()->SetNextScene(pLoadScene, false);
	}

	if(m_ButtonVec[2]->IsLUp())
		Destroy();

	// Click Button
	for(int i = 0; i < 4; ++i)
	{
		if(i != m_iPage && m_pSettingButton[i]->IsLDown())
		{
			m_iPage = i;
			Renew();
			break;
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		if(i != m_iBlurSelect && m_pBlurButton[i]->IsLDown())
		{
			m_iBlurSelect = i;

			if(m_iBlurSelect == 0)
				CSettingMgr::GetInstance()->SetBlurMode(0);
			else if(m_iBlurSelect == 1)
				CSettingMgr::GetInstance()->SetBlurMode(RENDER_MODE_RADIAL_BLUR);
			else if(m_iBlurSelect == 2)
				CSettingMgr::GetInstance()->SetBlurMode(RENDER_MODE_GAUSSIAN_BLUR);
			else if(m_iBlurSelect == 3)
				CSettingMgr::GetInstance()->SetBlurMode(RENDER_MODE_MOTION_BLUR);

			break;
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		if(i != m_iShadowSelect && m_pShadowButton[i]->IsLDown())
		{
			m_iShadowSelect = i;

			if(m_iShadowSelect == 0)
				CSettingMgr::GetInstance()->SetShadowMode(0);
			else if(m_iShadowSelect == 1)
				CSettingMgr::GetInstance()->SetShadowMode(RENDER_MODE_NORMAL_SHADOW);
			else if(m_iShadowSelect == 2)
				CSettingMgr::GetInstance()->SetShadowMode(RENDER_MODE_CASCADE_SHADOW);

			break;
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		if(i != m_iFogSelect && m_pFogButton[i]->IsLDown())
		{
			m_iFogSelect = i;

			if(m_iFogSelect == 0)
				CSettingMgr::GetInstance()->SetFogMode(0);
			else if(m_iFogSelect == 1)
				CSettingMgr::GetInstance()->SetFogMode(RENDER_MODE_EXPONENT_FOG);
			else if(m_iFogSelect == 2)
				CSettingMgr::GetInstance()->SetFogMode(RENDER_MODE_EXPONENT_SQUARE_FOG);
			else if(m_iFogSelect == 3)
				CSettingMgr::GetInstance()->SetFogMode(RENDER_MODE_HEIGHT_FOG);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iHDRSelect && m_pHDRButton[i]->IsLDown())
		{
			m_iHDRSelect = i;

			if(m_iHDRSelect == 0)
				CSettingMgr::GetInstance()->SetHDRMode(0);
			else if(m_iHDRSelect == 1)
				CSettingMgr::GetInstance()->SetHDRMode(RENDER_MODE_HDR);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iSSAOSelect && m_pSSAOButton[i]->IsLDown())
		{
			m_iSSAOSelect = i;

			if(m_iSSAOSelect == 0)
				CSettingMgr::GetInstance()->SetSSAOMode(0);
			else if(m_iSSAOSelect == 1)
				CSettingMgr::GetInstance()->SetSSAOMode(RENDER_MODE_SSAO);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iDistortionSelect && m_pDistortionButton[i]->IsLDown())
		{
			m_iDistortionSelect = i;

			if(m_iDistortionSelect == 0)
				CSettingMgr::GetInstance()->SetDistortionMode(0);
			else if(m_iDistortionSelect == 1)
				CSettingMgr::GetInstance()->SetDistortionMode(RENDER_MODE_DISTORTION);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iDebugBufferSelect && m_pDebugBufferButton[i]->IsLDown())
		{
			m_iDebugBufferSelect = i;

			if(m_iDebugBufferSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_DEBUG_TARGET);
			else if(m_iDebugBufferSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_DEBUG_TARGET);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iNavigationMeshSelect && m_pNavigationMeshButton[i]->IsLDown())
		{
			m_iNavigationMeshSelect = i;

			if(m_iNavigationMeshSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_NAVIGATION_MESH);
			else if(m_iNavigationMeshSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_NAVIGATION_MESH);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iCheckSphereSelect && m_pCheckSphereButton[i]->IsLDown())
		{
			m_iCheckSphereSelect = i;

			if(m_iCheckSphereSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_CHECK_SPHERE);
			else if(m_iCheckSphereSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_CHECK_SPHERE);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iCollisionSphereSelect && m_pCollisionSphereButton[i]->IsLDown())
		{
			m_iCollisionSphereSelect = i;

			if(m_iCollisionSphereSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_COLLISION_SPHERE);
			else if(m_iCollisionSphereSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_COLLISION_SPHERE);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iCollisionBoxSelect && m_pCollisionBoxButton[i]->IsLDown())
		{
			m_iCollisionBoxSelect = i;

			if(m_iCollisionBoxSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_COLLISION_BOX);
			else if(m_iCollisionBoxSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_COLLISION_BOX);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iFPSSelect && m_pFPSButton[i]->IsLDown())
		{
			m_iFPSSelect = i;

			if(m_iFPSSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_FPS);
			else if(m_iFPSSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_FPS);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iPointLightSelect && m_pPointLightButton[i]->IsLDown())
		{
			m_iPointLightSelect = i;

			if(m_iPointLightSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_POINT_LIGHT);
			else if(m_iPointLightSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_POINT_LIGHT);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iNPCBoxSelect && m_pNPCBoxButton[i]->IsLDown())
		{
			m_iNPCBoxSelect = i;

			if(m_iNPCBoxSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_NPC_BOX);
			else if(m_iNPCBoxSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_NPC_BOX);

			break;
		}
	}
	for(int i = 0; i < 2; ++i)
	{
		if(i != m_iProbBoxSelect && m_pProbBoxButton[i]->IsLDown())
		{
			m_iProbBoxSelect = i;

			if(m_iProbBoxSelect == 0)
				CSettingMgr::GetInstance()->RemoveGameMode(GAME_MODE_PROB_BOX);
			else if(m_iProbBoxSelect == 1)
				CSettingMgr::GetInstance()->AddGameMode(GAME_MODE_PROB_BOX);

			break;
		}
	}

	// Init Button
	for(int i = 0; i < 4; ++i)
	{
		if(m_pSettingButton[i]->IsOver())
			m_pSettingButton[i]->SetState(UI_OVER);
		else
			m_pSettingButton[i]->SetState(0);
	}
	for(int i = 0; i < 4; ++i)
	{
		if(m_pBlurButton[i]->IsOver())
			m_pBlurButton[i]->SetState(UI_OVER);
		else
			m_pBlurButton[i]->SetState(0);
	}
	for(int i = 0; i < 3; ++i)
	{
		if(m_pShadowButton[i]->IsOver())
			m_pShadowButton[i]->SetState(UI_OVER);
		else
			m_pShadowButton[i]->SetState(0);
	}
	for(int i = 0; i < 4; ++i)
	{
		if(m_pFogButton[i]->IsOver())
			m_pFogButton[i]->SetState(UI_OVER);
		else
			m_pFogButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pHDRButton[i]->IsOver())
			m_pHDRButton[i]->SetState(UI_OVER);
		else
			m_pHDRButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pSSAOButton[i]->IsOver())
			m_pSSAOButton[i]->SetState(UI_OVER);
		else
			m_pSSAOButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pDistortionButton[i]->IsOver())
			m_pDistortionButton[i]->SetState(UI_OVER);
		else
			m_pDistortionButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pDebugBufferButton[i]->IsOver())
			m_pDebugBufferButton[i]->SetState(UI_OVER);
		else
			m_pDebugBufferButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pNavigationMeshButton[i]->IsOver())
			m_pNavigationMeshButton[i]->SetState(UI_OVER);
		else
			m_pNavigationMeshButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCheckSphereButton[i]->IsOver())
			m_pCheckSphereButton[i]->SetState(UI_OVER);
		else
			m_pCheckSphereButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCollisionSphereButton[i]->IsOver())
			m_pCollisionSphereButton[i]->SetState(UI_OVER);
		else
			m_pCollisionSphereButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCollisionBoxButton[i]->IsOver())
			m_pCollisionBoxButton[i]->SetState(UI_OVER);
		else
			m_pCollisionBoxButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pFPSButton[i]->IsOver())
			m_pFPSButton[i]->SetState(UI_OVER);
		else
			m_pFPSButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pPointLightButton[i]->IsOver())
			m_pPointLightButton[i]->SetState(UI_OVER);
		else
			m_pPointLightButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pNPCBoxButton[i]->IsOver())
			m_pNPCBoxButton[i]->SetState(UI_OVER);
		else
			m_pNPCBoxButton[i]->SetState(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		if(m_pProbBoxButton[i]->IsOver())
			m_pProbBoxButton[i]->SetState(UI_OVER);
		else
			m_pProbBoxButton[i]->SetState(0);
	}

	// Set Button
	m_pSettingButton[m_iPage]->SetState(UI_L_DOWN);
	m_pBlurButton[m_iBlurSelect]->SetState(UI_L_DOWN);
	m_pShadowButton[m_iShadowSelect]->SetState(UI_L_DOWN);
	m_pFogButton[m_iFogSelect]->SetState(UI_L_DOWN);
	m_pHDRButton[m_iHDRSelect]->SetState(UI_L_DOWN);
	m_pSSAOButton[m_iSSAOSelect]->SetState(UI_L_DOWN);
	m_pDistortionButton[m_iDistortionSelect]->SetState(UI_L_DOWN);
	m_pDebugBufferButton[m_iDebugBufferSelect]->SetState(UI_L_DOWN);
	m_pNavigationMeshButton[m_iNavigationMeshSelect]->SetState(UI_L_DOWN);
	m_pCheckSphereButton[m_iCheckSphereSelect]->SetState(UI_L_DOWN);
	m_pCollisionSphereButton[m_iCollisionSphereSelect]->SetState(UI_L_DOWN);
	m_pCollisionBoxButton[m_iCollisionBoxSelect]->SetState(UI_L_DOWN);
	m_pFPSButton[m_iFPSSelect]->SetState(UI_L_DOWN);
	m_pPointLightButton[m_iPointLightSelect]->SetState(UI_L_DOWN);
	m_pNPCBoxButton[m_iNPCBoxSelect]->SetState(UI_L_DOWN);
	m_pProbBoxButton[m_iProbBoxSelect]->SetState(UI_L_DOWN);

	// LevelUpButton
	if(m_pCheatKeyButton[0]->IsLUp())
	{
		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
		if(pFindObject != NULL)
		{
			CPlayer* pPlayer = (CPlayer*)pFindObject;
			pPlayer->Kill(INT_MAX / 2);
		}
	}

	// QuestItemButton
	if(m_pCheatKeyButton[1]->IsLUp())
	{
		int iRand = rand() % 4;
		Item* pItem;
		if(iRand == 0)
			pItem = new Item(_T("고용계약서"), _T("Item_Quest_3"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_3, -1, -1, 1, 1, 2, 0, 10000, 1, 0, 0);
		else if(iRand == 1)
			pItem = new Item(_T("좀비눈알(청)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);
		else if(iRand == 2)
			pItem = new Item(_T("좀비눈알(적)"), _T("Item_Quest_8"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_8, -1, -1, 1, 1, 2, 0, 2000, 1, 0, 0);
		else if(iRand == 3)
			pItem = new Item(_T("열쇠"), _T("Item_Quest_6"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_6, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);

		if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
		{
			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
		}
		else
			CItemMgr::GetInstance()->CommitInven();
	}

	// NormalItemButton & MagicItemButton & UniqueItemButton & LegendItemButton & SetItemButton
	if(m_pCheatKeyButton[2]->IsLUp() || m_pCheatKeyButton[3]->IsLUp() || m_pCheatKeyButton[4]->IsLUp() || m_pCheatKeyButton[5]->IsLUp() || m_pCheatKeyButton[6]->IsLUp())
	{
		DWORD dwItemClass;
		if(m_pCheatKeyButton[2]->IsLUp())
			dwItemClass = ITEM_CLASS_NORMAL;
		else if(m_pCheatKeyButton[3]->IsLUp())
			dwItemClass = ITEM_CLASS_MAGIC;
		else if(m_pCheatKeyButton[4]->IsLUp())
			dwItemClass = ITEM_CLASS_UNIQUE;
		else if(m_pCheatKeyButton[5]->IsLUp())
			dwItemClass = ITEM_CLASS_LEGEND;
		else if(m_pCheatKeyButton[6]->IsLUp())
			dwItemClass = ITEM_CLASS_SET;

		DWORD dwItemType;
		int iRand = rand() % 13;
		if(iRand == 0)
			dwItemType = ITEM_TYPE_MAIN_WEAPON;
		else if(iRand == 1)
			dwItemType = ITEM_TYPE_HELMS;
		else if(iRand == 2)
			dwItemType = ITEM_TYPE_SHOULDERS;
		else if(iRand == 3)
			dwItemType = ITEM_TYPE_CHESTARMOR;
		else if(iRand == 4)
			dwItemType = ITEM_TYPE_BRACERS;
		else if(iRand == 5)
			dwItemType = ITEM_TYPE_GLOVES;
		else if(iRand == 6)
			dwItemType = ITEM_TYPE_BELT;
		else if(iRand == 7)
			dwItemType = ITEM_TYPE_PANTS;
		else if(iRand == 8)
			dwItemType = ITEM_TYPE_BOOTS;
		else if(iRand == 9)
			dwItemType = ITEM_TYPE_AMULET;
		else if(iRand == 10)
			dwItemType = ITEM_TYPE_RING;
		else if(iRand == 11)
			dwItemType = ITEM_TYPE_SUB_WEAPON;
		else if(iRand == 12)
			dwItemType = ITEM_TYPE_MAIN_WEAPON | ITEM_TYPE_SUB_WEAPON;

		CObject* pFindObject = NULL;
		m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);
		if(pFindObject != NULL)
		{
			CPlayer* pPlayer = (CPlayer*)pFindObject;
			Item* pItem = CItemMgr::GetInstance()->CreateItem(dwItemClass, dwItemType, 0, pPlayer->GetStat()->iLevel);
			if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
			{
				delete pItem;
				CItemMgr::GetInstance()->RollbackInven();
			}
			else
				CItemMgr::GetInstance()->CommitInven();
		}
	}

	// GemItemButton
	if(m_pCheatKeyButton[7]->IsLUp())
	{
		Item* pItem = CItemMgr::GetInstance()->CreateItem(0, ITEM_TYPE_GEM, 0, 0);
		if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
		{
			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
		}
		else
			CItemMgr::GetInstance()->CommitInven();
	}

	// MaterialItemButton
	if(m_pCheatKeyButton[8]->IsLUp())
	{
		Item* pItem = CItemMgr::GetInstance()->CreateItem(0, ITEM_TYPE_MATERIAL, 0, 0);
		if(CItemMgr::GetInstance()->AddItemInInven(pItem) == false)
		{
			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
		}
		else
			CItemMgr::GetInstance()->CommitInven();
	}

	// GoldMinusButton
	if(m_pCheatKeyButton[9]->IsLUp())
		CItemMgr::GetInstance()->SetGold(10000000);

	// GoldPlusButton
	if(m_pCheatKeyButton[10]->IsLUp())
		CItemMgr::GetInstance()->SetGold(0);

	return 0;
}

void CSettingWindow::Render()
{
	CWindowUI::Render();

	if(m_iPage == 0)
	{
		RECT rcText;
	
		SetRect(&rcText, 480, 140, 780, 152);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 블러"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 210, 780, 222);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 그림자"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 280, 780, 292);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 안개"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 350, 780, 362);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- HDR"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 420, 780, 432);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- SSAO"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 490, 780, 502);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 왜곡"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}
	else if(m_iPage == 1)
	{
	}
	else if(m_iPage == 2)
	{
		RECT rcText;

		SetRect(&rcText, 480, 140, 780, 152);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 디버그 버퍼"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 210, 780, 222);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 네비게이션 메쉬"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 280, 780, 292);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 검사구"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 350, 780, 362);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 충돌구"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 420, 780, 432);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 충돌박스"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 480, 490, 780, 502);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 프레임"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 736, 140, 1036, 152);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 점 조명"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 736, 210, 1036, 222);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- NPC 박스"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		SetRect(&rcText, 736, 280, 1036, 292);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- Prob 박스"), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}
	else if(m_iPage == 3)
	{
		RECT rcText;

		SetRect(&rcText, 480, 140, 1080, 152);
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, _T("- 무분별한 치트키 남용은 게임의 재미를 해칠 수 있습니다."), -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}
}

void CSettingWindow::Release()
{
	// SettingButton
	for(int i = 0; i < 4; ++i)
	{
		if(m_pSettingButton[i] != NULL)
		{
			m_pSettingButton[i]->Destroy();
			m_pSettingButton[i] = NULL;
		}
	}

	// BlurButton
	for(int i = 0; i < 4; ++i)
	{
		if(m_pBlurButton[i] != NULL)
		{
			m_pBlurButton[i]->Destroy();
			m_pBlurButton[i] = NULL;
		}
	}

	// ShadowButton
	for(int i = 0; i < 3; ++i)
	{
		if(m_pShadowButton[i] != NULL)
		{
			m_pShadowButton[i]->Destroy();
			m_pShadowButton[i] = NULL;
		}
	}

	// FogButton
	for(int i = 0; i < 4; ++i)
	{
		if(m_pFogButton[i] != NULL)
		{
			m_pFogButton[i]->Destroy();
			m_pFogButton[i] = NULL;
		}
	}

	// HDRButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pHDRButton[i] != NULL)
		{
			m_pHDRButton[i]->Destroy();
			m_pHDRButton[i] = NULL;
		}
	}

	// SSAOButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pSSAOButton[i] != NULL)
		{
			m_pSSAOButton[i]->Destroy();
			m_pSSAOButton[i] = NULL;
		}
	}

	// DistortionButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pDistortionButton[i] != NULL)
		{
			m_pDistortionButton[i]->Destroy();
			m_pDistortionButton[i] = NULL;
		}
	}

	// DebugBufferButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pDebugBufferButton[i] != NULL)
		{
			m_pDebugBufferButton[i]->Destroy();
			m_pDebugBufferButton[i] = NULL;
		}
	}

	// NavigationMeshButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pNavigationMeshButton[i] != NULL)
		{
			m_pNavigationMeshButton[i]->Destroy();
			m_pNavigationMeshButton[i] = NULL;
		}
	}

	// CheckSphereButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCheckSphereButton[i] != NULL)
		{
			m_pCheckSphereButton[i]->Destroy();
			m_pCheckSphereButton[i] = NULL;
		}
	}

	// CollisionSphereButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCollisionSphereButton[i] != NULL)
		{
			m_pCollisionSphereButton[i]->Destroy();
			m_pCollisionSphereButton[i] = NULL;
		}
	}

	// CollisionBoxButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pCollisionBoxButton[i] != NULL)
		{
			m_pCollisionBoxButton[i]->Destroy();
			m_pCollisionBoxButton[i] = NULL;
		}
	}

	// FPSButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pFPSButton[i] != NULL)
		{
			m_pFPSButton[i]->Destroy();
			m_pFPSButton[i] = NULL;
		}
	}

	// PointLightButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pPointLightButton[i] != NULL)
		{
			m_pPointLightButton[i]->Destroy();
			m_pPointLightButton[i] = NULL;
		}
	}

	// NPCBoxButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pNPCBoxButton[i] != NULL)
		{
			m_pNPCBoxButton[i]->Destroy();
			m_pNPCBoxButton[i] = NULL;
		}
	}

	// ProbBoxButton
	for(int i = 0; i < 2; ++i)
	{
		if(m_pProbBoxButton[i] != NULL)
		{
			m_pProbBoxButton[i]->Destroy();
			m_pProbBoxButton[i] = NULL;
		}
	}

	// CheatKeyButton
	for(int i = 0; i < 11; ++i)
	{
		if(m_pCheatKeyButton[i] != NULL)
		{
			m_pCheatKeyButton[i]->Destroy();
			m_pCheatKeyButton[i] = NULL;
		}
	}
}

void CSettingWindow::Renew()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// BlurButton
	for(int i = 0; i < 4; ++i)
	{
		pTransformCom = (CTransformCom*)m_pBlurButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// ShadowButton
	for(int i = 0; i < 3; ++i)
	{
		pTransformCom = (CTransformCom*)m_pShadowButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// FogButton
	for(int i = 0; i < 4; ++i)
	{
		pTransformCom = (CTransformCom*)m_pFogButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// HDRButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pHDRButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// SSAOButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pSSAOButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// DistortionButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pDistortionButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// DebugBufferButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pDebugBufferButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// NavigationMeshButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pNavigationMeshButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// CheckSphereButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pCheckSphereButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// CollisionSphereButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pCollisionSphereButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// CollisionBoxButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pCollisionBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// FPSButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pFPSButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// PointLightButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pPointLightButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// NPCBoxButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pNPCBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// ProbBoxButton
	for(int i = 0; i < 2; ++i)
	{
		pTransformCom = (CTransformCom*)m_pProbBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	// CheatKeyButton
	for(int i = 0; i < 11; ++i)
	{
		pTransformCom = (CTransformCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if(m_iPage == 0)
	{
		// BlurButton
		for(int i = 0; i < 4; ++i)
		{
			pTransformCom = (CTransformCom*)m_pBlurButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// ShadowButton
		for(int i = 0; i < 3; ++i)
		{
			pTransformCom = (CTransformCom*)m_pShadowButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// FogButton
		for(int i = 0; i < 4; ++i)
		{
			pTransformCom = (CTransformCom*)m_pFogButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// HDRButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pHDRButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// SSAOButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pSSAOButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// DistortionButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pDistortionButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
	}
	else if(m_iPage == 1)
	{
	}
	else if(m_iPage == 2)
	{
		// DebugBufferButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pDebugBufferButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// NavigationMeshButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pNavigationMeshButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// CheckSphereButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pCheckSphereButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// CollisionSphereButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pCollisionSphereButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// CollisionBoxButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pCollisionBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// FPSButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pFPSButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// PointLightButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pPointLightButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// NPCBoxButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pNPCBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
		// ProbBoxButton
		for(int i = 0; i < 2; ++i)
		{
			pTransformCom = (CTransformCom*)m_pProbBoxButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
	}
	else if(m_iPage == 3)
	{
		// CheatKeyButton
		for(int i = 0; i < 11; ++i)
		{
			pTransformCom = (CTransformCom*)m_pCheatKeyButton[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vSize = D3DXVECTOR3(0.129f, 0.082f, 0.0f);
		}
	}
}