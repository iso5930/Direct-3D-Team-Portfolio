#include "Stdafx.h"
#include "RenderMgr.h"

IMPLEMENT_SINGLETON(CRenderMgr)

CRenderMgr::CRenderMgr()
{
	// RenderMode
	m_dwRenderMode = 0;

	// Screen
	m_pScreen = CBufferMgr::GetInstance()->GetBuffer(_T("Screen"));

	// ShaderArr
	ZeroMemory(m_pShaderArr, sizeof(m_pShaderArr));
	m_pShaderArr[SHADER_TYPE_SHADOW] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Shadow"));
	m_pShaderArr[SHADER_TYPE_VELOCITY] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Velocity"));
	m_pShaderArr[SHADER_TYPE_BLUR] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Blur"));
	m_pShaderArr[SHADER_TYPE_BACK] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Back"));
	m_pShaderArr[SHADER_TYPE_SKYBOX] = CShaderMgr::GetInstance()->GetShader(_T("Shader_SkyBox"));
	m_pShaderArr[SHADER_TYPE_MESH] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Mesh"));
	m_pShaderArr[SHADER_TYPE_LIGHT] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Light"));
	m_pShaderArr[SHADER_TYPE_FOG] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Fog"));
	m_pShaderArr[SHADER_TYPE_BLEND] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Blend"));
	m_pShaderArr[SHADER_TYPE_UI] = CShaderMgr::GetInstance()->GetShader(_T("Shader_UI"));
	m_pShaderArr[SHADER_TYPE_HDR] = CShaderMgr::GetInstance()->GetShader(_T("Shader_HDR"));
	m_pShaderArr[SHADER_TYPE_MOUSE] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Mouse"));
	m_pShaderArr[SHADER_TYPE_SSAO] = CShaderMgr::GetInstance()->GetShader(_T("Shader_SSAO"));
	m_pShaderArr[SHADER_TYPE_EFFECT] = CShaderMgr::GetInstance()->GetShader(_T("Shader_Effect"));

	// TargetArr
	ZeroMemory(m_pTargetArr, sizeof(m_pTargetArr));
	m_pTargetArr[TARGET_TYPE_BLUR]			= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_SHADOW_MAP]	= new CRenderTarget(2048, 2048, D3DFMT_R32F, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTargetArr[TARGET_TYPE_VELOCITY]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_DEPTH]			= new CRenderTarget(WINCX, WINCY, D3DFMT_R16F, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTargetArr[TARGET_TYPE_ALBEDO]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_NORMAL]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_SPECULAR]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_SHADE]			= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_FOG]			= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_SSAO]			= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_SSAO_GRAY]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_SSAO_BLUR]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR]				= new CRenderTarget(WINCX, WINCY, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV1] = new CRenderTarget(1, 1, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV2] = new CRenderTarget(3, 3, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV3] = new CRenderTarget(9, 9, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV4] = new CRenderTarget(27, 27, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV5] = new CRenderTarget(81, 81, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV6] = new CRenderTarget(243, 243, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));	
	m_pTargetArr[TARGET_TYPE_HDR_BRIGHT_PASS]	= new CRenderTarget(WINCX / 2, WINCY / 2, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]	= new CRenderTarget(WINCX / 8, WINCY / 8, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_HORIZONTAL_BLUR]	= new CRenderTarget(WINCX / 8, WINCY / 8, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]		= new CRenderTarget(WINCX / 8, WINCY / 8, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	m_pTargetArr[TARGET_TYPE_SPECULAR_ACC]			= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_EFFECT]				= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_EFFECT_DISTORTION]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_EFFECT_REFRACTION]		= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_SHADOW]				= new CRenderTarget(WINCX, WINCY, D3DFMT_A8R8G8B8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pTargetArr[TARGET_TYPE_SHADOW_NEAR]			= new CRenderTarget(2048, 2048, D3DFMT_R32F, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTargetArr[TARGET_TYPE_SHADOW_MIDDLE]			= new CRenderTarget(1024, 1024, D3DFMT_R32F, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTargetArr[TARGET_TYPE_SHADOW_FAR]			= new CRenderTarget(512, 512, D3DFMT_R32F, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		
	// DebugBuffer
	m_pTargetArr[TARGET_TYPE_BLUR]->CreateDebugBuffer(-1.0f, -1.0f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADOW_MAP]->CreateDebugBuffer(-1.0f, -0.75f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_VELOCITY]->CreateDebugBuffer(-1.0f, -0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_DEPTH]->CreateDebugBuffer(-1.0f, -0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_ALBEDO]->CreateDebugBuffer(-1.f, 0.f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_NORMAL]->CreateDebugBuffer(-1.f, 0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SPECULAR]->CreateDebugBuffer(-1.f, 0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADE]->CreateDebugBuffer(-1.f, 0.75f, 0.25f, 0.25f);
	
	m_pTargetArr[TARGET_TYPE_FOG]->CreateDebugBuffer(-0.75f, -1.0f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SSAO]->CreateDebugBuffer(-0.75f, -0.75f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SSAO_GRAY]->CreateDebugBuffer(-0.75f, -0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SSAO_BLUR]->CreateDebugBuffer(-0.75f, -0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR]->CreateDebugBuffer(-0.75f, 0.f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV1]->CreateDebugBuffer(-0.75f, 0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV2]->CreateDebugBuffer(-0.75f, 0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV3]->CreateDebugBuffer(-0.75f, 0.75f, 0.25f, 0.25f);

	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV4]->CreateDebugBuffer(-0.5f, -1.0f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV5]->CreateDebugBuffer(-0.5f, -0.75f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV6]->CreateDebugBuffer(-0.5f, -0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_BRIGHT_PASS]->CreateDebugBuffer(-0.5f, -0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->CreateDebugBuffer(-0.5f, 0.f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_HORIZONTAL_BLUR]->CreateDebugBuffer(-0.5f, 0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]->CreateDebugBuffer(-0.5f, 0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SPECULAR_ACC]->CreateDebugBuffer(-0.5f, 0.75f, 0.25f, 0.25f);

	m_pTargetArr[TARGET_TYPE_EFFECT]->CreateDebugBuffer(0.75f, -1.f, 0.25f, 0.25f);					
	m_pTargetArr[TARGET_TYPE_EFFECT_DISTORTION]->CreateDebugBuffer(0.75f, -0.75f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_EFFECT_REFRACTION]->CreateDebugBuffer(0.75f, -0.5f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADOW]->CreateDebugBuffer(0.75f, -0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADOW_NEAR]->CreateDebugBuffer(0.75f, 0.f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADOW_MIDDLE]->CreateDebugBuffer(0.75f, 0.25f, 0.25f, 0.25f);
	m_pTargetArr[TARGET_TYPE_SHADOW_FAR]->CreateDebugBuffer(0.75f, 0.5f, 0.25f, 0.25f);

	// Blur
	m_fBlurWidth = 0.0f;
	m_fKernelSize = 1.0f;

	// FPS
	m_fTime = 0.0f;
	ZeroMemory(m_tszFPS, sizeof(m_tszFPS));
	m_dwFPS = 0;

	// Temp
	m_pTransformCom = NULL;
	m_pBufferCom = NULL;
	m_pRenderCom = NULL;
	m_pMaterialCom = NULL;
	m_pStaticMesh = NULL;
	m_pDynamicMesh = NULL;

	//Fog
	m_fFogHeight = -500.f;
	
	//HDR + Bloom
	m_fBrightThreshold = 0.5f;
	m_fGaussMultiplier = 1.9f;
	m_fGaussMean = 0.0f; //이거 제외하고
	m_fGaussStdDev = 3.5f;
	m_fExposure = 0.85f;

	float fU = 1.f / (float)WINCX;
	float fV = 1.f / (float)WINCY;

	m_vLuminanceOffset_LV6[0] = D3DXVECTOR4(-0.5f * fU, 0.5f * fV, 0.f, 0.f);
	m_vLuminanceOffset_LV6[1] = D3DXVECTOR4(0.5f * fU, 0.5f * fV, 0.f, 0.f);
	m_vLuminanceOffset_LV6[2] = D3DXVECTOR4(-0.5f * fU, -0.5f * fV, 0.f, 0.f);
	m_vLuminanceOffset_LV6[3] = D3DXVECTOR4(0.5f * fU, -0.5f * fV, 0.f, 0.f);

	int iIndex = (int)TARGET_TYPE_HDR_LUMINANCE_LV6;

	int iCount = 0;
	D3DSURFACE_DESC srcTexDesc;

	for(int i = 1; i < 6; ++i)
	{
		m_pTargetArr[(iIndex - i) + 1]->m_pTexture->GetLevelDesc(0, &srcTexDesc);
		int idx = 0;

		for(int x = -1; x < 2; x++)
		{
			for(int y = -1; y < 2; y++)
			{
				m_vLuminanceOffset[iCount][idx++] = D3DXVECTOR4((float)x / (float)srcTexDesc.Width, (float)y / (float)srcTexDesc.Height, 0.f, 0.f);
			}
		}

		++iCount;
	}

	m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->m_pTexture->GetLevelDesc(0, &srcTexDesc);

	iIndex = 0;

	for(int i = -2; i < 2; i++)
	{
		for(int j = -2; j < 2; j++)
		{
			m_vDownSamplerOffset[iIndex++] = D3DXVECTOR4((float)i + 0.5f * (1.f / (float)srcTexDesc.Width), (float)j + 0.5f * (1.f / (float)srcTexDesc.Height), 0.f, 0.f);
		}
	}

	for(int i = 0; i < 9; i++)
	{
		m_fBloomOffset_X[i] = ((float)i - 4.f) * (1.f / (float)srcTexDesc.Width);

		float fX = (float)i - 4.f / 4.f;

		m_fBloomWeight_X[i] = m_fGaussMultiplier * ComputeGaussianValue(fX, m_fGaussMean, m_fGaussStdDev);
	}

	for(int i = 0; i < 9; i++)
	{
		m_fBloomOffset_Y[i] = ((float)i - 4.f) * (1.f / (float)srcTexDesc.Height);
		
		float fX = (float)i - 4.f / 4.f;

		m_fBloomWeight_Y[i] = m_fGaussMultiplier * ComputeGaussianValue(fX, m_fGaussMean, m_fGaussStdDev);
	}
	
	m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]->m_pTexture->GetLevelDesc(0, &srcTexDesc);

	m_fBloom_w = 1.f / (float)srcTexDesc.Width;
	m_fBloom_h = 1.f / (float)srcTexDesc.Height;
}

CRenderMgr::~CRenderMgr()
{
	Release();
}

void CRenderMgr::Initialize()
{
	CDeviceMgr::GetInstance()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	CDeviceMgr::GetInstance()->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	CDeviceMgr::GetInstance()->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	CDeviceMgr::GetInstance()->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

int CRenderMgr::Update()
{
	// RenderMode
	if(m_dwRenderMode & RENDER_MODE_RADIAL_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_fBlurWidth += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_fBlurWidth > 1.0f)
			m_fBlurWidth = 1.0f;
	}
	else if(m_dwRenderMode & RENDER_MODE_GAUSSIAN_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_fKernelSize += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_fKernelSize > 5.0f)
			m_fKernelSize = 5.0f;
	}

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_FPS)
	{
		// FPS
		++m_dwFPS;
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
		if(m_fTime >= 1.0f)
		{
			StringCbPrintf(m_tszFPS, sizeof(m_tszFPS), _T("FPS : %d"), m_dwFPS);
			m_fTime = 0.0f;
			m_dwFPS = 0;
		}
	}

	return 0;
}

