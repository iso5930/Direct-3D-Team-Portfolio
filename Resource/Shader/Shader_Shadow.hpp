float4 g_vViewRightTop;

float4x4 g_mWorld;
float4x4 g_mInvView;
float4x4 g_mLightViewProj;
float4x4 g_mViewProj;
float4x4 g_mShadowMap0;
float4x4 g_mShadowMap1;
float4x4 g_mShadowMap2;

float4 g_vLightDir;
float4 g_CascadeDepths;

int g_iInfluenceMax;

texture g_SkinningTexture;
sampler SkinningSampler = sampler_state
{
	texture	= g_SkinningTexture;
};

texture	g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
};

texture	g_ShadowTexture;
sampler ShadowSampler = sampler_state
{
	texture = g_ShadowTexture;
	minfilter = linear;
	magfilter = linear;
};

texture	g_Cascaded_NearTexture;
sampler Cascaded_NearSampler = sampler_state
{
	texture = g_Cascaded_NearTexture;
	minfilter = linear;
	magfilter = linear;
};

texture	g_Cascaded_MidTexture;
sampler Cascaded_MidSampler = sampler_state
{
	texture = g_Cascaded_MidTexture;
	minfilter = linear;
	magfilter = linear;
};

texture	g_Cascaded_FarTexture;
sampler Cascaded_FarSampler = sampler_state
{
	texture = g_Cascaded_FarTexture;
	minfilter = linear;
	magfilter = linear;
};

texture g_SceneTexture;
sampler SceneSampler = sampler_state
{
	texture = g_SceneTexture;
};

