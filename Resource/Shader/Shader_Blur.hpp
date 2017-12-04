// Radial Blur
float2 g_vCenter = { 0.5, 0.5 };
float g_fBlurStart = 1.0f;
float g_fBlurWidth = -0.1;
int g_iSamplesForRadialBlur = 10;

// Gaussian Blur
float2 g_Kernel3[3] =
{
	{ -1, 0 },
	{ 0, 0 },
	{ 1, 0 }
};

float2 g_Kernel5[5] = 
{
	{ -2, 0 },
	{ -1, 0 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 }
};

float2 g_Kernel7[7] =
{
	{ -3, 0 },
	{ -2, 0 },
	{ -1, 0 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 }
};

float2 g_Kernel9[9] =
{
	{ -4, 0 },
	{ -3, 0 },
	{ -2, 0 },
	{ -1, 0 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 },
	{ 4, 0 }
};

float2 g_Kernel11[11] =
{
	{ -5, 0 },
	{ -4, 0 },
	{ -3, 0 },
	{ -2, 0 },
	{ -1, 0 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 },
	{ 4, 0 },
	{ 5, 0 }
};

float g_Weight3[3] = 
{
	0.25f,
	0.5f,
	0.25f
};

float g_Weight5[5] = 
{
	0.1f,
	0.2f,
	0.4f,
	0.2f,
	0.1f
};

float g_Weight7[7] = 
{
	0.045454f,
	0.090909f,
	0.181818f,
	0.363636f,
	0.181818f,
	0.090909f,
	0.045454f
};

float g_Weight9[9] = 
{
	0.021739f,
	0.043478f,
	0.086956f,
	0.173913f,
	0.347826f,
	0.173913f,
	0.086956f,
	0.043478f,
	0.021739f
};

float g_Weight11[11] = 
{
	0.010638f,
	0.021276f,
	0.041666f,
	0.085106f,
	0.170212f,
	0.340425f,
	0.170212f,
	0.085106f,
	0.041666f,
	0.021276f,
	0.010638f
};

float g_fWidth = 800.0f;
float g_fHeight = 600.0f;

int g_iKernelSize;

// Motion Blur
int g_iSamplesForMotionBlur = 5;

// VelocityTexture
texture g_VelocityTexture;
sampler VelocitySampler = sampler_state
{
	texture	= g_VelocityTexture;
};

// SceneTexture
texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture	= g_SceneTexture;

	minfilter = linear;
	magfilter = linear;
};

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass0_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

Pass0_VS_OUT Pass0_VS_MAIN(Pass0_VS_IN Input)
{
	Pass0_VS_OUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass0_PS_IN
{
	float2 vTexUV : TEXCOORD0;
};

float4 Pass0_PS_MAIN(Pass0_PS_IN Input) : COLOR
{
	float2 vTexUV = Input.vTexUV - g_vCenter;

	float fScale;
	float4 vColor = 0;
	for(int i = 0; i < g_iSamplesForRadialBlur; i++) 
	{
		fScale = g_fBlurStart + g_fBlurWidth * 0.1f * (i / (float)(g_iSamplesForRadialBlur - 1));
		vColor += tex2D(SceneSampler, vTexUV * fScale + g_vCenter);
	}

	vColor /= g_iSamplesForRadialBlur;

	return vColor;
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass1_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

Pass1_VS_OUT Pass1_VS_MAIN(Pass1_VS_IN Input)
{
	Pass1_VS_OUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass1_PS_IN
{
	float2 vTexUV : TEXCOORD0;
};

float4 Pass1_PS_MAIN(Pass1_PS_IN Input) : COLOR
{
	float4 vColor = 0;

	float2 vTexSize = float2(1.0f / g_fHeight, 1.0f / g_fWidth);

	if(g_iKernelSize == 3)
	{
		for(int i = 0; i < 3; ++i)
			vColor += tex2D(SceneSampler, Input.vTexUV + (g_Kernel3[i] * vTexSize)) * g_Weight3[i];
	}
	else if(g_iKernelSize == 5)
	{
		for(int i = 0; i < 5; ++i)
			vColor += tex2D(SceneSampler, Input.vTexUV + (g_Kernel5[i] * vTexSize)) * g_Weight5[i];
	}
	else if(g_iKernelSize == 7)
	{
		for(int i = 0; i < 7; ++i)
			vColor += tex2D(SceneSampler, Input.vTexUV + (g_Kernel7[i] * vTexSize)) * g_Weight7[i];
	}
	else if(g_iKernelSize == 9)
	{
		for(int i = 0; i < 9; ++i)
			vColor += tex2D(SceneSampler, Input.vTexUV + (g_Kernel9[i] * vTexSize)) * g_Weight9[i];
	}
	else if(g_iKernelSize == 11)
	{
		for(int i = 0; i < 11; ++i)
			vColor += tex2D(SceneSampler, Input.vTexUV + (g_Kernel11[i] * vTexSize)) * g_Weight11[i];
	}

	return vColor;
}

////////////////////////////////////////////////////////////////////////// Pass2
struct Pass2_VS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass2_VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

Pass2_VS_OUT Pass2_VS_MAIN(Pass2_VS_IN Input)
{
	Pass2_VS_OUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass2_PS_IN
{
	float2 vTexUV : TEXCOORD0;
};

float4 Pass2_PS_MAIN(Pass2_PS_IN Input) : COLOR
{
	// 속도맵으로부터 속도벡터와 Z값을 얻어옴
	float4 vVeloUV = tex2D(VelocitySampler, Input.vTexUV);
	//vVeloUV.xy /= 0.9f;

	int iCnt = 1;
	float4 vBColor;
	float4 vTexUV = float4(0.0f, 0.0f, 1.0f, 1.0f);

	// 씬의 렌더링 이미지를 얻어옴. a 성분에 Z값을 저장된다.
	float4 vColor = tex2D(SceneSampler, Input.vTexUV);

	for(int i = iCnt; i < g_iSamplesForMotionBlur; i++)
	{
		vTexUV.xy = Input.vTexUV + vVeloUV.xy * (float)i;
		vBColor = tex2Dlod(SceneSampler, vTexUV);

		// 속도 맵의 Z값과 속도 벡터 방향에 있는 텍셀 위치를 샘플링 한 씬의 렌더링 이미지의 Z값을 비교한다.
		if(vVeloUV.a < vBColor.a + 0.04f)
		{
			++iCnt;
			vColor += vBColor;
		}
	}

	vColor /= (float)iCnt;

	return vColor;
}

technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}

	pass Pass1
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}

	pass Pass2
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass2_VS_MAIN();
		PixelShader = compile ps_3_0 Pass2_PS_MAIN();
	}
};