void CRenderMgr::Render()
{
	// Sort
	sort(m_ObjectVec[RENDER_TYPE_UI].begin(), m_ObjectVec[RENDER_TYPE_UI].end(), RenderCompare);

	// Clear
	for(int i = 0; i < TARGET_TYPE_END; ++i)
		m_pTargetArr[i]->Clear();

	CreateShadowMap();
	CreateVelocityMap();
 	BlurBegin();
	FogBegin();
	HDR_Begin();
	SSAO_Begin();
	Effect_Begin();
	Shadow_Begin();
 	RenderBack();
	RenderSkyBox();
 	RenderDeffered();
 	RenderLight();
	RenderBlend();
	Shadow_End();
	Effect_End();
	SSAO_End();
	HDR_End();
	FogEnd();
 	BlurEnd();
 	RenderUI();
	RenderMouse();

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_NPC_BOX)
		RenderNPCBox();

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_PROB_BOX)
		RenderProbBox();

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_FPS)
		RenderFPS();

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_DEBUG_TARGET)
	{
		D3DXMATRIX mIdentity;
		D3DXMatrixIdentity(&mIdentity);

		CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &mIdentity);
		CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &mIdentity);
		CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &mIdentity);

		for(int i = 0; i < TARGET_TYPE_END; ++i)
			m_pTargetArr[i]->RenderDebugBuffer();
	}

	for(int i = 0; i < RENDER_TYPE_END; ++i)
		m_ObjectVec[i].clear();
}

void CRenderMgr::Release()
{
	delete m_pScreen;

	for(int i = 0; i < TARGET_TYPE_END; ++i)
		delete m_pTargetArr[i];

	for(int i = 0; i < RENDER_TYPE_END; ++i)
		m_ObjectVec[i].clear();
}

