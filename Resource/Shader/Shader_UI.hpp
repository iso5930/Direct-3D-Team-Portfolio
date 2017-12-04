float g_fFar;

float4 g_vColor;

float4x4 g_mWorld;
float4x4 g_mViewProj;

texture g_NormalDepthTexture;
sampler NormalDepthSampler = sampler_state
{
	texture	= g_NormalDepthTexture;
};

texture	g_BaseTexture;
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
	minfilter = linear;
	magfilter = linear;
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

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vPosition = mul(Output.vPosition, g_mViewProj);
	Output.vTexUV = Input.vTexUV;
	Output.vClipPosition = Output.vPosition;

	return Output;
}

struct Pass0_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
	float4 vClipPosition : TEXCOORD1;
};

float4 Pass0_PS_MAIN(Pass0_PS_INPUT Input) : COLOR0
{
	// ScreenPos
	float2 vScreenPos = Input.vClipPosition.xy / Input.vClipPosition.w;

	// DepthUV
	float2 vDepthUV = vScreenPos * float2(0.5, -0.5f) + float2(0.5, 0.5f);

	if(tex2D(NormalDepthSampler, vDepthUV).w < Input.vClipPosition.z / g_fFar)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);

	return tex2D(BaseSampler, Input.vTexUV);
}

////////////////////////////////////////////////////////////////////////// Pass1
struct Pass1_VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct Pass1_VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

Pass1_VS_OUTPUT Pass1_VS_MAIN(Pass1_VS_INPUT Input)
{
	Pass1_VS_OUTPUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass1_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
};

float4 Pass1_PS_MAIN(Pass1_PS_INPUT Input) : COLOR0
{
	float4 vColor;

	if(Input.vTexUV.x < 0.01f || Input.vTexUV.x > 0.99f || Input.vTexUV.y < 0.01f || Input.vTexUV.y > 0.99f)
	{
		vColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		vColor = tex2D(BaseSampler, Input.vTexUV);
		vColor *= g_vColor;
	}

	return vColor;
}

////////////////////////////////////////////////////////////////////////// Tech
technique Tech0
{
	pass Pass0
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;
		cullmode = none;

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}

	pass Pass1
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;
		zenable = false;
		zwriteenable = false;

		alphatestenable = false;
		// alphafunc = greater;
		// alpharef = 0x00000080;
		cullmode = ccw;

		VertexShader = compile vs_3_0 Pass1_VS_MAIN();
		PixelShader = compile ps_3_0 Pass1_PS_MAIN();
	}
};