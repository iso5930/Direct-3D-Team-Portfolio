float4 g_vColor;

float4x4 g_mWorld;

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
};

Pass0_VS_OUTPUT Pass0_VS_MAIN(Pass0_VS_INPUT Input)
{
	Pass0_VS_OUTPUT Output;

	Output.vPosition = mul(Input.vPosition, g_mWorld);
	Output.vTexUV = Input.vTexUV;

	return Output;
}

struct Pass0_PS_INPUT
{
	float2 vTexUV : TEXCOORD0;
};

struct Pass0_PS_OUTPUT
{
	float4 vColor : COLOR0;
};

Pass0_PS_OUTPUT Pass0_PS_MAIN(Pass0_PS_INPUT Input)
{
	Pass0_PS_OUTPUT Output;

	Output.vColor = tex2D(BaseSampler, Input.vTexUV);
	Output.vColor *= g_vColor;

	return Output;
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

		VertexShader = compile vs_3_0 Pass0_VS_MAIN();
		PixelShader = compile ps_3_0 Pass0_PS_MAIN();
	}
};