void CRenderMgr::CreateShadowMap()
{
	if(m_dwRenderMode & RENDER_MODE_NORMAL_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_SHADOW_MAP]->Begin(0);

		////////////////////////////////////////////////////////////////////////// Begin - Shadow
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mLightViewProj", CLightMgr::GetInstance()->GetViewProj());

		////////////////////////////////////////////////////////////////////////// BeginPass0 - StaticMesh
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(0);

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MAP].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_ITEM].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_STATIC_PROB].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
		////////////////////////////////////////////////////////////////////////// EndPass0 - StaticMesh

		////////////////////////////////////////////////////////////////////////// BeginPass1 - DynamicMesh
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(1);

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_FOLLOWER].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_PLAYER].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MONSTER].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_NPC].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
		////////////////////////////////////////////////////////////////////////// EndPass1 - DynamicMesh

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->End();
		////////////////////////////////////////////////////////////////////////// End - Shadow

		m_pTargetArr[TARGET_TYPE_SHADOW_MAP]->End(0);
	}
	else if(m_dwRenderMode & RENDER_MODE_CASCADE_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->Begin(NULL, 0);

		int iIndex = (int)TARGET_TYPE_SHADOW_NEAR;

		for(int iCascaded = 0; iCascaded < CASCADED_END; ++iCascaded)
		{
			m_pTargetArr[iIndex]->Begin(0);
			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mLightViewProj", CLightMgr::GetInstance()->GetCascadedViewProj((CASCADED_TYPE)iCascaded));

			////////////////////////////////////////////////////////////////////////// BeginPass0 - StaticMesh
			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(0);

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MAP].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
					for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
					{
						m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
						m_pStaticMesh->m_pMesh->DrawSubset(k);
					}
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_ITEM].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
					for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
					{
						m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
						m_pStaticMesh->m_pMesh->DrawSubset(k);
					}
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_STATIC_PROB].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
					for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
					{
						m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
						m_pStaticMesh->m_pMesh->DrawSubset(k);
					}
				}
			}

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
			////////////////////////////////////////////////////////////////////////// EndPass0 - StaticMesh

			////////////////////////////////////////////////////////////////////////// BeginPass1 - DynamicMesh
			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(1);

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_FOLLOWER].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
					RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_PLAYER].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
					RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MONSTER].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
					RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
					RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
				}
			}

			for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_NPC].size(); ++i)
			{
				m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_TRANSFORM);
				m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_BUFFER);

				m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
				for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
				{
					m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
					RenderShadowFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
				}
			}

			m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
			////////////////////////////////////////////////////////////////////////// EndPass1 - DynamicMesh

			m_pTargetArr[iIndex]->End(0);
			++iIndex;
		}

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->End();
	}
}

void CRenderMgr::CreateVelocityMap()
{
	if(m_dwRenderMode & RENDER_MODE_MOTION_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_VELOCITY]->Begin(0);

		////////////////////////////////////////////////////////////////////////// Begin - Velocity
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mCurViewProj", CCameraMgr::GetInstance()->GetViewProj());
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mPreViewProj", CCameraMgr::GetInstance()->GetPreViewProj());

		////////////////////////////////////////////////////////////////////////// BeginPass0 - StaticMesh
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->BeginPass(0);

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_ITEM].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mCurWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mPreWorld", &m_pTransformCom->m_mPreWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}

		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->EndPass();
		////////////////////////////////////////////////////////////////////////// EndPass0 - StaticMesh

		////////////////////////////////////////////////////////////////////////// BeginPass1 - DynamicMesh
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->BeginPass(1);

		for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_PLAYER].size(); ++i)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mCurWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetMatrix("g_mPreWorld", &m_pTransformCom->m_mPreWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderVelocityFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}

		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->EndPass();
		////////////////////////////////////////////////////////////////////////// EndPass1 - DynamicMesh

		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->End();
		////////////////////////////////////////////////////////////////////////// End - Velocity

		m_pTargetArr[TARGET_TYPE_VELOCITY]->End(0);
	}
}

void CRenderMgr::BlurBegin()
{
	if(m_dwRenderMode & RENDER_MODE_RADIAL_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_BLUR]->Begin(0);
	else if(m_dwRenderMode & RENDER_MODE_GAUSSIAN_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_BLUR]->Begin(0);
	else if(m_dwRenderMode & RENDER_MODE_MOTION_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_BLUR]->Begin(0);
}

void CRenderMgr::FogBegin()
{
	if(m_dwRenderMode & RENDER_MODE_EXPONENT_FOG & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_FOG]->Begin(0);
	else if(m_dwRenderMode & RENDER_MODE_EXPONENT_SQUARE_FOG & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_FOG]->Begin(0);
	else if(m_dwRenderMode & RENDER_MODE_HEIGHT_FOG & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_FOG]->Begin(0);
}

void CRenderMgr::HDR_Begin()
{
	if(m_dwRenderMode & RENDER_MODE_HDR & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_HDR]->Begin(0);
}

void CRenderMgr::SSAO_Begin()
{
	if(m_dwRenderMode & RENDER_MODE_SSAO & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_SSAO]->Begin(0);
}

void CRenderMgr::Effect_Begin()
{
	//if(m_ObjectVec[RENDER_TYPE_EFFECT].size() != 0)
	m_pTargetArr[TARGET_TYPE_EFFECT]->Begin(0);
}

void CRenderMgr::Shadow_Begin()
{
	if(m_dwRenderMode & RENDER_MODE_NORMAL_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_SHADOW]->Begin(0);
	else if(m_dwRenderMode & RENDER_MODE_CASCADE_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
		m_pTargetArr[TARGET_TYPE_SHADOW]->Begin(0);
}

void CRenderMgr::RenderBack()
{
	m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->BeginPass(0);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_BACK].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_BACK][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_BACK][i]->GetComponent(COM_TYPE_RENDER);
		m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_BACK][i]->GetComponent(COM_TYPE_MATERIAL);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_BACK][i]->GetComponent(COM_TYPE_BUFFER);

		m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
		m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->CommitChanges();

		m_pBufferCom->Render();
		m_ObjectVec[RENDER_TYPE_BACK][i]->Render();
	}

	m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->EndPass();
	m_pShaderArr[SHADER_TYPE_BACK]->m_pEffect->End();
}

void CRenderMgr::RenderSkyBox()
{
	m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->BeginPass(0);
	m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_SKYBOX].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_SKYBOX][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_SKYBOX][i]->GetComponent(COM_TYPE_BUFFER);
		m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_SKYBOX][i]->GetComponent(COM_TYPE_MATERIAL);

		m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->CommitChanges();

		m_pBufferCom->Render();
	}

	m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->EndPass();
	m_pShaderArr[SHADER_TYPE_SKYBOX]->m_pEffect->End();
}

