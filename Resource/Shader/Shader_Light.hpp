float4 g_vLightDir;
float4 g_vLightPos;
float g_fRange;

float4 g_vLightDiffuse;
float4 g_vLightAmbient;
float4 g_vLightSpecular;

float g_fPower = 10.0f;

float4 g_vCameraPos;
float4 g_vViewRightTop;

float4x4 g_mWorld;
float4x4 g_mViewProj;
float4x4 g_mInvView;

float4x4 g_matWorld;
float4x4 g_matViewProj;

float4x4 g_matInvViewProj;

texture g_NormalTexture;
sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
};

texture g_SpecularTexture;
sampler SpecularSampler = sampler_state
{
	texture = g_SpecularTexture;
};

////////////////////////////////////////////////////////////////////////// Pass0
struct Pass0_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass0_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	Output.vPosition = Input.vPosition;
	Output.vTexUV = Input.vTexUV;
	Output.vClipPosition = Input.vPosition;

	return Output;
}

struct Pass0_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

struct Pass0_PS_OUTPUT
{
	float4 vShade : COLOR0;
	float4 vSpecularAcc : COLOR1;
};

Pass0_PS_OUTPUT Pass0_PS_MAIN(Pass0_PS_INPUT Input)
{
	Pass0_PS_OUTPUT Output;

	// Normal
	float4 vNormal = tex2D(NormalSampler, Input.vTexUV);

	// Depth
	float fDepth = vNormal.w;

	// Normal
	vNormal = float4(vNormal.xyz * 2.0f - 1.0f, 0.0f);

	// Shade
	Output.vShade = saturate(dot(-g_vLightDir, vNormal));
	Output.vShade = Output.vShade * g_vLightDiffuse + g_vLightAmbient;

	// DepthUV
	float2 vDepthUV = Input.vClipPosition.xy * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);

	// Position
	float4 vPosition = mul(float4(vViewRay * fDepth, 1.0f), g_mInvView);

	// Look
	float4 vLook = normalize(vPosition - g_vCameraPos);

	// Reflect
	float4 vReflect = normalize(reflect(g_vLightDir, vNormal));

	// SpecularAcc
	Output.vSpecularAcc = pow(saturate(dot(-vLook, vReflect)), g_fPower) * g_vLightSpecular * tex2D(SpecularSampler, Input.vTexUV);

	return Output;
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_INPUT
{
	float4 vPosition : POSITION;
};

struct Pass1_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float4 vClipPosition : TEXCOORD1;
};

Pass1_VS_OUTPUT Pass1_VS_MAIN(Pass1_VS_INPUT Input)
{
	Pass1_VS_OUTPUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass1_PS_INPUT
{
	float4 vClipPosition : TEXCOORD1;
};

struct Pass1_PS_OUTPUT
{
	float4 vShade : COLOR0;
	float4 vSpecularAcc : COLOR1;
};

Pass1_PS_OUTPUT Pass1_PS_MAIN(Pass1_PS_INPUT Input)
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);

	// Normal
	float4 vNormal = tex2D(NormalSampler, vDepthUV);

	// ScreenDepth
	float fSceneDepth = vNormal.w;

	// ViewRay
	float3 vViewRay = float3(lerp(-g_vViewRightTop.xy, g_vViewRightTop.xy, vDepthUV).xy, g_vViewRightTop.z);
	
	// ViewPos
	float4 vViewPos = float4(vViewRay * fSceneDepth, 1.0f);

	// To World
	float4 vWorldPos = mul(vViewPos, g_mInvView);

	// To Local
	float4 vLocalPos = vWorldPos - g_vLightPos;

	// Dist
	float fDist = length(vLocalPos);
	clip(g_fRange - fDist);

	// Output
	Pass1_PS_OUTPUT Output;

	// Normal
	vNormal = float4(vNormal.xyz * 2.0f - 1.0f, 0.0f);

	// Att
	float fAtt = saturate((g_fRange - fDist) / g_fRange);

	// Normalize
	vLocalPos = normalize(vLocalPos);

	// Shade
	Output.vShade = saturate(dot(-vLocalPos, vNormal)) * fAtt;
	Output.vShade = Output.vShade * g_vLightDiffuse;// + g_vLightAmbient;

	// Look
	float4 vLook = normalize(vWorldPos - g_vCameraPos);

	// Reflect
	float4 vReflect = reflect(vLocalPos, vLook);

	// SpecularAcc
	Output.vSpecularAcc = pow(saturate(dot(-vLook, vReflect)), g_fPower) * g_vLightSpecular * tex2D(SpecularSampler, vDepthUV) * fAtt;

	return Output;
}

////////////////////////////////////////////////////////////////////////// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;
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
		alphablendenable = true;
		srcblend = one;
		destblend = one;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}
};