float4x4 GetSkinMatrix(int idx)
{
	float4 uvCol = float4(((float)((idx % 16) * 4) + 0.5f) / 64.0f, ((float)((idx / 16)) + 0.5f) / 64.0f, 0.0f, 0.0f);

	float4x4 mat = { tex2Dlod(SkinningSampler, uvCol),
		tex2Dlod(SkinningSampler, uvCol + float4(1.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(SkinningSampler, uvCol + float4(2.0f / 64.0f, 0, 0, 0)),
		tex2Dlod(SkinningSampler, uvCol + float4(3.0f / 64.0f, 0, 0, 0)) };

	return mat;
}

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_INPUT
{
	float4 vPosition : POSITION;
};

struct Pass0_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD1;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;
	Input.vPosition.w = 1.f;
	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mLightViewProj);
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass0_PS_INPUT
{
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass0_PS_MAIN(Pass0_PS_INPUT Input) : COLOR0
{
	float depth = Input.vClipPosition.z / Input.vClipPosition.w;

	return float4(depth.xxx, 1.0f);
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_INPUT
{
	float4 vPosition : POSITION;
	float4 vWeights : BLENDWEIGHT0;
	int4 vIndices : BLENDINDICES0;
};

struct Pass1_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD1;
};

Pass1_VS_OUTPUT Pass1_VS_MAIN(Pass1_VS_INPUT Input)
{
	Pass1_VS_OUTPUT Output;

	float4 vPosition = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float lastWeight = 0.0f;
	int n = g_iInfluenceMax - 1;

	for(int i = 0; i < n; ++i)
	{
		lastWeight += Input.vWeights[i];
		vPosition += Input.vWeights[i] * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[i]));
	}

	lastWeight = 1.0f - lastWeight;
	vPosition += lastWeight * mul(Input.vPosition, GetSkinMatrix(Input.vIndices[n]));
	vPosition.w = 1.0f;

	Output.vPosition = mul(vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mLightViewProj);
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass1_PS_INPUT
{
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass1_PS_MAIN(Pass1_PS_INPUT Input) : COLOR0
{
	float depth = Input.vClipPosition.z / Input.vClipPosition.w;
	return float4(depth.xxx, 1.0f);
}

////////////////////////////////////////////////////////////////////////// Pass2
struct Pass2_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass2_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass2_VS_OUTPUT Pass2_VS_MAIN(Pass2_VS_INPUT Input)
{
	Pass2_VS_OUTPUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;
	Output.vClipPosition = Input.vPosition;

	return Output;
}

struct Pass2_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass2_PS_MAIN(Pass2_PS_INPUT Input) : COLOR0
{
	float4 vColor = tex2D(SceneSampler, Input.vTexUV);

	// DepthUV
	float2 vDepthUV = Input.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// Depth
	float fDepth = tex2D(NormalSampler, vDepthUV).w;

	// ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	// 여기도 왜 이렇게 하는건지 모르게떠..
	float4 vViewPos = float4(vViewRay * fDepth, 1.0f);

	// Position
	float4 vPosition = mul(vViewPos, g_mInvView);

	// ClipPosition
	float4 vClipPosition = mul(vPosition, g_mLightViewProj);

	// CurDepth
	float fCurDepth = vClipPosition.z / vClipPosition.w;

	// uv
	float2 uv = vClipPosition.xy / vClipPosition.w;
	uv.y = -uv.y;
	uv = uv * 0.5f + 0.5f;

	if(0.0f <= uv.x && uv.x <= 1.0f && 0.0f <= uv.y && uv.y <= 1.0f)
	{
		// ShadowDepth
		float fShadowDepth = tex2D(ShadowSampler, uv);

		if(fCurDepth > fShadowDepth + 0.0000125f)
			vColor *= 0.5f;
	}

	return vColor;
}

////////////////////////////////////////////////////////////////////////// Pass3
struct Pass3_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass3_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass3_VS_OUTPUT Pass3_VS_MAIN(Pass3_VS_INPUT Input)
{
	Pass3_VS_OUTPUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;
	Output.vClipPosition = Input.vPosition;

	return Output;
}

struct Pass3_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass3_PS_MAIN(Pass3_PS_INPUT Input) : COLOR0
{
	float3 vLightDir = g_vLightDir.xyz * -1.f;
	float4 vColor = tex2D(SceneSampler, Input.vTexUV);

	// DepthUV
	float2 vDepthUV = Input.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// Normal
	float4 vNormal = tex2D(NormalSampler, Input.vTexUV);

	// Depth
	float fDepth = vNormal.w;

	// Normal
	vNormal.w = 0.0f;
	vNormal = normalize(vNormal * 2.0f - 1.0f);
	
	// ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	// 여기도 왜 이렇게 하는건지 모르게떠..
	float4 vViewPos = float4(vViewRay * fDepth, 1.0f);

	// Position
	float4 vPosition = mul(vViewPos, g_mInvView);

	float4 vClipPos0 = mul(vPosition, g_mShadowMap0);
	float4 vClipPos1 = mul(vPosition, g_mShadowMap1);
	float4 vClipPos2 = mul(vPosition, g_mShadowMap2);

	float fCurDepth0 = vClipPos0.z / vClipPos0.w;
	float fCurDepth1 = vClipPos1.z / vClipPos1.w;
	float fCurDepth2 = vClipPos2.z / vClipPos2.w;

	float4 vShadowColor = float4(0.5f, 0.5f, 0.5f, 0.5f);
	float fShadowBais = 0.0022f;

	float4 vWVPPos = float4(vPosition.x, vPosition.y, vPosition.z, 1.f);

	vWVPPos = mul(vWVPPos, g_mViewProj);

	float fPosInv = 1.f / vWVPPos.w;
	
	float fLightPosInv0 = 1.f / vClipPos0.w;
	float fLightPosInv1 = 1.f / vClipPos1.w;
	float fLightPosInv2 = 1.f / vClipPos2.w;

	float fDepthTest = vWVPPos.z * fPosInv;
	//??

	float fLightIntensity = 0.f;

	float2 fShadowCoord[3] = 
	{
		float2(vClipPos0.x * fLightPosInv0 * 0.5f + 0.5f, -vClipPos0.y * fLightPosInv0 * 0.5 + 0.5),
		float2(vClipPos1.x * fLightPosInv1 * 0.5f + 0.5f, -vClipPos1.y * fLightPosInv1 * 0.5 + 0.5),
		float2(vClipPos2.x * fLightPosInv2 * 0.5f + 0.5f, -vClipPos2.y * fLightPosInv2 * 0.5 + 0.5),
	};

	float LightDepthValue[3];
	LightDepthValue[0] = vClipPos0.z * fLightPosInv0;
	LightDepthValue[1] = vClipPos1.z * fLightPosInv1;
	LightDepthValue[2] = vClipPos2.z * fLightPosInv2;

	int iIndex = 3;

	if((saturate(fShadowCoord[0].x) == fShadowCoord[0].x) && (saturate(fShadowCoord[0].y) == fShadowCoord[0].y) && (fDepthTest > (1.f - (g_CascadeDepths.x * fPosInv))))
		iIndex = 0;
	else if((saturate(fShadowCoord[1].x) == fShadowCoord[1].x) && (saturate(fShadowCoord[1].y) == fShadowCoord[1].y) && (fDepthTest > (1.f - (g_CascadeDepths.y * fPosInv))))
		iIndex = 1;
	else if((saturate(fShadowCoord[2].x) == fShadowCoord[2].x) && (saturate(fShadowCoord[2].y) == fShadowCoord[2].y) && (fDepthTest > (1.f - (g_CascadeDepths.z * fPosInv))))
		iIndex = 2;

	if(iIndex != 3)
	{
		float fDepthVal = 0.f;

		if(iIndex == 0)
			fDepthVal = tex2D(Cascaded_NearSampler, fShadowCoord[iIndex]).r;
		else if(iIndex == 1)
			fDepthVal = tex2D(Cascaded_MidSampler, fShadowCoord[iIndex]).r;
		else if(iIndex == 2)
			fDepthVal = tex2D(Cascaded_FarSampler, fShadowCoord[iIndex]).r;

		if((LightDepthValue[iIndex] - fShadowBais) < fDepthVal)
		{
			fLightIntensity = saturate(dot(vNormal, vLightDir));

			if(fLightIntensity > 0.f)
			{
				vShadowColor = float4(1.f, 1.f, 1.f, 1.f);
			}
		}
	}
	else 
	{
		fLightIntensity = saturate(dot(vNormal, vLightDir));

		if(fLightIntensity > 0.f)
		{
			vShadowColor = float4(1.f, 1.f, 1.f, 1.f);
		}
	}

	float4 vReturnColor = float4(0.f, 0.f, 0.f, 0.f);

	/*
	if(iIndex == 0)
		vReturnColor = float4(1.f, 0.f, 0.f, 1.f) * vColor * vShadowColor;
	else if(iIndex == 1)
		vReturnColor = float4(0.f, 1.f, 0.f, 1.f) * vColor * vShadowColor;
	else if(iIndex == 2)
		vReturnColor = float4(0.f, 0.f, 1.f, 1.f) * vColor * vShadowColor;
	*/
	
	vReturnColor = vColor * vShadowColor;

	return vReturnColor;
}

////////////////////////////////////////////////////////////////////////// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}

	pass Pass1
	{
		alphablendenable = false;
		// srcblend = srcalpha;
		// destblend = invsrcalpha;
		zenable = true;
		zwriteenable = true;

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

	pass Pass3
	{
		alphablendenable = false;
		//srcblend = srcalpha;
		//destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass3_VS_MAIN();
		PixelShader = compile ps_3_0 Pass3_PS_MAIN();
	}
};