void CRenderMgr::RenderDeffered()
{
	m_pTargetArr[TARGET_TYPE_ALBEDO]->Begin(0);
	m_pTargetArr[TARGET_TYPE_NORMAL]->Begin(1);
	m_pTargetArr[TARGET_TYPE_SPECULAR]->Begin(2);
	m_pTargetArr[TARGET_TYPE_DEPTH]->Begin(3);

	////////////////////////////////////////////////////////////////////////// Begin - Mesh
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetFloat("g_fFar", CCameraMgr::GetInstance()->GetFar());
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vCameraPos", CCameraMgr::GetInstance()->GetPos4D());

	////////////////////////////////////////////////////////////////////////// BeginPass0 - StaticMesh
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->BeginPass(0);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MAP].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_MAP][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
			for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
			{
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);

				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->CommitChanges();
				m_pStaticMesh->m_pMesh->DrawSubset(k);
			}
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_ITEM].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_ITEM][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
			for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
			{
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);

				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->CommitChanges();
				m_pStaticMesh->m_pMesh->DrawSubset(k);
			}
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_STATIC_PROB].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
			for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
			{
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);

				m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->CommitChanges();
				m_pStaticMesh->m_pMesh->DrawSubset(k);
			}
		}
	}

	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->EndPass();
	////////////////////////////////////////////////////////////////////////// EndPass0 - StaticMesh

	////////////////////////////////////////////////////////////////////////// BeginPass1 - DynamicMesh
	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->BeginPass(1);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_FOLLOWER].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_FOLLOWER][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_PLAYER].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_PLAYER][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MONSTER].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_MONSTER][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_NPC].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_NPC][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MODEL].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MODEL][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MODEL][i]->GetComponent(COM_TYPE_BUFFER);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_MODEL][i]->GetComponent(COM_TYPE_RENDER);

		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetVector("g_vRimColor", &m_pRenderCom->m_vRimColor);
		m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
		{
			m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
			RenderFrame(m_pShaderArr[SHADER_TYPE_MESH], (MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
		}
	}

	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->EndPass();
	////////////////////////////////////////////////////////////////////////// EndPass1 - DynamicMesh

	m_pShaderArr[SHADER_TYPE_MESH]->m_pEffect->End();
	////////////////////////////////////////////////////////////////////////// End - Mesh

	m_pTargetArr[TARGET_TYPE_ALBEDO]->End(0);
	m_pTargetArr[TARGET_TYPE_NORMAL]->End(1);
	m_pTargetArr[TARGET_TYPE_SPECULAR]->End(2);
	m_pTargetArr[TARGET_TYPE_DEPTH]->End(3);
}

void CRenderMgr::RenderLight()
{
	D3DXVECTOR4 vViewRightTop;
	memcpy_s(&vViewRightTop, sizeof(D3DXVECTOR4), CCameraMgr::GetInstance()->GetViewPoint4D(6), sizeof(D3DXVECTOR4));
	vViewRightTop.y = -vViewRightTop.y;

	m_pTargetArr[TARGET_TYPE_SHADE]->Begin(0);
	m_pTargetArr[TARGET_TYPE_SPECULAR_ACC]->Begin(1);

	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vCameraPos", CCameraMgr::GetInstance()->GetPos4D());
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetMatrix("g_mInvView", CCameraMgr::GetInstance()->GetInvView());
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetTexture("g_SpecularTexture", m_pTargetArr[TARGET_TYPE_SPECULAR]->m_pTexture);

	CLight* pLight;
	D3DXMATRIX mWorld;
	for(int i = 0; i < 100; ++i)
	{
		pLight = CLightMgr::GetInstance()->GetLight(i);

		if(pLight == NULL)
			continue;

		switch(pLight->GetLightType())
		{
		case LIGHT_TYPE_DIRECTION:
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->BeginPass(0);

			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightDir", pLight->GetDir());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightDiffuse", pLight->GetDiffuse());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightAmbient", pLight->GetAmbient());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightSpecular", pLight->GetSpecular());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->CommitChanges();

			m_pScreen->Render();
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->EndPass();
			break;

		case LIGHT_TYPE_POINT:
			if(CCameraMgr::GetInstance()->IsIn(&D3DXVECTOR3(pLight->GetPos()->x, pLight->GetPos()->y, pLight->GetPos()->z), pLight->GetRange()))
			{
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->BeginPass(1);

				D3DXMatrixTranslation(&mWorld, pLight->GetPos()->x, pLight->GetPos()->y, pLight->GetPos()->z);
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetMatrix("g_mWorld", &mWorld);
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetFloat("g_fRange", pLight->GetRange());
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightPos", pLight->GetPos());
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightDiffuse", pLight->GetDiffuse());
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightAmbient", pLight->GetAmbient());
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightSpecular", pLight->GetSpecular());
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->CommitChanges();

				pLight->GetSphere()->DrawSubset(0);
				m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->EndPass();
			}
			break;

		case LIGHT_TYPE_SPOT:
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->BeginPass(2);

			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightDiffuse", pLight->GetDiffuse());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightAmbient", pLight->GetAmbient());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->SetVector("g_vLightSpecular", pLight->GetSpecular());
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->CommitChanges();

			m_pScreen->Render();
			m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->EndPass();
			break;
		}
	}

	m_pShaderArr[SHADER_TYPE_LIGHT]->m_pEffect->End();

	m_pTargetArr[TARGET_TYPE_SHADE]->End(0);
	m_pTargetArr[TARGET_TYPE_SPECULAR_ACC]->End(1);
}

void CRenderMgr::RenderBlend()
{
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->BeginPass(0);
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->SetTexture("g_AlbedoTexture", m_pTargetArr[TARGET_TYPE_ALBEDO]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->SetTexture("g_ShadeTexture", m_pTargetArr[TARGET_TYPE_SHADE]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->SetTexture("g_SpecularAccTexture", m_pTargetArr[TARGET_TYPE_SPECULAR_ACC]->m_pTexture);
	
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->CommitChanges();
	m_pScreen->Render();

	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->EndPass();
	m_pShaderArr[SHADER_TYPE_BLEND]->m_pEffect->End();
}

void CRenderMgr::Shadow_End()
{
	if(m_dwRenderMode & RENDER_MODE_NORMAL_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_SHADOW]->End(0);

		D3DXVECTOR4 vViewRightTop;
		memcpy_s(&vViewRightTop, sizeof(D3DXVECTOR4), CCameraMgr::GetInstance()->GetViewPoint4D(6), sizeof(D3DXVECTOR4));
		vViewRightTop.y = -vViewRightTop.y;

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(2);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mInvView", CCameraMgr::GetInstance()->GetInvView());
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mLightViewProj", CLightMgr::GetInstance()->GetViewProj());
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_ShadowTexture", m_pTargetArr[TARGET_TYPE_SHADOW_MAP]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_SHADOW]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->End();
	}	
	else if(m_dwRenderMode & RENDER_MODE_CASCADE_SHADOW & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_SHADOW]->End(0);

		D3DXVECTOR4 vViewRightTop;
		memcpy_s(&vViewRightTop, sizeof(D3DXVECTOR4), CCameraMgr::GetInstance()->GetViewPoint4D(6), sizeof(D3DXVECTOR4));
		vViewRightTop.y = -vViewRightTop.y;

		CTransformCom* pTransformCom = NULL;
		D3DXVECTOR3 vLigthDir(0.f, 0.f, 0.f);
			
		if(CLightMgr::GetInstance()->GetLight() != NULL)
		{
			pTransformCom = (CTransformCom*)CLightMgr::GetInstance()->GetLight()->GetComponent(COM_TYPE_TRANSFORM);
			vLigthDir = pTransformCom->m_vAxisZ;
		}

		float fFar[CASCADED_END] = { 0.f };

		for(int i = 0; i < CASCADED_END; ++i)
		{
			fFar[i] = CLightMgr::GetInstance()->GetCascadedFar((CASCADED_TYPE)i);
		}

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->BeginPass(3);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetVector("g_CascadeDepths", &D3DXVECTOR4(fFar[CASCADED_NEAR], fFar[CASCADED_MIDDLE], fFar[CASCADED_FAR], 0.f));
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetVector("g_vLightDir", &D3DXVECTOR4(vLigthDir, 0.f));
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mInvView", CCameraMgr::GetInstance()->GetInvView());
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mShadowMap0", CLightMgr::GetInstance()->GetCascadedViewProj(CASCADED_NEAR));
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mShadowMap1", CLightMgr::GetInstance()->GetCascadedViewProj(CASCADED_MIDDLE));
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mShadowMap2", CLightMgr::GetInstance()->GetCascadedViewProj(CASCADED_FAR));
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_SHADOW]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_Cascaded_NearTexture", m_pTargetArr[TARGET_TYPE_SHADOW_NEAR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_Cascaded_MidTexture", m_pTargetArr[TARGET_TYPE_SHADOW_MIDDLE]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_Cascaded_FarTexture", m_pTargetArr[TARGET_TYPE_SHADOW_FAR]->m_pTexture);

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->End();
	}
}

void CRenderMgr::Effect_End()
{
	m_pTargetArr[TARGET_TYPE_EFFECT_DISTORTION]->Begin(1);
	m_pTargetArr[TARGET_TYPE_EFFECT_REFRACTION]->Begin(2);

	D3DXVECTOR4 vViewRightTop;
	memcpy_s(&vViewRightTop, sizeof(D3DXVECTOR4), CCameraMgr::GetInstance()->GetViewPoint4D(6), sizeof(D3DXVECTOR4));
	vViewRightTop.y = -vViewRightTop.y;
	////////////////////////////////////////////////////////////////////////// Begin - Effect
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fFar", CCameraMgr::GetInstance()->GetFar());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetVector("g_vViewPosition", CCameraMgr::GetInstance()->GetPos4D());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetVector("g_vLightPosition", CLightMgr::GetInstance()->GetPos4D());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mInvView", CCameraMgr::GetInstance()->GetInvView());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mProj", CCameraMgr::GetInstance()->GetProj());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mView", CCameraMgr::GetInstance()->GetView());
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NormalDepthTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DepthTexture", m_pTargetArr[TARGET_TYPE_DEPTH]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fTime", CTimeMgr::GetInstance()->GetAccTime());

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_EFFECT].size(); ++i)
	{
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_RENDER);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->BeginPass(m_pRenderCom->m_dwPass);

		////////////////////////////////////////////////////////////////////////// Pass0
		if(m_pRenderCom->m_dwPass == 0)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);

					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		////////////////////////////////////////////////////////////////////////// Pass1 - 이펙트에 왜곡이 들어가는 녀석
		else if(m_pRenderCom->m_dwPass == 1)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_ObjectVec[RENDER_TYPE_EFFECT][i]->Render();
			m_pBufferCom->m_BufferVec[0]->Render();
		}
		////////////////////////////////////////////////////////////////////////// Pass2 - 이펙트에 왜곡이 안들어가고 트레일 매쉬인녀석
		else if(m_pRenderCom->m_dwPass == 2)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_ObjectVec[RENDER_TYPE_EFFECT][i]->Render();
			m_pBufferCom->m_BufferVec[0]->Render();
		}
		else if(m_pRenderCom->m_dwPass == 3)// 그냥 RcTex
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 4)//데칼
		{
			D3DXMATRIX matInvWorld;
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			D3DXMatrixInverse(&matInvWorld, NULL, &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mInvWorld", &matInvWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 5)	//깊이 소팅x 	
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 6)	// 알파 RcTex + 왜곡
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_ObjectVec[RENDER_TYPE_EFFECT][i]->Render();
			m_pBufferCom->m_BufferVec[0]->Render();		
		}
		else if(m_pRenderCom->m_dwPass == 7)	//	 알파 데칼
		{
			D3DXMATRIX matInvWorld;
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			D3DXMatrixInverse(&matInvWorld, NULL, &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mInvWorld", &matInvWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
			m_pBufferCom->Render();
		}	
		else if(m_pRenderCom->m_dwPass == 8)	//  알파 RcTex
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 9)	// staticMesh UV 좌표 Y이동.
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];

				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}	
		}
		else if(m_pRenderCom->m_dwPass == 10)	// 검은색? 빨강색? 잔상
		{
			//다이나믹 매쉬 잔상.
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderAfterImageFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}
		else if(m_pRenderCom->m_dwPass == 11)	// 검은색 잔상
		{
			//난사 잔상
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderAfterImageFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}
		else if(m_pRenderCom->m_dwPass == 12)	// 스태틱 매쉬 (검은색으로 렌더)
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 13)	// StaticMesh 굴절 효과 + 알파 값 조절.
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					//m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NormalTexture", m_pStaticMesh->m_ppNormalTexture[k]);
					//m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SpecularTexture", m_pStaticMesh->m_ppSpecularTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 14)	// StaticMesh 매쉬 알파값 조절
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 15) // uv Y축 애니매이션 RcTex
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();

			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 16) //다이나믹 매쉬 이펙트
		{
			//다이나믹 매쉬 잔상.
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pDynamicMesh = (CDynamicMesh*)m_pBufferCom->m_BufferVec[j];
				RenderDynamicEffectFrame((MeshFrame*)m_pDynamicMesh->m_pRootFrame, m_pDynamicMesh->m_pRootVTF);
			}
		}
		else if(m_pRenderCom->m_dwPass == 17) //힘의 파동 전용 패스
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_AlphaTexture", m_pMaterialCom->m_pTexture);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 18) // 파티클 전용 패스
		{
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			
			D3DXMATRIX matWorld;
			D3DXMatrixIdentity(&matWorld);

			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &matWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pMaterialCom->m_pTexture);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
			m_ObjectVec[RENDER_TYPE_EFFECT][i]->Render();
		}
		else if(m_pRenderCom->m_dwPass == 19) // Cull Mode None && Diffuse만 + 알파값 적용 + zenable == false
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 20) // 비전보주 전용 패스
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			vector<LPDIRECT3DTEXTURE9>*	m_pTexture = &((CWizard_ArcaneOrb_GalaxyEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_TextureVec;

			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", (*m_pTexture)[0]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_AlphaTexture", (*m_pTexture)[1]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_BlendTexture", (*m_pTexture)[2]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
			m_pBufferCom->Render();
		}
		else if(m_pRenderCom->m_dwPass == 21) //UV 애니메이션 + Alpha텍스쳐 따로 있는 패스
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_MATERIAL);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);

			if(typeid(*(m_ObjectVec[RENDER_TYPE_EFFECT][i])) == typeid(CMonk_CycloneStrike_NovaEffect))
			{
				float fTime = ((CMonk_CycloneStrike_NovaEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fTime;
				m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fTime", fTime);
			}
			
			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_AlphaTexture", m_pMaterialCom->m_pTexture);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 22) // Water
		{
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fAlpha", ((CEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fAlpha);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fX", ((CWaterEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fSpeedX);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fY", ((CWaterEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fSpeedY);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetFloat("g_fDetail", ((CWaterEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i])->m_fDetail);

			for(size_t j = 0; j < m_pBufferCom->m_BufferVec.size(); ++j)
			{
				m_pStaticMesh = (CStaticMesh*)m_pBufferCom->m_BufferVec[j];
				for(DWORD k = 0; k < m_pStaticMesh->m_dwSubsetCnt; ++k)
				{
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", m_pStaticMesh->m_ppDiffuseTexture[k]);
					m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
					m_pStaticMesh->m_pMesh->DrawSubset(k);
				}
			}
		}
		else if(m_pRenderCom->m_dwPass == 23) // Fire
		{
			CFireEffect* pFireEffect = (CFireEffect*)m_ObjectVec[RENDER_TYPE_EFFECT][i];
			m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_TRANSFORM);
			m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_EFFECT][i]->GetComponent(COM_TYPE_BUFFER);

			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_FireTexture", pFireEffect->m_TextureVec[0]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NoiseTexture", pFireEffect->m_TextureVec[1]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_FireAlphaTexture", pFireEffect->m_TextureVec[2]);
			m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
			m_pBufferCom->Render();
		}
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->EndPass();
	}
	m_pTargetArr[TARGET_TYPE_EFFECT]->End(0);
	m_pTargetArr[TARGET_TYPE_EFFECT_DISTORTION]->End(1);
	m_pTargetArr[TARGET_TYPE_EFFECT_REFRACTION]->End(2);

	//최종 블렌드 코드.
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->BeginPass(24);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DistortionTexture", m_pTargetArr[TARGET_TYPE_EFFECT_DISTORTION]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_RefractionTexture", m_pTargetArr[TARGET_TYPE_EFFECT_REFRACTION]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_EFFECT]->m_pTexture);
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
	m_pScreen->Render();
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->EndPass();
	m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->End();
	////////////////////////////////////////////////////////////////////////// End - Effect
}
void CRenderMgr::SSAO_End()
{
	if(m_dwRenderMode & RENDER_MODE_SSAO & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_SSAO]->End(0);

		m_pTargetArr[TARGET_TYPE_SSAO_GRAY]->Begin(0);
		
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->BeginPass(0);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_DepthTexture", m_pTargetArr[TARGET_TYPE_DEPTH]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->EndPass();
		m_pTargetArr[TARGET_TYPE_SSAO_GRAY]->End(0);

		m_pTargetArr[TARGET_TYPE_SSAO_BLUR]->Begin(0);

		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->BeginPass(1);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_DepthTexture", m_pTargetArr[TARGET_TYPE_DEPTH]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_BlurTexture", m_pTargetArr[TARGET_TYPE_SSAO_GRAY]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->EndPass();
		m_pTargetArr[TARGET_TYPE_SSAO_BLUR]->End(0);
		
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->BeginPass(2);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_SceneTexure", m_pTargetArr[TARGET_TYPE_SSAO]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->SetTexture("g_BlurTexture", m_pTargetArr[TARGET_TYPE_SSAO_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->EndPass();

		m_pShaderArr[SHADER_TYPE_SSAO]->m_pEffect->End();
	}	
}

void CRenderMgr::HDR_End()
{
	if(m_dwRenderMode & RENDER_MODE_HDR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		HDR_Offset();

		m_pTargetArr[TARGET_TYPE_HDR]->End(0);

		//======= HDR_Luminance_DownsSampler Begin
		m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV6]->Begin(0);

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(0);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_HDR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetVectorArray("g_vLumOffSets", m_vLuminanceOffset_LV6, 4);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();
		
		m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV6]->End(0);
		
		int iIndex = (int)TARGET_TYPE_HDR_LUMINANCE_LV6; //16

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(1);

		for(int i = 1; i < 6; ++i)
		{
			m_pTargetArr[iIndex - i]->Begin(0);	
			
			m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[(iIndex - i) + 1]->m_pTexture);
			m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetVectorArray("g_vSampleOffest", m_vLuminanceOffset[i - 1], 9);
			m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
			m_pScreen->Render();

			m_pTargetArr[iIndex - i]->End(0);
		}
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();
		//======= HDR_Luminance_DownsSampler End

		//======= HDR_BrightPass Begin
		m_pTargetArr[TARGET_TYPE_HDR_BRIGHT_PASS]->Begin(0);

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(2);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_HDR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloat("g_fThreshold", m_fBrightThreshold);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetVectorArray("g_vDownSamplerOffset", m_vLuminanceOffset_LV6, 4);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();

		m_pTargetArr[TARGET_TYPE_HDR_BRIGHT_PASS]->End(0);
		//======= HDR_BrightPass End

		//======= HDR_DownSampler Begin
		m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->Begin(0);

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(3);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_HDR_BRIGHT_PASS]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetVectorArray("g_vDownSamplerOffset", m_vDownSamplerOffset, 16);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();

		m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->End(0);
		//======= HDR_DownSampler End
		
		//======= HDR_HorizontalBlur_Begin
		m_pTargetArr[TARGET_TYPE_HDR_HORIZONTAL_BLUR]->Begin(0);

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(4);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloatArray("g_fBloomWeights", m_fBloomWeight_X, 9);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloatArray("g_fBloomOffset", m_fBloomOffset_X, 9);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();

		m_pTargetArr[TARGET_TYPE_HDR_HORIZONTAL_BLUR]->End(0);
		//======= HDR_HorizontalBlur_End

		//======= HDR_VerticalBlur_Begin
		m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]->Begin(0);

		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(5);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_HDR_HORIZONTAL_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloatArray("g_fBloomWeights", m_fBloomWeight_Y, 9);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloatArray("g_fBloomOffset", m_fBloomOffset_Y, 9);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();

		m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]->End(0);
		//======= HDR_VerticalBlur_End

		//======= HDR_ToneMapping_Begin
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->BeginPass(6);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_HDRTexture", m_pTargetArr[TARGET_TYPE_HDR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_LumTexture", m_pTargetArr[TARGET_TYPE_HDR_LUMINANCE_LV1]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetTexture("g_BloomTexture", m_pTargetArr[TARGET_TYPE_HDR_VERTICAL_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloat("g_fBloom_w", m_fBloom_w);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloat("g_fBloom_h", m_fBloom_h);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloat("g_fExposure", m_fExposure);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->SetFloat("g_fGaussianScalar", m_fGaussMultiplier);
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_HDR]->m_pEffect->End();
		//======= HDR_ToneMapping_End
	}
}

void CRenderMgr::FogEnd()
{
	D3DXVECTOR4 vViewRightTop;
	memcpy_s(&vViewRightTop, sizeof(D3DXVECTOR4), CCameraMgr::GetInstance()->GetViewPoint4D(6), sizeof(D3DXVECTOR4));
	vViewRightTop.y = -vViewRightTop.y;

	if(m_dwRenderMode & RENDER_MODE_EXPONENT_FOG & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_FOG]->End(0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->BeginPass(0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_FOG]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vFog", &D3DXVECTOR4(0.33f, 8000.f, 0.f, 0.f));
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->End();
	}
	else if(m_dwRenderMode & RENDER_MODE_EXPONENT_SQUARE_FOG & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_FOG]->End(0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->BeginPass(1);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_FOG]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vFog", &D3DXVECTOR4(0.33f, 8000.f, 0.f, 0.f));
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->End();
	}
	else if(m_dwRenderMode & RENDER_MODE_HEIGHT_FOG & CSettingMgr::GetInstance()->GetRenderMode())
	{
		float fHeight, fEnd = 0.f;
		float fY = CCameraMgr::GetInstance()->GetPos3D()->y;
		if(fY >= 0.f)
		{
			fHeight = fY + m_fFogHeight;
			fEnd = fY + 8000.f;
		}
		else
		{
			fHeight = fY - m_fFogHeight;
			fEnd = fY - 8000.f;
		}

		m_pTargetArr[TARGET_TYPE_FOG]->End(0);

		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->BeginPass(2);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vViewRightTop", &vViewRightTop);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vCameraPos", CCameraMgr::GetInstance()->GetPos4D());
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_FOG]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetTexture("g_NormalTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetMatrix("g_mInvView", CCameraMgr::GetInstance()->GetInvView());
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->SetVector("g_vFog", &D3DXVECTOR4(0.33f, fEnd, fHeight, 0.f));
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->CommitChanges();
		m_pScreen->Render();
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_FOG]->m_pEffect->End();
	}
}	

void CRenderMgr::BlurEnd()
{
	if(m_dwRenderMode & RENDER_MODE_RADIAL_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_BLUR]->End(0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->BeginPass(0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetFloat("g_fBlurWidth", m_fBlurWidth);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->End();
	}
	else if(m_dwRenderMode & RENDER_MODE_GAUSSIAN_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_BLUR]->End(0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->BeginPass(1);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetInt("g_iKernelSize", int(m_fKernelSize) * 2 + 1);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->End();
	}
	else if(m_dwRenderMode & RENDER_MODE_MOTION_BLUR & CSettingMgr::GetInstance()->GetRenderMode())
	{
		m_pTargetArr[TARGET_TYPE_BLUR]->End(0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->Begin(NULL, 0);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->BeginPass(2);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetTexture("g_VelocityTexture", m_pTargetArr[TARGET_TYPE_VELOCITY]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->SetTexture("g_SceneTexture", m_pTargetArr[TARGET_TYPE_BLUR]->m_pTexture);
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->CommitChanges();
		m_pScreen->Render();

		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->EndPass();
		m_pShaderArr[SHADER_TYPE_BLUR]->m_pEffect->End();
	}
}

void CRenderMgr::RenderUI()
{
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetFloat("g_fFar", CCameraMgr::GetInstance()->GetFar());
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetMatrix("g_mViewProj", CCameraMgr::GetInstance()->GetViewProj());
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetTexture("g_NormalDepthTexture", m_pTargetArr[TARGET_TYPE_NORMAL]->m_pTexture);

	////////////////////////////////////////////////////////////////////////// BeginPass0 - Drop
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->BeginPass(0);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_DROP].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_DROP][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_DROP][i]->GetComponent(COM_TYPE_MATERIAL);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_DROP][i]->GetComponent(COM_TYPE_BUFFER);

		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->CommitChanges();

		m_pBufferCom->Render();
	}

	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->EndPass();
	////////////////////////////////////////////////////////////////////////// EndPass0 - Drop

	////////////////////////////////////////////////////////////////////////// BeginPass1 - UI
	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->BeginPass(1);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_UI].size(); ++i)
	{
		if(m_ObjectVec[RENDER_TYPE_UI][i]->IsDestroy())
			continue;

		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_UI][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pRenderCom = (CRenderCom*)m_ObjectVec[RENDER_TYPE_UI][i]->GetComponent(COM_TYPE_RENDER);
		m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_UI][i]->GetComponent(COM_TYPE_MATERIAL);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_UI][i]->GetComponent(COM_TYPE_BUFFER);

		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetVector("g_vColor", &m_pRenderCom->m_vColor);
		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
		m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->CommitChanges();

		m_pBufferCom->Render();
		m_ObjectVec[RENDER_TYPE_UI][i]->Render();
	}

	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->EndPass();
	////////////////////////////////////////////////////////////////////////// EndPass1 - UI

	m_pShaderArr[SHADER_TYPE_UI]->m_pEffect->End();
}

void CRenderMgr::RenderMouse()
{
	m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->Begin(NULL, 0);
	m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->BeginPass(0);

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_MOUSE].size(); ++i)
	{
		m_pTransformCom = (CTransformCom*)m_ObjectVec[RENDER_TYPE_MOUSE][i]->GetComponent(COM_TYPE_TRANSFORM);
		m_pMaterialCom = (CMaterialCom*)m_ObjectVec[RENDER_TYPE_MOUSE][i]->GetComponent(COM_TYPE_MATERIAL);
		m_pBufferCom = (CBufferCom*)m_ObjectVec[RENDER_TYPE_MOUSE][i]->GetComponent(COM_TYPE_BUFFER);

		m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->SetMatrix("g_mWorld", &m_pTransformCom->m_mWorld);
		m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->SetTexture("g_BaseTexture", m_pMaterialCom->m_pTexture);
		m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->CommitChanges();

		m_pBufferCom->Render();
		m_ObjectVec[RENDER_TYPE_MOUSE][i]->Render();
	}

	m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->EndPass();
	m_pShaderArr[SHADER_TYPE_MOUSE]->m_pEffect->End();
}

void CRenderMgr::RenderNPCBox()
{
	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_NPC].size(); ++i)
		m_ObjectVec[RENDER_TYPE_NPC][i]->Render();
}

void CRenderMgr::RenderProbBox()
{
	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_STATIC_PROB].size(); ++i)
		m_ObjectVec[RENDER_TYPE_STATIC_PROB][i]->Render();

	for(size_t i = 0; i < m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB].size(); ++i)
		m_ObjectVec[RENDER_TYPE_DYNAMIC_PROB][i]->Render();
}

void CRenderMgr::RenderFPS()
{
	RECT rcFPS;
	SetRect(&rcFPS, long(WINCX / 2.0f - 100), 0, long(WINCX / 2.0f + 100), 100);
	CFontMgr::GetInstance()->GetKostarFont(20, 10)->DrawText(NULL, m_tszFPS, -1, &rcFPS, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CRenderMgr::RenderShadowFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL)
		RenderShadowContainer((MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	if(_pMeshFrame->pFrameFirstChild != NULL)
		RenderShadowFrame((MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	if(_pMeshFrame->pFrameSibling != NULL)
		RenderShadowFrame((MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}

void CRenderMgr::RenderShadowContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pMeshContainer->pCombinationBuf->GetBufferPointer();
	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetTexture("g_SkinningTexture", _pSkinningVTF->ppCurVTF[i]);
		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->SetInt("g_iInfluenceMax", _pMeshContainer->dwMaxVertexInfl);

		m_pShaderArr[SHADER_TYPE_SHADOW]->m_pEffect->CommitChanges();
		_pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

void CRenderMgr::RenderVelocityFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL)
		RenderVelocityContainer((MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	if(_pMeshFrame->pFrameFirstChild != NULL)
		RenderVelocityFrame((MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	if(_pMeshFrame->pFrameSibling != NULL)
		RenderVelocityFrame((MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}

void CRenderMgr::RenderVelocityContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetTexture("g_CurSkinningTexture", _pSkinningVTF->ppCurVTF[i]);
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetTexture("g_PreSkinningTexture", _pSkinningVTF->ppPreVTF[i]);
		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->SetInt("g_iInfluenceMax", _pMeshContainer->dwMaxVertexInfl);

		m_pShaderArr[SHADER_TYPE_VELOCITY]->m_pEffect->CommitChanges();
		_pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

void CRenderMgr::RenderFrame(CShader* _pShader, MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL)
		RenderContainer(_pShader, (MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	if(_pMeshFrame->pFrameFirstChild != NULL)
		RenderFrame(_pShader, (MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	if(_pMeshFrame->pFrameSibling != NULL)
		RenderFrame(_pShader, (MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}

void CRenderMgr::RenderContainer(CShader* _pShader, MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pMeshContainer->pCombinationBuf->GetBufferPointer();
	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		_pShader->m_pEffect->SetTexture("g_DiffuseTexture", _pMeshContainer->ppDiffuseTexture[pBoneCombination[i].AttribId]);
		_pShader->m_pEffect->SetTexture("g_NormalTexture", _pMeshContainer->ppNormalTexture[pBoneCombination[i].AttribId]);
		_pShader->m_pEffect->SetTexture("g_SpecularTexture", _pMeshContainer->ppSpecularTexture[pBoneCombination[i].AttribId]);
		_pShader->m_pEffect->SetTexture("g_SkinningTexture", _pSkinningVTF->ppCurVTF[i]);
		_pShader->m_pEffect->SetInt("g_iInfluenceMax", _pMeshContainer->dwMaxVertexInfl);

		_pShader->m_pEffect->CommitChanges();
		_pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

void CRenderMgr::RenderAfterImageFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL)
		RenderAfterImageContainer((MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	if(_pMeshFrame->pFrameFirstChild != NULL)
		RenderAfterImageFrame((MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	if(_pMeshFrame->pFrameSibling != NULL)
		RenderAfterImageFrame((MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}

void CRenderMgr::RenderAfterImageContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pMeshContainer->pCombinationBuf->GetBufferPointer();
	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SkinningTexture", _pSkinningVTF->ppCurVTF[i]);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetInt("g_iInfluenceMax", _pMeshContainer->dwMaxVertexInfl);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
		_pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

void CRenderMgr::RenderDynamicEffectFrame(MeshFrame* _pMeshFrame, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshFrame == NULL)
		return;

	if(_pMeshFrame->pMeshContainer != NULL)
		RenderDynamicEffectContainer((MeshContainer*)_pMeshFrame->pMeshContainer, _pSkinningVTF);

	if(_pMeshFrame->pFrameFirstChild != NULL)
		RenderDynamicEffectFrame((MeshFrame*)_pMeshFrame->pFrameFirstChild, _pSkinningVTF->pFirstChild);

	if(_pMeshFrame->pFrameSibling != NULL)
		RenderDynamicEffectFrame((MeshFrame*)_pMeshFrame->pFrameSibling, _pSkinningVTF->pSibling);
}	

void CRenderMgr::RenderDynamicEffectContainer(MeshContainer* _pMeshContainer, SkinningVTF* _pSkinningVTF)
{
	if(_pMeshContainer->pSkinInfo == NULL)
		return;

	LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pMeshContainer->pCombinationBuf->GetBufferPointer();

	for(DWORD i = 0; i < _pMeshContainer->NumMaterials; ++i)
	{
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SkinningTexture", _pSkinningVTF->ppCurVTF[i]);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_DiffuseTexture", _pMeshContainer->ppDiffuseTexture[pBoneCombination[i].AttribId]);
		//m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_NormalTexture", _pMeshContainer->ppNormalTexture[pBoneCombination[i].AttribId]);
		//m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetTexture("g_SpecularTexture", _pMeshContainer->ppSpecularTexture[pBoneCombination[i].AttribId]);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->SetInt("g_iInfluenceMax", _pMeshContainer->dwMaxVertexInfl);
		m_pShaderArr[SHADER_TYPE_EFFECT]->m_pEffect->CommitChanges();
		_pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}

void CRenderMgr::AddObject(RENDER_TYPE _eRenderType, CObject* _pObject)
{
	m_ObjectVec[_eRenderType].push_back(_pObject);
}

void CRenderMgr::RemoveObject(RENDER_TYPE _eRenderType, CObject* _pObject)
{
	for(size_t i = 0; i < m_ObjectVec[_eRenderType].size(); ++i)
	{
		if(m_ObjectVec[_eRenderType][i] == _pObject)
		{
			m_ObjectVec[_eRenderType][i] = m_ObjectVec[_eRenderType][m_ObjectVec[_eRenderType].size() - 1];
			m_ObjectVec[_eRenderType].pop_back();
		}
	}
}

float CRenderMgr::ComputeGaussianValue(float fX, float fMean, float fStd_Deviation)
{
	float fResult = (1.f / sqrt(2.f * D3DX_PI * fStd_Deviation * fStd_Deviation)) * expf(-((fX - fMean) * (fX - fMean)) / (2.f * fStd_Deviation * fStd_Deviation));

	return fResult;
}

void CRenderMgr::HDR_Offset(void)
{
	D3DSURFACE_DESC srcTexDesc;
	m_pTargetArr[TARGET_TYPE_HDR_DOWNSAMPLED]->m_pTexture->GetLevelDesc(0, &srcTexDesc);

	for(int i = 0; i < 9; i++)
	{
		m_fBloomOffset_X[i] = ((float)i - 4.f) * (1.f / (float)srcTexDesc.Width);

		float fX = (float)i - 4.f / 4.f;

		m_fBloomWeight_X[i] = m_fGaussMultiplier * ComputeGaussianValue(fX, m_fGaussMean, m_fGaussStdDev);
	}

	for(int i = 0; i < 9; i++)
	{
		m_fBloomOffset_Y[i] = ((float)i - 4.f) * (1.f / (float)srcTexDesc.Height);

		float fX = (float)i - 4.f / 4.f;

		m_fBloomWeight_Y[i] = m_fGaussMultiplier * ComputeGaussianValue(fX, m_fGaussMean, m_fGaussStdDev);
	}
}